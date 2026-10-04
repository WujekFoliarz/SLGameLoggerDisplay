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

As of now, you need to provide a log file called `log.scpd` in the exec directory for the program to run.

Log files can be generated with this [plugin](https://github.com/WujekFoliarz/SLGameLogger)
