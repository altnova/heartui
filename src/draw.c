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
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include "rows.h"

V draw_side(S col, C ch, I w, I dif)
{
	O("%s", col);
	DO((w - HEART_W)/2 + dif, {O("%c", ch);});
	fflush(stdout);
}


V show_img(background heart_par, ter_conf _ter_conf)								//< print img 
{
	I j, dif, k = 0;
	struct winsize a;
	ter_conf _ter_var = &a;
	C cnrm[7] = "\x1b[0;0m";

	gotoxy(0, 0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, _ter_conf);															//<	get window size

	if (_ter_conf->ws_col < HEART_W || _ter_conf->ws_row < HEART_H) {										//<	in case of small screen
		DO(_ter_conf->ws_row, {DO(_ter_conf->ws_col, {O(" ");});O("\n");});									//<	draw blank screen
		R;
	}

	O("%s", heart_par->bck_col);																			//<	set background colour
	DO((_ter_conf->ws_row - HEART_H)/2, {DO(_ter_conf->ws_col, {O("%c", heart_par->ch);}); O("\n");}); 		//< draw top
	fflush(stdout);

	dif = (_ter_conf->ws_col % 2) ? 0 : 1;													
	// dif = 1;
	/*	row_1()		*/
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, 0);								//<	draw left
	row_1(heart_par->bck_col, heart_par->ch, heart_par->hrt_col, cnrm);
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, dif);
	O("\n");

	/*	row_2()		*/
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, 0);
	row_2(heart_par->hrt_col, heart_par->blink, heart_par->bln_col, cnrm);
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, dif);
	O("\n");

	/*	row_3()	*/
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, 0);
	row_3(heart_par->hrt_col, cnrm);
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, dif);
	O("\n");

	/* row_4()	*/
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, 0);
	row_4(heart_par->bck_col, heart_par->ch, heart_par->hrt_col, heart_par->string, heart_par->str_col, cnrm);
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, dif);
	O("\n");

	/*	row_5()	*/
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, 0);
	row_5(heart_par->bck_col, heart_par->ch, heart_par->hrt_col, cnrm);
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, dif);
	O("\n");

	/*	row_6()	*/
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, 0);
	row_6(heart_par->bck_col, heart_par->ch, heart_par->hrt_col, cnrm);
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, dif);
	O("\n");

	/*	row_7()	*/

	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, 0);
	row_7(heart_par->bck_col, heart_par->ch, heart_par->hrt_col, cnrm);
	draw_side(heart_par->bck_col, heart_par->ch, _ter_conf->ws_col, dif);
	O("\n");


	dif = (_ter_conf->ws_row % 2) ? 0 : 1;

	DO((_ter_conf->ws_row - HEART_H)/2 + dif, {DO(_ter_conf->ws_col, {O("%c", heart_par->ch);}); O("\n");}); 	//< draw down
	// DO((_ter_conf->ws_row - HEART_H)/2 + dif - 3, {DO(_ter_conf->ws_col, {O("%c", heart_par->ch);}); O("\n");}); 	//< draw down (test mode)

	// O("w %d * h %d\n", _ter_conf->ws_col, _ter_conf->ws_row);

	fflush(stdout);
}


V window_dif_change(background heart_par, ter_conf _ter_conf, I pause)
{
	struct winsize a;
	ter_conf _ter_var = &a;
	I j, i, p = SEC/60;
	j = pause/p;

	show_img(heart_par, _ter_conf);
	// O("w %d * h %d\n", _ter_conf->ws_col, _ter_conf->ws_row);
	for (i = 0; i < j; i++) {
		usleep(p);
		ioctl(STDOUT_FILENO, TIOCGWINSZ, _ter_var);
		if (_ter_var->ws_col != _ter_conf->ws_col || _ter_var->ws_row != _ter_conf->ws_row)	
			show_img(heart_par, _ter_conf);
	}
}



V draw_heart()																								//< print rand img
{
	FILE *db, *idx;
	I pos, i, j, pause = SEC, n, num = 0;
	C c = ' ';
	pParams para = {0};
	params par = &para;
	pBackground back_;
	background heart_par = &back_;
	struct winsize a;
	ter_conf _ter_conf = &a;

	db = fopen("bin/db.dat", "r+b");
	idx = fopen("bin/idx.dat", "r+b");

	get_params(idx, par);
	O("draw_heart();\n");

	//<		background heart_par 	-->		keeps img colour sequence
	//<		NEED TO:
	//<		* get random position
	//<		* get img sequence into background heart_par
	//<		* make S* heart 
	//< 	* pass to window dif change


	CLEAR;
	for (;;) {
		// O("!\n");
		num = rand() % par->amount;
		while (!num)
			num = rand() % par->amount;
		// num = (!num) ? 1 : num;

		pos = get_addr(num, idx); 									//<!!	check get_addr()!!!! 
		get_background(db, heart_par, pos);							//< get img pattern into heart_par		//<!!	check get_backgorund()!!!!
		pause = (pause == (SEC * 6)/7) ? (SEC*1)/2 : (SEC * 6)/7;	//< set pause
		// pause = SEC * 3 /2;
		window_dif_change(heart_par, _ter_conf, pause);	
		// O("%d\n", num);
		if(kbhit())													//< break if any key pressed
    		break;	
	}

	O("%s\n", CNRM);												//<	set back to normal


	fclose(db);
	fclose(idx);
}
