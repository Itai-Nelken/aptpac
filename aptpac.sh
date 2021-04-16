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
appver="0.2.0-alpha"

#functions
function help() {
    echo "USAGE:"
    echo "	aptpac [option] [options for the option]"
    echo "	EXAMPLE: ./aptpac.sh search qemu"
    echo "AVAILABLE OPTIONS:"
    echo "	install - install a package."
    echo "	remove - uninstall a package."
    echo "	search - search a package."
    echo "	find - (pacman -F) in debian: 'apt-file search'."
    echo "	update - equivalent of 'apt upgdate && apt upgrade' in debian."
    echo "	autoclean - clean up all local caches."
    echo "	autoremove - remove packages that are no longer needed."
	echo "	list-installed - list all installed packages."
    echo "	help - show this help."
	echo "	version - show version and about information."
	echo " "
	echo -e "\e[1mIf you don't supply any option, the help and about will be printed.\e[0m"
}
function about() {
    echo "      APTPAC      "
    echo "  ==============  "
    echo "A simple wrapper for pacman with a syntax similar to apt to help people transitioning to arch and arch based distros like manjaro."
    echo "version: $appver"
    echo ' '
    echo "MIT license"
    echo "Copyright (c) 2021 Itai Nelken"
}

if [[ "$1" == '' ]]; then
    about
    echo ' '
    help
	exit 0
fi

while [[ "$1" != '' ]]; do
	case $1 in
		install)
			shift
			sudo pacman -S "$@"
			break
		;;
		remove)
			shift
			sudo pacman -Rs "$@"
			break
		;;
		search)
			shift
			pacman -Ss "$@"
			break
		;;
		find)
			shift
			pacman -F "$@"
			break
		;;
		update)
			sudo pacman -Syu
			break
		;;
		autoclean|clean)
			sudo pacman -Sc
			break
		;;
		autoremove)
			sudo pacman -Qdtq | sudo pacman -Rs -
			break
		;;
		list-installed)
			pacman -Qqe
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
            help
            exit 0
	esac
	#shift
done	
