#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "config.h"
#include "draw.h"
#include "square.h"

S* get_heart(FILE* db, I ptr, S* heart)					//< get img pattern from ptr
{
	C c = 'c';
	I i, j;
	fseek(db, ptr + SZ(pBackground), SEEK_SET);		//< go to img part 

	for (i = 0; i < HEART_H; i++) {							//< for each line
		for (j = 0; c != '@' && c != '#'; j++) {		//< read untill delim 
			fread(&c, SZ(C), 1, db);
			heart[i][j] = c;
		}
		heart[i][--j] = 0;
		if (c == '@')
			break;
		c = 'c';
	}
	
	R heart;
}

I get_addr(I num, FILE *idx)								//< get ptr of specific img
{
	I addr;
	rewind(idx);
	fseek(idx, num * SZ(I) + SZ(pParams), SEEK_SET);
	fread(&addr, SZ(I), 1, idx);
	rewind(idx);
	R addr;
}

V get_background(FILE *db, background back, I ptr)		//< get background info for specific img
{
	rewind(db);
	fseek(db, ptr, SEEK_SET);
	fread(back, SZ(pBackground), 1, db);

	rewind(db);
}

V get_params(FILE *idx, params par)					 	//< get pParams from idx
{
	rewind(idx);
	fread(par, SZ(pParams), 1, idx);
	rewind(idx);
}

V make_db()													//< compose db and idx
{
	FILE *db, *idx;
	I addr;
	params par, heart_par;
	pParams p = {0, 0}, heart_par_;
	I i, j, k ,l, m, n, o, len = 0;
	I limj1, limj2, limo1, limo2;
	S par_str_col;


	/*  make your own combination   */

	C bck_chr[3] = " :\0";

	S bck_col[6]	= {CWHT, CBLU, CCYN, BCYN, BPNKCW, BMGNCW};
	S hrt_col[3]	= {CRED, CWHT, BPNKCW};
	S blnk[2];
	S blnk_col[2]   = {CWHT, CRED};
	S str[4];
	S str_col[3]	= {CRED, CWHT, CBLU};

	C bl1[3]		=   ".|\0";
	C bl2[3]		=   "::\0";
	C str_1[6]	  =   ":::::\0";
	C str_2[6]	  =   "MYDAK\0";
	C str_3[6]	  =   " love\0";
	C str_4[6]	  =   " you \0";

	blnk[0] = bl1; blnk[1] = bl2;
	str[0] = str_1; str[1] = str_2; str[2] = str_3; str[3] = str_4;
   
	db = 	fopen("bin/db.dat", "w+b");
	idx = 	fopen("bin/idx.dat", "w+b");

	par = &p;
	heart_par = &heart_par_;

	fwrite(par, SZ(pParams), 1, idx);

	/*  if you changed settings ^ don't forget to modify cycles' params	 */

	for (i = 0; i < 2; i++){						//< background character
		limj1 = (i) ? 0 : 3;
		limj2 = limj1 + 3;

		for (j = limj1; j < limj2; j++) {						//< background colour
			for (k = 0; k < 3; k++){							//< heart colour
				for (l = 0; l < 2; l++) {						//< blink style
					m = l;										//< blink colour
						for (n = 0; n < 4; n++) {				//< string style
							limo1 = (n) ? 1 : 0;
							limo2 = (n) ? 3 : 1;

							for (o = limo1; o < limo2; o++) { 	//< string colour
								addr = ftell(db);
								par_str_col = (!n) ? hrt_col[k] : str_col[o];
								heart_par = fill_heart(db, bck_col[j], bck_chr[i], hrt_col[k], blnk[l], blnk_col[m], str[n], par_str_col);

								par->max_len = MAX(par->max_len, heart_par->max_len);
								par->max_line = MAX(par->max_line, heart_par->max_line);

								par->amount++;
								fwrite(&addr, SZ(I), 1, idx);
							}	
						}
				}
			}
		}
	}
	rewind(idx);
	fwrite(par, SZ(pParams), 1, idx);
	fclose(db);
	fclose(idx);
}