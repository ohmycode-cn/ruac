"""Thread-safe, cross-platform system information fetcher.

Supports CPU, GPU, memory, and disk metrics on Windows, Linux, and macOS.
Requires: pip install psutil gputil (optional for GPU)
"""

import platform
import subprocess
import threading
from dataclasses import dataclass, field
from typing import Dict, List, Optional

import psutil


@dataclass(frozen=True)
class CpuInfo:
    physical_cores: int
    logical_cores: int
    max_freq_mhz: float
    current_freq_mhz: float
    usage_percent: float
    per_core_percent: List[float]
    model: str


@dataclass(frozen=True)
class GpuInfo:
    index: int
    name: str
    load_percent: float
    memory_total_mb: float
    memory_used_mb: float
    memory_free_mb: float
    temperature_c: Optional[float]


@dataclass(frozen=True)
class MemoryInfo:
    total_gb: float
    available_gb: float
    used_gb: float
    percent: float
    swap_total_gb: float
    swap_used_gb: float
    swap_percent: float


@dataclass(frozen=True)
class DiskPartition:
    device: str
    mountpoint: str
    fstype: str
    total_gb: float
    used_gb: float
    free_gb: float
    percent: float


@dataclass(frozen=True)
class SystemInfo:
    cpu: CpuInfo
    gpu: List[GpuInfo]
    memory: MemoryInfo
    disks: List[DiskPartition]
    os_name: str
    os_version: str
    hostname: str


_lock = threading.Lock()


def _bytes_to_gb(b: float) -> float:
    return round(b / (1024**3), 2)


def get_cpu_info() -> CpuInfo:
    """Fetch CPU metrics in a thread-safe manner."""
    with _lock:
        freq = psutil.cpu_freq()
        usage = psutil.cpu_percent(interval=0.1, percpu=True)
        return CpuInfo(
            physical_cores=psutil.cpu_count(logical=False) or 0,
            logical_cores=psutil.cpu_count(logical=True) or 0,
            max_freq_mhz=freq.max if freq else 0.0,
            current_freq_mhz=freq.current if freq else 0.0,
            usage_percent=round(sum(usage) / len(usage), 1) if usage else 0.0,
            per_core_percent=usage,
            model=platform.processor() or "Unknown",
        )


def _try_gputil() -> List[GpuInfo]:
    """Attempt GPU detection via GPUtil (NVIDIA only)."""
    try:
        import GPUtil

        gpus = GPUtil.getGPUs()
        return [
            GpuInfo(
                index=g.id,
                name=g.name,
                load_percent=round(g.load * 100, 1),
                memory_total_mb=g.memoryTotal,
                memory_used_mb=g.memoryUsed,
                memory_free_mb=g.memoryFree,
                temperature_c=g.temperature,
            )
            for g in gpus
        ]
    except Exception:
        return []


def _try_nvidia_smi() -> List[GpuInfo]:
    """Fallback: parse nvidia-smi output."""
    try:
        result = subprocess.run(
            [
                "nvidia-smi",
                "--query-gpu=index,name,utilization.gpu,memory.total,memory.used,memory.free,temperature.gpu",
                "--format=csv,noheader,nounits",
            ],
            capture_output=True,
            text=True,
            timeout=5,
        )
        if result.returncode != 0:
            return []
        gpus = []
        for line in result.stdout.strip().splitlines():
            parts = [p.strip() for p in line.split(",")]
            if len(parts) >= 7:
                gpus.append(
                    GpuInfo(
                        index=int(parts[0]),
                        name=parts[1],
                        load_percent=float(parts[2]),
                        memory_total_mb=float(parts[3]),
                        memory_used_mb=float(parts[4]),
                        memory_free_mb=float(parts[5]),
                        temperature_c=float(parts[6]),
                    )
                )
        return gpus
    except Exception:
        return []


def get_gpu_info() -> List[GpuInfo]:
    """Fetch GPU metrics; tries GPUtil first, then nvidia-smi."""
    with _lock:
        gpus = _try_gputil()
        if not gpus:
            gpus = _try_nvidia_smi()
        return gpus


