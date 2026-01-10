CC = gcc
RM = rm -rf
MD = mkdir -p

CFLAGS +=	\
-Wextra		\
-Wall   	\


PICT_DIR = stock
PICT_SAMPLE = output_000.ppm
PICT_NAME = output
EXAMPLE_DIR = picture
VIDEO_NAME = video.mp4

CPROG += \
writeimage \
readimage

CSRC += \
writeimage.c \
readimage.c


COMPMODE ?= P1


.PHONY: prog1 prog2 prog_dyn prog_static play_video create_video clean

prog1: writeimage readimage

prog2: writeimage readimage | libImagefile.o

prog_dyn: writeimage readimage | libImagefile.so

prog_static: writeimage readimage | libImagefile.a


libImagefile.o: libImagefile.h
	$(CC) -DLIBIMAGEFILE_IMPLEMENTATION -x c -c libImagefile.h

libImagefile.so: Imagefile.c
	$(CC) $(CFLAGS) -DPROG3 -fPIC -shared -o libImagefile.so Imagefile.c

libImagefile.a: Imagefile.c
	$(CC) $(CFLAGS) -c Imagefile.c
	ar -cvq libImagefile.a Imagefile.o
	@ar -t libImagefile.a


writeimage: writeimage.c
ifeq ($(COMPMODE), P1)
	@echo Simple compilation of programs
	$(CC) writeimage.c -o writeimage -DPROG1 $(CFLAGS)
else ifeq ($(COMPMODE), P2)
	@echo Compile with obj lib
	$(CC) writeimage.c libImagefile.o -o writeimage -DPROG2 $(CFLAGS)
else ifeq ($(COMPMODE), PD)
	@echo Compile the dynamique library
	$(CC) writeimage.c -o writeimage -DPROG3 $(CFLAGS) -L. -lImagefile -Wl,-rpath=./
else ifeq ($(COMPMODE), PS)
	@echo Compile the static library
	$(CC) writeimage.c -o writeimage -L. -lImagefile -DPROG4 $(CFLAGS)
else
	@echo ERROR
endif

readimage: readimage.c
ifeq ($(COMPMODE), P1)
	@echo Simple compilation of programs
	$(CC) readimage.c -o readimage -DPROG1 $(CFLAGS)
else ifeq ($(COMPMODE), P2)
	@echo Compile with obj lib
	$(CC) readimage.c libImagefile.o -o readimage -DPROG2 $(CFLAGS)
else ifeq ($(COMPMODE), PD)
	@echo Compile the dynamique library
	$(CC) readimage.c -o readimage -DPROG3 $(CFLAGS) -L. -lImagefile -Wl,-rpath=./
else ifeq ($(COMPMODE), PS)
	@echo Compile the static library
	$(CC) readimage.c -o readimage -L. -lImagefile -DPROG4 $(CFLAGS)
else
	@echo ERROR
endif





play_video: $(VIDEO_NAME)
	mpv $(VIDEO_NAME) --loop-file=yes

create_gif: $(VIDEO_NAME) | $(EXAMPLE_DIR)
	ffmpeg -i $(VIDEO_NAME) -vf "fps=15,scale=500:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" $(EXAMPLE_DIR)/example.gif

$(EXAMPLE_DIR):
	$(MD) $(EXAMPLE_DIR)

create_video: $(VIDEO_NAME)


$(VIDEO_NAME): $(PICT_DIR)/$(PICT_SAMPLE)
	ffmpeg -i $(PICT_DIR)/$(PICT_NAME)_%03d.ppm -r 60 $(VIDEO_NAME)

$(PICT_DIR)/$(PICT_SAMPLE): $(PROG)
	./$(PROG)

$(PROG): $(PROG).c
	$(CC) $(PROG).c -o $(PROG) -DPROG1 $(CFLAGS)

clean:
	$(RM) *.o
	$(RM) *.a
	$(RM) *.so
	$(RM) *.mp4
	$(RM) writeimage
	$(RM) readimage
	$(RM) $(PICT_DIR)/*
