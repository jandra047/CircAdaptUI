# CircAdaptUI

A front-end to the [CircAdapt_Library](https://gitlab.maastrichtuniversity.nl/circadapt/circadapt/CircAdapt_Library)

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

```sh
cd CircAdaptUI
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DQT_DIR=*/path/to/Qt/lib/cmake/Qt6* -DDMAKE_BUILD_TYPE=*/path/to/lib/cmake*
cmake --build . --target CircAdaptUI --config Release
```

### Deploying (for Windows)
In order to pack all the necessary libraries together with the executable, ```windeploy``` needs to be run.

```sh
*path/to/Qt/bin*/windeploy --dir *path/to/deployment/dir* *path/to/CircAdaptUI.exe*
```
