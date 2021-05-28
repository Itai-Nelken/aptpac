#define VER "2.5"
//#define CALLCOMMAND "./aptpac" //defined in CMakeLists.txt
//#define LEARN //can be defined in CMakeLists.txt using the '-DLEARN=1' command, so 'cmake -DLEARN=1 ..' from build folder.

void echo(char text[501]);
#ifdef DEBUG
	void debug(char text[101], char info[101]);
#endif
void help();
void about();
void config(char opt[10], char **conf);
