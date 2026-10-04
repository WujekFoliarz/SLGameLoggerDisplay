# SLGameLoggerDisplay

## Not tested on Windows

## Build Requirements

- CMake 3.23 or newer (required for the included presets)
- C++23
- Git
- Raylib's dependencies

## Build on Linux

Configure and build the available x64 `RelWithDebInfo` preset from the repository root:

```sh
cmake --preset x64-relwithdebinfo
cmake --build out/x64-relwithdebinfo
```

## Build for the Web with Emscripten

Use the Emscripten SDK for the project and configure the web preset before building:

```sh
source /path/to/emsdk/emsdk_env.sh
emcmake cmake --preset emscripten-web
cmake --build out/emscripten-web
```

This produces a browser-targeted build with the Web platform enabled via raylib.

As of now, you need to provide a log file called `log.scpd` in the exec directory for the program to run.

Log files can be generated with this [plugin](https://github.com/WujekFoliarz/SLGameLogger)
