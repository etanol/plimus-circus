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
 * gradas.c
 *
 * Funciones para crear las gradas del interior del circo
 *
 * $Id$
 */

#include <GL/gl.h>
#include <math.h>

#include "piezas.h"


int crear_grada_frontal(struct config *c)
{
	int i, lista;
	float x      = c->grada_frontal_ancho / 2;
	float paso_v = c->gradas_alto  / (float)c->gradas_escalones;
	float paso_h = c->gradas_largo / (float)c->gradas_escalones;
	float datos[8][3];
	float normal[6][3] = { /* Normales */
		{0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {-1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},  {0.0, 0.0, -1.0},
		{0.0, 1.0, 0.0} /* Parte trasera de la grada */
	};
	GLubyte cara[6][4] = { /* Índices */
		{0, 1, 3, 2}, {2, 3, 5, 4}, {0, 2, 4, 6},
		{1, 3, 5, 7}, {0, 1, 7, 6},
		{6, 7, 5, 4} /* Parte trasera de la grada */
	};

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	/* Escalones */
	for (i = 0; i < c->gradas_escalones; ++i) {
		/* Datos del escalón (laterales y base incluídos) */
		datos[0][X] = datos[2][X] = datos[4][X] = datos[6][X] = -x;
		datos[1][X] = datos[3][X] = datos[5][X] = datos[7][X] = x;
		datos[0][Y] = datos[1][Y] = datos[2][Y] = datos[3][Y] =
			paso_h * i;
		datos[4][Y] = datos[5][Y] = datos[6][Y] = datos[7][Y] =
			paso_h * (i+1);
		datos[0][Z] = datos[1][Z] = datos[6][Z] = datos[7][Z] =
			0.0;
		datos[2][Z] = datos[3][Z] = datos[4][Z] = datos[5][Z] =
			paso_v * (i+1);
		glInterleavedArrays(GL_V3F, 0, datos[0]);
		/* Dibujamos */
		glNormal3fv(normal[0]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[0]);
		glNormal3fv(normal[1]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[1]);
		glNormal3fv(normal[2]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[2]);
		glNormal3fv(normal[3]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[3]);
		glNormal3fv(normal[4]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[4]);
	}
	/* 
	 * Aprovechamos que el vertex array contiene los datos del último
	 * escalón para pintar la parte trasera.
	 */
	glNormal3fv(normal[5]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[5]);
	glEndList();
	return lista;
}


int crear_grada_lateral(struct config *c)
{
	int i, j, lista;
	float r;
	float radio_ex   = (c->carpa_largo / 2) - c->sep_gradas_carpa;
	float radio_in   = radio_ex - c->gradas_largo;
	float paso_v     = c->gradas_alto  / (float)c->gradas_escalones;
	float paso_h     = c->gradas_largo / (float)c->gradas_escalones;
	float angulo     = 180.0 / c->grada_lateral_caras;
	float angulo_rad = M_PI  / c->grada_lateral_caras;
	float sin_angulo = sinf(angulo_rad);
	float cos_angulo = cosf(angulo_rad);
	float datos[c->gradas_escalones*4][3];
	float ldatos[(c->gradas_escalones*3)+1][3];

	lista = glGenLists(1);
	if (lista == 0)
		return 0;

	ldatos[0][X] = ldatos[0][Z] = 0.0;
	ldatos[0][Y] = radio_in;
	for (i = 0; i < c->gradas_escalones; ++i) {
		j = i * 4;
		r = radio_in + paso_h*i;
		datos[j][Z] = datos[j+1][Z] = datos[j+2][Z] = datos[j+3][Z] = 
			paso_v * (i+1);
		datos[j][X] = r * sin_angulo;
		datos[j+1][X] = datos[j+2][X] = 0.0;
		datos[j+3][X] = (r + paso_h) * sin_angulo;
		datos[j][Y] = r * cos_angulo;
		datos[j+1][Y] = r;
		datos[j+2][Y] = r + paso_h;
		datos[j+3][Y] = (r + paso_h) * cos_angulo;
		j = i * 3;
		ldatos[j+1][X] = ldatos[j+2][X] = ldatos[j+3][X] = 0.0;
		ldatos[j+1][Y] = radio_in + paso_h*i;
		ldatos[j+2][Y] = ldatos[j+3][Y] = radio_in + paso_h*(i+1);
		ldatos[j+1][Z] = ldatos[j+2][Z] = paso_v * (i+1);
		ldatos[j+3][Z] = 0.0;
	}

	glNewList(lista, GL_COMPILE);
	/* Laterales */
	glInterleavedArrays(GL_V3F, 0, ldatos[0]);
	glNormal3f(-1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(-(angulo*c->grada_lateral_apertura), 0.0, 0.0, 1.0);
	for (i = 0; i < c->gradas_escalones; ++i) 
		glDrawArrays(GL_QUADS, i * 3, 4);
	glPopMatrix();
	glNormal3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(-180.0 + (angulo*c->grada_lateral_apertura), 0.0, 0.0, 1.0);
	for (i = 0; i < c->gradas_escalones; ++i) 
		glDrawArrays(GL_QUADS, i * 3, 4);
	glPopMatrix();
	/* Resto de grada */
	glInterleavedArrays(GL_V3F, 0, datos[0]);
	for (i = c->grada_lateral_apertura; i < (c->grada_lateral_caras - c->grada_lateral_apertura); ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		/* Parte horizontal de los escalones */
		glNormal3f(0.0, 0.0, 1.0);
		glDrawArrays(GL_QUADS, 0, c->gradas_escalones*4);
		/* Parte vertical de los escalones */
		glBegin(GL_QUADS);
		for (j = 0; j < c->gradas_escalones; ++j) {
			r = radio_in + paso_h*j;
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(0.0, r, paso_v * j);
			glVertex3f(0.0, r, paso_v * (j+1));
			glNormal3f(-sin_angulo, -cos_angulo, 0.0);
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * (j+1));
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * j);
		}
		/* Base */
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, radio_in, 0.0);
		glVertex3f(0.0, radio_ex, 0.0);
		glVertex3f(radio_ex*sin_angulo, radio_ex*cos_angulo, 0.0);
		glVertex3f(radio_in*sin_angulo, radio_in*cos_angulo, 0.0);
		/* Trasero */
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, radio_ex, 0.0);
		glVertex3f(0.0, radio_ex, c->gradas_alto);
		glNormal3f(sin_angulo, cos_angulo, 0.0);
		glVertex3f(radio_ex*sin_angulo, radio_ex*cos_angulo, c->gradas_alto);
		glVertex3f(radio_ex*sin_angulo, radio_ex*cos_angulo, 0.0);
		glEnd();
		glPopMatrix();
	}
	glEndList();
	return lista;
}
