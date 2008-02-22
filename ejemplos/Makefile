#
# Makefile para los ejemplos
#

binarios := $(patsubst %.c,%,$(wildcard *.c))

CFLAGS := -pipe -Wall -I..
ifeq ($(debug),yes)
CFLAGS += -O0 -pg -g
STRIP  :=
else
CFLAGS += -O2 -fomit-frame-pointer
STRIP  := -Wl,-s
endif


all: $(binarios)

ifeq ($(shell uname -s),Darwin)
$(binarios): %: %.c
	$(CC) $(CFLAGS) $(STRIP) -framework OpenGL -frameowrk GLUT -lobjc -lmx -o $@ $^
else
$(binarios): %: %.c
	$(CC) $(CFLAGS) $(STRIP) -lGL -lGLU -lglut -o $@ $^
endif

.PHONY: clean
clean:
	@-rm -fv $(binarios)

