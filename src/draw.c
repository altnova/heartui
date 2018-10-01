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

V include_string(S str_1, S str_2, I ptr, I max)	
{
	I i;
	for (i = 0; str_2[i] != 0 && i < max; i++) 
		str_1[ptr + i] = str_2[i];	
}

V clear_str(S str, I j)
{
	for (I i = 0; i < j; i++)
		str[i] = 0;
}


I fill_heart(FILE *ptr, S background_colour, C background_char, S heart_colour, S blink, S blink_colour, S string, S string_colour)		//< compose img into dat
{
	C CNRM[7] = 		{27, '[', '0', ';', '0', 'm', '\0'};
	C cap[6] = 			{'.', ':', ':', ':', '.', '\0'};
	C sec_line[12] = 	{':', ':', ':', ':', ':', ':', ':', '.', ':', ':', ':', '\0'};
	C th_line[16] = 	{':', ':', ':', ':', ':', ':', ':', ':', ':', ':', ':', ':', ':', ':', ':', '\0'};
	C 4_line_1[6] = 	{'\'', ':', ':', ':', ':', '\0'};
	C 4_line_2[6] =		{':', ':', ':', ':', '\'', '\0'};
	C 5_line[12] = 		{'\'', ':', ':', ':', ':', ':', ':', ':', ':', ':', '\'', '\0'};
	C 6_line[8] =		{'\'', ':', ':', ':', ':', ':', '\'', '\0'}; 	
	C 7_line[4] = 		{'\'', ':', '\'', '\0'};	

	S line = malloc(SZ(C) * 100);
	I i = 0, len = 0, j;
	
	background bck;

	strcpy(bck->col, background_colour);
	bck->ch = background_char;

	fwrite(bck, SZ(background), 1, ptr);

	/*	first line 	*/
/*	
	include_string(line, background_colour, i, 15);
	i += scnt(background_colour);
	line[i++] = background_char;

	if (background_char == ':') 
		line[i++] = '\'';
	else {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, cap, i, 6);
	i += scnt(cap);
	include_string(line, background_colour, i, 15);
	i += scnt(background_colour);

	if (background_char == ':') {
		line[i++] = '\'';
		line[i++] = ':';
		line[i++] = '\'';
	}
	else {
		for (j = 0; j < 3; j++)
			line[i++] = ' ';
	}
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, cap, i, 6);
	i += scnt(cap);

	if (background_char == ':') {
		include_string(line, background_colour, i, 15);
		line[i++] = '\'';
		line[i++] = background_char;
	}
	else {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 15);
		line[i++] = background_char;
	}
	line[i] = 0;
	len += i;
	i = 0;
	fwrite(line, SZ(line), 1, ptr);
	clear_str(line, scnt(line));
*/
	/*	second line */
/*
	include_string(line, CNRM, i, 7);
	i += scnt(CNRM);
	line[i++] = ' ';
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, sec_line, i, 12);
	i += scnt(sec_line);
	include_string(line, blink_colour, i, 15);
	i +=  scnt(blink_colour);
	include_string(line, blink, i, 3);
	i += scnt(blink);
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	line[i++] = ':';
	line[i++] = ':';
	include_string(line, CNRM, i, 7);
	i += scnt(CNRM);
	line[i++] = ' ';
	line[i] = 0;
	len += i;
	i = 0;
	fwrite(line, SZ(line), 1, ptr);
	clear_str(line, scnt(line));
*/
	/*	third line 	*/
/*
	include_string(line, CNRM, i, 7);
	i += scnt(CNRM);
	line[i++] = ' ';
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, th_line, i, 16);
	i += scnt(th_line);
	include_string(line, CNRM, i, 7);
	i += scnt(CNRM);
	line[i++] = ' ';
	line[i] = '\0';
	len += i;
	i = 0;
	fwrite(line, SZ(line), 1, ptr);
	clear_str(line, scnt(line));
*/
	/*	fourth line */
/*	
	if (background_char == ':') {
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);

	include_string(line, 4_line_1, i, 6);
	i += scnt(4_line_1);
	include_string(line, string_colour, i, 15);
	i += scnt(string_colour);
	include_string(line, string, i, 6);
	i += scnt(string);
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, 4_line_2, i, 6);
	i += scnt(4_line_2);

	if (background_char == ':') {
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
	}

	line[i++] = ' ';
	line[i] = '\0';
	len += i;
	i = 0;
	fwrite(line, SZ(line), 1, ptr);
	clear_str(line, scnt(line));
*/
	/*	fifth line 	*/
/*
	include_string(line, background_colour, i, 15);
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
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, 5_line, i, 12);
	i += scnt(5_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);	
	}

	line[i++] = background_char;
	line[i++] = background_char;
	line[i] = '\0';
	len += i;
	i = 0;
	fwrite(line, SZ(line), 1, ptr);
	clear_str(line, scnt(line));
*/
	/*	sixth line 	*/
/*
	include_string(line, background_colour, i, 15);
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
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, 6_line, i, 8);
	i += scnt(6_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);	
	}

	for (j = 0; j < 4; j++)
		line[i++] = background_char;

	line[i] = '\0';
	len += i;
	i = 0;
	fwrite(line, SZ(line), 1, ptr);
	clear_str(line, scnt(line));
*/
	/*	seventh line*/
/*
	include_string(line, background_colour, i, 15);
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
	include_string(line, heart_colour, i, 15);
	i += scnt(heart_colour);
	include_string(line, 7_line, i, 4);
	i += scnt(7_line);

	if (background_char == ':') {
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);
		line[i++] = '.';
	}
	else  {
		include_string(line, CNRM, i, 7);
		i += scnt(CNRM);
		line[i++] = ' ';
		include_string(line, background_colour, i, 15);
		i += scnt(background_colour);	
	}

	for (j = 0; j < 6; j++)
		line[i++] = background_char;

	line[i++] = '\0';
	line[i] = END;
	len += i;
	i = 0;
	fwrite(line, SZ(line), 1, ptr);
*/
	free(line);
	R len;
}


