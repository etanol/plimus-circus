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
 * etapa1.c
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* Tama�o incial de la ventana */
const int W_WIDTH = 500;
const int W_HEIGHT = 500;

/* Variable que indica el �ngulo de rotaci�n de los ejes. */
GLfloat fAngulo;

void Display (void)
{
	/* Borramos la escena */
	glClear (GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	/* Rotamos las proximas primitivas */
	glRotatef (fAngulo, 0.0f, 0.0f, 1.0f);
	/* Creamos a continuaci�n dibujamos los tres poligonos */
	glBegin (GL_POLYGON);
	glColor3f (1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f (0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f (0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glEnd();

	glBegin (GL_POLYGON);
	glColor3f (1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f (1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f (0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();

	glBegin (GL_POLYGON);
	glColor3f (1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f (0.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glColor3f (0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();

	glPopMatrix();
	glFlush();
}


void Idle (void)
{
	/* Incrementamos el �ngulo */
	fAngulo += 0.3f;
	/* Si es mayor que dos pi la decrementamos */
	if (fAngulo > 360)
		fAngulo -= 360;
	/* Indicamos que es necesario repintar la pantalla */
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	/* Inicializamos la librer�a GLUT */
	glutInit (&argc, argv);

	/* Indicamos como ha de ser la nueva ventana */
	glutInitWindowPosition (100,100);
	glutInitWindowSize (W_WIDTH, W_HEIGHT);
	glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE);

	/* Creamos la nueva ventana */
	glutCreateWindow ("Ventana principal");

	/* Indicamos cuales son las funciones de redibujado e idle */
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	/* El color de fondo ser� el blanco (RGBA, RGB + Alpha channel) */
	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);

	/* Comienza la ejecuci�n del core de GLUT */
	glutMainLoop();
	return 0;
}
