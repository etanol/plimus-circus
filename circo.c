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
 * circo.c
 *
 * Programa principal que queda trivializado ya que los módulos también
 * realizan inicialización de los elementos que vayan a manipular.
 *
 * $Id$
 */

#define FICHERO_CONFIG "circo.cfg"

#include <stdio.h>
#include <GL/glut.h>

#include "config.h"
#include "escena.h"
#include "interaccion.h"

int
main (int argc, char **argv)
{
        config_t cfg;
        FILE    *test;

        glutInit (&argc, argv);

        /* Aquí ofrecemos la posibilidad de cargar un fichero de configuración
         * distinto al fichero por defecto si así lo indicamos en la línea de
         * comandos (y si el fichero es accesible, obviamente). */
        if (argc > 1) {
                test = fopen (argv[1], "r");
                if (test == NULL) {
                        printf ("El fichero %s no se pudo abrir, utilizando "
                                "configuración por defecto.\n", argv[1]);
                        cfg = leer_config (FICHERO_CONFIG);
                } else {
                        fclose (test);
                        cfg = leer_config (argv[1]);
                }
        } else {
                cfg = leer_config (FICHERO_CONFIG);
        }

        glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize (valor_entero (cfg, v_width),
                            valor_entero (cfg, v_height));
        glutInitWindowPosition (valor_entero (cfg, v_posx),
                                valor_entero (cfg, v_posy));
        glutCreateWindow (valor_cadena (cfg, v_title));
        glClearColor (0.0, 0.0, 0.0, 1.0);
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_TEXTURE_2D);
        glEnable (GL_ALPHA_TEST);
        glEnable (GL_CULL_FACE);
        glAlphaFunc (GL_GREATER, 0.4);
        glCullFace (GL_BACK);
        glFrontFace (GL_CW);
        /* Llamamos a los módulos */
        init_interaccion (cfg);
        init_escena (cfg);

        /* Dejamos que GLUT trabaje por nosotros */
        glutMainLoop ();
        return 0;
}
