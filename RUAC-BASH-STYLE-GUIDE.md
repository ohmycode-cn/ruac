# RUAC Bash 风格指南

## 1. 文件注释头

- 每个 Bash 脚本文件的开头必须包含一个注释头。
- 模板注释头如下：

```Bash
#!/bin/bash
# *********************************************************************************************
# | Limit Line Length: Suggest wrapping in column 96 and forcing wrapping in column 120.
# | Author: .author
# | Date: YYYY-MM-DD HH:MM:SS
# | Bash: Recommended usage bash version 5.0 or higher
# | Bash Style Guide: RUAC-BASH-STYLE-GUIDE.md
# | Bash Style Inherited From: https://github.com/ohmycode-cn/codestyle/OMC-BASH-STYLE-GUIDE.md
# | Description:
# | Usage:
# *********************************************************************************************
```

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

## 2. 全局变量与全局只读变量

- 不建议在 Bash 脚本中使用全局变量，应当使用只读变量。同时应当减少对只读变量的使用。
- 全局变量与只读变量使用无后缀 + 全大写字母 + 下划线分隔单词的方式命名。
- 对于只读变量，应当先定义为全局变量，再定义为只读变量。当变量值是静态值时，应当直接定义为只读变量。

```Bash
# Define global only read variable.
VAR_NAME=value; readonly VAR_NAME
# Define static value only read variable.
readonly VAR_NAME=value
# Define global variable.
VAR_NAME=value
```

## 3. 局部变量与局部只读变量

- 局部变量与局部只读变量使用无后缀 + 全小写字母 + 下划线分隔单词的方式命名。
- 局部变量应当使用 `local` 限定符，避免污染脚本作用域。
- 对于局部只读变量，应当使用 `local -r` 限定符。

```Bash
# Define local only read variable.
local -r var_name=value
# Define local variable.
local var_name=value
```

## 4. 函数

- 函数名称应当使用全小写字母 + 下划线分隔单词的方式命名。
- 函数定义不会遵循 POSIX 标准。
- 函数定义应当使用 `function` 限定符。

```Bash
# Define function.
function function_name() {
    # Function body.
}
```

- 当函数的参数只有一个时，应当使用 `${1}` 而不是 `${@}`。
- 变量的引用应当使用更安全的 `${var_name}` 或者 `"${var_name}"`，避免使用 `$var_name`。
- 当引用的变量值是数字时，应当使用 `${var_name}` 而不是 `"${var_name}"`。
- 其余情况，应当使用 `"${var_name}"`。

```Bash
# Define function.
function function_name() {
    local var_name="${1}"
    local -r var_name_1="${var_name}"
    local -r number=10
    local number_1=${number}
}
function_name "${1}" # 函数调用示例
```
