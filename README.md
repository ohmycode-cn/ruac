# ruac (Runtime Unified Access Controller Database)

## Foreword

RUAC is a runtime unified access controller database implemented in C++, Rust, and C, with the majority of functionality written in C++. I am not sure what RUAC will become in the future, but I hope to explore a more radical database system. This means RUAC may undergo major refactors at certain points or during specific version stages.

The core philosophy of RUAC is absolute modularity. Each module only needs to provide well-defined interfaces without knowledge of other modules' internal implementations, ensuring long-term maintainability and extensibility. I am not a professional software engineer (perhaps I will become one in the future), just a free software enthusiast.

If you are interested in RUAC, you are welcome to participate in development and discussion.

## Vision

RUAC is inspired by the Linux philosophy, adhering to principles of "small and focused," "large and comprehensive," "modular," and "extensible."

RUAC employs a multi-language implementation: most functionality is implemented in C++, memory safety-critical parts use Rust, and performance-critical parts use C. This design leverages the strengths of each language to achieve optimal performance while ensuring development efficiency and safety.

Regarding language standards, RUAC will completely abandon outdated programming paradigms and language standards. The minimum C++ standard for RUAC is C++17, but the actual project uses C++26, and the compiler standard is also set to C++26. For C components, RUAC will directly adopt the C23 standard. Rust components will use the latest long-term support version of the official Rust standard library. RUAC is a complex project and may be quite challenging!

Like an operating system, RUAC has its own standard library, which means third-party libraries will gradually be replaced by its own standard library. In the future, RUAC will have its own C++/C/Rust standard library. This requires reinventing the wheel, which is both a challenge and a learning opportunity.

RUAC has its own database model, kernel layer, user layer, and network layer. Similar to the Linux user system, RUAC's user layer has its own user space, where the default root user has full permissions and controls the RUAC system. In the future, RUAC will also introduce a user+group permission model.

## Standards and Specifications

For RUAC to develop healthily in the long term, standards and specifications are essential. All contributors must comply with the specifications in RUAC-CXX-STYLE-GUIDE.md. Currently, only C++ specifications exist; specifications for other languages will be introduced when RUAC incorporates those languages.

Code submissions that do not comply with RUAC-CXX-STYLE-GUIDE.md specifications will be rejected.

RUAC currently uses the GPL-3.0 open source license on GitHub. In the future, RUAC may consider switching to the MIT license.
