/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                            I N F O R M Á T I C A                            |
 |                                G R Á F I C A                                |
 |                                                                             |
 |                                                                             |
 |       Alumnos : Esteban Martínez Tristancho (estebanmartinez@ono.com)       |
 |                 Isaac Jurado Peinado (etanol@telefonica.net)                |
 |       Estudios: Ingeniería Técnica en Informática de Gestión (TIG2)         |
 |       Curso   : 2003/2004                                                   |
 |       Facultad: Universitat de les Illes Balears (UIB)                      |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * escena.c
 *
 * Primitivas para dibujar la escena completa.
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static void actualiza_viewport(int ancho, int alto)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)ancho / (GLdouble)alto, 0.5, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, ancho, alto);
	glutPostRedisplay();
}

static void dibuja_escena(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(90.0, -1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.2, 0.8, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.2, -0.8, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(-1.2, -0.8, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.2, 0.8, 0.0);
	glColor3f(0.0, 0.5, 0.5);
	glVertex3f(-1.0, 1.0, 0.0);
	glColor3f(0.5, 0.5, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void init_escena(void)
{
	glutDisplayFunc(dibuja_escena);
	glutReshapeFunc(actualiza_viewport);
}
