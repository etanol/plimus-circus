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
 * interaccion.c
 *
 * Implementación de la gestión de teclado y ventana
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

float angulo_h = 0.0;
float angulo_v = 0.0;
float camara_x = 0.0;
float camara_y = 0.2;
float camara_z = 0.0;
float direcc_x = 0.0;
float direcc_y = 0.2;
float direcc_z = 1.0;

void teclado_especial(int tecla, int x, int y)
{
	switch (tecla) {
		case GLUT_KEY_LEFT:
			// Girar izquierda
			angulo_h -= 0.2;
			break;
		case GLUT_KEY_RIGHT:
			// Girar derecha
			angulo_h += 0.2;
			break;
		case GLUT_KEY_UP:
			// Avanzar
			camara_x += sinf(angulo_h);
			camara_z += cosf(angulo_h);
			break;
		case GLUT_KEY_DOWN:
			// Retroceder
			camara_x -= sinf(angulo_h);;
			camara_z -= cosf(angulo_h);
			break;
		case GLUT_KEY_F1:
			camara_x = 0.0;
			camara_y = 0.0;
			direcc_y = 0.0;
			camara_z = 0.0;
			angulo_h = 0.0;
	}
	direcc_x = camara_x + sinf(angulo_h);
	direcc_z = camara_z + cosf(angulo_h);
	glLoadIdentity();
	gluLookAt(camara_x, camara_y, camara_z, direcc_x, direcc_y, direcc_z,
			0.0, 1.0, 0.0);
	glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case 'a':
			camara_y += 0.1;
			direcc_y += 0.1;
			break;
		case 'z':
			camara_y -= 0.1;
			direcc_y -= 0.1;
			break;
	}
	glLoadIdentity();
	gluLookAt(camara_x, camara_y, camara_z, direcc_x, direcc_y, direcc_z,
			0.0, 1.0, 0.0);
	glutPostRedisplay();
}

void redimensionado(int ancho, int alto)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)ancho / (GLdouble)alto, 0.5, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, ancho, alto);
	glutPostRedisplay();
}

