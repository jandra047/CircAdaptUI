# CircAdaptUI

A front-end to the [CircAdapt_Library](https://gitlab.maastrichtuniversity.nl/circadapt/CircAdapt_Library)

## Features

- Real-time simulation and visualisation of cardiovascular biomechanics.

## Requirements

- git (to clone this repository)
- C++ compiler (e.g., g++, clang++, MSVC)
- CMake 3.29 or higher
- Qt6

## Getting Started

### Downloading

Clone the repository:

```sh
git clone https://gitlab.maastrichtuniversity.nl/circadapt/CircAdaptUI.git
```
or 
```sh
git clone git@gitlab.maastrichtuniversity.nl:circadapt/CircAdaptUI.git
```
if you have SSH keys set up.

### Building
**NOTE:** In order to resolve dependencies from protected gitlab server, your SSH key needs to be added to an ssh-agent.
```sh
cd CircAdaptUI
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DQT_DIR=_/path/to/Qt/lib/cmake/Qt6_ -DCMAKE_PREFIX_PATH=_/path/to/Qt/lib/cmake_
cmake --build . --target CircAdaptUI --config Release
```

### Deploying (for Windows)
In order to run the executable, all the necessary Qt libraries need to be packed with the executable.

~~~sh
path/to/Qt/bin/windeployqt --dir path/to/deployment/dir path/to/CircAdaptUI.exe
~~~

Copy the `CircAdaptLib.dll` (Windows) or `CircAdaptLib.so` (Linux) to the deployment directory.
