#include <stdio.h>
#include <string.h>
#include "functions.h"


void echo(char text[501]) {
	printf("%s\n", text);
}
#ifdef DEBUG
	void debug(char text[101], char info[101]) {
		printf("\e[1m\n DEBUG INFO \e[0m\n");
		printf("============\n");
		printf("%s: %s\n\n", text, info);
	}
#endif

void help() {
	echo("\e[1mUSAGE:\e[0m");
	echo("	aptpac [command] [packages (if applicable for the command)]");
	echo("	\e[1mEXAMPLE:\e[0m aptpac search qemu");
	echo("\e[1mLEARNING MODE:\e[0m");
	echo("	to enable learning mode, run with the environment variable 'APTPAC_LEARN' set to 1");
	echo("	\e[1mEXAMPLE:\e[0m APTPAC_LEARN=1 aptpac");
	echo("	or add 'export APTPAC_LEARN=1' to your bashrc or equivalent to have it always on.");
	echo("\e[1mAVAILABLE OPTIONS:\e[0m");
	echo("	install - install a package.");
	echo("	install-local - install a local package. accpets the path to the package as a argument.");
	echo("	remove - uninstall a package.");
	echo("	purge - uninstall a package along with its configuration files.");
	echo("	search - search a package.");
	echo("	find - (pacman -F) in debian: 'apt-file search'.");
	echo("	update - equivalent of 'apt update' in debian.");
	echo("	upgrade - equivalent of 'apt upgrade' in debian.");
	echo("	full-upgrade - full system upgrade.");
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
	echo("A simple wrapper for pacman with a syntax similar to apt to help people transitioning to Arch and Arch based distros like Manjaro.");
	printf("\e[1mVersion:\e[0m %s built on %s.\n\n", VER, __TIMESTAMP__);
	echo("License: MIT");
	echo("Copyright (c) 2021 Itai Nelken");
}

//print the command being run: <the contents of the command variable> if int learn == 1
void learn(char command[101], int learn) {
	if(learn==1) {
		printf("The command being run is: \e[1m%s\e[0m\n", command);
	}
}

//get all command line arguments starting with argc=int startarg.
//requires argc and argv to be passed as well as a char array to write the output to.
void get_cmdargs(int argc, char **argv, int startarg, char out[101]) {
	strcat(out, argv[startarg]);
	for(int i=startarg+1; i<argc; i++) {
		strcat(out, " ");
		strcat(out, argv[i]);
	}
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
		if cat config | grep $>/dev/null ; then
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
