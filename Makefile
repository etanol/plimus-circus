#  __^__                                                                  __^__
# ( ___ )----------------------------------------------------------------( ___ )
#  | / |                                                                  | \ |
#  | / |                      I N F O R M � T I C A                       | \ |
#  | / |                          G R � F I C A                           | \ |
#  | / |                                                                  | \ |
#  | / |                                                                  | \ |
#  | / | Alumnos : Esteban Mart�nez Tristancho (estebanmartinez@ono.com)  | \ |
#  | / |           Isaac Jurado Peinado (etanol@telefonica.net)           | \ |
#  | / | Estudios: Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)    | \ |
#  | / | Curso   : 2003/2004                                              | \ |
#  | / | Facultad: Universitat de les Illes Balears (UIB)                 | \ |
#  |___|                                                                  |___|
# (_____)----------------------------------------------------------------(_____)

#
# Makefile global
#
# $Id$
#

etapas   := etapa1 etapa2
ejemplos := robot

ejemplos := $(patsubst %,ejemplos/%,$(ejemplos))
BINFILES := $(etapas) $(ejemplos)


CFLAGS := -pipe -Wall 
ifeq ($(debug),yes)
CFLAGS += -O0 -pg -g
STRIP  := 
else
CFLAGS += -O2 -fomit-frame-pointer -Wl,-s
STRIP  := -Wl,-s 
endif

join_obj = $(CC) $(CFLAGS) -Wl,-r -o $@ $^
mk_obj   = $(CC) $(CFLAGS) -c -o $@ $^
mk_bingl = $(CC) $(CFLAGS) $(STRIP) -lGL -lGLU -lglut -o $@ $^

all: etapas
etapas: $(etapas)
ejemplos: $(ejemplos)

$(etapas): %: %.c
	$(mk_bingl)

$(ejemplos): %: %.c
	$(mk_bingl)

.PHONY: clean 
clean:
	-rm -f $(wildcard *.o ejemplos/*.o $(BINFILES) gmon.out ejemplos/gmon.out)
