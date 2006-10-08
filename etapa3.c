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
 * etapa3.c
 *
 * $Id$
 */

#include <stdlib.h>
#include <GL/glut.h>

/* Tamaño incial de la ventana */
const int W_WIDTH = 500;
const int W_HEIGHT = 500;

/* Variable que indica el ángulo de rotación de los ejes. */
GLfloat fAngulo;

void
Display (void)
{
        /* Borramos la escena */
        glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glPushMatrix ();
        /* glTranslatef (0.0f, 0.0f, -2.5f); */
        glRotatef (fAngulo, 0.0f, 1.0f, 1.0f);
        
        glColor3f (0.0f, 1.0f, 0.0f);
        glutSolidCube (1.0);
        glColor3f (0.0f, 0.0f, 0.0f);
        glutWireCube (1.01);
        
        glPopMatrix ();
        glFlush ();
        glutSwapBuffers ();
}


void
Rota (unsigned char c, int x, int y)
{
        if (c == (char) 27)
                exit (0);
        /* Incrementamos el ángulo */
        fAngulo += 2.0;
        /* Si es mayor que dos pi la decrementamos */
        if (fAngulo > 360)
                fAngulo -= 360;
        /* Indicamos que es necesario repintar la pantalla */
        glutPostRedisplay ();
}


void
Reshape (int ancho, int alto)
{
        int lado, x, y;

        if (ancho < alto) {
                lado = ancho;
                x = 0;
                y = (alto - ancho) / 2;
        } else {
                lado = alto;
                x = (ancho - alto) / 2;
                y = 0;
        }
        glViewport (x, y, lado, lado);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluPerspective (90.0, 1.0, 0.5, 10.0);
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();
        gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, -0.3, 1.0, 0.0);
}


int
main (int argc, char **argv)
{
        /* Inicializamos la librería GLUT */
        glutInit (&argc, argv);

        /* Indicamos como ha de ser la nueva ventana */
        glutInitWindowPosition (100, 100);
        glutInitWindowSize (W_WIDTH, W_HEIGHT);
        glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);

        /* Creamos la nueva ventana */
        glutCreateWindow ("Ventana principal");

        /* Indicamos cuales son las funciones de redibujado e idle */
        glutDisplayFunc (Display);
        glutKeyboardFunc (Rota);
        glutReshapeFunc (Reshape);

        glEnable (GL_DEPTH_TEST);
        /* El color de fondo será el blanco (RGBA, RGB + Alpha channel) */
        glClearColor (1.0f, 1.0f, 1.0f, 1.0f);

        /* Comienza la ejecución del core de GLUT */
        glutMainLoop ();
        return 0;
}
