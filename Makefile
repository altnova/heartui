all: 
	gcc -o img_pop src/main.c src/draw.c src/kbhit.c src/square.c src/dat.c src/col_palette.c src/rows.c

heart:
	./img_pop

db:
	gcc -o database src/make_db.c src/dat.c src/square.c src/col_palette.c && ./database 

dbf: 
	gcc -o database src/make_db.c src/dat.c src/square.c src/col_palette.c && ./database f

clean:
	rm bin/db.dat && rm bin/idx.dat && rm ./img_pop 