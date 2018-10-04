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

/* wtites into ptr the block of unique img patter */

params fill_heart(FILE *ptr, S background_colour, C background_char, S heart_colour, S blink, S blink_colour, S string, S string_colour)		//< compose img into dat straight to ptr
{
	C line[200];
	I i = 0, len = 0, j, m_line = 0;

	C cap[6] = 			 ".:::.\0";
	C sec_line[12] = 	":::::::.:::\0";
	C th_line[16] = 	":::::::::::::::\0";
	C fourth_line_1[6] = 	"\'::::\0";
	C fourth_line_2[6] =		"::::\'\0";
	C fifth_line[12] = 		"\':::::::::\'\0";
	C sixth_line[8] =		"\':::::\'\0";
	C sev_line[4] = 		"\':\'\0";

	pParams par_;
	params par = &par_;
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

	
	include_string(line, heart_colour, i, scnt(heart_colour));					//<	set heart colour 			//!!!!
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

	include_string(line, heart_colour, i, scnt(heart_colour));					//<	set heart colour
	i += scnt(heart_colour);
	include_string(line, cap, i, scnt(cap));							//< write cap
	i += scnt(cap);

	if (background_char == ':') {								//<	if ':' --> set background colour && '':'
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);
		line[i++] = '\'';
		line[i++] = background_char;
	}
	else {														//< if ' ' --> set nrm && ' ' && set background colour && ' '
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);
		line[i++] = background_char;
	}
	line[i] = DELIM;											//< DELIM
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);								//< write in
	clear_str(line, i+1);										//< clear line
	m_line = MAX(m_line, i);
	i = 0;



	/*	second line */

	include_string(line, CNRM, i, scnt(CNRM));						//<	set nrm
	i += scnt(CNRM);
	line[i++] = ' ';										//<	' '
	include_string(line, heart_colour, i, scnt(heart_colour));				//<	set heart colour
	i += scnt(heart_colour);
	include_string(line, sec_line, i, scnt(sec_line));					//< sec_line
	i += scnt(sec_line);
	include_string(line, blink_colour, i, scnt(blink_colour));				//<	blink colour
	i +=  scnt(blink_colour);
	include_string(line, blink, i, scnt(blink));						//< blink
	i += scnt(blink);
	include_string(line, heart_colour, i, scnt(heart_colour));				//<	heart colour
	i += scnt(heart_colour);
	line[i++] = ':';										//< '::'
	line[i++] = ':';
	include_string(line, CNRM, i, scnt(CNRM));						//< set nrm
	i += scnt(CNRM);
	line[i++] = ' ';										//<	' '
	line[i] = DELIM;										//<	DELIM
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);							//<	write in
	clear_str(line, i+1);									//<	clear line
	m_line = MAX(m_line, i);
	i = 0;

	
	/*	third line 	*/

	include_string(line, CNRM, i, scnt(CNRM));						
	i += scnt(CNRM);
	line[i++] = ' ';
	include_string(line, heart_colour, i, scnt(heart_colour));
	i += scnt(heart_colour);
	include_string(line, th_line, i, scnt(th_line));
	i += scnt(th_line);
	include_string(line, CNRM, i, scnt(CNRM));
	i += scnt(CNRM);
	line[i++] = ' ';
	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	m_line = MAX(m_line, i);
	i = 0;



	/*	fourth line */
	
	if (background_char == ':') {
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	include_string(line, heart_colour, i, scnt(heart_colour));
	i += scnt(heart_colour);

	include_string(line, fourth_line_1, i, scnt(fourth_line_1));
	i += scnt(fourth_line_1);
	include_string(line, string_colour, i, scnt(string_colour));
	i += scnt(string_colour);
	include_string(line, string, i, scnt(string));
	i += scnt(string);
	include_string(line, heart_colour, i, scnt(heart_colour));
	i += scnt(heart_colour);
	include_string(line, fourth_line_2, i, scnt(fourth_line_2));
	i += scnt(fourth_line_2);

	if (background_char == ':') {
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	m_line = MAX(m_line, i);
	i = 0;


	/*	fifth line 	*/

	include_string(line, background_colour, i, scnt(background_colour));
	i += scnt(background_colour);
	line[i++] = background_char;
	line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
	}
	include_string(line, heart_colour, i, scnt(heart_colour));
	i += scnt(heart_colour);
	include_string(line, fifth_line, i, scnt(fifth_line));
	i += scnt(fifth_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);	
	}

	line[i++] = background_char;
	line[i++] = background_char;
	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	m_line = MAX(m_line, i);
	i = 0;



	/*	sixth line 	*/

	include_string(line, background_colour, i, scnt(background_colour));
	i += scnt(background_colour);

	for (j = 0; j < 4; j++)
		line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
	}
	include_string(line, heart_colour, i, scnt(heart_colour));
	i += scnt(heart_colour);
	include_string(line, sixth_line, i, scnt(sixth_line));
	i += scnt(sixth_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);	
	}

	for (j = 0; j < 4; j++)
		line[i++] = background_char;

	line[i] = DELIM;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	clear_str(line, i+1);
	m_line = MAX(m_line, i);
	i = 0;



	/*	seventh line*/

	include_string(line, background_colour, i, scnt(background_colour));
	i += scnt(background_colour);

	for (j = 0; j < 6; j++)
		line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
	}
	include_string(line, heart_colour, i, scnt(heart_colour));
	i += scnt(heart_colour);
	include_string(line, sev_line, i, 4);
	i += scnt(sev_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, scnt(CNRM));
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, scnt(background_colour));
		i += scnt(background_colour);	
	}

	for (j = 0; j < 6; j++)
		line[i++] = background_char;

	line[i] = END;
	
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);

	// clear_str(line, i+1);
	m_line = MAX(m_line, i);
	// i = 0;

	par->max_line = m_line;
	par->max_len = len;

	R par;
}
