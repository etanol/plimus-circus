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
 * interaccion.c
 *
 * Implementaci�n de la gesti�n de teclado y rat�n.
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define ESC 27

static const GLfloat AVANCE   = 0.1;
static const GLfloat ROTACION = 3.0;

static GLfloat angulo_h = 0.0; /* �ngulo de rotaci�n horizontal */
static GLfloat angulo_v = 0.0; /* �ngulo de rotaci�n vertical */
static GLfloat camara_x = 0.0; /* Posici�n de la c�mara */
static GLfloat camara_y = 0.0;
static GLfloat camara_z = 0.0;


static inline void corrige_angulo(GLfloat *angulo)
{
	if (*angulo < 0.0)
		*angulo += 360.0;
	else if (*angulo > 360.0)
		*angulo -= 360.0;
}


static inline void actualiza_camara(void)
{
	/*
	 * Pasos:
	 *    1. Trasladarnos al punto donde se encuentra la c�mara.
	 *    2. Girar la c�mara horizontalmente (plano XZ).
	 *    3. Girar la c�mara verticalmente (plano ZY).
	 */
	glLoadIdentity();
	glRotatef(angulo_v, 1.0, 0.0, 0.0);            /* 3 */
	glRotatef(angulo_h, 0.0, 1.0, 0.0);            /* 2 */
	glTranslatef(-camara_x, -camara_y, -camara_z); /* 1 */
	glutPostRedisplay();
}


static void teclado_especial(int tecla, int x, int y)
{
	GLfloat radianes, grados = 0.0, avance = 0.0;

	switch (tecla) {
		case GLUT_KEY_UP:    /* Paso hacia adelante */
			grados = angulo_h + 90.0;
			avance = -AVANCE;
			break;
		case GLUT_KEY_DOWN:  /* Paso hacia atr�s */
			grados = angulo_h + 90.0;
			avance = AVANCE;
			break;
		case GLUT_KEY_LEFT:  /* Paso hacia la izquierda */
			grados = angulo_h;
			avance = -AVANCE;
			break;
		case GLUT_KEY_RIGHT: /* Paso hacia la derecha */
			grados = angulo_h;
			avance = AVANCE;
			break;
		case GLUT_KEY_F1:    /* Camara 1. Hay que cambiar la tecla */
			camara_x = 0.0;
			camara_y = 0.0;
			camara_z = 0.0;
			angulo_h = 0.0;
			angulo_v = 0.0;
			actualiza_camara();
			/* NO BREAK */
		default:
			return;
	}
	radianes = (grados * M_PI) / 180.0;
	camara_x += cosf(radianes) * avance;
	camara_z += sinf(radianes) * avance;
	actualiza_camara();
}


static void teclado(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case 'a':  /* Elevaci�n */
			camara_y += AVANCE;
			break;
		case 'z':  /* Descenso */
			camara_y -= AVANCE;
			break;
		case 'd':  /* Giro de c�mara a la izquierda */
			angulo_h -= ROTACION;
			corrige_angulo(&angulo_h);
			break;
		case 'g':  /* Giro de c�mara a la derecha */
			angulo_h += ROTACION;
			corrige_angulo(&angulo_h);
			break;
		case 'r':  /* Giro de c�mara hacia arriba */
			angulo_v -= ROTACION;
			corrige_angulo(&angulo_v);
			break;
		case 'f':  /* Giro de c�mara hacia abajo */
			angulo_v += ROTACION;
			corrige_angulo(&angulo_v);
			break;
		case ESC:  /* Salimos del programa */
			exit(0);
	}
	actualiza_camara();
}


void init_interaccion(void)
{
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclado_especial);
}
