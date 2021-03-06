# cayv-rpg

Poor man's 2d top-down RPG written in C++ using SDL.

Required libraries: SDL2, SDL2\_image, SDL2\_mixer
Built using CMake (minimum version 3.1).

All other libraries are in `extlib/` and will automatically be built:
- fmtlib - [https://github.com/fmtlib/fmt](https://github.com/fmtlib/fmt)
- microtar - [https://github.com/rxi/microtar](https://github.com/rxi/microtar)

## Build Instructions (Linux/OSX)

Creating an external build directory is recommended.
Navigate to the cayv-rpg directory.

```sh
mkdir ../build-cayv-rpg
cd ../build-cayv-rpg
cmake ../cayv-rpg
make
```

If you are using clang, ensure the build options `-std=c++11 -stdlib=libc++`
are present.
