CC = gcc
RM = rm -rf

CFLAGS +=	\
-Wextra		\
-Wall   	\


PICT_DIR = stock
PICT_SAMPLE = output_000.ppm
PICT_NAME = output
VIDEO_NAME = video.mp4
EXEC = main

.PHONY: play_video create_video prog1 prog2 prog_dyn prog_static clean

prog1: main.c
	$(CC) main.c -o $(EXEC) -DPROG1 $(CFLAGS)



libImagefile.o:
	$(CC) -DLIBIMAGEFILE_IMPLEMENTATION -x c -c libImagefile.h

prog2: libImagefile.o
	$(CC) main.c libImagefile.o -o $(EXEC) -DPROG2 $(CFLAGS)



# Pour lancer le $(EXEC) si pas "-Wl,-rpath=./"
# LD_LIBRARY_PATH="./" ./main
libImagefile.so: Imagefile.c
	$(CC) $(CFLAGS) -DPROG3 -fPIC -shared -o libImagefile.so Imagefile.c

prog_dyn: main.c | libImagefile.so
	$(CC) main.c -o $(EXEC) $(CFLAGS) -L. -lImagefile -Wl,-rpath=./



libImagefile.a: Imagefile.c
	$(CC) $(CFLAGS) -c Imagefile.c
	ar -cvq libImagefile.a Imagefile.o
	@ar -t libImagefile.a

prog_static: main.c | libImagefile.a
	$(CC) main.c -o $(EXEC) -L. -lImagefile $(CFLAGS)



play_video: $(VIDEO_NAME)
	mpv $(VIDEO_NAME) --loop-file=yes

create_video: $(VIDEO_NAME)


$(VIDEO_NAME): $(PICT_DIR)/$(PICT_SAMPLE)
	ffmpeg -i $(PICT_DIR)/$(PICT_NAME)_%03d.ppm -r 60 $(VIDEO_NAME)

$(PICT_DIR)/$(PICT_SAMPLE): $(EXEC)
	./main

$(EXEC): main.c
	$(CC) main.c -o $(EXEC) -DPROG1 $(CFLAGS)

clean:
	$(RM) *.o
	$(RM) *.a
	$(RM) *.so
	$(RM) *.mp4
	$(RM) main
	$(RM) $(PICT_DIR)/*
