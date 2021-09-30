#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct config {
	unsigned int version;
	int learn;
};

void println(const char *format, ...);

#ifdef DEBUG
	void debug(char *text, char *info);
#endif

void help(char *argv0);

void about();

void learn(char *command, int learn);

void get_cmdargs(int argc, char **argv, int startarg, char *out);

// initialize a struct config.
struct config *config_init();

void config_free(struct config *conf);

// returns 1 on invalid configuration option and 0 on success
int config_save(struct config *config);

void config_load();

int run(char **command);

#endif // FUNCTIONS_H
