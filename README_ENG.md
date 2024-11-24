# SpaceStation

## Description

Welcome to the Space Station project! This project is in the C++ programming language using CMake, Google Test.

## Checking the necessary utilities
- **cmake** - for managing the software build process
- **ninja** - the generator

Install **ninja** using the commands:

For Ubuntu/Debian:
```
sudo apt update
sudo apt install ninja-build
```
For macOS:
```
brew install ninja
```
or suitable for your system.

- **g++/clang** - the compiler

### Optional:
- **clang-tidy**

For Ubuntu/Debian:
```
sudo apt update
sudo apt install clang-tidy
```
For MacOS:
```
brew install llvm
echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

- **clang-format**

For Ubuntu/Debian:
```
sudo apt update
sudo apt install clang-format
```
For MacOS:
```
brew install clang-format
```

## Build and run

1. Move to the root directory of the project (Space Station by default)
   ```
   cd SpaceStation/
   ```

2. Configure the project:
   ```
   cmake --preset release
   ```

3. Run the application build:
   ```
   cmake --build --preset release
   ```
   and test build:
   ```
   cmake --build --preset test
   ```

4. Run the server and the client in different terminal windows:
   ```
   ./build/release/bin/server
   ```
   ```
   ./build/release/bin/client
   ```

5. Run the tests:
   ```
   ./build/release/bin/test_lib
   ```
   ```
   ctest --preset test
   ```

## Formatting Settings

The project uses [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) for automatic formatting of the code. The formatting configuration is located in the .clang-format file.

## Project structure

```
SpaceStation/
├── build/                       # Folder for build files
├── external/                    # Submodules and third-party libraries
│   ├── CMakeLists.txt           # CMakeLists to build
│   └── gtest/                   # Google Test submodule
│       └── CMakeLists.txt       # CMakeLists for building the library
├── include/                     # Header files of the project
│   └── libspace/                # Library folder
│       └── libspace.hpp         # Header file
├── src/                         # Source files of the project
│   ├── app/                     # The source files folder for the program
│   │   ├── CMakeLists.txt       # CMakeLists to build
│   │   ├── server.cc            # Source file of the server part
│   │   └── client.cc            # The source file of the client part
│   ├── libspace/                # The source files folder for the program
│   │   ├── CMakeLists.txt       # CMakeLists to build
│   │   ├── spacemodule.cc       # Library source file
│   │   └── spacestation.cc      # Source library file
│   └─── CMakeLists.txt # CMakeLists to build
├── tests/                       # Test project files
│   ├── CMakeLists.txt             # CMakeLists to build the library
│   └── test.cc                    # Test file
├── CMakeLists.txt               # The main CMake file
├── CMakePresets.json            # Presets for CMake
├── .clang-format                # Configuration file ClangFormat 
├── .gitignore                   # git ignore file
├── README_ENG.md                # Version README.md in English
└── README.md                    # Version README.md in Russian
```