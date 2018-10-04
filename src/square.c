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

V include_n_cnt(S str_1, S str_2, I *i, I max)
{
	include_string(str_1, str_2, *i, max);
	*i += scnt(str_2);
}

params fill_heart(FILE *ptr, S background_colour, C background_char, S heart_colour, S blink, S blink_colour, S string, S string_colour)		//< compose img into dat straight to ptr
{
	C line[250];
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

	include_n_cnt(line, background_colour, &i, scnt(background_colour));		//<	background colour
	line[i++] = background_char;												//<	' ' || ':'
	if (background_char == ':') 												//<	if ':'	--> ':''
		line[i++] = '\'';
	else {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));								//<	if ' '	--> set nrm && ' '
		line[i++] = ' ';
	}
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));					//<	set heart colour
	include_n_cnt(line, cap, &i, scnt(cap));									//<	write cap
	include_n_cnt(line, background_colour, &i, scnt(background_colour));		//<	write background colour
	if (background_char == ':') {												//<	if ':' --> '':''
		line[i++] = '\'';
		line[i++] = ':';
		line[i++] = '\'';
	}
	else {																		//<	if ' '	-->	'   '
		for (j = 0; j < 3; j++)
			line[i++] = ' ';
	}
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));					//<	set heart colour
	include_n_cnt(line, cap, &i, scnt(cap));									//<	write cap
	if (background_char == ':') {												//<	if ':' --> set background colour && '':'
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
		line[i++] = '\'';
		line[i++] = background_char;
	}
	else {																		//< if ' ' --> set nrm && ' ' && set background colour && ' '
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
		line[i++] = background_char;
	}
	line[i] = DELIM;															//< DELIM
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);												//< write in
	clear_str(line, i+1);														//< clear line
	m_line = MAX(m_line, i);
	i = 0;

	/*	second line */

	include_n_cnt(line, CNRM, &i, scnt(CNRM));									//<	set nrm
	line[i++] = ' ';															//<	' '
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));					//<	set heart col
	include_n_cnt(line, sec_line, &i, scnt(sec_line));							//<	sec line
	include_n_cnt(line, blink_colour, &i, scnt(blink_colour));					//<	blink colour
	include_n_cnt(line, blink, &i, scnt(blink));								//<	blink
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));					//<	heart colour
	line[i++] = ':';															//< '::'
	line[i++] = ':';
	include_n_cnt(line, CNRM, &i, scnt(CNRM));									//<	set nrm
	line[i++] = ' ';															//<	' '
	line[i] = DELIM;															//<	DELIM
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);												//<	write in
	clear_str(line, i+1);														//<	clear line
	m_line = MAX(m_line, i);
	i = 0;

	
	/*	third line 	*/

	include_n_cnt(line, CNRM, &i, scnt(CNRM));
	line[i++] = ' ';
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));
	include_n_cnt(line, th_line, &i, scnt(th_line));
	include_n_cnt(line, CNRM, &i, scnt(CNRM));
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
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
		line[i++] = '.';
	}
	else {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
	}
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));
	include_n_cnt(line, fourth_line_1, &i, scnt(fourth_line_1));
	include_n_cnt(line, string_colour, &i, scnt(string_colour));
	include_n_cnt(line, string, &i, scnt(string));
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));
	include_n_cnt(line, fourth_line_2, &i, scnt(fourth_line_2));

	if (background_char == ':') {
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
		line[i++] = '.';
	}
	else {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
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

	include_n_cnt(line, background_colour, &i, scnt(background_colour));
	line[i++] = background_char;
	line[i++] = background_char;
	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
	}
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));
	include_n_cnt(line, fifth_line, &i, scnt(fifth_line));
	if (background_char == ':') {
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
		line[i++] = '.';
	}
	else  {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
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

	include_n_cnt(line, background_colour, &i, scnt(background_colour));
	for (j = 0; j < 4; j++)
		line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
	}
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));
	include_n_cnt(line, sixth_line, &i, scnt(sixth_line));
	if (background_char == ':') {
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
		line[i++] = '.';
	}
	else  {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
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

	include_n_cnt(line, background_colour, &i, scnt(background_colour));
	for (j = 0; j < 6; j++)
		line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '.';
	else  {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
	}
	include_n_cnt(line, heart_colour, &i, scnt(heart_colour));
	include_n_cnt(line, sev_line, &i, scnt(sev_line));
	if (background_char == ':') {
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
		line[i++] = '.';
	}
	else  {
		include_n_cnt(line, CNRM, &i, scnt(CNRM));
		line[i++] = ' ';
		include_n_cnt(line, background_colour, &i, scnt(background_colour));
	}
	for (j = 0; j < 6; j++)
		line[i++] = background_char;
	line[i] = END;
	len += ++i;
	line[i] = 0;
	fwrite(line, SZ(C), i, ptr);
	/*	*/
	par->max_line = MAX(m_line, i);
	par->max_len = len;

	R par;
}
