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
static const float color_madera[3] = {1.0, 1.0, 1.0};

int crear_grada_frontal(struct config *c)
{
	int i, lista;
	float x      = c->grada_frontal_ancho / 2;
	float paso_v = c->gradas_alto  / (float)c->gradas_escalones;
	float paso_h = c->gradas_largo / (float)c->gradas_escalones;
	float smin   = 0.0;
	float smax   = c->grada_frontal_ancho;

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glColor3fv(color_madera);
	/* Escalones */
	glBegin(GL_QUADS);
	for (i = 0; i < c->gradas_escalones; ++i) {
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
	glDisable(GL_TEXTURE_2D);
	glColor3fv(color_lateral);
	glBegin(GL_QUADS);
	for (i = 0; i < c->gradas_escalones; ++i) {
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
	glEndList();
	return lista;
}


int crear_grada_lateral(struct config *c)
{
	int i, j, lista;
	float r;
	float radio_ex   = c->carpa_lateral_radio - SEP_GRADAS_CARPA;
	float radio_in   = radio_ex - c->gradas_largo;
	float paso_v     = c->gradas_alto  / (float)c->gradas_escalones;
	float paso_h     = c->gradas_largo / (float)c->gradas_escalones;
	float angulo     = 180.0 / c->grada_lateral_caras;
	float angulo_rad = M_PI  / c->grada_lateral_caras;
	float sin_angulo = sinf(angulo_rad);
	float cos_angulo = cosf(angulo_rad);
	float s, ss;

	lista = glGenLists(1);
	if (lista == 0)
		return 0;

	glNewList(lista, GL_COMPILE);
	/* Laterales */
	glNormal3f(-1.0, 0.0, 0.0);
	glColor3fv(color_lateral);
	for (i = 0; i < 2; ++i) {
		glPushMatrix();
		if (i) 
			glScalef(1.0, -1.0, 1.0);
		glRotatef(angulo * c->grada_lateral_apertura, 0.0, 0.0, -1.0);
		glBegin(GL_QUADS);
		for (j = 0; j < c->gradas_escalones; ++j) {
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
	for (i = c->grada_lateral_apertura; i < (c->grada_lateral_caras - c->grada_lateral_apertura); ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glColor3fv(color_madera);
		glBegin(GL_QUADS);
		for (j = 0; j < c->gradas_escalones; ++j) {
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
	glDisable(GL_TEXTURE_2D);
	glEndList();
	return lista;
}
