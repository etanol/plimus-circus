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
piezas   := carpa.c gradas.c

BINFILES   := $(etapas) $(practica)
WDISTFILES := Makefile README.* *.c *.h ChangeLog


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

$(etapas): %: %.c
	$(mk_bingl)

circo: circo.o escena.o interaccion.o config.o $(piezas:%.c=%.o)
	$(mk_bingl)

test_pieza: test_pieza.o config.o $(piezas:%.c=%.o)
	$(mk_bingl)

#
# Reglas específicas para los módulos
#
interaccion.o: interaccion.c interaccion.h camaras.h
	$(mk_obj)
escena.o: escena.c escena.h config.h
	$(mk_obj)
carpa.o: carpa.c piezas.h config.h
	$(mk_obj)
gradas.o: gradas.c piezas.h config.h
	$(mk_obj)
config.o: config.c config.h
	$(mk_obj)

.PHONY: clean wdist wdistclean changelog
clean:
	@-rm -fv *.o ejemplos/*.o $(BINFILES) gmon.out ejemplos/gmon.out ChangeLog*

wdist: changelog
	@test -d IG1 || mkdir IG1; \
	cp -v $(WDISTFILES) IG1; rm IG1/template.h; \
	for i in IG1/*.c; do \
		mv -v $$i $${i%.c}.cpp; \
	done; \
	for i in IG1/*; do \
		perl -pi -e's/\n/\r\n/g' $$i; \
	done; \
	perl -pi -e's/\.c([^a-z])/.cpp$$1/g' IG1/Makefile; \
	zip -r IG1.zip IG1

changelog:
	@cvs2cl -S -P -b -T --show-dead

wdistclean: 
	@-rm -rf IG1 IG1.zip ChangeLog*

