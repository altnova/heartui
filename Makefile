all: 
	gcc -o draw_it src/main.c src/draw.c src/kbhit.c src/square.c src/dat.c

go:
	./draw_it

clean:
	rm bin/db.dat bin/idx.dat 