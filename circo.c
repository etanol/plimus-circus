/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado        (etanol@telefonica.net)        |
 |                  Esteban Martínez Tristancho (estebanmartinez@ono.com)      |
 |      Asignatura: Informática Gráfica I                                      |
 |      Profesor  : Jose María Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingeniería Técnica en Informática de Gestión (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * circo.c
 *
 * Programa principal que queda trivializado ya que los módulos también
 * realizan inicialización de los elementos que vayan a manipular.
 *
 * $Id$
 */

#define FICHERO_CONFIG "medidas_circo.cfg"
#ifdef THIS_IS_UNIX
#define TEXTURA_SUELO_EXTERIOR "imagen/cesped1.tga"
#define TEXTURA_SUELO_INTERIOR "imagen/arena1.tga"
#define TEXTURA_GRADA "imagen/madera1.tga"
#else
#define TEXTURA_SUELO_EXTERIOR "imagen\\cesped1.tga"
#define TEXTURA_SUELO_INTERIOR "imagen\\arena1.tga"
#define TEXTURA_GRADA "imagen\\madera1.tga"
#endif

#include <GL/gl.h>
#include <GL/glut.h>

#include "config.h"
#include "escena.h"
#include "interaccion.h"
#include "textura.h"

int main(int argc, char **argv)
{
	struct config cfg;
	struct texturas texes;

	leer_config(FICHERO_CONFIG, &cfg);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Plimus Circus");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	/* Ahora que ya tenemos inicializado OpenGL, cargamos las texturas */
	texes.suelo_exterior = cargar_textura(TEXTURA_SUELO_EXTERIOR);
	texes.suelo_interior = cargar_textura(TEXTURA_SUELO_INTERIOR);
	texes.grada          = cargar_textura(TEXTURA_GRADA);
	/* Llamamos a los módulos */
	init_interaccion();
	init_escena(&cfg, &texes);
	/* Dejamos que GLUT trabaje por nosotros */
	glutMainLoop();
	return 0;
}
