#include <stdio.h>
#include <string.h>   // strlen(), strcat(), strerror()
#include <stdlib.h>   // malloc(), free(), exit(), getenv()
#include <unistd.h>   // fork(), execvp()
#include <errno.h>    // errno
#include <sys/wait.h> // waitpid()
#include <stdarg.h>   // va_list, va_start(), va_end(), vprintf()

#include "functions.h"

void println(const char *format, ...) {
	char *str=malloc(sizeof(char)*strlen(format)+3);
	snprintf(str, sizeof(char)*strlen(format)+3, "%s\n", format);
	va_list args;
	va_start(args, format);
	
	vprintf(str, args);
	
	va_end(args);
	free(str);
}
#ifdef DEBUG
	void debug(char *text, char *info) {
		printf("\e[1m\n DEBUG INFO \e[0m\n");
		printf("============\n");
		printf("%s: %s\n\n", text, info);
	}
#endif

void help(char *argv0) {
	println("\e[1mUSAGE:\e[0m");
	println("	%s [command] [packages (if applicable for the command)]", argv0);
	println("	\e[1mEXAMPLE:\e[0m aptpac search qemu");
	println("\e[1mLEARNING MODE:\e[0m");
	println("	to enable learning mode, run with the environment variable 'APTPAC_LEARN' set to 1");
	println("	\e[1mEXAMPLE:\e[0m APTPAC_LEARN=1 aptpac");
	println("	or add 'export APTPAC_LEARN=1' to your bashrc or equivalent to have it always on.");
	println("\e[1mAVAILABLE OPTIONS:\e[0m");
	println("	install - install a package.");
	println("	install-local - install a local package. accepts the path to the package as a argument.");
	println("	remove - uninstall a package.");
	println("	purge - uninstall a package along with its configuration files.");
	println("	search - search a package.");
	println("	find - (pacman -F) in debian: 'apt-file search'.");
	println("	update - equivalent of 'apt update' in debian.");
	println("	upgrade - equivalent of 'apt upgrade' in debian.");
	println("	full-upgrade - update + upgrade.");
	println("	autoclean - clean up all local caches.");
	println("	clean - same as 'autoclean'.");
	println("	autoremove - remove packages that are no longer needed.");
	println("	show - show the information of a package that is installed.");
	println("	show-all - same as 'show', but shows packages from the repos.");
	println("	list-installed - list all installed packages.");
	println("	help - show this help.");
	println("	version - show version and about information.\n");
	println("\e[1mCONFIGURATION:\e[0m");
	println("	--config <set|unset> <configuration> - set/unset configuration options.");
	println("\e[1mAVAILABLE CONFIGURATION OPTIONS:\e[0m");
	println("	learn (default: off)");
	println("	Configuration is set to the default values if there is no configuration file.");
	println("\e[1moptions are not case sensitive.\e[0m");
}
 
void about() {
	println("\e[1m   APTPAC \e[0m\n ==========");
	println("A simple wrapper for pacman with a syntax similar to apt to help people transitioning to Arch and Arch based distros like Manjaro.");
	printf("\e[1mVersion:\e[0m %s built on %s.\n\n", VER, __TIMESTAMP__);
	println("License: MIT");
	println("Copyright (c) 2021 Itai Nelken");
}

//print the command being run: <the contents of the command variable> if int learn == 1
void learn(char *command, int learn) {
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
		// There is no config file, set the configuration values to the defaults.
		config->version = CONF_FILE_VERSION;
		config->learn = 0;
		return;
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
			perror("run(): execv()");
			exit=1;
			return 1;
		}
	} else if(child<0) {
		perror("run(): fork()");
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
