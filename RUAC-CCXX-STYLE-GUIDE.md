# RUAC C/C++ 编码规范

### `禁止在C文件中使用C++代码`

## C++ 前言

- C/CXX 文件注释必须仅使用专业英语术语。
- 注释内容必须基于当前文件中的实际声明或实现。

## C/C++ 注释指南

- 文件头注释：
  - 当存在头文件时：文件头的“文件功能描述”部分必须包含文件的功能描述。
  - 当存在源文件时：仅当源文件包含与头文件声明显著不同的实现时才需要注释；否则，留空注释。
  - 正确的注释示例：
```cpp
/**
 * ......
 * 文件功能描述：
 * 内容 ...
 */
```
- 在头文件中：仅注释类本身；不要注释内部内容（例如，成员变量、成员函数）。
- 在源文件中：注释类、函数、全局变量和常量。

- 不符合 RUAC C++ 编码规范的代码将被拒绝。

## C++ 目录结构

- `src/cxx/` 是 C++ 源文件和头文件的顶级目录。
- `include/` 是头文件的根目录，位于顶级目录下。
- `src/` 是源文件的根目录，位于顶级目录下。

## C++ 命名空间

- 命名空间必须全部小写。不接受驼峰命名法（例如，`namespace targetName` 或 `namespace TargetName`）。

- 有效示例：

```cpp
namespace ruac::target {

} // namespace ruac::target

namespace ruac::target_name1 {

} // namespace ruac::target_name1
```

- 创建新文件时，使用 `mkf.sh` 脚本处理注释内容、命名空间和类初始化。
- 手动创建文件时，内容必须与 `mkf.sh` 的输出匹配。
- 所有命名空间都在根 `ruac` 命名空间下（`ruac_main.cpp` 除外）。
- 位于 `src/cxx/` 顶级目录下的文件使用命名空间 `ruac`：

```cpp
// FILE: src/cxx/include/target.hpp
//       src/cxx/src/target.cpp
namespace ruac {

} // namespace ruac
```

- 位于子目录下的文件使用命名空间 `ruac::dirname`：

```cpp
// FILE: src/cxx/include/dirname/target.hpp
//       src/cxx/src/dirname/target.cpp
namespace ruac::dirname {

} // namespace ruac::dirname
```

## C++ 类 / 枚举 / 联合体 / 结构体

- 类名必须以大写字母开头。允许使用驼峰命名法。
- 核心模块有一个例外，以保持命名一致性。

- 有效示例：

```cpp
class Target {

};

enum class TargetType {

};

union TargetUnion {

};

struct TargetStruct {

};
```

- 枚举必须使用 `enum class` 定义。不接受具有隐式类型转换的裸枚举。枚举值必须全部大写。
- 每个命名空间应暴露不超过9个类。标准做法是每个命名空间1个类。

## C++ 成员变量和常量

- 成员变量：`m_member_name`
- 成员常量：`M_MEMBER_NAME`

## C++ 非成员变量和常量

- 局部变量：`var_name`，全部小写，下划线分隔。
- 全局变量：`g_var_name`，前缀 `g_`，下划线分隔（不推荐）。
- 局部常量：`VAR_NAME`，全部大写，下划线分隔。
- 全局常量：`G_VAR_NAME`，前缀 `G_`，下划线分隔（仅在关键场景中使用）。

## C++ 参数命名

- 参数名必须全部小写，下划线分隔，并以结尾下划线 `_` 结尾。示例：`param_name_`。

## C++ 函数

- 函数返回格式：

```cpp
// void 使用前置返回类型
void functionName() {}

// 其他类型使用后置返回类型（特别是当返回类型依赖于参数时）
auto functionName() -> return_type {}
```

## C++ 函数命名

- 函数名必须以小写字母开头。后续单词必须以大写字母开头（驼峰命名法）。

- 有效示例：

```cpp
auto example() -> return_type {}
auto functionName() -> return_type {}
```

## C++ 缩写名称

- 当名称过长时，建议使用缩写。全名应记录在文档中。

## C++ 隐藏实现细节

- 使用匿名命名空间或 `static` 隐藏实现细节。

```cpp
namespace {

}

static auto functionName() -> return_type {}
```

# C 编码规范

## C 前言

- 不符合 RUAC C 编码规范的代码将被拒绝。
- C 代码必须针对 C23（ISO/IEC 9899:2024）编写。
- 优先使用 C23 特性，而非传统宏和遗留模式，以提高类型安全性和可读性。

## C 目录结构

