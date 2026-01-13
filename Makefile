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


COMPMODE ?= P1


.PHONY: header obj static dynamic play_video create_video clean

header:
	@$(MAKE) --no-print-directory MODE=P1 writeimage readimage

obj:
	@$(MAKE) --no-print-directory MODE=P2 writeimage readimage

dynamic:
	@$(MAKE) --no-print-directory MODE=PD writeimage readimage

static:
	@$(MAKE) --no-print-directory MODE=PS writeimage readimage



libImagefile.o: libImagefile.h
	$(CC) -DLIBIMAGEFILE_IMPLEMENTATION -x c -c $<

libImagefile.so: Imagefile.c
	$(CC) $(CFLAGS) -DPROG3 -fPIC -shared -o $@ $<


libImagefile.a: Imagefile.o
	ar -cvq $@ $<
	@ar -t $@

Imagefile.o: Imagefile.c
	$(CC) $(CFLAGS) -c $<


ifeq ($(MODE), P1)
writeimage: writeimage.c
	@echo Simple compilation of programs
	$(CC) $< -o $@ -DPROG1 $(CFLAGS)
else ifeq ($(MODE), P2)
writeimage: writeimage.c libImagefile.o
	@echo Compile with obj lib
	$(CC) $< libImagefile.o -o $@ -DPROG2 $(CFLAGS)
else ifeq ($(MODE), PD)
writeimage: writeimage.c libImagefile.so
	@echo Compile the dynamique library
	$(CC) $< -o $@ -DPROG3 $(CFLAGS) -L. -lImagefile -Wl,-rpath=./
else ifeq ($(MODE), PS)
writeimage: writeimage.c libImagefile.a
	@echo Compile the static library
	$(CC) $< -o $@ -L. -lImagefile -DPROG4 $(CFLAGS)
else
	@echo ERROR
endif

ifeq ($(MODE), P1)
readimage: readimage.c
	@echo Simple compilation of programs
	$(CC) $< -o $@ -DPROG1 $(CFLAGS)
else ifeq ($(MODE), P2)
readimage: readimage.c
	@echo Compile with obj lib
	$(CC) $< libImagefile.o -o $@ -DPROG2 $(CFLAGS)
else ifeq ($(MODE), PD)
readimage: readimage.c
	@echo Compile the dynamique library
	$(CC) $< -o $@ -DPROG3 $(CFLAGS) -L. -lImagefile -Wl,-rpath=./
else ifeq ($(MODE), PS)
readimage: readimage.c
	@echo Compile the static library
	$(CC) $< -o $@ -L. -lImagefile -DPROG4 $(CFLAGS)
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
	$(RM) readimage
	$(RM) writeimage
	$(RM) $(PICT_DIR)/*
