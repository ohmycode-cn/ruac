# RUAC 项目规则


## 1.简易记录文件 

- 注意：对于作者字段，应当将自己的用户名与账号写入当前目录的 `.author.json` 文件中。
- 操作日期格式为 `YYYY-MM-DD-HH-MM`。
- 模板：
```json
{
    "all file author": "ohmycode-cn(ohcode@163.com)", // 主要作者。
    "repo master": "ohmycode-cn(ohcode@163.com)"      // 仓库作者。
}
```
- 例如：
- 当然如果你只希望提供主要作者与仓库作者，也可以只写供主要作者与地址。
```json
{
    "all file author": "ohmycode-cn(ohcode@163.com)", // 主要作者。
    "repo master": "ohmycode-cn(ohcode@163.com)",     // 仓库作者。
    "可用邮件地址.作者名称": { "该作者操作的文件":{ "操作日期": ["操作开始行", "操作结束行"] } },
    "vailed_email@example.com.author_name": {
        "example.1.txt":{
            "date time": ["start line", "end line"]
        },
        "example.2.txt":{
            "date time": ["start line", "end line"]
        }
        "example.3.txt": 0                    // 0 - 省略文件具体操作日期 
        "d.directory name": 0                 // 0 - 省略目录具体操作日期（在文件名前添加前缀 `d.` 表示目录）
    },
    "example@xxx.com.author_name": 1          // 1 - 只愿意提供邮件地址与作者名称
}
```