# aptpac

[![latest release badge](https://img.shields.io/github/v/release/Itai-Nelken/aptpac?include_prereleases&style=flat-square)](github.com/Itai-Nelken/aptpac/releases/latest) [![license badge](https://img.shields.io/github/license/Itai-Nelken/aptpac?style=flat-square)](https://github.com/Itai-Nelken/aptpac/blob/main/LICENSE) ![Build-x64 status badge](https://img.shields.io/github/workflow/status/Itai-Nelken/aptpac/Build-x64?label=Build%20x64&style=flat-square) ![Build-arm64 status badge](https://img.shields.io/github/workflow/status/Itai-Nelken/aptpac/Build-arm64?label=Build%20arm64&style=flat-square) ![Build-armhf status badge](https://img.shields.io/github/workflow/status/Itai-Nelken/aptpac/Build-armhf?label=Build%20armhf&style=flat-square)


aptpac is a program which helps with the transition to Arch Linux and Arch based distros like Manjaro.

It simplifies using pacman as it works like the easier to use APT package manager found in Debian based distributions.

The program comes in 2 variants, a bash shell version, and a C code variant.
It is recommended to use the C code variant since C code is quicker and better than shell scripts. the C variant is more friendly and more feature rich, but the bash version gets new commands before as its simpler and easier to debug.

## Note
This program has nothing to do with the other projects named `aptpac` like [this one](https://github.com/FascodeNet/aptpac). please don't ask for support for other `aptpac`'s or ask for support for this `aptpac` in the other `aptpac`'s repositories.

## Usage

```
USAGE:
        aptpac [option] [options for the option]
        EXAMPLE: aptpac search qemu
AVAILABLE OPTIONS:
        install - install a package.
        remove - uninstall a package.
        purge - uninstall a package along with its configuration files.
        search - search a package.
        find - (`pacman -F`) in debian: `apt-file search`.
        update - equivalent of `apt update` in debian.
        upgrade - equivalent of `apt upgrade` in debian.
        full-upgrade - same as 'upgrade'.
        autoclean - clean up pacman caches.
        clean - same as 'autoclean'.
        autoremove - remove packages that are no longer needed.
        show - show the information of a package that is installed.
        show-all - same as 'show', but shows packages from the repos.
        list-installed - list all installed packages.
        help - show this help.
        version - show version and about information.
        
 options are not case sensitive (C version only).
```
### Bash version only (for now):
`--learning-mode=<on|off>` - accepts 'on' or 'off' as values. turns learning mode on or off.

## Installation

Since there are 2 variants of aptpac, there are 2 install methods, please choose the variant you would like:

1) C (recommended)<br>
2) Bash

### Guide to installing C aptpac:

``` bash
sudo pacman -S cmake make git gcc
cd $HOME
git clone https://github.com/Itai-Nelken/aptpac
cd ./aptpac/C-edition
mkdir build
cd build 
cmake -DCMAKE_BUILD_TYPE=Release -DCALLCOMMAND="aptpac" ..
make
# Optional however crucial
sudo make install # This moves aptpac to /usr/local/bin so it can be run easily
```
#### Learning mode (C-edition only)
If you want to enable 'learning mode' which prints the commands being run, add  `-DLEARN=1` before the .. in the `cmake` line during installation so it looks like this:<br>
```bash
cmake -DLEARN=1 -DCALLCOMMAND="aptpac" -DCMAKE_BUILD_TYPE=Release ..
```

### Guide to installing Bash aptpac:

``` bash
sudo pacman -S wget
cd $HOME
mkdir ~/.aptpac
wget https://github.com/Itai-Nelken/aptpac/releases/download/2.2/aptpac.sh -O ~/.aptpac/aptpac.sh
chmod +x .aptpac/aptpac.sh
echo "alias aptpac=\"~/.aptpac/aptpac.sh\"" >> $HOME/.bashrc
source ~/.bashrc
```

## Uninstalling

Choose the correct uninstall method - the one you chose when installing

### Guide to uninstalling C aptpac:

``` bash
cd ~/aptpac/C-edition/build
sudo make uninstall
cd $HOME
sudo rm -r ./aptpac
```

### Guide to uninstalling Bash aptpac:

``` bash
cd $HOME
sed -i '/alias aptpac=.*aptpac.*/d' .bashrc
rm -r .aptpac
source .bashrc
```

## Reviews

<a href="https://github.com/CleanMachine1" target="_blank">CleanMachine1</a> - aptpac is a great piece of software, making the move to arch easier (the better Linux in my opinion).

## Daily builds

Daily builds for x64, arm64, and armhf are now available, these can be found in the actions tab on the aptpac repo, once you have clicked on the actions tab, click on 'Build-x64', 'Build-arm64', or 'Build-armhf' then
click on the latest build with a green ✔️, scroll down to the 'artifacts' section, and click on the zip there.
keep in mind you need a github account to download them.

## Build checks

Build checks for arm64, armhf, and X86-64 are run for every commit and pr. you can see the status in the badges at the top of the README.
The check are not run for README updates.
