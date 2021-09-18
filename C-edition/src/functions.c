#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
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
	echo("\e[1mCONFIGURATION:\e[0m");
	echo("	--config <set|unset> <configuration> - set/unset configuration options.");
	echo("\e[1mAVAILABLE CONFIGURATION OPTIONS:\e[0m");
	echo("	learn");
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
void get_cmdargs(int argc, char **argv, int startarg, char *out) {
	strcat(out, argv[startarg]);
	for(int i=startarg+1; i<argc; i++) {
		strcat(out, " ");
		strcat(out, argv[i]);
	}
}

//initialize a struct config.
struct config *config_init() {
	struct config *conf=malloc(sizeof(struct config)*1);
	conf->version=CONF_FILE_VERSION;
	return conf;
}

void config_free(struct config *conf) {
	free(conf);
}

//returns 1 if opening config file failed and 0 on success
int config_save(struct config *config) {
	FILE *file;
	char *env=getenv("HOME");
	char conf_file[101]="";
	sprintf(conf_file, "%s/.config/aptpac.config", env);
#ifdef DEBUG
	debug("configuration file", conf_file);
#endif
	file=fopen(conf_file, "w");
	if(file==NULL) {
		fprintf(stderr, "\e[1;31mERROR:\e[0;31m failed to open config file: %s\e[0m\n", strerror(errno));
		return 1;
	}
	fwrite(config, sizeof(struct config), 1, file);
	fclose(file);
	return 0;
}

//exits with return value -1 on fail and a pointer to the config struct on success
void config_load(struct config *config) {
	FILE *file;
	char *env=getenv("HOME");
	char conf_file[101]="";
	sprintf(conf_file, "%s/.config/aptpac.config", env);
#ifdef DEBUG
	debug("configuration file", conf_file);
#endif
	file=fopen(conf_file, "r");
	if(file==NULL) {
		fprintf(stderr, "config_load(): fopen(): %s: %s\n", strerror(errno), conf_file);
		exit(-1);
	}
	fread(config, sizeof(struct config), 1, file);
	if(config->version!=CONF_FILE_VERSION) {
		int learn_old=config->learn;
		config_free(config);
		config=config_init();
		config->learn=learn_old;
	}
	fclose(file);
}

int run(char **command) {
	int exit=0, stat_loc;
	pid_t child=fork();
	if(child==0) {
		if(execvp(command[0], command)==-1) {
			perror("execv");
			exit=1;
			return 1;
		}
	} else if(child<0) {
		perror("fork");
		exit=1;
	} else {
		waitpid(child, &stat_loc, WUNTRACED);
	}
	if(exit==1) {
		return 1;
	} else {
		return 0;
	}
}
