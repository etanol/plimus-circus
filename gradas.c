/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado        (etanol@telefonica.net)        |
 |                  Esteban Martínez Tristancho (estebanmartinez@ono.com)      |
 |      Asignatura: Informática Gráfica I                                      |
 |      Profesor  : Jose María Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingeniería Técnica en Informática de Gestión (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * gradas.c
 *
 * Funciones para crear las gradas del interior del circo
 *
 * $Id$
 */

#include <math.h>
#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#else
#include <GL/glut.h>
#define M_PI 3.1415927
#endif

#include "piezas.h"

static const float color_lateral[3] = {0.7, 0.0, 0.1};

int crear_grada_frontal(config_t c)
{  /* {{{ */
	int i, lista;
	int gesc     = valor_entero(c, gs_esc);
	float x      = valor_decimal(c, g_f_ancho) / 2;
	float paso_v = valor_decimal(c, gs_alto)  / (float)gesc;
	float paso_h = valor_decimal(c, gs_largo) / (float)gesc;
	float smin   = 0.0;
	float smax   = valor_decimal(c, g_f_ancho);

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	/* Laterales */
	glColor3fv(color_lateral);
	glBegin(GL_QUADS);
	for (i = 0; i < gesc; ++i) {
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-x, paso_h * i, 0.0);
		glVertex3f(-x, paso_h * i, paso_v * (i+1));
		glVertex3f(-x, paso_h * (i+1), paso_v * (i+1));
		glVertex3f(-x, paso_h * (i+1), 0.0);

		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(x, paso_h * i, 0.0);
		glVertex3f(x, paso_h * i, paso_v * (i+1));
		glVertex3f(x, paso_h * (i+1), paso_v * (i+1));
		glVertex3f(x, paso_h * (i+1), 0.0);
	}
	glEnd();
	/* Escalones */
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	for (i = 0; i < gesc; ++i) {
		smin += 0.3;
		smax += 0.3;
		if (smin > 1.0) {
			smin -= 1.0;
			smax -= 1.0;
		}
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(smin, 0.0);
		glVertex3f(-x, paso_h * i, paso_v * i);
		glTexCoord2f(smax, 0.0);
		glVertex3f(x, paso_h * i, paso_v * i);
		glTexCoord2f(smax, 0.5);
		glVertex3f(x, paso_h * i, paso_v * (i+1));
		glTexCoord2f(smin, 0.5);
		glVertex3f(-x, paso_h * i, paso_v * (i+1));

		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(smin, 0.5);
		glVertex3f(-x, paso_h * i, paso_v * (i+1));
		glTexCoord2f(smax, 0.5);
		glVertex3f(x, paso_h * i, paso_v * (i+1));
		glTexCoord2f(smax, 1.0);
		glVertex3f(x, paso_h * (i+1), paso_v * (i+1));
		glTexCoord2f(smin, 1.0);
		glVertex3f(-x, paso_h * (i+1), paso_v * (i+1));
	}
	glEnd();
	glPopAttrib();
	glEndList();
	return lista;
}  /* }}} */


int crear_grada_lateral(config_t c)
{  /* {{{ */
	int i, j, lista;
	int gesc = valor_entero(c, gs_esc);  /* Escalones */
	int gdet = valor_entero(c, g_l_det); /* Detalle (nº caras) */
	int gap  = valor_entero(c, g_l_ap);  /* Apertura */
	float r;
	float radio_ex   = valor_decimal(c, c_l_radio)-valor_decimal(c, gs_sep);
	float radio_in   = radio_ex - valor_decimal(c, gs_largo);
	float paso_v     = valor_decimal(c, gs_alto) / (float)gesc;
	float paso_h     = valor_decimal(c, gs_largo) / (float)gesc;
	float angulo     = 180.0 / (float)gdet;
	float angulo_rad = M_PI  / (float)gdet;
	float sin_angulo = sinf(angulo_rad);
	float cos_angulo = cosf(angulo_rad);
	float s, ss;

	lista = glGenLists(1);
	if (lista == 0)
		return 0;

	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	/* Laterales */
	glNormal3f(-1.0, 0.0, 0.0);
	glColor3fv(color_lateral);
	for (i = 0; i < 2; ++i) {
		glPushMatrix();
		if (i) 
			glScalef(1.0, -1.0, 1.0);
		glRotatef(angulo * gap, 0.0, 0.0, -1.0);
		glBegin(GL_QUADS);
		for (j = 0; j < gesc; ++j) {
			r = radio_in + paso_h*j;
			glVertex3f(0.0, r, 0.0);
			glVertex3f(0.0, r, paso_v * (j+1));
			glVertex3f(0.0, r + paso_h, paso_v * (j+1));
			glVertex3f(0.0, r + paso_h, 0.0);
		}
		glEnd();
		glPopMatrix();
	}
	/* Escalones */
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	for (i = gap; i < (gdet - gap); ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		for (j = 0; j < gesc; ++j) {
			r = radio_in + paso_h*j;
			s = r*i*angulo_rad + j*0.3;
			s = (s > 1.0 ? s - 1.0 : s);
			ss = s + r*angulo_rad; 
			/* Parte horizontal de los escalones */
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(s , 0.0);
			glVertex3f(0.0, r, paso_v * (j+1));
			glTexCoord2f(s , 0.5);
			glVertex3f(0.0, r + paso_h, paso_v * (j+1));
			glTexCoord2f(ss, 0.5);
			glVertex3f((r+paso_h)*sin_angulo,
					(r+paso_h)*cos_angulo, paso_v * (j+1));
			glTexCoord2f(ss, 0.0);
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * (j+1));
			/* Parte vertical de los escalones */
			glNormal3f(0.0, -1.0, 0.0);
			glTexCoord2f(s , 0.5);
			glVertex3f(0.0, r, paso_v * j);
			glTexCoord2f(s , 1.0);
			glVertex3f(0.0, r, paso_v * (j+1));
			glNormal3f(-sin_angulo, -cos_angulo, 0.0);
			glTexCoord2f(ss, 1.0);
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * (j+1));
			glTexCoord2f(ss, 0.5);
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * j);
		}
		glEnd();
		glPopMatrix();
	}
	glPopAttrib();
	glEndList();
	return lista;
}  /* }}} */

