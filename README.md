# aptpac

aptpac is a program which helps with the transition to Arch Linux and Arch based distros like Manjaro.

It simplifies using pacman as it works like the easier to use APT package manager found in Debian based distributions.

The program comes in 2 variants, a bash shell version, and a C code variant.
It is recommended to use the C code variant since C code is quicker and better than shell scripts. the C variant is more friendly and more feature rich, but the bash version gets new commands befoer as its simpler and easier to debug. 

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
        autoclean - clean up all local caches.
        autoremove - remove packages that are no longer needed.
        show - show the information of a package that is installed.
        show-all - same as 'show', but shows packages from the repos.
        list-installed - list all installed packages.
        help - show this help.
        version - show version and about information.
 
If you don't supply any option, the help and about will be printed.
```

## Installation

Since there are 2 variants of aptpac, there are 2 install methods, please choose the variant you would like:

1) C (recommended)
2) Bash

**Guide to installing C aptpac:**

``` bash
sudo pacman -S cmake make git gcc
cd $HOME
git clone https://github.com/Itai-Nelken/aptpac
cd ./aptpac/C-edition
mkdir build
cd build 
cmake ..
make
# Optional however crucial
sudo make install # This moves aptpac to /usr/local/bin so it can be run easily
```

**Guide to installing Bash aptpac:**

``` bash
sudo pacman -S wget
cd $HOME
mkdir ~/.aptpac
wget https://github.com/Itai-Nelken/aptpac/releases/download/2.1/aptpac.sh -O ~/.aptpac/aptpac.sh
chmod +x .aptpac/aptpac.sh
echo "alias aptpac=\"~/.aptpac/aptpac.sh\"" >> $HOME/.bashrc
source ~/.bashrc
```

## Uninstalling

Choose the correct uninstall method - the one you chose when installing

**Guide to uninstalling C aptpac:**

``` bash
cd ~/aptpac/C-edition/build
sudo make uninstall
cd $HOME
sudo rm -r ./aptpac
```

**Guide to uninstalling Bash aptpac:**

``` bash
cd $HOME
sed -i '/alias aptpac=.*aptpac.*/d' .bashrc
rm -r .aptpac
source .bashrc
```

## Reviews

<a href="https://github.com/CleanMachine1" target="_blank">CleanMachine1</a> - aptpac is a great piece of software, making the move to arch easier (the better Linux)
