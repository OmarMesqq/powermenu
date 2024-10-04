# A small Linux power menu

This project is made for my current dekstop setup (Arch Linux with Sway) so it probably won't work in your system :/

For optimized build, just compile a normal CMake project:
```
mkdir build
cd build
cmake .. && make
```

and CMake will default to Release mode.

Otherwise, set a flag during project configuration:
```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```