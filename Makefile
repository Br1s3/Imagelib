CC = gcc
RM = rm -rf

CFLAGS +=	\
-Wextra		\
-Wall   	\

.PHONY: clean static dyn

static: main.c | libImagefile.a
	$(CC) main.c -o main -L. -lImagefile $(CFLAGS)

libImagefile.a: Imagefile.c
	$(CC) $(CFLAGS) -c Imagefile.c
	ar -cvq libImagefile.a Imagefile.o
	@ar -t libImagefile.a


# Pour lancer le main si pas "-Wl,-rpath=./"
# LD_LIBRARY_PATH="./" ./main

dyn: main.c | libImagefile.so
	$(CC) main.c -o main $(CFLAGS) -L. -lImagefile -Wl,-rpath=./


libImagefile.so: Imagefile.c
	$(CC) $(CFLAGS) -fPIC -shared -o libImagefile.so Imagefile.c

clean:
	$(RM) *.o
	$(RM) *.a
	$(RM) *.so
	$(RM) main
	$(RM) stock/*