V show_img(S* heart, S background_col, C background_char, I w, I h)								//< print img 
{
	I j, dif;

	if (w < 17 || h < 7) {
		DO(h, {DO(w, {O(" ");});O("\n")});
		R;
	}


	O("%s", background_colour);
	DO((h - 7)/2, {DO(w, {O("%c", background_char);}); O("\n");}); 			//< draw top
	fflush(stdout);
	for (j = 0; j < 7; j++){
		O("%s", background_colour);
		DO((w - 17)/2, {O("%c", background_char);});
		O("%s", heart[j]);
		dif = (w % 2) ? 1 : 0;
		DO((w - 17)/2 + dif, {O("%c", background_char);});
		fflush(stdout);
	}

	dif = (h % 2) ? 1 : 0;
	DO((h - 7)/2 + dif, {DO(w, {O("%c", background_char);}); O("\n");}); 	//< draw down
	fflush(stdout);
}

V draw_heart()																					//< print rand img
{
	FILE *db, *idx;
	I pos, i, num;
	S *heart[7];
	params par;
	background back;

	db = fopen("../bin/db.dat", "r+b");
	idx = fopen("../bin/idx.dat", "r+b");

	par = fread(par, SZ(params), 1, idx);

	for (i = 0; i < 7; i++) 
		heart[i] = malloc(SZ(C) * 150);

	CLEAR;
	for(i = 0; i < 15; i++) { 
	
		num = rand() % par->amount;
		pos = get_addr(num, idx);
		heart = get_heart(db, pos, heart);
		fseek(db, pos, SEEK_SET);
		fread(back, SZ(background), 1, db);

		show_img(heart, back->col, back->ch, ter_conf->w, ter_conf->h)

		gotoxy(0, 0);

		fflush(stdout);
		usleep(SEC);
	}
}
