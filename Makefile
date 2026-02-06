CC = gcc
RM = rm -rf
MD = mkdir -p
EXEC +=				\
ReadImage			\
ConsImage			\
WriteRGBAdditiveCircle24bImage	\
WriteWhiteNoiseImage		\
WriteMovingCheckerImage		\
WriteRGBAdditiveCircle8bImage \
ConsAnimation

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
	@$(MAKE) --no-print-directory MODE=P1 all

obj:
	@$(MAKE) --no-print-directory MODE=P2 all

dynamic:
	@$(MAKE) --no-print-directory MODE=PD all

static:
	@$(MAKE) --no-print-directory MODE=PS all

.PHONY: all
all: $(EXEC)

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
%: %.c
	@echo Simple compilation of programs
	$(CC) $< -o $@ -DPROG1 $(CFLAGS)
else ifeq ($(MODE), P2)
%: %.c libImagefile.o
	@echo Compile with obj lib
	$(CC) $< libImagefile.o -o $@ -DPROG2 $(CFLAGS)
else ifeq ($(MODE), PD)
%: %.c libImagefile.so
	@echo Compile the dynamique library
	$(CC) $< -o $@ -DPROG3 $(CFLAGS) -L. -lImagefile -Wl,-rpath=./
else ifeq ($(MODE), PS)
%: %.c libImagefile.a
	@echo Compile the static library
	$(CC) $< -o $@ -L. -lImagefile -DPROG4 $(CFLAGS)
else
	@echo ERROR
endif

.PHONY: play_video
play_video: $(VIDEO_NAME)
	mpv $(VIDEO_NAME) --loop-file=yes

.PHONY: create_gif
create_gif: $(VIDEO_NAME) | $(EXAMPLE_DIR)
	ffmpeg -i $(VIDEO_NAME) -vf "fps=15,scale=500:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" $(EXAMPLE_DIR)/example.gif

$(EXAMPLE_DIR):
	$(MD) $(EXAMPLE_DIR)

.PHONY: create_video
create_video: $(VIDEO_NAME)


$(VIDEO_NAME): $(PICT_DIR)/$(PICT_SAMPLE)
	ffmpeg -i $(PICT_DIR)/$(PICT_NAME)_%03d.ppm -r 60 $(VIDEO_NAME)

$(PICT_DIR)/$(PICT_SAMPLE): $(PROG)
	./$(PROG)

$(PROG): $(PROG).c
	$(CC) $(PROG).c -o $(PROG) -DPROG1 $(CFLAGS)

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) *.a
	$(RM) *.so
	$(RM) *.mp4
	$(RM) $(EXEC)
	$(RM) $(PICT_DIR)/*
