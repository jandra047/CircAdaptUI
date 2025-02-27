# CircAdaptUI

A front-end to the [CircAdapt_Library](https://gitlab.maastrichtuniversity.nl/circadapt/CircAdapt_Library)

## Features

- Real-time simulation and visualisation of cardiovascular biomechanics.

## Requirements

- git (to clone this repository)
- C++ compiler
    - **Supported compilers:** g++, MSVC
- CMake 3.29 or higher
- Qt6.4

## Getting Started

### Setting up SSH keys to communicate with GitLab

To be able to resolve the dependencies, your SSH keys need to be added to your GitLab account.
1. [If you haven't already, generate a SSH key pair](https://docs.gitlab.com/user/ssh/#see-if-you-have-an-existing-ssh-key-pair).
2. [Add the key to your GitLab account](https://docs.gitlab.com/user/ssh/#add-an-ssh-key-to-your-gitlab-account)


### Setting up `ssh-agent`
To authenticate with GitLab automatically, an ssh-agent server needs to be started and set-up.
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

#### Using QtCreator
Open the `CMakeLists.txt` from QtCreator and the `cmake` should run automatically and resolve the dependencies. If not, right click the CircAdaptUI project and then "Run CMake".

From the left-side navigation pane go to "Projects" tab and under "Build" configuration in "Build steps" click on "Details" and select CircAdaptUI as target and deselect "all".

Build the project. After build is complete, copy `config.json` from project root to the folder where the executable is generated.

### Deploying (for Windows)
In order to run the executable, all the necessary Qt libraries need to be packed with the executable.

~~~sh
path/to/Qt/bin/windeployqt --dir path/to/deployment/dir path/to/CircAdaptUI.exe
~~~

Copy `CircAdaptLib.dll` and `Oxygen.dll` (Windows) or `CircAdaptLib.so` and `libOxygen.so` (Linux) to the deployment directory.
