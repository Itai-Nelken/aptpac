#!/bin/bash

#
#MIT License
#
#Copyright (c) 2021 Itai Nelken
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.
#

#variables
appver="2.3.1-bash"
CALLCOMMAND="./aptpac.sh"

#functions
function help() {
	echo "USAGE:"
	echo "	$CALLCOMMAND [option] [options for the option]"
	echo "	EXAMPLE: $CALLCOMMAND search qemu"
	echo "AVAILABLE OPTIONS:"
	echo "	install - install a package."
	echo "	remove - uninstall a package."
	echo "	purge - uninstall a package along with its configuration files. in debian (apt): 'apt purge'."
	echo "	search - search a package."
	echo "	find - (pacman -F) in debian: 'apt-file search'."
	echo "	update - equivalent of 'apt update' in debian."
	echo "	upgrade - equivalent of 'apt upgrade' in debian."
	echo "	full-upgrade - same as 'upgrade'."
	echo "	autoclean - clean up pacman caches."
	echo "	clean - same as 'autoclean'."
	echo "	autoremove - remove packages that are no longer needed."
	echo "	show - show the information of a package that is installed."
	echo "	show-all - same as 'show', but shows packages from the repos."
	echo "	list-installed - list all installed packages."
	echo "	help - show this help."
	echo "	version - show version and about information."
	echo "SETTINGS:"
	echo "	--learning-mode=<on|off> - accepts 'on' or 'off' as values. turns learning mode on or off."
	echo " "
	echo -e "\e[1mIf you don't supply any option, the help and about will be printed.\e[0m"
}
function about() {
	echo "      APTPAC      "
	echo "  ==============  "
	echo "A simple wrapper for pacman with a syntax similar to apt to help people transitioning to Arch and Arch based distros like Manjaro."
	echo -e "Version: $appver\n"
	echo "License: MIT"
	echo "Copyright (c) 2021 Itai Nelken"
}

function config() {
#	SAVE:
#	$1=save
#	$2=setting to add to config
#	$3=optional text to printed
#	DELETE:
#	$1=delete
#	$2=setting to delete
#	$3=optional text to print.
#	LOAD:
#	$1=load
#	$2=setting to load
#	$3=setting name when loading
#
	local DIR="$(pwd)"
	if [[ ! -d "${HOME}/.config/aptpac/" ]]; then
		mkdir "${HOME}/.config/aptpac/"
	fi
	local CONF="${HOME}/.config/aptpac"
	cd "$CONF"
	if [[ ! -f config ]]; then
		touch config
	fi
	if [[ "$1" == "save" ]]; then
		echo "$2" >> config
		if [[ ! -z "$3" ]]; then
			echo -e "$3"
		fi
	elif [[ "$1" == "delete" ]]; then
		sed -i "/$2/d" config
		if [[ ! -z "$3" ]]; then
			echo -e "$3"
		fi
	elif [[ "$1" == "load" ]]; then
		if [[ "$(cat config | grep $2)" == "$2" ]]; then
			export SETTING=$3
		else
			echo -e "\e[31m\e[1mERROR: \e[0m\e[31mfailed to find requested setting!\e[0m"
			exit 1
		fi
	elif [[ "$1" == "load-all" ]]; then
		export SETTING="$(cat config)"
	fi
	cd "$DIR"
}

if [[ "$1" == '' ]]; then
	echo -e "\e[31m\e[1mERROR:\e[0m\e[31m no operation specified!\e[0m"
	echo -e "\e[1mrun \"$CALLCOMMAND --help\" for help\e[0m"
	exit 0
fi
while [[ "$1" != '' ]]; do
	config load-all
	case $SETTING in
		learn)
			export LEARN=1
		;;
	esac
	case $1 in
		--learning-mode*)
			MODE=$(echo $1 | sed -e 's/^[^=]*=//g')
			if [[ "$MODE" == "on" ]]; then
				config save "learn"
				echo -e "learning mode on"
			elif [[ "$MODE" == "off" ]]; then
				config delete "learn"
				echo "learning mode off"
			else
				echo -e "\e[31m\e[1mERROR:\e[0m\e[31m Invalid option '$MODE' for option '--learning-mode'!\e[0m"
			fi
			shift
		;;
		install)
			shift
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -S \"$@\"\e[0m"
			fi
			sudo pacman -S "$@"
			break
		;;
		remove)
			shift
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Rs \"$@\"\e[0m"
			fi
			sudo pacman -Rs "$@"
			break
		;;
		purge)
			shift
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Rn \"$@\"\e[0m"
			fi
			sudo pacman -Rn "$@"
			break
		;;
		search)
			shift
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1mpacman -Ss \"$@\"\e[0m"
			fi
			pacman -Ss "$@"
			break
		;;
		find)
			shift
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1mpacman -F \"$@\"\e[0m"
			fi
			pacman -F "$@"
			break
		;;
		update)
			if [[ $LEARN == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Sy\e[0m"
			fi
			sudo pacman -Sy
			break
		;;
		upgrade|full-upgrade)
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Su\e[0m"
			fi
			sudo pacman -Su
			break
		;;
		autoclean|clean)
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Scc\e[0m"
			fi
			sudo pacman -Scc
			break
		;;
		autoremove)
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Qdtq | sudo pacman -Rs - \"$@\"\e[0m"
			fi
			sudo pacman -Qdtq | sudo pacman -Rs -
			break
		;;
		list-installed)
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Qqe\e[0m"
			fi
			pacman -Qqe
			break
		;;
		show)
			shift
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Qi \"$@\"\e[0m"
			fi
			pacman -Qi "$@"
			break
		;;
		show-all)
			shift
			if [[ "$LEARN" == 1 ]]; then
				echo -e "The command being run is: \e[1msudo pacman -Si \"$@\"\e[0m"
			fi
			pacman -Si "$@"
			break
		;;
		help|-h|--help|-help)
			help
			exit 0
		;;
		version|-v|--version)
            about
            exit 0
        ;;
        *)
            echo -e "\e[1m\e[31minvalid option \"$1\"!\e[0m"
            exit 0
	esac
	#shift
done	
