//#define VER "2.5" //defined in CMakeLists.txt
//#define CALLCOMMAND "./aptpac" //defined in CMakeLists.txt

void echo(char text[501]);
#ifdef DEBUG
	void debug(char text[101], char info[101]);
#endif
void learn(char command[101], int learn);
void help();
void about();
void config(char opt[10], char **conf);
