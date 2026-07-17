# ruac (Runtime Unified Access Controller Database)

## Preface

RUAC is a runtime unified access controller database implemented in C++, Rust, and C, with the majority of functionality written in C++. I am not certain what RUAC will become in the future, but I hope to explore a more radical database system. This means RUAC may be overhauled at certain points in time or during specific version stages.

The core philosophy of RUAC is absolute modularity. Each module only needs to provide well-defined interfaces without understanding other modules' internal implementations, ensuring long-term maintainability and extensibility. I am not a professional software engineer (perhaps I will become one someday), just a free software enthusiast.

If you are interested in RUAC, welcome to participate in development and discussion.

## Vision

RUAC draws inspiration from Linux philosophy, embracing principles such as "small and focused," "large and comprehensive," "modular," and "extensible."

RUAC adopts a multi-language implementation: the majority of functionality is implemented in C++, memory safety-critical parts use Rust, and performance-critical parts use C. This design leverages the strengths of each language, ensuring both development efficiency and safety with optimal performance.

Regarding language standards, RUAC will completely abandon outdated programming paradigms and language standards. The minimum C++ standard for RUAC is C++17, but the actual project uses C++26 with the compiler standard also set to C++26. For the C components, RUAC will directly adopt the C23 standard. The Rust components will use the official Rust standard library with the latest long-term support version. RUAC is a complex project and can be quite challenging!

Like an operating system, RUAC has its own standard library, meaning third-party libraries will gradually be replaced by its own standard library. In the future, RUAC will have its own C++/C/Rust standard libraries. This requires reinventing the wheel, which is both a challenge and a learning opportunity.

RUAC has its own database model, kernel layer, user layer, and network layer. Similar to the Linux user system, RUAC's user layer has its own user space, with a default root user having full permissions and control over the RUAC system. In the future, RUAC will also introduce a user+group permission model.

## Standards and Guidelines

For RUAC to thrive long-term, standards and guidelines are essential. All contributors must adhere to the specifications in RUAC-CXX-STYLE-GUIDE.md. Currently, only C++ guidelines are available. Guidelines for other languages will be introduced when RUAC incorporates them in the future.

Code submissions that do not comply with the specifications in RUAC-CXX-STYLE-GUIDE.md will be rejected.

RUAC currently uses the GPL-3.0 open-source license on GitHub. In the future, RUAC may consider switching to the MIT license.
