#  __^__                                                                  __^__
# ( ___ )----------------------------------------------------------------( ___ )
#  | / |                                                                  | \ |
#  | / |                    P L I M U S   C I R C U S                     | \ |
#  | / |                                                                  | \ |
#  | / | Alumnos   : Isaac Jurado Peinado          [C2H5OH]               | \ |
#  | / |             Esteban Martínez Tristancho   [Tito Houzy]           | \ |
#  | / | Asignatura: Informática Gráfica I                                | \ |
#  | / | Profesor  : Jose María Buades Rubio                              | \ |
#  | / | Curso     : 2003/2004                                            | \ |
#  | / | Estudios  : Ingeniería Técnica en Informática de Gestión (TIG2)  | \ |
#  | / | Facultad  : Universitat de les Illes Balears (UIB)               | \ |
#  |___|                                                                  |___|
# (_____)----------------------------------------------------------------(_____)

#
# Makefile global
#

CC  ?= gcc
HCC ?= i586-mingw32msvc-gcc

ifdef debug
CFLAGS  := -pipe -O0 -pg -g
LDFLAGS := 
else
CFLAGS  := -pipe -O2 -fomit-frame-pointer 
LDFLAGS := -Wl,-s,-O1
endif

ifeq ($(shell uname -s),Darwin)
mk_bingl  = $(CC) $(CFLAGS) $(LDFLAGS) -framework OpenGL -framework GLUT -lobjc -lmx -o $@ $^
Hmk_bingl = false
else
mk_bingl  = $(CC)  $(CFLAGS) $(LDFLAGS) -lGL -lGLU -lglut -o $@ $^
Hmk_bingl = $(HCC) $(CFLAGS) $(LDFLAGS) -L$(mingw_glut) -o $@ $^ -mwindows -lopengl32 -lglu32 -lglut32 
endif

# Abreviaturas
mingw_glut := $(shell pwd)/GLUTMingw32
tests      := test_pieza test_config
etapas     := etapa1 etapa2 etapa3
piezas     := carpa gradas suelo complementos
conf       := config conf_keys
circo_deps := circo escena textura interaccion $(conf) $(piezas)

# Aliases
.PHONY: all etapas test hase hetapas htest clean dclean dist hdist cl help

# Reglas importantes
all   : circo
etapas: $(etapas)
test  : $(tests)

circo: $(circo_deps:=.o)
	$(mk_bingl)

$(etapas): %: %.o
	$(mk_bingl)

test_pieza: test_pieza.o textura.o $(conf:=.o) $(piezas:=.o)
	$(mk_bingl)

test_config: test_config.o $(conf:=.o)
	$(CC) $(CFLAGS) $(STRIP) -o $@ $^

#
# Soporte para Hasefroch (MinGW)
#
hase   : circo.exe
hetapas: $(etapas:=.exe)
htest  : $(tests:=.exe)

circo.exe: $(circo_deps:=.obj)
	$(Hmk_bingl)

$(etapas:=.exe): %.exe: %.obj
	$(Hmk_bingl)

test_pieza.exe: test_pieza.obj textura.obj textura.obj $(conf:=.obj) $(piezas:=.obj)
	$(Hmk_bingl)

test_config.exe: test_config.obj $(conf:=.obj)
	$(HCC) $(CFLAGS) $(STRIP) -o $@ $^

# Reglas genéricas
%.o: %.c
	$(CC) -Wall $(CFLAGS) -c $<

%.obj: %.c
	$(HCC) $(CFLAGS) -I$(mingw_glut) -c -o $@ $<

# Limpieza
clean:
	@-rm -fv *.o *.obj ejemplos/*.o gmon.out ejemplos/gmon.out ChangeLog CommitLog

dclean: clean
	@-rm -fv *.exe circo $(tests) $(etapas) *.zip

dist: circo CommitLog ChangeLog
	@mkdir plimus_circus; \
	cp -vl circo CommitLog ChangeLog circo.cfg plimus_circus; \
	cp -rvl imagen plimus_circus; \
	rm -rf plimus_circus/imagen/CVS; \
	zip -rm9 pcircus.zip plimus_circus

hdist: circo.exe CommitLog ChangeLog
	@mkdir plimus_circus_win32; \
	cp -vl circo.exe CommitLog ChangeLog circo.cfg plimus_circus_win32; \
	cp -rvl imagen plimus_circus_win32; \
	rm -rf plimus_circus_win32/imagen/CVS; \
	cp -vl $(mingw_glut)/glut32.dll plimus_circus_win32; \
	zip -rm9 pcircus_win32.zip plimus_circus_win32

cl: ChangeLog CommitLog
ChangeLog:
	@hg log --style=changelog >$@

CommitLog:
	@hg log --style=./simple.hgstyle | expand -t 4 >$@

#
# Ayuda
#
help:
	@echo 'Reglas para compilar:'; \
	echo  '	all     - Binario para UNIX [default].'; \
	echo  '	test    - Programas de prueba.'; \
	echo  '	etapas  - Ejercicios iniciales.'; \
	echo  '	hase    - Binario para Hasefroch (win32).'; \
	echo  '	htest   - Programas de prueba (win32).'; \
	echo  '	hetapas - Ejercicios iniciales (win32).'; \
	echo  ''; \
	echo  'Reglas de mantenimiento:'; \
	echo  '	dist   - Empaqueta el binario UNIX.'; \
	echo  '	hdist  - Empaqueta el binario Hasefroch.'; \
	echo  '	clean  - Borra los ficheros objeto.'; \
	echo  '	dclean - Borra binarios y paquetes.'; \
	echo  '	cl     - Genera el ChangeLog'; \

#
# Dependencias automáticas
#
carpa.o       : carpa.c piezas.h config.h conf_keys.h textura.h
circo.o       : circo.c config.h conf_keys.h escena.h interaccion.h
complementos.o: complementos.c piezas.h config.h conf_keys.h textura.h
config.o      : config.c config.h conf_keys.h
escena.o      : escena.c config.h conf_keys.h interaccion.h textura.h piezas.h
gradas.o      : gradas.c piezas.h config.h conf_keys.h textura.h
interaccion.o : interaccion.c config.h conf_keys.h camaras.h escena.h
suelo.o       : suelo.c piezas.h config.h conf_keys.h textura.h
test_config.o : test_config.c config.h conf_keys.h
test_pieza.o  : test_pieza.c config.h conf_keys.h piezas.h
textura.o     : textura.c config.h conf_keys.h

carpa.obj       : carpa.c piezas.h config.h conf_keys.h textura.h
circo.obj       : circo.c config.h conf_keys.h escena.h interaccion.h
complementos.obj: complementos.c piezas.h config.h conf_keys.h textura.h
config.obj      : config.c config.h conf_keys.h
escena.obj      : escena.c config.h conf_keys.h interaccion.h textura.h piezas.h
gradas.obj      : gradas.c piezas.h config.h conf_keys.h textura.h
interaccion.obj : interaccion.c config.h conf_keys.h camaras.h escena.h
suelo.obj       : suelo.c piezas.h config.h conf_keys.h textura.h
test_config.obj : test_config.c config.h conf_keys.h
test_pieza.obj  : test_pieza.c config.h conf_keys.h piezas.h
textura.obj     : textura.c config.h conf_keys.h

