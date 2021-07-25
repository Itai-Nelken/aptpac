#pragma once
//#define VER "2.5" //defined in CMakeLists.txt
//#define CALLCOMMAND "./aptpac" //defined in CMakeLists.txt

struct config {
	int learn;
};

void echo(char text[501]);
#ifdef DEBUG
	void debug(char text[101], char info[101]);
#endif
void help();
void about();
void learn(char command[101], int learn);
void get_cmdargs(int argc, char **argv, int startarg, char *out);
//initialize a struct config.
struct config *config_init();
void config_free(struct config *conf);
//returns 1 on invalid configuration option and 0 on success
int config_save(struct config *config);
void config_load();
int run(char **command);
