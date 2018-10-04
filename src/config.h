#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <sys/ioctl.h>


#define SEC 1000000
#define END '@'
#define DELIM '#'

#define HEART_H 7
#define HEART_W 17
// #define MAX_COL_LEN 19

#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))

#define UP(x) printf("\033[%dA", (x)); 		// Move up X lines;
#define DOWN(x) printf("\033[%dB", (x)); 	// Move down X lines;
#define RIGHT(x) printf("\033[%dC", (x)); 	// Move right X column;
#define LEFT(x) printf("\033[%dD", (x)); 	// Move left X column;
#define CLEAR printf("\033[2J"); // Clear screen


typedef struct Params {
	UJ amount;
	UJ max_len;
	UJ max_line;
} pParams;

typedef struct Background {
	C col[19];
	C ch;
} pBackground;


typedef struct winsize pTerminal_conf;

/*
typedef struct Terminal_conf {
	I width;
	I height;
}	pTer_conf;
*/
typedef pParams* params;
typedef pBackground* background;
typedef pTerminal_conf* ter_conf;



#define CWHT 	"\x1b[0;0m\x1b[37m\0"
#define CBLU 	"\x1b[0;0m\x1b[34m\0"
#define CCYN 	"\x1b[0;0m\x1b[36m\0"
#define BCYN 	"\x1b[0;0m\x1b[37;40m\0"
#define BPNKCW 	"\x1b[0;0m\x1b[37;41m\0"
#define BMGNCW 	"\x1b[0;0m\x1b[37:45m\0"
#define CRED 	"\x1b[0;0m\x1b[31m\0"
#define CNRM 	"\x1b[0;0m\0"

	
ext V get_background(FILE *db, background back, I ptr);
ext V get_params(FILE *idx, params par);
