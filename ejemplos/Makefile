#
# Makefile para los ejemplos
#
# $Id$
#

binarios := $(patsubst %.c,%,$(wildcard *.c))

CFLAGS := -pipe -Wall 
ifeq ($(debug),yes)
CFLAGS += -O0 -pg -g
STRIP  := 
else
CFLAGS += -O2 -fomit-frame-pointer 
STRIP  := -Wl,-s 
endif


all: $(binarios)

$(binarios): %: %.c
	$(CC) $(CFLAGS) $(STRIP) -lGL -lGLU -lglut -o $@ $^

.PHONY: clean
clean:
	@-rm -fv $(binarios)

