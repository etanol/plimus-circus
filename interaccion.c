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

static const GLfloat MOV_STEP = 0.1;
static const GLfloat ROT_STEP = 3.0;

static GLfloat angulo_h = 0.0; /* Ángulo de rotación horizontal */
static GLfloat angulo_v = 0.0; /* Ángulo de rotación vertical */
static GLfloat camara_x = 0.0; /* Posición de la cámara */
static GLfloat camara_y = 0.0;
static GLfloat camara_z = 0.0;

static inline void actualiza_camara(void)
{
	/*
	 * Pasos:
	 *    1. Trasladarnos al punto donde se encuentra la cámara.
	 *    2. Girar la cámara horizontalmente (plano XZ).
	 *    3. Girar la cámara verticalmente (plano ZY).
	 */
	glLoadIdentity();
	glRotatef(angulo_v, 1.0, 0.0, 0.0); /* 3 */
	glRotatef(angulo_h, 0.0, 1.0, 0.0); /* 2 */
	glTranslatef(-camara_x, -camara_y, -camara_z); /* 1 */
	glutPostRedisplay();
}

void teclado_especial(int tecla, int x, int y)
{
	GLfloat radianes;
	switch (tecla) {
		case GLUT_KEY_DOWN:
			radianes = ((angulo_h + 90.0) * M_PI) / 180.0;
			camara_z += sinf(radianes) * MOV_STEP;
			camara_x += cosf(radianes) * MOV_STEP;
			break;
		case GLUT_KEY_UP:
			radianes = ((angulo_h + 90.0) * M_PI) / 180.0;
			camara_z -= sinf(radianes) * MOV_STEP;
			camara_x -= cosf(radianes) * MOV_STEP;
			break;
		case GLUT_KEY_LEFT:
			radianes = (angulo_h * M_PI) / 180.0;
			camara_z -= sinf(radianes) * MOV_STEP;
			camara_x -= cosf(radianes) * MOV_STEP;
			break;
		case GLUT_KEY_RIGHT:
			radianes = (angulo_h * M_PI) / 180.0;
			camara_z += sinf(radianes) * MOV_STEP;
			camara_x += cosf(radianes) * MOV_STEP;
			break;
		case GLUT_KEY_F1:
			camara_x = 0.0;
			camara_y = 0.0;
			camara_z = 0.0;
			angulo_h = 0.0;
			angulo_v = 0.0;
	}
	actualiza_camara();
}

void teclado(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case 'a':
			/* Elevación */
			camara_y += MOV_STEP;
			break;
		case 'z':
			/* Descenso */
			camara_y -= MOV_STEP;
			break;
		case 'd':
			angulo_h -= 2*ROT_STEP;
			/* NO BREAK */
		case 'g':
			angulo_h += ROT_STEP;
			if (angulo_h < 0.0)
				angulo_h += 360.0;
			else if (angulo_h > 360.0)
				angulo_h -= 360.0;
			break;
		case 'f':
			angulo_v += 2*ROT_STEP;
			/* NO BREAK */
		case 'r':
			angulo_v -= ROT_STEP;
			if (angulo_v < 0.0)
				angulo_v += 360.0;
			else if (angulo_v > 360.0)
				angulo_v -= 360.0;
			break;
	}
	actualiza_camara();
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

