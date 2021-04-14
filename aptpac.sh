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

while [[ "$#" != 0 ]]; do
	case $1 in
		install)
			pacman -S "$2"
		;;
		remove)
			pacman -Rs "$2"
		;;
		search)
			pacman -Ss "$2"
		;;
		query)
			pacman -F "$2"
		;;
		update)
			pacman -Syu
		;;
		autoclean)
			pacman -Sc
		;;
		autoremove)
			pacman -Qdtq | pacman -Rs -
		;;
		help|-h|--help|-help)
			echo "USAGE:"
			echo "	./aptpac.sh [option] [options for the option]"
			echo "	EXAMPLE: ./aptpac.sh search \"qemu\""
			echo "AVAILABLE OPTIONS:"
			echo "	install - install a package."
			echo "	remove - uninstall a package."
			echo "	search - search a package."
			echo "	query - (pacman -F) in debian: 'apt-file search'."
			echo "	update - equivalent of 'apt upgdate && apt upgrade' in debian."
			echo "	autoclean - clean up all local caches."
			echo "	autoremove - remove packages that are no longer needed."
			echo "	help - show this help."
		;;
		version|-v|--version)
			echo "aptpac - a pacman wrapper that makes it easy apt users to transition to arch linux"
			echo "version 0.1-alpha"
			echo "MIT license"
			echo "Copyright (c) 2021 Itai Nelken"
		
	esac
	shift
done
		