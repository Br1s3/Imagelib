CC = gcc
RM = rm -rf

CFLAGS +=	\
-Wextra		\
-Wall   	\

.PHONY: prog1 prog2 prog_dyn prog_static clean

prog1: main.c
	$(CC) main.c -o main -DPROG1 $(CFLAGS)



libImagefile.o:
	$(CC) -DLIBIMAGEFILE_IMPLEMENTATION -x c -c libImagefile.h

prog2: libImagefile.o
	$(CC) main.c libImagefile.o -o main -DPROG2 $(CFLAGS)



# Pour lancer le main si pas "-Wl,-rpath=./"
# LD_LIBRARY_PATH="./" ./main
libImagefile.so: Imagefile.c
	$(CC) $(CFLAGS) -DPROG3 -fPIC -shared -o libImagefile.so Imagefile.c

prog_dyn: main.c | libImagefile.so
	$(CC) main.c -o main $(CFLAGS) -L. -lImagefile -Wl,-rpath=./



libImagefile.a: Imagefile.c
	$(CC) $(CFLAGS) -c Imagefile.c
	ar -cvq libImagefile.a Imagefile.o
	@ar -t libImagefile.a

prog_static: main.c | libImagefile.a
	$(CC) main.c -o main -L. -lImagefile $(CFLAGS)



clean:
	$(RM) *.o
	$(RM) *.a
	$(RM) *.so
	$(RM) main
	$(RM) stock/*
