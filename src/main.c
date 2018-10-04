#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include "config.h"
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "draw.h"
#include "dat.h"



	/*
	C cap[6] = 			 ".:::.\0";
	C sec_line[12] = 	":::::::.:::\0";
	C th_line[16] = 	":::::::::::::::\0";
	C four_line_1[6] = 	"\'::::\0";
	C four_line_2[6] =		"::::\'\0";
	C five_line[12] = 		"\':::::::::\'\0";
	C six_line[8] =		"\':::::\'\0";
	C sev_line[4] = 		"\':\'\0";*/

	// C bck_chr[3] = " :\0";


I main()
{
	srand(time(NULL));

	// O("Im here!\n");
	if (access("../bin/db.dat", F_OK) == -1) 
		make_db();

	// O("Im here!\n");

	draw_heart();

	R0;
}