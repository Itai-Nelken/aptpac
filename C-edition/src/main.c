/*********************
MIT License

Copyright (c) 2021 Itai Nelken

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h" //VER defined in "functions.h"

int main(int argc, char **argv) {
	char command[101], cmdflags[4097]="";
	int LEARN=0;
	struct config *conf=config_init();
	//set the 'APTPAC_LEARN' env var to "0" (yes, a string) to avoid a segfault in getenv if it isn't set
	//set its value to 0, and don't overwrite it if it already exists.
	setenv("APTPAC_LEARN", "0", 0);
	//activate learning mode if env var 'APTPAC_LEARN' = 1
	char *learn_env=getenv("APTPAC_LEARN");
	//load the configuration
	config_load(conf);
	if(!strcmp(learn_env, "1")||conf->learn==1) {
		LEARN=1;
	}
	while(argc>1) {
		if(!strcasecmp(argv[1], "--config")) {
			if(argc!=4) {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m not enough options for option 'config' provided!\e[0m\n");
				free(conf);
				return 1;
			}
			if(!strcmp(argv[2], "set")) {
				if(!strcmp(argv[3], "learn")) {
					conf->learn=1;
				} else {
					fprintf(stderr, "\e[1;31mERROR: \e[0;31minvalid configuration option '%s'!\e[0m\n", argv[3]);
					config_free(conf);
					return 1;
				}
			} else if(!strcmp(argv[2], "unset")) {
				if(!strcmp(argv[3], "learn")) {
					conf->learn=0;
				} else {
					fprintf(stderr, "\e[1;31mERROR: \e[0;31minvalid configuration option '%s'!\e[0m\n", argv[3]);
					config_free(conf);
					return 1;
				}
			} else {
				fprintf(stderr, "\e[1;31mERROR:\e[0;31m invalid config mode!\e[0m\n");
				config_free(conf);
				return 1;
			}
			if(config_save(conf)) {
				fprintf(stderr, "\e[1;31mERROR:\e[0;31m Failed to write config changes!\e[0m\n");
				free(conf);
				return 1;
			} else {
				printf("\e[1mConfiguration '%s' %s successfully!\e[0m\n", argv[3], argv[2]);
				config_free(conf);
				return 0;
			}
		} else if(!strcasecmp(argv[1], "install")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m '%s' option passed, but no app provided!\e[0m\n", argv[1]);
				break;
			}
			strcpy(command, "sudo pacman -S ");
			strcat(command, cmdflags);
			//if learning mode is on, print the command being run using the 'learn' function
			learn(command, LEARN);
			system(command);
			break;
		} else if(!strcasecmp(argv[1], "install-local")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'install-local' option passed, but no package(s) provided!\e[0m\n");
				break;
			}
			strcpy(command, "sudo pacman -U ");
			strcat(command, cmdflags);
			learn(command, LEARN);
			system(command);
			break;
		} else if(!strcasecmp(argv[1], "remove") || !strcasecmp(argv[1], "uninstall")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'install' option passed, but no app provided!\e[0m\n");
				break;
			}
			strcpy(command, "sudo pacman -Rs ");
			strcat(command, cmdflags);
			learn(command, LEARN);
			system(command);
			break;
		} else if(!strcasecmp(argv[1], "purge")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'purge' option passed, but no app provided!\e[0m\n");
				break;
			}
			strcpy(command, "sudo pacman -Rn ");
			strcat(command, cmdflags);
			learn(command, LEARN);
			system(command);
			break;
		} else if(!strcasecmp(argv[1], "search")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'search' option passed, but no search string provided!\e[0m\n");
				break;
			}
		strcpy(command, "pacman -Ss ");
		strcat(command, cmdflags);
		learn(command, LEARN);
		system(command);
		break;
		} else if(!strcasecmp(argv[1], "find")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'find' option passed, but no search string provided!\e[0m\n");
				break;
			}
			strcpy(command, "pacman -F ");
			strcat(command, cmdflags);
			learn(command, LEARN);
			system(command);
			break;
		} else if(!strcasecmp(argv[1], "update")) {
			learn("sudo pacman -Sy", LEARN);
			system("sudo pacman -Sy");
			break;
		} else if(!strcasecmp(argv[1], "upgrade")) {
			learn("sudo pacman -Su", LEARN);
			system("sudo pacman -Su");
			break;
		} else if(!strcasecmp(argv[1], "full-upgrade")) {
			learn("sudo pacman -Syu", LEARN);
			system("sudo pacman -Syu");
			break;
		} else if(!strcasecmp(argv[1], "clean") || !strcasecmp(argv[1], "autoclean")) {
			learn("sudo pacman -Scc", LEARN);
			system("sudo pacman -Scc");
			break;
		} else if(!strcasecmp(argv[1], "autoremove")) {
			learn("sudo pacman -Qdtq | sudo pacman -Rs -", LEARN);
			system("sudo pacman -Qdtq | sudo pacman -Rs -");
			break;
		} else if(!strcasecmp(argv[1], "list-installed")) {
			learn(command, LEARN);
			system("pacman -Qqe");
			break;
        } else if(!strcasecmp(argv[1], "show")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
#ifdef DEBUG
				debug("comdflags", cmdflags);
#endif
				strcpy(command, "pacman -Qi ");
				strcat(command, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'show' option passed, but no package provided \e[0m\n");
				break;
			}

			learn(command, LEARN);
#ifdef DEBUG
			debug("command", command);
#endif
			system(command);
			break;
		} else if(!strcasecmp(argv[1], "show-all")) {
			if(argv[2]) {
				get_cmdargs(argc, argv, 2, cmdflags);
				strcpy(command, "pacman -Si ");
				strcat(command, cmdflags);
			} else {
				fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'show-all' option passed, but no package provided \e[0m\n");
				break;
			}
			learn(command, LEARN);
			system(command);
			break;
		} else if(!strcasecmp(argv[1], "help") || !strcasecmp(argv[1], "-help") || !strcasecmp(argv[1], "--help") || !strcasecmp(argv[1], "-h")) {
			help(argv[0]);
			break;
		} else if(!strcasecmp(argv[1], "version") || !strcasecmp(argv[1], "-v") || !strcasecmp(argv[1], "--version")) {
			about();
			break;
		} else {
			fprintf(stderr, "\e[31m\e[1mERROR:\e[0m \e[31minvalid option \"%s\"!\e[0m\n", argv[1]);
			break;
		}
	}
	if(argc==1) {
		fprintf(stderr, "\e[31m\e[1mERROR:\e[0m \e[31mno operation specified!\e[0m\n");
		fprintf(stderr, "\e[1mrun \"%s --help\" for help\e[0m\n", argv[0]);
		//about();
		//echo("");
		//help();
	}
	config_free(conf);
	return 0;
}


