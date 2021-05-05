# aptpac

aptpac is a program which helps with the transition to Arch Linux and similar.

It simplifies using pacman as it works like the easier to use APT package manager found in Debian based distributions.

The program comes in 2 variants, a bash shell version, and a C code variant.
It is recommended to use the C code variant since C code is quicker and better than shell scripts.

## Usage

``` bash
aptpac install $PACKAGENAME 
aptpac search $PACKAGENAME
aptpac remove $PACKAGENAME
```

## **Installation**

Since there are 2 variants of aptpac, there are 2 install methods, please choose the variant you would like, C or Bash

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
mkdir .aptpac
wget https://github.com/Itai-Nelken/aptpac/releases/download/0.2.0-alpha/aptpac.sh -O .aptpac/aptpac.sh
chmod +x .aptpac/aptpac.sh
echo "alias aptpac=\"~/.aptpac/aptpac.sh\"" >> $HOME/.bashrc
source .bashrc
```

## Uninstalling

Choose the correct uninstall method - the one you chose when installing

**Guide to uninstalling C aptpac:**

``` bash
cd ~/aptpac/C-edition/build
sudo make uninstall
cd ~
sudo rm ./aptpac -r 
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
