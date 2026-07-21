# RUAC Project Rules


## 1. Simple Record File

- Note: For the author field, you should write your username and account into the `.author.json` file in the current directory.
- Operation date format is `YYYY-MM-DD-HH-MM`.
- Template:
```json
{
    "all file author": "ohmycode-cn(ohcode@163.com)", // Primary author.
    "repo master": "ohmycode-cn(ohcode@163.com)"      // Repository owner.
}
```
- Example:
- If you only wish to provide the primary author and repository owner, you can just write the primary author and address.
```json
{
    "all file author": "ohmycode-cn(ohcode@163.com)", // Primary author.
    "repo master": "ohmycode-cn(ohcode@163.com)",     // Repository owner.
    "valid_email@example.com.author_name": { "files operated by this author":{ "operation date": ["start line", "end line"] } },
    "vailed_email@example.com.author_name": {
        "example.1.txt":{
            "date time": ["start line", "end line"]
        },
        "example.2.txt":{
            "date time": ["start line", "end line"]
        },
        "example.3.txt": 0,                   // 0 - omit specific operation date for file
        "d.directory name": 0                 // 0 - omit specific operation date for directory (prefix `d.` before filename indicates directory)
    },
    "example@xxx.com.author_name": 1          // 1 - only willing to provide email address and author name
}
```
