all: 
	gcc -o img_pop src/main.c src/draw.c src/kbhit.c src/square.c src/dat.c src/col_palette.c

heart:
	./img_pop

clean:
	rm bin/db.dat bin/idx.dat 