#  __^__                                                                  __^__
# ( ___ )----------------------------------------------------------------( ___ )
#  | / |                                                                  | \ |
#  | / |                      I N F O R M Á T I C A                       | \ |
#  | / |                          G R Á F I C A                           | \ |
#  | / |                                                                  | \ |
#  | / |                                                                  | \ |
#  | / | Alumnos : Isaac Jurado Peinado        (etanol@telefonica.net)    | \ |
#  | / |           Esteban Martínez Tristancho (estebanmartinez@ono.com)  | \ |
#  | / | Estudios: Ingeniería Técnica en Informática de Gestión (TIG2)    | \ |
#  | / | Curso   : 2003/2004                                              | \ |
#  | / | Facultad: Universitat de les Illes Balears (UIB)                 | \ |
#  |___|                                                                  |___|
# (_____)----------------------------------------------------------------(_____)

#
# Makefile global
#
# $Id$
#

practica := circo
etapas   := etapa1 etapa2 etapa3
ejemplos := robot checker

ejemplos := $(patsubst %,ejemplos/%,$(ejemplos))
BINFILES := $(etapas) $(ejemplos) $(practica)


CFLAGS := -pipe -Wall 
ifeq ($(debug),yes)
CFLAGS += -O0 -pg -g
STRIP  := 
else
CFLAGS += -O2 -fomit-frame-pointer 
STRIP  := -Wl,-s 
endif

join_obj = $(CC) $(CFLAGS) -Wl,-r -o $@ $^
mk_obj   = $(CC) $(CFLAGS) -c -o $@ $(filter-out %.h,$^)
mk_bingl = $(CC) $(CFLAGS) $(STRIP) -lGL -lGLU -lglut -o $@ $(filter-out %.h,$^)

all: $(practica)
etapas: $(etapas)
ejemplos: $(ejemplos)

$(etapas): %: %.c
	$(mk_bingl)

$(ejemplos): %: %.c
	$(mk_bingl)

$(practica): circo.o escena.o interaccion.o
	$(mk_bingl)

interaccion.o: interaccion.c camaras.h
	$(mk_obj)

.PHONY: clean 
clean:
	-rm -f $(wildcard *.o ejemplos/*.o $(BINFILES) gmon.out ejemplos/gmon.out)