def get_memory_info() -> MemoryInfo:
    """Fetch memory metrics in a thread-safe manner."""
    with _lock:
        vm = psutil.virtual_memory()
        sw = psutil.swap_memory()
        return MemoryInfo(
            total_gb=_bytes_to_gb(vm.total),
            available_gb=_bytes_to_gb(vm.available),
            used_gb=_bytes_to_gb(vm.used),
            percent=vm.percent,
            swap_total_gb=_bytes_to_gb(sw.total),
            swap_used_gb=_bytes_to_gb(sw.used),
            swap_percent=sw.percent,
        )


def get_disk_info() -> List[DiskPartition]:
    """Fetch disk partition metrics in a thread-safe manner."""
    with _lock:
        partitions = []
        for part in psutil.disk_partitions(all=False):
            try:
                usage = psutil.disk_usage(part.mountpoint)
                partitions.append(
                    DiskPartition(
                        device=part.device,
                        mountpoint=part.mountpoint,
                        fstype=part.fstype,
                        total_gb=_bytes_to_gb(usage.total),
                        used_gb=_bytes_to_gb(usage.used),
                        free_gb=_bytes_to_gb(usage.free),
                        percent=usage.percent,
                    )
                )
            except (PermissionError, OSError):
                continue
        return partitions


def get_system_info() -> SystemInfo:
    """Fetch all system information atomically."""
    return SystemInfo(
        cpu=get_cpu_info(),
        gpu=get_gpu_info(),
        memory=get_memory_info(),
        disks=get_disk_info(),
        os_name=platform.system(),
        os_version=platform.version(),
        hostname=platform.node(),
    )


def _build_content_lines(info: SystemInfo) -> List[str]:
    """Build plain content lines from SystemInfo."""
    lines = [
        f"Host: {info.hostname}",
        f"OS:   {info.os_name} {info.os_version}",
        "",
        "[CPU]",
        f"Model:     {info.cpu.model}",
        f"Cores:     {info.cpu.physical_cores}P / {info.cpu.logical_cores}L",
        f"Freq:      {info.cpu.current_freq_mhz:.0f} / {info.cpu.max_freq_mhz:.0f} MHz",
        f"Usage:     {info.cpu.usage_percent}%",
        "",
        "[Memory]",
        f"RAM:       {info.memory.used_gb} / {info.memory.total_gb} GB  ({info.memory.percent}%)",
        f"Swap:      {info.memory.swap_used_gb} / {info.memory.swap_total_gb} GB  ({info.memory.swap_percent}%)",
    ]

    if info.gpu:
        lines.append("")
        lines.append("[GPU]")
        for g in info.gpu:
            lines.append(f"  [{g.index}] {g.name}")
            lines.append(f"      Load:  {g.load_percent}%   Temp: {g.temperature_c} C")
            lines.append(f"      VRAM:  {g.memory_used_mb} / {g.memory_total_mb} MB")

    if info.disks:
        total = sum(d.total_gb for d in info.disks)
        used = sum(d.used_gb for d in info.disks)
        percent = round(used / total * 100, 1) if total else 0.0
        lines.append("")
        lines.append(f"[Disks]  {used} / {total} GB  ({percent}%)")

    return lines


def format_system_info(info: SystemInfo) -> str:
    """Format SystemInfo into a bordered box with dynamic width."""
    # Box-drawing characters
    tl, tr, bl, br = "╔", "╗", "╚", "╝"
    h, v = "═", "║"

    content_lines = _build_content_lines(info)
    max_len = max(len(line) for line in content_lines) if content_lines else 0
    width = max_len + 4  # 2 padding on each side

    top = f"{tl}{h * width}{tr}"
    bottom = f"{bl}{h * width}{br}"

    bordered = [top]
    for line in content_lines:
        padded = f"  {line}{' ' * (max_len - len(line))}  "
        bordered.append(f"{v}{padded}{v}")
    bordered.append(bottom)

    return "\n".join(bordered)


if __name__ == "__main__":
    print(format_system_info(get_system_info()))
