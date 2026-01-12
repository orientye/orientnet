orientnet is a high performance c++ server engine.

NOTE: It is in the experimental stage of development.

## Building

### Linux/macOS

To build with CMake:

    $ (mkdir -p build && cd build && cmake .. -DBUILD_TEST=ON) # generate project with tests
    $ cmake --build build  # add `-j <n>` with cmake >= 3.16

### Windows

For detailed Windows build instructions, see [BUILD_WINDOWS.md](BUILD_WINDOWS.md).

Quick start with Visual Studio:

    > mkdir build && cd build
    > cmake .. -DBUILD_TEST=ON
    > cmake --build . --config Release
