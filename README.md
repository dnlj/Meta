# Meta

Meta is a header only C++ library that provides type manipulation utilities.

## Getting Started

Since Meta is header only, all that you need to do is make the `./include/` directory visible to your project.

## Running the Tests

Before we begin it should be noted that, currently, building the tests is only configured for Windows with Visual Studio (see build/vs_build.lua for version details). We will also need [premake.](https://github.com/premake/premake-core)

First download and build the needed dependencies:

```Batchfile
premake5 download-deps
premake5 build-deps
```

Next generate the project files and build them:

```Batchfile
premake5 vs2017
premake5 build
```

Finally to run the tests:

```Batchfile
premake5 test
```

## Examples
