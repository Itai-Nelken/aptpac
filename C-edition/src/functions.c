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
    echo("	autoclean - clean up all local caches.");
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
    printf("version: %s built on %s.\n\n", VER, __TIMESTAMP__);
    echo("license: MIT");
    echo("Copyright (c) 2021 Itai Nelken");
}
