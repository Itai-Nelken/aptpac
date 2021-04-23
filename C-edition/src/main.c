/*
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
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h" //APPVERR defined in "functions.h"

int main(int argc, char **argv) {
    char command[101], app[501];
    while(argc>1) {
        if(!strcmp(argv[1], "install")) {
            if(argv[2]) {
                strcpy(app, argv[2]);
        } else {
            fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'install' option passed, but no app provided!\e[0m\n");
            break;
        }
        strcpy(command, "sudo pacman -S ");
        strcat(command, app);
        system(command);
        break;
        } else if(!strcmp(argv[1], "remove") || !strcmp(argv[1], "uninstall")) {
            if(argv[2]) {
                strcpy(app, argv[2]);
        } else {
            fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'uninstall' option passed, but no app provided!\e[0m\n");
            break;
        }
        strcpy(command, "sudo pacman -Rs ");
        strcat(command, app);
        system(command);
        break;
        } else if(!strcmp(argv[1], "search")) {
            if(argv[2]) {
                strcpy(app, argv[2]);
        } else {
            fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'search' option passed, but no search string provided!\e[0m\n");
            break;
        }
        strcpy(command, "sudo pacman -Ss ");
        strcat(command, app);
        system(command);
        break;
        } else if(!strcmp(argv[1], "find")) {
            if(argv[2]) {
                strcpy(app, argv[2]);
        } else {
                fprintf(stderr, "\e[31m\e[1mERROR:\e[0m\e[31m 'find' option passed, but no search string provided!\e[0m\n");
                break;
            }
            strcpy(command, "sudo pacman -F ");
            strcat(command, app);
            system(command);
            break;
        } else if(!strcmp(argv[1], "update")) {
            system("sudo pacman -Syu");
            break;
        } else if(!strcmp(argv[1], "clean") || !strcmp(argv[1], "autoclean")) {
            system("sudo pacman -Sc");
            break;
        } else if(!strcmp(argv[1], "autoremove")) {
            system("sudo pacman -Qdtq | sudo pacman -Rs -");
            break;
        } else if(!strcmp(argv[1], "list-installed")) {
            system("pacman -Qqe");
            break;
        } else if(!strcmp(argv[1], "list-installed")) {
            system("pacman -Qqe");
            break;
        } else if(!strcmp(argv[1], "help") || !strcmp(argv[1], "-help") || !strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
            help();
            break;
        } else if(!strcmp(argv[1], "version") || !strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
            about();
            break;
        } else {
            fprintf(stderr, "\e[31m\e[1mERROR:\e[0m \e[31minvalid option \"%s\"!\e[0m\n", argv[1]);
            break;
        }
    }
    if(argc==1) {
        fprintf(stderr, "\e[31m\e[1mERROR:\e[0m \e[31mno operation specified!\e[0m\n");
		about();
        echo("");
        help();
	}
	return 0;
}


