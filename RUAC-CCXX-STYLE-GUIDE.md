# RUAC C/C++ Coding Standards

### `Using C++ code in C files is prohibited`

## Table of Contents

- [C++ Coding Standards](#c-coding-standards)
  - [C++ Foreword](#c-foreword)
  - [C/C++ Comment Guidelines](#cc-comment-guidelines)
  - [C++ Directory Structure](#c-directory-structure)
  - [C++ Namespaces](#c-namespaces)
  - [C++ Classes / Enums / Unions / Structs](#c-classes--enums--unions--structs)
  - [C++ Member Variables and Constants](#c-member-variables-and-constants)
  - [C++ Non-Member Variables and Constants](#c-non-member-variables-and-constants)
  - [C++ Parameter Naming](#c-parameter-naming)
  - [C++ Functions](#c-functions)
  - [C++ Function Naming](#c-function-naming)
  - [C++ Abbreviated Names](#c-abbreviated-names)
  - [C++ Hiding Implementation Details](#c-hiding-implementation-details)
- [C Coding Standards](#c-coding-standards)
  - [C Foreword](#c-foreword-1)
  - [C Directory Structure](#c-directory-structure-1)
  - [C Comment Guidelines](#c-comment-guidelines)
  - [C Module Prefix](#c-module-prefix)
  - [C Header File Guard Macros](#c-header-file-guard-macros)
  - [C Include Order](#c-include-order)
  - [C Type Definitions (Struct/Enum/Union)](#c-type-definitions-structenumunion)
  - [C Member Variables and Constants](#c-member-variables-and-constants-1)
  - [C Non-Member Variables and Constants](#c-non-member-variables-and-constants-1)
  - [C Parameter Naming](#c-parameter-naming-1)
  - [C Functions](#c-functions-1)
  - [C Function Naming](#c-function-naming-1)
  - [C Abbreviated Names](#c-abbreviated-names-1)
  - [C Hiding Implementation Details](#c-hiding-implementation-details-1)
  - [C23 Feature Usage](#c23-feature-usage)
  - [C Memory Management](#c-memory-management)
  - [C Error Handling](#c-error-handling)
  - [C Preprocessor](#c-preprocessor)
  - [C Formatting](#c-formatting)
  - [C File Organization](#c-file-organization)

---

## C++ Coding Standards

## C++ Foreword

- C/CXX file comments must use professional English terminology only.
- Comment content must be based on actual declarations or implementations in the current file.

## C/C++ Comment Guidelines

- File header comments:
  - When a header file exists: the "File Description" section of the file header must contain a description of the file's functionality.
  - When a source file exists: comments are only required when the source file contains implementations significantly different from the header file declarations; otherwise, leave the comment empty.
  - Correct comment example:
```cpp
/**
 * ......
 * File Description:
 * Content ...
 */
```
- In header files: only comment the class itself; do not comment internal contents (e.g., member variables, member functions).
- In source files: comment classes, functions, global variables, and constants.

- Code that does not comply with RUAC C++ coding standards will be rejected.

## C++ Directory Structure

- `src/cxx/` is the top-level directory for C++ source and header files.
- `include/` is the root directory for header files, located under the top-level directory.
- `src/` is the root directory for source files, located under the top-level directory.

## C++ Namespaces

- Namespaces must be all lowercase. CamelCase is not accepted (e.g., `namespace targetName` or `namespace TargetName`).

- Valid examples:

```cpp
namespace ruac::target {

} // namespace ruac::target

namespace ruac::target_name1 {

} // namespace ruac::target_name1
```

- When creating new files, use the `mkf.sh` script to handle comment content, namespace, and class initialization.
- When manually creating files, content must match the output of `mkf.sh`.
- All namespaces are under the root `ruac` namespace (except `ruac_main.cpp`).
- Files located in the `src/cxx/` top-level directory use namespace `ruac`:

```cpp
// FILE: src/cxx/include/target.hpp
//       src/cxx/src/target.cpp
namespace ruac {

} // namespace ruac
```

- Files located in subdirectories use namespace `ruac::dirname`:

```cpp
// FILE: src/cxx/include/dirname/target.hpp
//       src/cxx/src/dirname/target.cpp
namespace ruac::dirname {

} // namespace ruac::dirname
```

## C++ Classes / Enums / Unions / Structs

- Class names must start with an uppercase letter. CamelCase is allowed.
- There is one exception for core modules to maintain naming consistency.

- Valid examples:

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

- Enums must be defined using `enum class`. Bare enums with implicit type conversion are not accepted. Enum values must be all uppercase.
- Each namespace should expose no more than 9 classes. The standard practice is 1 class per namespace.

## C++ Member Variables and Constants

- Member variables: `m_member_name`
- Member constants: `M_MEMBER_NAME`

## C++ Non-Member Variables and Constants

- Local variables: `var_name`, all lowercase, underscore-separated.
- Global variables: `g_var_name`, prefix `g_`, underscore-separated (not recommended).
- Local constants: `VAR_NAME`, all uppercase, underscore-separated.
- Global constants: `G_VAR_NAME`, prefix `G_`, underscore-separated (use only in critical scenarios).

## C++ Parameter Naming

- Parameter names must be all lowercase, underscore-separated, and end with a trailing underscore `_`. Example: `param_name_`.

## C++ Functions

- Function return format:

```cpp
// void uses leading return type
void functionName() {}

// Other types use trailing return type (especially when return type depends on parameters)
auto functionName() -> return_type {}
```

## C++ Function Naming

- Function names must start with a lowercase letter. Subsequent words must start with an uppercase letter (CamelCase).

- Valid examples:

```cpp
auto example() -> return_type {}
auto functionName() -> return_type {}
```

## C++ Abbreviated Names

- When names are too long, abbreviations are recommended. Full names should be documented.

## C++ Hiding Implementation Details

- Use anonymous namespaces or `static` to hide implementation details.

```cpp
namespace {

}

static auto functionName() -> return_type {}
```

# C Coding Standards

## C Foreword

- Code that does not comply with RUAC C coding standards will be rejected.
- C code must be written targeting C23 (ISO/IEC 9899:2024).
- Prefer C23 features over legacy macros and patterns for improved type safety and readability.

## C Directory Structure

- `src/cxx/` is the top-level directory for C/C++ source and header files.
- `include/` is the root directory for header files, located under the top-level directory.
- `src/` is the root directory for source files, located under the top-level directory.
- Header file extension: `.h`. Source file extension: `.c`.
- All C files must be prefixed with `ruac_c_`: `ruac_c_<module>.h` / `ruac_c_<module>.c`.

## C Comment Guidelines

- The "File Description" in the file header must be based on actual declarations or implementations in the current file.
  - For source files, the "File Description" section usually does not need comments unless there are implementations significantly different from the header file.
- Header files: comment struct/enum/union types when present; do not comment their internal members.
- Source files: comment functions, global variables, and constants.
- Comments must use professional English terminology. Other languages are not accepted to avoid character encoding issues.
- Doxygen-style comments are recommended:

```c
/**
 * @brief Brief description of the function.
 *
 * Detailed description when needed.
 *
 * @param c_param_name_ Parameter description.
 * @return Return value description.
 */
```

## C Module Prefix

- C has no namespaces. Use module prefixes to isolate identifiers across modules.
- Module prefixes must be all lowercase, underscore-separated.
- All public functions and constants must have the module prefix: `c_<module>_`.
- All struct types must have the `C_` prefix: `C_<Module><Name>`.

- Valid examples:

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

- Files located in the `src/cxx/` top-level directory use prefix `ruac_c_`:

```c
// FILE: src/cxx/include/ruac_c_target.h
//       src/cxx/src/ruac_c_target.c
int c_target_func(void);
```

- Files located in subdirectories use prefix `ruac_c_<dirname>_`:

```c
// FILE: src/cxx/include/ruac_c_dirname_target.h
//       src/cxx/src/ruac_c_dirname_target.c
int c_dirname_target_func(void);
```

## C Header File Guard Macros

- All header files must use `#define` guard macros to prevent multiple inclusion.
- Guard macro format: `RUAC_C_<PATH>_<FILE>_H_`, all uppercase, underscore-separated.
- `#pragma once` may be used as a supplement in C23, but `#define` guard macros are mandatory.

- Valid examples:

```c
// FILE: src/cxx/include/ruac_c_dirname_target.h
#ifndef RUAC_C_DIRNAME_TARGET_H_
#define RUAC_C_DIRNAME_TARGET_H_

// ... declarations ...

#endif // RUAC_C_DIRNAME_TARGET_H_
```

## C Include Order

- Includes must follow this order, with blank lines separating each group:
  1. Corresponding header file (e.g., `foo.c` includes `foo.h`)
  2. C standard library headers (e.g., `<stdio.h>`, `<stdlib.h>`, `<string.h>`)
  3. System headers (e.g., `<unistd.h>`, `<sys/types.h>`)
  4. Third-party library headers
  5. Project headers

- Within each group, headers must be sorted alphabetically.

```c
#include "ruac_c_target.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "ruac_c_other_module.h"
```

## C Type Definitions (Struct/Enum/Union)

- Use `typedef` to create type aliases for structs, enums, and unions.
- Struct type names must be prefixed with `C_`, CamelCase is allowed.
- Enum/union type names must start with an uppercase letter, CamelCase is allowed.
- `typedef` must be placed together with the `struct`/`enum`/`union` definition.

- Valid examples:

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

- Enum values must be all uppercase, underscore-separated, with a type prefix to avoid naming conflicts.
- Enums should explicitly specify the underlying value type (C23 feature):

```c
typedef enum TargetType : int {
    TARGET_TYPE_NONE = 0,
    TARGET_TYPE_A = 1,
    TARGET_TYPE_B = 2,
} TargetType;
```

- Anonymous structs/unions are only allowed inside type definitions (C11+):

```c
typedef struct C_Target {
    union {
        int m_int_val;
        float m_float_val;
    }; // Anonymous union, direct access to m_int_val / m_float_val
} C_Target;
```

## C Member Variables and Constants

- Member variables: `m_member_name`, prefix `m_`, underscore-separated.
- Member constants: `M_MEMBER_NAME`, prefix `M_`, all uppercase, underscore-separated.

```c
typedef struct C_Target {
    int m_count;
    const int M_MAX_COUNT;
    char m_name[64];
} C_Target;
```

## C Non-Member Variables and Constants

- Local variables: `c_var_name`, prefix `c_`, all lowercase, underscore-separated.
- Local constants: `C_VAR_NAME`, prefix `C_`, all uppercase, underscore-separated.
- **Global variables are prohibited.**
- Global constants should be minimized and used only in critical scenarios, such as compile-time configuration values.
- Prefer `constexpr` over `#define` for defining constants (C23 feature):

```c
// Recommended: C23 constexpr
constexpr int C_MAX_BUFFER_SIZE = 1024;

// Legacy (still allowed, but constexpr is recommended)
#define C_MAX_BUFFER_SIZE 1024
```

## C Parameter Naming

- Parameter names must be all lowercase, underscore-separated, prefixed with `c_`, and end with a trailing underscore `_`. Example: `c_param_name_`.

```c
int c_target_process(const char *c_input_, size_t c_length_, char *c_output_);
```

## C Functions

- Functions must use prototype declarations. K&R-style declarations are prohibited.
- Return type and function name must be on the same line.

```c
// Correct
int c_target_init(void);
void c_target_process(const char *c_data_, size_t c_len_);

// Wrong: K&R style (deprecated)
int c_target_init();
```

- `void` parameters must be explicitly declared:

```c
// Correct
int c_target_init(void);

// Wrong: empty parentheses mean unspecified parameters, not no parameters
int c_target_init();
```

## C Function Naming

- Function names must be all lowercase, underscore-separated (snake_case).
- Function names must have the module prefix: `c_<module>_<name>`.

- Valid examples:

```c
int c_target_init(void);
void c_target_destroy(void);
int c_target_compare(const C_Target *c_a_, const C_Target *c_b_);
```

## C Abbreviated Names

- When names are too long, abbreviations are recommended. Full names should be documented.

```c
// URI: Uniform Resource Identifier
int c_uri_parse(const char *c_uri_, C_Uri *c_result_);
```

## C Hiding Implementation Details

- Use `static` to restrict functions and local constants to the current file only.
- Do not declare non-public symbols in header files.
- Global variables are prohibited. To share state between functions, pass it through parameters or encapsulate it in a struct.

```c
// c_target.c
static int c_internal_helper(void) {
    return 0;
}
```

## C23 Feature Usage

### nullptr

- Use `nullptr` instead of `NULL` and `0` for null pointers (C23 feature).

```c
// Correct
char *c_ptr = nullptr;
if (c_ptr == nullptr) { ... }

// Wrong: legacy NULL
char *c_ptr = NULL;
```

### constexpr

- Use `constexpr` to define compile-time constants (C23 feature).
- Local constants use the `C_` prefix:

```c
constexpr size_t C_MAX_NAME_LEN = 64;
constexpr double C_PI = 3.14159265358979323846;
```

### typeof / auto

- Use `typeof` or `auto` to simplify complex type declarations (C23 feature).

```c
// typeof obtains the type of an expression
int c_x = 42;
typeof(c_x) c_y = c_x;

// auto deduces the type
auto c_result = c_target_compute(c_input_);
```

### static_assert

- Use `static_assert` instead of compile-time assertion macros (C23 feature).

```c
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
static_assert(alignof(C_Target) <= 64, "C_Target alignment exceeds cache line");
```

### Attributes

- Use C23 standard attributes instead of compiler extensions:

```c
// Return value cannot be ignored
[[nodiscard]] int c_target_init(void);

// Mark unused parameter
void c_target_callback([[maybe_unused]] void *c_ctx_);

// Mark deprecated interface
[[deprecated("Use c_target_new() instead")]]
int c_target_create(void);
```

### Generic Selection (_Generic)

- Use `_Generic` to implement type-safe generic macros (C11+, enhanced in C23):

```c
#define c_print(c_val_) _Generic((c_val_), \
    int:     c_print_int,                   \
    float:   c_print_float,                 \
    char *:  c_print_str,                   \
    default: c_print_unknown                \
)(c_val_)
```

## C Memory Management

- Return values of `malloc`/`calloc`/`realloc` must be checked.
- Prefer `calloc` to initialize memory to zero and avoid uninitialized memory issues.
- Set the pointer to `nullptr` immediately after freeing.

```c
C_Target *c_target = calloc(1, sizeof(C_Target));
if (c_target == nullptr) {
    return -1;
}

// Done using
free(c_target);
c_target = nullptr;
```

- Use C23 `typeof` to simplify type-safe memory allocation macros:

```c
#define RUAC_ALLOC(c_type_) ((c_type_ *)calloc(1, sizeof(c_type_)))
#define RUAC_ALLOC_ARRAY(c_type_, c_count_) ((c_type_ *)calloc(c_count_, sizeof(c_type_)))
```

## C Error Handling

- Functions return `int` as error codes: `0` for success, negative values for errors.
- Output parameters are passed via pointers and placed at the end of the parameter list.

```c
int c_target_parse(const char *c_input_, C_Target *c_output_);
```

- Use the `goto` pattern for resource cleanup (idiomatic C style):

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

    // ... processing ...

cleanup:
    free(c_target);
    free(c_buf);
    return c_ret;
}
```

## C Preprocessor

- Prefer C23 features (`constexpr`, `static_assert`, `typeof`) over macros.
- Macros should only be used in the following scenarios:
  - Header file guard macros
  - Conditional compilation
  - Generic macros (`_Generic`)
  - Logging/debugging macros
- Macro parameters must be enclosed in parentheses. Multi-statement macros must use the `do { ... } while (0)` pattern:

```c
#define RUAC_C_SWAP(c_a_, c_b_)  \
    do {                         \
        typeof(c_a_) c_t_ = c_a_;\
        c_a_ = c_b_;             \
        c_b_ = c_t_;             \
    } while (0)
```

- Macro parameters with side effects must be enclosed in parentheses:

```c
// Correct
#define RUAC_C_MAX(c_a_, c_b_) ((c_a_) > (c_b_) ? (c_a_) : (c_b_))

// Wrong: may cause side effects
#define RUAC_C_MAX(c_a_, c_b_) c_a_ > c_b_ ? c_a_ : c_b_
```

## C Formatting

### Indentation and Whitespace

- Use 2 spaces for indentation. Tabs are not allowed.
- Line width limit: 80 columns.
- Pointer `*` attaches to the type name:

```c
char *c_name = nullptr;
const C_Target *c_target = nullptr;
```

### Braces

- Function definition braces are placed on separate lines:

```c
int c_target_init(void)
{
    return 0;
}
```

- Control statement braces use K&R style (opening brace on the same line):

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

### Struct/Enum Definitions

- Members are indented and aligned. Brace style matches function definitions:

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

### Blank Lines and Vertical Whitespace

- One blank line between function definitions.
- Use blank lines to separate logically related code blocks.
- Do not add unnecessary blank lines at the beginning or end of functions.
- Do not add trailing whitespace at the end of lines.

## C File Organization

### Header Files (.h)

- Contain only type declarations, function prototypes, macro definitions, and `constexpr` constants.
- Do not contain function implementations (except very short `static inline` functions).
- `static inline` functions must not exceed 10 lines:

```c
// Short inline functions allowed in header files
static inline int c_target_is_valid(const C_Target *c_target_)
{
    return c_target_ != nullptr && c_target_->m_id > 0;
}
```

### Source Files (.c)

- Include the corresponding header file and all dependencies.
- Global variables are prohibited. File-scope `static` functions are visible only within the current file.
- Public function implementations must follow the declaration order in the header file.
