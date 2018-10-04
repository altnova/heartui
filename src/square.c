#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "dat.h"
#include "config.h"
#include "draw.h"


I fill_heart(FILE *ptr, S background_colour, C background_char, S heart_colour, S blink, S blink_colour, S string, S string_colour)		//< compose img into dat straight to ptr
{
	C line[200];
	I i = 0, len = 0, j;

	C cap[6] = 			 ".:::.\0";
	C sec_line[12] = 	":::::::.:::\0";
	C th_line[16] = 	":::::::::::::::\0";
	C four_line_1[6] = 	"\'::::\0";
	C four_line_2[6] =		"::::\'\0";
	C five_line[12] = 		"\':::::::::\'\0";
	C six_line[8] =		"\':::::\'\0";
	C sev_line[4] = 		"\':\'\0";
	
	pBackground bck_;
	background bck = &bck_;
	strcpy(bck->col, background_colour);

	bck->ch = background_char;									//<		bck 	img pattern 
	fwrite(bck, SZ(pBackground), 1, ptr);						//<	|_______|_______________________|
																//<	write in bck info
	len += SZ(pBackground);


	clear_str(line, i+1);

	/*	first line 	*/

	include_string(line, background_colour, i, scnt(background_colour));				//<	background colour
	i += scnt(background_colour);
	line[i++] = background_char;								//<	' ' || ':'


	if (background_char == ':') 								//<	if ':'	--> ':''
		line[i++] = '\'';
	else {
		include_string(line, CNRM, i, scnt(CNRM));				//<	if ' '	--> set nrm && ' '
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	
	include_string(line, heart_colour, i, 19);					//<	set heart colour 			//!!!!
	i += scnt(heart_colour);

	include_string(line, cap, i, scnt(cap));											//<	write cap
	i += scnt(cap);
	include_string(line, background_colour, i, scnt(background_colour));		//<	set background colour
	i += scnt(background_colour);

	if (background_char == ':') {								//<	if ':' --> '':''
		line[i++] = '\'';
		line[i++] = ':';
		line[i++] = '\'';
	}
	else {														//<	if ' '	-->	'   '
		for (j = 0; j < 3; j++)
			line[i++] = ' ';
	}

	include_string(line, heart_colour, i, 19);					//<	set heart colour
	i += scnt(heart_colour);
	include_string(line, cap, i, 6);							//< write cap
	i += scnt(cap);

	if (background_char == ':') {								//<	if ':' --> set background colour && '':'
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);
		line[i++] = '\'';
		line[i++] = background_char;
	}
	else {														//< if ' ' --> set nrm && ' ' && set background colour && ' '
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);
		line[i++] = background_char;
	}
	line[i] = DELIM;											//< DELIM
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);								//< write in
	clear_str(line, i+1);										//< clear line
	i = 0;


	/*	second line */

	include_string(line, CNRM, i, 7);						//<	set nrm
	i += scnt(CNRM);
	line[i++] = ' ';										//<	' '
	include_string(line, heart_colour, i, 19);				//<	set heart colour
	i += scnt(heart_colour);
	include_string(line, sec_line, i, 12);					//< sec_line
	i += scnt(sec_line);
	include_string(line, blink_colour, i, 19);				//<	blink colour
	i +=  scnt(blink_colour);
	include_string(line, blink, i, 3);						//< blink
	i += scnt(blink);
	include_string(line, heart_colour, i, 19);				//<	heart colour
	i += scnt(heart_colour);
	line[i++] = ':';										//< '::'
	line[i++] = ':';
	include_string(line, CNRM, i, 7);						//< set nrm
	i += scnt(CNRM);
	line[i++] = ' ';										//<	' '
	line[i] = DELIM;										//<	DELIM
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);							//<	write in
	clear_str(line, i+1);									//<	clear line
	i = 0;
	
	/*	third line 	*/

	include_string(line, CNRM, i, 7);						
	i += scnt(CNRM);
	line[i++] = ' ';
	include_string(line, heart_colour, i, 19);
	i += scnt(heart_colour);
	include_string(line, th_line, i, 16);
	i += scnt(th_line);
	include_string(line, CNRM, i, 7);
	i += scnt(CNRM);
	line[i++] = ' ';
	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	i = 0;


	/*	fourth line */
	
	if (background_char == ':') {
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	include_string(line, heart_colour, i, 19);
	i += scnt(heart_colour);

	include_string(line, four_line_1, i, 6);
	i += scnt(four_line_1);
	include_string(line, string_colour, i, 19);
	i += scnt(string_colour);
	include_string(line, string, i, 6);
	i += scnt(string);
	include_string(line, heart_colour, i, 19);
	i += scnt(heart_colour);
	include_string(line, four_line_2, i, 6);
	i += scnt(four_line_2);

	if (background_char == ':') {
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	i = 0;


	/*	fifth line 	*/

	include_string(line, background_colour, i, 19);
	i += scnt(background_colour);
	line[i++] = background_char;
	line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}
	include_string(line, heart_colour, i, 19);
	i += scnt(heart_colour);
	include_string(line, five_line, i, 12);
	i += scnt(five_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);	
	}

	line[i++] = background_char;
	line[i++] = background_char;
	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	i = 0;


	/*	sixth line 	*/

	include_string(line, background_colour, i, 19);
	i += scnt(background_colour);

	for (j = 0; j < 4; j++)
		line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}
	include_string(line, heart_colour, i, 19);
	i += scnt(heart_colour);
	include_string(line, six_line, i, 8);
	i += scnt(six_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);	
	}

	for (j = 0; j < 4; j++)
		line[i++] = background_char;

	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	i = 0;


	/*	seventh line*/

	include_string(line, background_colour, i, 19);
	i += scnt(background_colour);

	for (j = 0; j < 6; j++)
		line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}
	include_string(line, heart_colour, i, 19);
	i += scnt(heart_colour);
	include_string(line, sev_line, i, 4);
	i += scnt(sev_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 19);
		i += scnt(background_colour);	
	}

	for (j = 0; j < 6; j++)
		line[i++] = background_char;

	line[i] = END;
	
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);

	clear_str(line, i+1);
	i = 0;

	R len;
}
