/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                            I N F O R M � T I C A                            |
 |                                G R � F I C A                                |
 |                                                                             |
 |                                                                             |
 |       Alumnos : Esteban Mart�nez Tristancho (estebanmartinez@ono.com)       |
 |                 Isaac Jurado Peinado (etanol@telefonica.net)                |
 |       Estudios: Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)         |
 |       Curso   : 2003/2004                                                   |
 |       Facultad: Universitat de les Illes Balears (UIB)                      |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * robot.c
 *
 * Programa que ilustra c�mo componer transformaciones de modelizaci�n. Para
 * mover el hombro pulsar 'h' � 'H', para mover el codo pulsar 'c' � 'C'
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static int hombro = 0, codo = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(-1.0, 0.0, 0.0);
		glRotatef((GLfloat) hombro, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
			glScalef(2.0, 0.4, 1.0);
			glutWireCube(1.0);
		glPopMatrix();

		glTranslatef(1.0, 0.0, 0.0);
		glRotatef((GLfloat) codo, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
			glScalef(2.0, 0.4, 1.0);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int ancho, int alto)
{
	glViewport(0, 0, ancho, alto);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat) ancho /(GLfloat) alto, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case 'h':
			hombro = (hombro + 5) % 360;
			glutPostRedisplay();
			break;
		case 'H':
			hombro = (hombro - 5) % 360;
			glutPostRedisplay();
			break;
		case 'c':
			codo = (codo + 5) % 360;
			glutPostRedisplay();
			break;
		case 'C':
			codo = (codo - 5) % 360;
			glutPostRedisplay();
			break;
		case 27: /* Tecla ESC */
			exit(0);
			break;
		default:
			break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

