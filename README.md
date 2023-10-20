# cashew

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/mrivnak/cashew/build.yml)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/mrivnak/cashew/test.yml?label=tests)

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![LLVM](https://img.shields.io/badge/llvm-%23323330.svg?style=for-the-badge&logo=llvm&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

Functional, strongly-typed programming language, implemented with C++ and LLVM

## Development

### Prerequisites

- LLVM 16
- Clang
- CMake

### Using Nix

![Nix](https://img.shields.io/badge/NIX-5277C3.svg?style=for-the-badge&logo=NixOS&logoColor=white)

A `shell.nix` file is provided for use with Nix. To enter a shell with all the necessary dependencies, run `nix-shell` in the root of the project.
Alternatively `nix-direnv` can be used to automatically enter the shell when entering the project directory.
