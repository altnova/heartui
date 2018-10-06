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
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include "make_palette.h"

I dir_exists(S dirname)
{
    DIR *d;
    R ((d = opendir(dirname)) != NULL) ? 0 : 1;
}

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
	params par;
	pParams p = {0};
	I i, j, k ,l, m, n, o, len;
	I limj1, limj2, limo1, limo2;
	S par_str_col;
    // C path[6] = "/bin/\0";
    C cur_dir[PATH_MAX];
    DIR *d;
    // S par_str_col;

    len = lines();
	/*  make your own combination   */

	C bck_chr[3] = " :\0";

	// S bck_col[6]	= {CWHT, CBLU, CCYN, BCYN, BPNKCW, BMGNCW};
	// S hrt_col[3]	= {CRED, CWHT, BPNKCW};

    S* palette = make_palette(); 

    //< ^


	S blnk[2];
	S blnk_col[2]   = {CWHT, CRED};
	S str[4];
	S str_col[3]	= {CRED, CWHT, CBLU};

	C bl1[3]		=   ".|\0";
	C bl2[3]		=   "::\0";
	C str_1[6]		=   ":::::\0";
	C str_2[6]		=   "MYDAK\0";
	C str_3[6]		=   " love\0";
	C str_4[6]		=   " you \0";
	C str_0[6]		=	"pain \0";

	blnk[0] = bl1; blnk[1] = bl2;
	str[0] = str_1; str[1] = str_2; str[2] = str_3; str[3] = str_4, str[4] = str_0;

    getcwd(cur_dir, SZ(cur_dir));                                               //< if /bin doesn't exist
    if (!dir_exists(strcat(cur_dir, "/bin/")));
         mkdir(cur_dir, S_IRUSR | S_IWUSR | S_IXUSR);


	db = 	fopen("bin/db.dat", "w+b");
	idx = 	fopen("bin/idx.dat", "w+b");

	par = &p;
	// heart_par = &heart_par_;

	fwrite(par, SZ(pParams), 1, idx);

	// O("%d len\n", len);
	// R;

	/*  if you changed settings ^ don't forget to modify cycles' params	 */

	for (i = 0; i < 2; i++){										//< background character
		for (j = 0; j < len; j++) {									//< background colour
			// O("im here!\n");
			for (k = 0; k < len; k++){								//< heart colour
				if (!k && !j)
					k++;
				for (l = 0; l < 2; l++) {							//< blink style
					// m = l;										//< blink colour
						for (n = 0; n < 5; n++) {					//< string style

							for (o = 0; o < 3; o++) { 				//< string colour
								addr = ftell(db);

								par_str_col = (!n) ? palette[k] : str_col[o];
								// heart_par = fill_heart(db, palette[j], bck_chr[i], palette[k], blnk[l], blnk_col[l], str[n], str_col[o]);
								fill_heart(db, palette[j], bck_chr[i], palette[k], blnk[l], blnk_col[l], str[n], par_str_col);
								// par->max_len = MAX(par->max_len, heart_par->max_len);
								// par->max_line = MAX(par->max_line, heart_par->max_line);

								par->amount++;
								fwrite(&addr, SZ(I), 1, idx);
							}	
						}
				}
				// O("%d  \t", k);
			}
			if (!(j%100)) {
				O("%d \tin\n", (j + 1)* len * 12);

			}
		}
		O("HALF DONE\n");
	}
	
    // for (i = 0; i < len; i++)
        // free(palette[i]);
    // free(palette);


    O("ALL FINE in making db && idx\n");
	rewind(idx);
	fwrite(par, SZ(pParams), 1, idx);
	fclose(db);
	fclose(idx);
}