- `src/cxx/` 是 C/C++ 源文件和头文件的顶级目录。
- `include/` 是头文件的根目录，位于顶级目录下。
- `src/` 是源文件的根目录，位于顶级目录下。
- 头文件扩展名：`.h`。源文件扩展名：`.c`。
- 所有 C 文件必须以 `ruac_c_` 为前缀：`ruac_c_<module>.h` / `ruac_c_<module>.c`。

## C 注释指南

- 文件头的“文件功能描述”必须基于当前文件中的实际声明或实现。
  - 对于源文件，除非存在与头文件显著不同的实现，否则“文件功能描述”部分通常不需要注释。
- 头文件：存在时注释结构体/枚举/联合体类型；不要注释其内部成员。
- 源文件：注释函数、全局变量和常量。
- 注释必须使用专业英语术语。不接受其他语言以避免字符编码问题。
- 推荐使用 Doxygen 风格注释：

```c
/**
 * @brief 函数简要描述。
 *
 * 需要时的详细描述。
 *
 * @param c_param_name_ 参数描述。
 * @return 返回值描述。
 */
```

## C 模块前缀

- C 没有命名空间。使用模块前缀来隔离跨模块的标识符。
- 模块前缀必须全部小写，下划线分隔。
- 所有公共函数和常量必须带有模块前缀：`c_<module>_`。
- 所有结构体类型必须带有 `C_` 前缀：`C_<Module><Name>`。

- 有效示例：

```c
// FILE: src/cxx/include/ruac_c_target.h
//       src/cxx/src/ruac_c_target.c
#ifndef RUAC_C_TARGET_H_
#define RUAC_C_TARGET_H_

typedef struct C_Target {
    int m_id;
} C_Target;

int c_target_init(C_Target *target_);
void c_target_destroy(C_Target *target_);

#endif // RUAC_C_TARGET_H_
```

- 位于 `src/cxx/` 顶级目录下的文件使用前缀 `ruac_c_`：

```c
// FILE: src/cxx/include/ruac_c_target.h
//       src/cxx/src/ruac_c_target.c
int c_target_func(void);
```

- 位于子目录下的文件使用前缀 `ruac_c_<dirname>_`：

```c
// FILE: src/cxx/include/ruac_c_dirname_target.h
//       src/cxx/src/ruac_c_dirname_target.c
int c_dirname_target_func(void);
```

## C 头文件保护宏

- 所有头文件必须使用 `#define` 保护宏以防止多重包含。
- 保护宏格式：`RUAC_C_<PATH>_<FILE>_H_`，全部大写，下划线分隔。
- `#pragma once` 可以在 C23 中作为补充使用，但 `#define` 保护宏是强制性的。

- 有效示例：

```c
// FILE: src/cxx/include/ruac_c_dirname_target.h
#ifndef RUAC_C_DIRNAME_TARGET_H_
#define RUAC_C_DIRNAME_TARGET_H_

// ... 声明 ...

#endif // RUAC_C_DIRNAME_TARGET_H_
```

## C 包含顺序

- 包含必须遵循此顺序，各组之间用空行分隔：
  1. 对应的头文件（例如，`foo.c` 包含 `foo.h`）
  2. C 标准库头文件（例如，`<stdio.h>`、`<stdlib.h>`、`<string.h>`）
  3. 系统头文件（例如，`<unistd.h>`、`<sys/types.h>`）
  4. 第三方库头文件
  5. 项目头文件

- 在每组内，头文件必须按字母顺序排序。

```c
#include "ruac_c_target.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "ruac_c_other_module.h"
```

## C 类型定义（结构体/枚举/联合体）

- 使用 `typedef` 为结构体、枚举和联合体创建类型别名。
- 结构体类型名必须以 `C_` 为前缀，允许使用驼峰命名法。
- 枚举/联合体类型名必须以大写字母开头，允许使用驼峰命名法。
- `typedef` 必须与 `struct`/`enum`/`union` 定义放在一起。

- 有效示例：

```c
typedef struct C_Target {
    int m_member;
} C_Target;

typedef enum TargetType {
    TARGET_TYPE_NONE = 0,
    TARGET_TYPE_A,
    TARGET_TYPE_B,
    TARGET_TYPE_COUNT,
} TargetType;

typedef union TargetData {
    int m_int_val;
    float m_float_val;
} TargetData;
```

- 枚举值必须全部大写，下划线分隔，并带有类型前缀以避免命名冲突。
- 枚举应显式指定底层值类型（C23 特性）：

```c
typedef enum TargetType : int {
    TARGET_TYPE_NONE = 0,
    TARGET_TYPE_A = 1,
    TARGET_TYPE_B = 2,
} TargetType;
```

- 匿名结构体/联合体仅允许在类型定义内使用（C11+）：

