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

#include "camaras.h"

#define ESC 27

enum tipo_de_giro {HORIZONTAL, VERTICAL};

static const float AVANCE     = 0.1;
static const float ROTACION   = 3.0;
static const float DEFINICION = 1.5;

static float angulo_h = 0.0; /* �ngulo de rotaci�n horizontal */
static float angulo_v = 0.0; /* �ngulo de rotaci�n vertical */
static float camara_x = 0.0; /* Posici�n de la c�mara */
static float camara_y = 0.0;
static float camara_z = 0.0;


static inline void actualiza_camara(void)
{
	/*
	 * Pasos:
	 *    1. Trasladarnos al punto donde se encuentra la c�mara.
	 *    2. Girar la c�mara horizontalmente (plano XZ).
	 *    3. Girar la c�mara verticalmente (plano ZY).
	 */
	glLoadIdentity();
	glRotatef((GLfloat) -angulo_v, 1.0, 0.0, 0.0);	/* 3 */
	glRotatef((GLfloat) -angulo_h, 0.0, 1.0, 0.0);	/* 2 */
	glTranslatef(	(GLfloat) -camara_x,
			(GLfloat) -camara_y,
			(GLfloat) -camara_z);		/* 1 */
	glutPostRedisplay();
}


static inline void paso_frontal(float sentido)
{
	float radianes;

	radianes = (angulo_h * M_PI) / 180.0;
	camara_x += sinf(radianes) * AVANCE * sentido;
	camara_z += cosf(radianes) * AVANCE * sentido;
}


static inline void paso_lateral(float sentido)
{
	float radianes;

	radianes = (angulo_h * M_PI) / 180.0;
	camara_x += cosf(radianes) * AVANCE * sentido;
	camara_z += -sinf(radianes) * AVANCE * sentido;
}


static inline void giro_camara(float sentido, enum tipo_de_giro g)
{
	float *angulo;

	switch (g) {
		case VERTICAL: 
			angulo = &angulo_v;
			break;
		case HORIZONTAL:
			angulo = &angulo_h;
			break;
	}
	*angulo += ROTACION * sentido;
	if (*angulo < -360.0)
		*angulo += 360.0;
	else if (*angulo > 360.0)
		*angulo -= 360.0;
}


static void teclado_especial(int tecla, int x, int y)
{
	switch (tecla) {
		case GLUT_KEY_UP:        /* Paso hacia adelante */
			paso_frontal(-1.0);
			break;
		case GLUT_KEY_DOWN:      /* Paso hacia atr�s */
			paso_frontal(1.0);
			break;
		case GLUT_KEY_LEFT:      /* Paso hacia la izquierda */
			paso_lateral(-1.0);
			break;
		case GLUT_KEY_RIGHT:     /* Paso hacia la derecha */
			paso_lateral(1.0);
			break;
		case GLUT_KEY_PAGE_UP:   /* Elevaci�n */
			camara_y += AVANCE;
			break;
		case GLUT_KEY_PAGE_DOWN: /* Descenso */
			camara_y -= AVANCE;
			break;
		default:
			return;
	}
	actualiza_camara();
}


static void teclado(unsigned char tecla, int x, int y)
{
	int i;

	switch (tecla) {
		case 'd':  /* Giro de c�mara a la izquierda */
			giro_camara(1.0, HORIZONTAL);
			break;
		case 'g':  /* Giro de c�mara a la derecha */
			giro_camara(-1.0, HORIZONTAL);
			break;
		case 'r':  /* Giro de c�mara hacia arriba */
			giro_camara(1.0, VERTICAL);
			break;
		case 'f':  /* Giro de c�mara hacia abajo */
			giro_camara(-1.0, VERTICAL);
			break;
		case ESC:  /* Salimos del programa */
			exit(0);
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			i = (int)tecla - (int)'0';
			angulo_h = CAMARA[i].angulo_h;
			angulo_v = CAMARA[i].angulo_v;
			camara_x = CAMARA[i].camara_x;
			camara_y = CAMARA[i].camara_y;
			camara_z = CAMARA[i].camara_z;
			break;
		default:   /* Cualquier otra tecla, ignorada */
			return;
	}
	actualiza_camara();
}


static void raton(int x, int y)
{
	static int ox = 0, oy = 0;

	if (x > ox)
		giro_camara(-0.7, HORIZONTAL);
	else if (x < ox)
		giro_camara(0.7, HORIZONTAL);
	ox = x;
	if (y > oy)
		giro_camara(-0.7, VERTICAL);
	else if (y < oy)
		giro_camara(0.7, VERTICAL);
	oy = y;
	actualiza_camara();
}


void init_interaccion(void)
{
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclado_especial);
	glutMotionFunc(raton);
}
