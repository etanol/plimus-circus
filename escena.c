/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                            I N F O R M Á T I C A                            |
 |                                G R Á F I C A                                |
 |                                                                             |
 |                                                                             |
 |       Alumnos : Isaac Jurado Peinado        (etanol@telefonica.net)         |
 |                 Esteban Martínez Tristancho (estebanmartinez@ono.com)       |
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


static void cupula(void)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(-2.0, 0.0, 1.0);
	glVertex3f(-1.0, 0.0, 2.0);
	glVertex3f(1.0, 0.0, 2.0);
	glVertex3f(2.0, 0.0, 1.0);
	glVertex3f(2.0, 0.0, -1.0);
	glVertex3f(1.0, 0.0, -2.0);
	glVertex3f(-1.0, 0.0, -2.0);
	glVertex3f(-2.0, 0.0, -1.0);
	glVertex3f(-2.0, 0.0, 1.0);
	glEnd();
}


static void base(void)
{
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-4.0, 1.0, 2.0);
	glVertex3f(-4.0, 0.0, 2.0);
	glVertex3f(-5.0, 1.0, 1.0);
	glVertex3f(-5.0, 0.0, 1.0);
	glVertex3f(-5.0, 1.0, -1.0);
	glVertex3f(-5.0, 0.0, -1.0);
	glVertex3f(-4.0, 1.0, -2.0);
	glVertex3f(-4.0, 0.0, -2.0);
	glVertex3f(4.0, 1.0, -2.0);
	glVertex3f(4.0, 0.0, -2.0);
	glVertex3f(5.0, 1.0, -1.0);
	glVertex3f(5.0, 0.0, -1.0);
	glVertex3f(5.0, 1.0, 1.0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(4.0, 1.0, 2.0);
	glVertex3f(4.0, 0.0, 2.0);
	glVertex3f(-4.0, 1.0, 2.0);
	glVertex3f(-4.0, 0.0, 2.0);
	glEnd();
}


static void escena(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.8);
	glPushMatrix();
	glTranslatef(-3.0, 1.0, 0.0);
	cupula();
	glPopMatrix();

	glColor3f(0.0, 0.8, 0.0);
	glPushMatrix();
	glTranslatef(3.0, 1.0, 0.0);
	cupula();
	glPopMatrix();

	glColor3f(0.8, 0.0, 0.8);
	base();

	glutSwapBuffers();
}

void init_escena(void)
{
	glutDisplayFunc(escena);
	glutReshapeFunc(actualiza_viewport);
}
