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

practica := circo test_pieza
etapas   := etapa1 etapa2 etapa3
ejemplos := robot checker
piezas   := carpa.c gradas.c

ejemplos  := $(patsubst %,ejemplos/%,$(ejemplos))
BINFILES  := $(etapas) $(ejemplos) $(practica)
DISTFILES := *.c *.h $(practica)


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

circo: circo.o escena.o interaccion.o $(piezas:%.c=%.o)
	$(mk_bingl)

test_pieza: test_pieza.o $(piezas:%.c=%.o)
	$(mk_bingl)

#
# Reglas específicas para los módulos
#
interaccion.o: interaccion.c interaccion.h camaras.h
	$(mk_obj)
escena.o: escena.c escena.h
	$(mk_obj)
carpa.o: carpa.c piezas.h
	$(mk_obj)
gradas.o: gradas.c piezas.h
	$(mk_obj)

.PHONY: clean dist distclean
clean:
	-rm -f $(wildcard *.o ejemplos/*.o $(BINFILES) gmon.out ejemplos/gmon.out)

dist: $(practica)
	@test -d IG1 || mkdir IG1; \
	cp -v $(DISTFILES) IG1; rm IG1/template.h; \
	for i in IG1/*.c; do \
		mv -v $$i $${i%.c}.cpp; \
	done; \
	for i in IG1/*; do \
		perl -pi -e's/\n/\r\n/g' $$i; \
	done; \
	mv -v IG1/circo IG1/circo.linux; \
	mv -v IG1/test_pieza IG1/test_pieza.linux; \
	zip -r IG1.zip IG1

distclean: clean
	-rm -rf IG1 IG1.zip IG1.tar.gz

