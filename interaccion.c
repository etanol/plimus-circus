/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado        (etanol@telefonica.net)        |
 |                  Esteban Mart�nez Tristancho (estebanmartinez@ono.com)      |
 |      Asignatura: Inform�tica Gr�fica I                                      |
 |      Profesor  : Jose Mar�a Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * interaccion.c
 *
 * Implementaci�n de la gesti�n de teclado y rat�n.
 *
 * $Id$
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/glut.h>
#define M_PI 3.1415927
#endif

#include "camaras.h"
#include "config.h"

#define ESC 27

#define AVANCE		0.1
#define ROTACION	3.0
#define DEFINICION	1.5

enum tipo_de_giro {HORIZONTAL, VERTICAL};

int modo_exterior;
float desp_cielo_h = 0.0;
float desp_cielo_v = 0.0;

static struct config *C;
static float angulo_h = 0.0; /* �ngulo de rotaci�n horizontal */
static float angulo_v = 0.0; /* �ngulo de rotaci�n vertical */
static float camara_x = 0.0; /* Posici�n de la c�mara */
static float camara_y = 0.6;
static float camara_z = 0.0;


void actualiza_camara(void)
{  /* {{{ */
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
}  /* }}} */


static void comprueba_situacion(enum tipo_de_giro t)
{  /* {{{ */
	static float radio = 0.0;
	float x, cx, cz;

	if (t == VERTICAL) {
		if (camara_y <= C->carpa_faldon_alto) {
			radio = C->carpa_lateral_radio + CAIDA_FALDON + 0.1;
		} else if (camara_y <= (C->carpa_techo_alto + C->carpa_faldon_alto)) {
			/* faldon_alto < cam_y <= faldon_alto + techo_alto */
			radio = (C->carpa_lateral_radio * (camara_y -
				C->carpa_faldon_alto - C->carpa_techo_alto)) /
				-C->carpa_techo_alto;
		} else {
			/* faldon_alto < faldon_alto + techo_alto < cam_y */
			radio = 0.0;
			modo_exterior = 1;
			return;
		}
	} 
	cx = (float)fabs((double)camara_x);
	cz = (float)fabs((double)camara_z);
	x  = C->carpa_frontal_ancho / 2.0;
	if (cz <= radio) {
		if (cx <= x) {
			modo_exterior = 0;
		} else if (cx <= (x + radio)) {
			/* x < cx <= x + radio */
			modo_exterior = (hypotf(cx-x, cz) <= radio ? 0 : 1);
		} else {
			/* x < x + radio < cx */
			modo_exterior = 1;
		}
	} else {
		/* cz > radio */
		modo_exterior = 1;
	}
}  /* }}} */


static void paso_frontal(float sentido)
{  /* {{{ */
	float radianes;

	radianes = (angulo_h * M_PI) / 180.0;
	camara_x += sinf(radianes) * AVANCE * sentido;
	camara_z += cosf(radianes) * AVANCE * sentido;
}  /* }}} */


static void paso_lateral(float sentido)
{  /* {{{ */
	float radianes;

	radianes = (angulo_h * M_PI) / 180.0;
	camara_x += cosf(radianes) * AVANCE * sentido;
	camara_z += -sinf(radianes) * AVANCE * sentido;
} /* }}} */


static void giro_camara(float sentido, enum tipo_de_giro g)
{  /* {{{ */
	float *angulo;
	float *despl;

	switch (g) {
		case VERTICAL: 
			angulo = &angulo_v;
			despl  = &desp_cielo_v;
			break;
		case HORIZONTAL:
			angulo = &angulo_h;
			despl  = &desp_cielo_h;
			break;
		default:
			angulo = NULL;
			return;
	}
	*angulo += ROTACION * sentido;
	*despl  += 0.05 * (g == HORIZONTAL ? -sentido : sentido);
	if (*angulo < -360.0)
		*angulo += 360.0;
	else if (*angulo > 360.0)
		*angulo -= 360.0;
	if (*despl < 0.0)
		*despl += 1.0;
	else if (*despl > 1.0)
		*despl -= 1.0;
}  /* }}} */


static void teclado_especial(int tecla, int x, int y)
{  /* {{{ */
	static int is_full = 0;
	
	switch (tecla) {
		case GLUT_KEY_UP:        /* Paso hacia adelante */
			paso_frontal(-1.0);
			comprueba_situacion(HORIZONTAL);
			break;
		case GLUT_KEY_DOWN:      /* Paso hacia atr�s */
			paso_frontal(1.0);
			comprueba_situacion(HORIZONTAL);
			break;
		case GLUT_KEY_LEFT:      /* Paso hacia la izquierda */
			paso_lateral(-1.0);
			comprueba_situacion(HORIZONTAL);
			break;
		case GLUT_KEY_RIGHT:     /* Paso hacia la derecha */
			paso_lateral(1.0);
			comprueba_situacion(HORIZONTAL);
			break;
		case GLUT_KEY_PAGE_UP:   /* Elevaci�n */
			camara_y += AVANCE;
			comprueba_situacion(VERTICAL);
			break;
		case GLUT_KEY_PAGE_DOWN: /* Descenso */
			if (camara_y > 0.65f) {
				camara_y -= AVANCE;
				comprueba_situacion(VERTICAL);
			} else {
				/* Cortocircuito */
				return;
			}
			break;
		case GLUT_KEY_F5:	/* Pantalla completa */
			if (is_full)
				glutReshapeWindow(500, 500);
			else
				glutFullScreen();
			is_full = !is_full;
			break;
		default:
			return;
	}
	glutPostRedisplay();
}  /* }}} */


static void teclado(unsigned char tecla, int x, int y)
{  /* {{{ */
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
		case 'p': /* Imprimimos el estado actual de la c�mara */
			printf("Angulo H: %f\n", angulo_h);
			printf("Angulo V: %f\n", angulo_v);
			printf("Camara (x, y, z): (%f, %f, %f)\n", camara_x,
					camara_y, camara_z);
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
			comprueba_situacion(VERTICAL);
			break;
		default:   /* Cualquier otra tecla, ignorada */
			return;
	}
	glutPostRedisplay();
}  /* }}} */


static void raton(int x, int y)
{  /* {{{ */
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
	glutPostRedisplay();
}  /* }}} */


static void menu(int valor)
{  /* {{{ */
	static int light_flag = 1;
	static int smooth_flag = 1;
	static int animation_flag = 1;

	switch (valor) {
		case 0:
			if (light_flag)
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);
			light_flag = !light_flag;
			break;
		case 1:
			if (smooth_flag)
				glShadeModel(GL_FLAT);
			else
				glShadeModel(GL_SMOOTH);
			smooth_flag = !smooth_flag;
			break;
		case 2:
			break;
	}
}  /* }}} */


void init_interaccion(struct config *conf)
{  /* {{{ */
	C = conf;
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclado_especial);
	glutMotionFunc(raton);
	glutCreateMenu(menu);
	glutAddMenuEntry("Activar/Desactivar iluminaci�n.", 0);
	glutAddMenuEntry("Modelo de shading FLAT/SMOOTH.", 1);
	glutAddMenuEntry("Activar/Desactivar animaci�n.", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	comprueba_situacion(VERTICAL);
}  /* }}} */
