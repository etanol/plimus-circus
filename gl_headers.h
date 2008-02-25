/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado          [C2H5OH]                     |
 |                  Esteban Martínez Tristancho   [Tito Houzy]                 |
 |      Asignatura: Informática Gráfica I                                      |
 |      Profesor  : Jose María Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingeniería Técnica en Informática de Gestión (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * gl_headers.h
 *
 * Fichero para incluír todas las cabeceras de OpenGL necesarias, dependiendo
 * de la plataforma.  En vistas de la velocidad de compilación de las máquinas
 * nuevas, no merece la pena el esfuerzo de minimizar el número de cabeceras a
 * incluír.
 *
 * Así pues, los demás ficheros únicamente tendrán que incluír este cuando
 * necesiten invocar las funciones de OpenGL y GLUT.
 */
#ifndef _GL_HEADERS_H_
#define _GL_HEADERS_H_


#ifdef __APPLE__

/*
 * En Mac OSX, OpenGL y GLUT son frameworks separados.  Esto también implica
 * que los flags de linkado son distintos (ver Makefile).
 */
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#endif /* __APPLE__ */


#endif /* _GL_HEADERS_H_ */