```c
typedef struct C_Target {
    union {
        int m_int_val;
        float m_float_val;
    }; // 匿名联合体，直接访问 m_int_val / m_float_val
} C_Target;
```

## C 成员变量和常量

- 成员变量：`m_member_name`，前缀 `m_`，下划线分隔。
- 成员常量：`M_MEMBER_NAME`，前缀 `M_`，全部大写，下划线分隔。

```c
typedef struct C_Target {
    int m_count;
    const int M_MAX_COUNT;
    char m_name[64];
} C_Target;
```

## C 非成员变量和常量

- 局部变量：`c_var_name`，前缀 `c_`，全部小写，下划线分隔。
- 局部常量：`C_VAR_NAME`，前缀 `C_`，全部大写，下划线分隔。
- **禁止使用全局变量。**
- 全局常量应最小化，仅在关键场景中使用，例如编译时配置值。
- 优先使用 `constexpr` 而非 `#define` 定义常量（C23 特性）：

```c
// 推荐：C23 constexpr
constexpr int C_MAX_BUFFER_SIZE = 1024;

// 传统（仍允许，但推荐使用 constexpr）
#define C_MAX_BUFFER_SIZE 1024
```

## C 参数命名

- 参数名必须全部小写，下划线分隔，以 `c_` 为前缀，并以结尾下划线 `_` 结尾。示例：`c_param_name_`。

```c
int c_target_process(const char *c_input_, size_t c_length_, char *c_output_);
```

## C 函数

- 函数必须使用原型声明。禁止使用 K&R 风格声明。
- 返回类型和函数名必须在同一行。

```c
// 正确
int c_target_init(void);
void c_target_process(const char *c_data_, size_t c_len_);

// 错误：K&R 风格（已弃用）
int c_target_init();
```

- `void` 参数必须显式声明：

```c
// 正确
int c_target_init(void);

// 错误：空括号表示未指定参数，而非无参数
int c_target_init();
```

## C 函数命名

- 函数名必须全部小写，下划线分隔（蛇形命名法）。
- 函数名必须带有模块前缀：`c_<module>_<name>`。

- 有效示例：

```c
int c_target_init(void);
void c_target_destroy(void);
int c_target_compare(const C_Target *c_a_, const C_Target *c_b_);
```

## C 缩写名称

- 当名称过长时，建议使用缩写。全名应记录在文档中。

```c
// URI：统一资源标识符
int c_uri_parse(const char *c_uri_, C_Uri *c_result_);
```

## C 隐藏实现细节

- 使用 `static` 限制函数和局部常量仅在当前文件中可见。
- 不要在头文件中声明非公共符号。
- 禁止使用全局变量。要在函数之间共享状态，请通过参数传递或将其封装在结构体中。

```c
// c_target.c
static int c_internal_helper(void) {
    return 0;
}
```

## C23 特性使用

### nullptr

- 使用 `nullptr` 代替 `NULL` 和 `0` 表示空指针（C23 特性）。

```c
// 正确
char *c_ptr = nullptr;
if (c_ptr == nullptr) { ... }

// 错误：传统 NULL
char *c_ptr = NULL;
```

### constexpr

- 使用 `constexpr` 定义编译时常量（C23 特性）。
- 局部常量使用 `C_` 前缀：

```c
constexpr size_t C_MAX_NAME_LEN = 64;
constexpr double C_PI = 3.14159265358979323846;
```

### typeof / auto

- 使用 `typeof` 或 `auto` 简化复杂类型声明（C23 特性）。

```c
// typeof 获取表达式的类型
int c_x = 42;
typeof(c_x) c_y = c_x;

// auto 推导类型
auto c_result = c_target_compute(c_input_);
```

### static_assert

- 使用 `static_assert` 代替编译时断言宏（C23 特性）。

```c
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
static_assert(alignof(C_Target) <= 64, "C_Target alignment exceeds cache line");
```

### 属性

- 使用 C23 标准属性代替编译器扩展：

```c
// 返回值不能忽略
[[nodiscard]] int c_target_init(void);

// 标记未使用的参数
void c_target_callback([[maybe_unused]] void *c_ctx_);

// 标记已弃用的接口
[[deprecated("Use c_target_new() instead")]]
int c_target_create(void);
```

### 泛型选择（_Generic）

- 使用 `_Generic` 实现类型安全的泛型宏（C11+，在 C23 中增强）：

```c
#define c_print(c_val_) _Generic((c_val_), \
    int:     c_print_int,                   \
    float:   c_print_float,                 \
    char *:  c_print_str,                   \
    default: c_print_unknown                \
)(c_val_)
```

## C 内存管理

- 必须检查 `malloc`/`calloc`/`realloc` 的返回值。
- 优先使用 `calloc` 将内存初始化为零，避免未初始化内存问题。
- 释放立即将指针设置为 `nullptr`。

