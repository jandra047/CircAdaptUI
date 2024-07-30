# CircAdaptUI

A front-end to the [CircAdapt_Library](https://gitlab.maastrichtuniversity.nl/circadapt/CircAdapt_Library)

## Features

- Real-time simulation and visualisation of cardiovascular biomechanics.

## Requirements

- git (to clone this repository)
- C++ compiler
    - **Supported compilers:** g++, MSVC
- CMake 3.29 or higher
- Qt6

## Getting Started

### Setting up `ssh-agent`
To be able to resolve the dependencies an ssh server needs to be started and set-up. 
#### Starting the server and adding an ssh-key
- **Windows:**

1. Open Services from the start menu

2. Scroll down to `OpenSSH Authentication Agent` > right click > properties

3. Change the Startup type from Disabled to any of the other 3 options, eg. `Automatic (Delayed Start)`

4. Run `ssh-add` in cmd to add your ssh key to the agent. If you're using more than one ssh key, make sure that you append the path to the key you're using for authentication with gitlab.maastrichtuniversity.nl.

- **Linux:**

1. open terminal and run `systemctl start ssh-agent --user`

2. Run `ssh-add`.


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
**NOTE:** In order to resolve dependencies from protected gitlab server, your SSH key needs to be added to a running ssh-agent.
```sh
cd CircAdaptUI
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DQT_DIR=/path/to/Qt/lib/cmake/Qt6 -DCMAKE_PREFIX_PATH=/path/to/Qt/lib/cmake
cmake --build . --target CircAdaptUI --config Release
```

### Deploying (for Windows)
In order to run the executable, all the necessary Qt libraries need to be packed with the executable.

~~~sh
path/to/Qt/bin/windeployqt --dir path/to/deployment/dir path/to/CircAdaptUI.exe
~~~

Copy the `CircAdaptLib.dll` (Windows) or `CircAdaptLib.so` (Linux) to the deployment directory.
