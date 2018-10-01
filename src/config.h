#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

#define SEC 1000000
#define END '@'

#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))


#define UP(x) printf("\033[%dA", (x)); 		// Move up X lines;
#define DOWN(x) printf("\033[%dB", (x)); 	// Move down X lines;
#define RIGHT(x) printf("\033[%dC", (x)); 	// Move right X column;
#define LEFT(x) printf("\033[%dD", (x)); 	// Move left X column;
#define CLEAR printf("\033[2J"); // Clear screen


typedef struct Params {
	I amount;
	I max_len;
} pParams;

typedef struct Background {
	C col[15];
	C ch;
} pBackground;

typedef struct Terminal_conf {
	I width;
	I height;
}	pTer_conf;

typedef pParams* params;
typedef pBackground* background;
typedef pTer_conf* ter_conf;



#define CWHT 	"\x1b[0;0m\x1b[37m\0"
#define CBLU 	"\x1b[0;0m\x1b[34m\0"
#define CCYN 	"\x1b[0;0m\x1b[36m\0"
#define BCYN 	"\x1b[0;0m\x1b[37;40m\0"
#define BPNKCW 	"\x1b[0;0m\x1b[37;41m\0"
#define BMGNCW 	"\x1b[0;0m\x1b[37:45m\0"
#define CRED 	"\x1b[0;0m\x1b[31m\0"
#define CNRM 	"\x1b[0;0m\0"

	
	C cap[6] = 			 ".:::.\0";
	C sec_line[12] = 	":::::::.:::\0";
	C th_line[16] = 	":::::::::::::::\0";
	C 4_line_1[6] = 	"\'::::\0";
	C 4_line_2[6] =		"::::\'\0";
	C 5_line[12] = 		"\':::::::::\'\0";
	C 6_line[8] =		"\':::::\'\0";
	C 7_line[4] = 		"\':\'\0";

	C bck_chr[2] = {' ', ':'};
