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


V show_img(S* heart, S background_col, C background_char, I w, I h)								//< print img 
{
	I j, dif, dif_1;

	if (w < 17 || h < 7) {													//<	in case of small screen
		DO(h, {DO(w, {O(" ");});O("\n");});
		R;
	}

	O("%s", background_col);
	DO((h - 7)/2, {DO(w, {O("%c", background_char);}); O("\n");}); 			//< draw top
	fflush(stdout);

	for (j = 0; j < 7; j++){
		O("%s", background_col);
		DO((w - 17)/2, {O("%c", background_char);});						//<	draw left

		O("%s", heart[j]);
		dif = (w % 2) ? 0 : 1;
		O("%s", background_col);
		DO((w - 17)/2 + dif, {O("%c", background_char);});					//<	draw right
		fflush(stdout);
		O("\n");
	}
	dif = (w % 2) ? 0 : 1;
	dif = (h % 2) ? 1 : 0;
	DO((h - 7)/2 + dif, {DO(w, {O("%c", background_char);}); O("\n");}); 	//< draw down
	fflush(stdout);
}

V draw_heart()																					//< print rand img
{
	FILE *db, *idx;
	I pos, i, num, j, pause = SEC;
	S *heart;
	pParams para = {0, 0};
	params par = &para;
	pBackground back_;
	background back = &back_;
	pTer_conf a = {136, 37};		//<	test [136, 37];
	ter_conf _ter_conf = &a;

	db = fopen("bin/db.dat", "r+b");
	idx = fopen("bin/idx.dat", "r+b");

	get_params(idx, par);

	heart = malloc(SZ(S) * 7);
	for (i = 0; i < 7; i++) 
		heart[i] = malloc(SZ(C) * 200);


	CLEAR;

	for(i = 0; i < 15; i++) { 
		num = rand() % par->amount;

		pos = get_addr(num, idx);

		get_heart(db, pos, heart);
		get_background(db, back, pos);
	
		show_img(heart, back->col, back->ch, _ter_conf->width, _ter_conf->height);

		gotoxy(0, 0);

		fflush(stdout);
		pause = (pause == SEC) ? (SEC*2)/3 : SEC;
		usleep(pause);
	}

	for (i = 0; i < 7; i++) 
		free(heart[i]); 
	free(heart);

	fclose(db);
	fclose(idx);
}
