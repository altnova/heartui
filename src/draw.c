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
#include <sys/ioctl.h>
#include "kbhit.h"


V include_string(S str_1, S str_2, I ptr, I max)				//<	writes in str_2 into str_1
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


V show_img(S* heart, S background_col, C background_char, ter_conf _ter_conf)								//< print img 
{
	I j, dif, k = 0;
	struct winsize a;
	ter_conf _ter_var = &a;

	gotoxy(0, 0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, _ter_conf);
	if (_ter_conf->ws_col < HEART_W || _ter_conf->ws_row < HEART_H) {													//<	in case of small screen
		DO(_ter_conf->ws_row, {DO(_ter_conf->ws_col, {O(" ");});O("\n");});
		R;
	}
	O("%s", background_col);
	DO((_ter_conf->ws_row - HEART_H)/2, {DO(_ter_conf->ws_col, {O("%c", background_char);}); O("\n");}); 			//< draw top
	fflush(stdout);
	for (j = 0; j < HEART_H; j++){
		O("%s", background_col);
		DO((_ter_conf->ws_col - HEART_W)/2, {O("%c", background_char);});						//<	draw left
		O("%s", heart[j]);
		dif = (_ter_conf->ws_col % 2) ? 0 : 1;
		O("%s", background_col);
		DO((_ter_conf->ws_col - HEART_W)/2 + dif, {O("%c", background_char);});					//<	draw right
		fflush(stdout);
		O("\n");
	}
	dif = (_ter_conf->ws_row % 2) ? 1 : 0;
	DO((_ter_conf->ws_row - HEART_H)/2 + dif, {DO(_ter_conf->ws_col, {O("%c", background_char);}); O("\n");}); 	//< draw down
	fflush(stdout);

	ioctl(STDOUT_FILENO, TIOCGWINSZ, _ter_var);
	if (_ter_var->ws_col != _ter_conf->ws_col || _ter_conf->ws_row != _ter_var->ws_row)
		show_img(heart, background_col, background_char, _ter_conf);
}

V draw_heart()																					//< print rand img
{
	FILE *db, *idx;
	I pos, i, j, pause = SEC, n, bytesWaiting;
	S *heart;
	C c = ' ';
	pParams para = {0, 0};
	params par = &para;
	pBackground back_;
	background back = &back_;
	struct winsize a;
	ter_conf _ter_conf = &a;

	db = fopen("bin/db.dat", "r+b");
	idx = fopen("bin/idx.dat", "r+b");

	get_params(idx, par);

	heart = malloc(SZ(S) * HEART_H);
	for (i = 0; i < HEART_H; i++) 
		heart[i] = malloc(SZ(C) * par->max_line);


	CLEAR;

	for(;;) { 																			//< testing 
		pos = get_addr(rand() % par->amount, idx);					//< get address of img in db

		get_heart(db, pos, heart);									//< get img pattern into heart
		get_background(db, back, pos);								//< get background info into back
	
		show_img(heart, back->col, back->ch, _ter_conf);			//<	draw img

		pause = (pause == (SEC * 6)/7) ? (SEC*1)/2 : (SEC * 6)/7;	//< set pause
		usleep(pause);				

    	if (kbhit()) {
    		// fseek(stdin, -1, SEEK_CUR);
    		// fwrite(&c, SZ(C), 1, stdin);
    		// fflush(stdin);
    		break;
    	}
	}



	for (i = 0; i < HEART_H; i++) 
		free(heart[i]); 
	free(heart);

	fclose(db);
	fclose(idx);
}
