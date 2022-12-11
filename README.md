orientnet is a high performance c++ server engine.

NOTE: It is in the experimental stage of development.

To build with CMake:

    $ (mkdir -p build && cd build && cmake .. -DBUILD_TEST=ON) # generate project with tests
    $ cmake --build build  # add `-j <n>` with cmake >= 3.16
