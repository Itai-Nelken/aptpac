#include <stdio.h>
#include "functions.h"


void echo(char text[501]) {
	printf("%s\n", text);
}

void help() {
	echo("\e[1mUSAGE:\e[0m");
	echo("	aptpac [option] [options for the option]");
	echo("	\e[1mEXAMPLE:\e[0m aptpac search \"qemu\"");
	echo("\e[1mAVAILABLE OPTIONS:\e[0m");
	echo("	install - install a package.");
	echo("	remove - uninstall a package.");
	echo("	purge - uninstall a package along with its configuration files.");
	echo("	search - search a package.");
	echo("	find - (pacman -F) in debian: 'apt-file search'.");
	echo("	update - equivalent of 'apt update' in debian.");
	echo("	upgrade - equivalent of 'apt upgrade' in debian.");
	echo("	full-upgrade - same as 'upgrade'.");
	echo("	autoclean - clean up all local caches.");
	echo("	clean - same as 'autoclean'.");
	echo("	autoremove - remove packages that are no longer needed.");
	echo("	show - show the information of a package that is installed.");
	echo("	show-all - same as 'show', but shows packages from the repos.");
	echo("	list-installed - list all installed packages.");
	echo("	help - show this help.");
	echo("	version - show version and about information.\n");
	echo("\e[1moptions are not case sensitive.\e[0m");
}

void about() {
	echo("\e[1m   APTPAC \e[0m\n ==========");
	echo("A simple wrapper for pacman with a syntax similar to apt to help people transitioning to arch and arch based distros like manjaro.");
	printf("\e[1mversion:\e[0m %s built on %s.\n\n", VER, __TIMESTAMP__);
	echo("license: MIT");
	echo("Copyright (c) 2021 Itai Nelken");
}

void config(char opt[10], char **conf) {
/*****************
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
****************/
}
