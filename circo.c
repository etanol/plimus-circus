/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado        (etanol@telefonica.net)        |
 |                  Esteban Mart�nez Tristancho (estebanmartinez@ono.com)      |
 |      Asignatura: Inform�tica Gr�fica I                                      |
 |      Profesor  : Jose Mar�a Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
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

#define FICHERO_CONFIG "circo.cfg"

#include <stdio.h>
#include <GL/glut.h>

#include "config.h"
#include "escena.h"
#include "interaccion.h"

int main(int argc, char **argv)
{
	config_t cfg;
	FILE *test;

	glutInit(&argc, argv);

	/* Aqu� ofrecemos la posibilidad de cargar un fichero de configuraci�n
	 * distinto al fichero por defecto si as� lo indicamos en la l�nea de
	 * comandos (y si el fichero es accesible, obviamente). */
	if (argc > 1) {
		test = fopen(argv[1], "r");
		if (test == NULL) {
			printf("El fichero %s no se pudo abrir, utilizando \
					configuraci�n por defecto.\n", argv[1]);
			cfg = leer_config(FICHERO_CONFIG);
		} else {
			fclose(test);
			cfg = leer_config(argv[1]);
		}
	} else {
		cfg = leer_config(FICHERO_CONFIG);
	}

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(valor_entero(cfg, v_width),
			valor_entero(cfg, v_height));
	glutInitWindowPosition(valor_entero(cfg, v_posx),
			valor_entero(cfg, v_posy));
	glutCreateWindow(valor_cadena(cfg, v_title));
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_CULL_FACE);
	glAlphaFunc(GL_GREATER, 0.4);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	/* Llamamos a los m�dulos */
	init_interaccion(cfg);
	init_escena(cfg);

	/* Dejamos que GLUT trabaje por nosotros */
	glutMainLoop();
	return 0;
}
