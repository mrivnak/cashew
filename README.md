# cashew

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/mrivnak/cashew/build.yml?label=build+and+test&logo=github)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/mrivnak/cashew/docs.yml?label=docs&logo=github)

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![LLVM](https://img.shields.io/badge/llvm-%23323330.svg?style=for-the-badge&logo=llvm&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

Functional, strongly-typed programming language, implemented with C++ and LLVM

## Links

- **[Documentation](https://mrivnak.github.io/cashew)**

## Development

### Prerequisites

- Clang
- LLD
- CMake
- Ninja
- Doxygen (for documentation)

### Building

```bash
mkdir build && cd build

cmake \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DTARGETS_TO_BUILD="X86;Aarch64;RISCV" \
  ..
  
ninja
```

#### Documentation

This builds Doxygen docs to `build/docs/dist/html`

```bash
mkdir build && cd build
cmake -G Ninja .. -DBUILD_DOCS=YES
ninja docs
```
