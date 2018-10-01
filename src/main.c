#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "draw.h"
#include "dat.h"



I main()
{
	srand(time(NULL));

	if (access("../bin/db.dat", F_OK) == -1) 
		make_db();

	draw_heart();

	R0;
}