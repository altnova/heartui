#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "draw.h"
#include "config.h"

S* get_heart(FILE* db, I ptr, S* heart)				//< get img from ptr
{
	C c = 'c';
	I i, j;
	fseek(db, ptr + SZ(background), SEEK_SET);

	for (i = 0; i < 7; i++) 
		for (j = 0; c != '@' && c != '\0') {
			fread(&c, SZ(C), 1, db);
			heart[i][j++] = c;
		}
	

	if (c == '@')
		heart[--i][--j] = '\0';

	R heart;
}

I get_addr(I num, FILE *idx)						//< get ptr of specific img
{
	I addr;
	fseek(idx, num + SZ(params), SEEK_SET);
	fread(&addr, SZ(I), 1, idx);
	R addr;
}



V make_db()											//< compose db and idx
{
	FILE *db, *idx;
	S buf;
	I addr,  num, j, pos;
	params par;
/*
	I i, j, k ,l, m, n, o;
    I limj1, limj2, limo1, limo2;

    S sstr, par_str_col;

    C bck_chr[2] = {' ', ':'};

    S bck_col[6];
    S hrt_col[3];
    S blnk[2];
    S blnk_col[2];
    S str[4];
    S str_col[3];

    bck_col[0] = CWHT; bck_col[1] = CBLU; bck_col[2] = CCYN; bck_col[3] = BCYN; bck_col[4] = BPNKCW; bck_col[5] = BMGNCW;
    hrt_col[0] = CRED; hrt_col[1] = CWHT; hrt_col[2] = BPNKCW;
    blnk[0] = bl1; blnk[1] = bl2;
    blnk_col[0] = CWHT; blnk_col[1] = CRED;
    str[0] = str_1; str[1] = str_2; str[2] = str_3; str[3] = str_4;
    str_col[0] = CRED; str_col[1] = CWHT; str_col[2] = CBLU;
*/

	db = 	fopen("../bin/db.dat", "w+b");
	idx = 	fopen("../bin/idx.dat", "w+b");

	par->amount = 0;
	par->max_len = 0;

	fseek(idx, SZ(params), SEEK_SET);

	for (i = 0; i < 2; i++){						//< background character
    	if (!i) {
	   		limj1 = 3;
	   		limj2 = 6;
  		}
  		else {
  			limj1 = 0;
  			limj2 = 3;
  		}


    	for (j = limj1; j < limj2; j++) {			//< background colour
    		for (k = 0; k < 3; k++) {				//<	heart colour
    			for (l = 0; l < 2; l++) {			//< blink style
    				m = l;				
    					for (n = 0; n < 4; n++) {	//< string style
    						if (!n) {
    							limo1 = 0;
    							limo2 = 1;
    						}
    						else {
    							limo1 = 1;
    							limo2 = 3;
    						}

    						for (o = limo1; o < limo2; o++) {
    							addr = ftell(db);
    							par_str_col = (!n) ? hrt_col[k] : str_col[o];
    							par->max_len = MAX(par->max_len, fill_heart(db, bck_col[j], bck_chr[i], hrt_col[k], blnk[l], blnk_col[m], str[n], par_str_col));
    							par->amount++;
    							fwrite(&addr, SZ(I), 1, idx);
    						}	
    					}
    			}
    		}
    	}
  	}

  	fseek(idx, 0, SEEK_SET);
  	fwrite(par, SZ(params), 1, idx);

  	fclose(db);
  	fclose(idx);
}