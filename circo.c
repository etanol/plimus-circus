/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                            I N F O R M � T I C A                            |
 |                                G R � F I C A                                |
 |                                                                             |
 |                                                                             |
 |       Alumnos : Isaac Jurado Peinado        (etanol@telefonica.net)         |
 |                 Esteban Mart�nez Tristancho (estebanmartinez@ono.com)       |
 |       Estudios: Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)         |
 |       Curso   : 2003/2004                                                   |
 |       Facultad: Universitat de les Illes Balears (UIB)                      |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * circo.c
 *
 * Programa principal que queda trivializado ya que los m�dulos tambi�n
 * realizan inicializaci�n de los elementos que vayan a manipular.
 *
 * $Id$
 */

#define FICHERO_CONFIG "medidas_circo.cfg"
#ifdef THIS_IS_UNIX
#define TEXTURA_SUELO_EXTERIOR "imagen/cesped1.tga"
#else
#define TEXTURA_SUELO_EXTERIOR "imagen\\cesped1.tga"
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Plimus Circus");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	/* Ahora que ya tenemos inicializado OpenGL, cargamos las texturas */
	texes.suelo_exterior = cargar_textura(TEXTURA_SUELO_EXTERIOR);
	/* Llamamos a los m�dulos */
	init_interaccion();
	init_escena(&cfg, &texes);
	/* Dejamos que GLUT trabaje por nosotros */
	glutMainLoop();
	return 0;
}
