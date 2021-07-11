# aptpac

[![latest release badge](https://img.shields.io/github/v/release/Itai-Nelken/aptpac?include_prereleases&style=flat-square)](https://github.com/Itai-Nelken/aptpac/releases/latest) [![license badge](https://img.shields.io/github/license/Itai-Nelken/aptpac?style=flat-square)](https://github.com/Itai-Nelken/aptpac/blob/main/LICENSE) ![Build-x64 status badge](https://img.shields.io/github/workflow/status/Itai-Nelken/aptpac/Build-x64?label=Build%20x64&style=flat-square) ![Build-arm64 status badge](https://img.shields.io/github/workflow/status/Itai-Nelken/aptpac/Build-arm64?label=Build%20arm64&style=flat-square) ![repository size badge](https://img.shields.io/github/repo-size/Itai-Nelken/aptpac?style=flat-square)
<!--![Build-armhf status badge](https://img.shields.io/github/workflow/status/Itai-Nelken/aptpac/Build-armhf?label=Build%20armhf&style=flat-square)-->


**`aptpac`** is a program which helps with the transition to Arch Linux and Arch based distros like Manjaro.

It simplifies using pacman as it works like the easier to use `apt` package manager found in Debian and derivatives.

The program comes in 2 variants, a bash shell version, and a C code variant.
It is recommended to use the C code variant since C it is more friendly and feature rich, but the bash version sometimes gets new features before as its simpler and easier to write.

## Note
This program has nothing to do with the other projects named `aptpac` like [this one](https://github.com/FascodeNet/aptpac). please don't ask for support for other `aptpac`'s in this repository or ask for support for this `aptpac` in the other `aptpac`'s repositories.

## Usage

```
USAGE:
        aptpac [option] [options for the option]
        EXAMPLE: aptpac search qemu
AVAILABLE OPTIONS:
        install - install a package.
        install-local - install a local package. accpets the path to the package as a argument.
        remove - uninstall a package.
        purge - uninstall a package along with its configuration files.
        search - search a package.
        find - (pacman -F) in debian: 'apt-file search'.
        update - equivalent of 'apt update' in debian.
        upgrade - equivalent of 'apt upgrade' in debian.
        full-upgrade - full system upgrade.
        full-upgrade - same as 'upgrade'.
        autoclean - clean up all local caches.
        clean - same as 'autoclean'.
        autoremove - remove packages that are no longer needed.
        show - show the information of a package that is installed.
        show-all - same as 'show', but shows packages from the repos.
        list-installed - list all installed packages.
        help - show this help.
        version - show version and about information.

options are not case sensitive.
```
## Learning mode:
### using a configuration file
#### C edition
`--config <set|unset> learn` - use `set` to turn it on and `unset` to turn it off. the configuration file is in `~/.config/aptpac`.
### Bash edition
`--learning-mode=<on|off>` - accepts `on` or `off` as values. the configuration file is in `~/.aptpac/config`.
###  using a environment variable
If the environment variable `APTPAC_LEARN` has the value of `1`, learning mode will be enabled. there are 3 ways to set it:
1) If you want to test it only for one run, run aptpac like this: `APTPAC_LEARN=1 aptpac <option>`.
2) If you want to have learning mode on until you end your shell session (close the terminal window), run `export APTPAC_LEARN=1`.
3) To have learning mode permanently on, add `export APTPAC_LEARN=1` to your bashrc or equivalent. then restart your terminal or source the bashrc.
to turn it off, delete that line or change the value of the variable.

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

### Guide to installing Bash aptpac:

``` bash
sudo pacman -S wget
cd $HOME
mkdir ~/.aptpac
wget https://github.com/Itai-Nelken/aptpac/releases/download/2.6/aptpac.sh -O ~/.aptpac/aptpac.sh
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
#### To delete the configuration file, run `rm -f ~/.config/aptpac.config`

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

