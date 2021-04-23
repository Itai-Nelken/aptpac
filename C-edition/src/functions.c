#include <stdio.h>
#include "functions.h"


void echo(char text[501]) {
    printf("%s\n", text);
}

int help(void) {
    echo("\e[1mUSAGE:\e[0m");
    echo("	aptpac [option] [options for the option]");
    echo("	\e[1mEXAMPLE:\e[0m aptpac search \"qemu\"");
    echo("\e[1mAVAILABLE OPTIONS:\e[0m");
    echo("	install - install a package.");
    echo("	remove - uninstall a package.");
    echo("	search - search a package.");
    echo("	find - (pacman -F) in debian: 'apt-file search'.");
    echo("	update - equivalent of 'apt upgdate && apt upgrade' in debian.");
    echo("	autoclean - clean up all local caches.");
    echo("	autoremove - remove packages that are no longer needed.");
	echo("	list-installed - list all installed packages.");
    echo("	help - show this help.");
	echo("	version - show version and about information.\n");
	echo("\e[1mIf you don't supply any option, the help and about will be printed.\e[0m");
}

int about(void) {
    echo("\e[1m   APTPAC \e[0m\n ==========");
    echo("A simple wrapper for pacman with a syntax similar to apt to help people transitioning to arch and arch based distros like manjaro.");
    printf("version: %s\n\n", APPVER);
    echo("license: MIT");
    echo("Copyright (c) 2021 Itai Nelken");
}