```c
C_Target *c_target = calloc(1, sizeof(C_Target));
if (c_target == nullptr) {
    return -1;
}

// 使用完毕
free(c_target);
c_target = nullptr;
```

- 使用 C23 `typeof` 简化类型安全的内存分配宏：

```c
#define RUAC_ALLOC(c_type_) ((c_type_ *)calloc(1, sizeof(c_type_)))
#define RUAC_ALLOC_ARRAY(c_type_, c_count_) ((c_type_ *)calloc(c_count_, sizeof(c_type_)))
```

## C 错误处理

- 函数返回 `int` 作为错误代码：`0` 表示成功，负值表示错误。
- 输出参数通过指针传递，放在参数列表末尾。

```c
int c_target_parse(const char *c_input_, C_Target *c_output_);
```

- 使用 `goto` 模式进行资源清理（地道的 C 风格）：

```c
int c_target_process(const char *c_input_, C_Result *c_result_)
{
    int c_ret = 0;
    C_Buffer *c_buf = nullptr;
    C_Target *c_target = nullptr;

    c_buf = RUAC_ALLOC(C_Buffer);
    if (c_buf == nullptr) {
        c_ret = -1;
        goto cleanup;
    }

    c_target = RUAC_ALLOC(C_Target);
    if (c_target == nullptr) {
        c_ret = -1;
        goto cleanup;
    }

    // ... 处理 ...

cleanup:
    free(c_target);
    free(c_buf);
    return c_ret;
}
```

## C 预处理器

- 优先使用 C23 特性（`constexpr`、`static_assert`、`typeof`）而非宏。
- 宏仅应在以下场景中使用：
  - 头文件保护宏
  - 条件编译
  - 泛型宏（`_Generic`）
  - 日志/调试宏
- 宏参数必须用括号括起来。多语句宏必须使用 `do { ... } while (0)` 模式：

```c
#define RUAC_C_SWAP(c_a_, c_b_)  \
    do {                         \
        typeof(c_a_) c_t_ = c_a_;\
        c_a_ = c_b_;             \
        c_b_ = c_t_;             \
    } while (0)
```

- 具有副作用的宏参数必须用括号括起来：

```c
// 正确
#define RUAC_C_MAX(c_a_, c_b_) ((c_a_) > (c_b_) ? (c_a_) : (c_b_))

// 错误：可能导致副作用
#define RUAC_C_MAX(c_a_, c_b_) c_a_ > c_b_ ? c_a_ : c_b_
```

## C 格式化

### 缩进和空白

- 使用 2 个空格缩进。不允许使用制表符。
- 行宽限制：80 列。
- 指针 `*` 附加到类型名：

```c
char *c_name = nullptr;
const C_Target *c_target = nullptr;
```

### 大括号

- 函数定义的大括号放在单独的行上：

```c
int c_target_init(void)
{
    return 0;
}
```

- 控制语句的大括号使用 K&R 风格（左大括号在同一行）：

```c
if (c_condition) {
    c_do_something();
} else {
    c_do_other();
}

for (int c_i = 0; c_i < c_count; ++c_i) {
    c_process(c_i);
}

switch (c_type) {
    case TARGET_TYPE_A:
        c_handle_a();
        break;
    case TARGET_TYPE_B:
        c_handle_b();
        break;
    default:
        break;
}
```

### 结构体/枚举定义

- 成员缩进并对齐。大括号风格与函数定义匹配：

```c
typedef struct C_Target {
    int m_id;
    char m_name[64];
    TargetType m_type;
} C_Target;

typedef enum TargetType : int {
    TARGET_TYPE_NONE = 0,
    TARGET_TYPE_A = 1,
    TARGET_TYPE_B = 2,
} TargetType;
```

### 空行和垂直空白

- 函数定义之间空一行。
- 使用空行分隔逻辑相关的代码块。
- 不要在函数开头或结尾添加不必要的空行。
- 不要在行尾添加尾随空白。

## C 文件组织

### 头文件（.h）

- 仅包含类型声明、函数原型、宏定义和 `constexpr` 常量。
- 不包含函数实现（除非是非常短的 `static inline` 函数）。
- `static inline` 函数不得超过 10 行：

```c
// 允许在头文件中使用的短内联函数
static inline int c_target_is_valid(const C_Target *c_target_)
{
    return c_target_ != nullptr && c_target_->m_id > 0;
}
```

### 源文件（.c）

- 包含对应的头文件和所有依赖项。
- 禁止使用全局变量。文件作用域的 `static` 函数仅在当前文件中可见。
- 公共函数实现必须遵循头文件中的声明顺序。