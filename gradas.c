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
#include <stdio.h>
#include <stdlib.h>
#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#else
#include <GL/glut.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#include "piezas.h"
#include "textura.h"

static const float color_lateral[3] = {0.7, 0.0, 0.1};
static int gradas_textura = 0;

static void *my_malloc(size_t s)
{  /* {{{ */ 
	void *r;

	r = malloc(s);
	if (r == NULL) {
		fprintf(stderr, "Error al reservar memoria para grada.\n");
		exit(6);
	}
	return r;
}  /* }}} */


int crear_grada_frontal(config_t c)
{  /* {{{ */
	int i, lista;
	int gesc     = valor_entero(c, gs_esc);
	int gdet     = valor_entero(c, gs_det);
	float x      = valor_decimal(c, g_f_ancho) / 2;
	float paso_v = valor_decimal(c, gs_alto)  / (float)gesc;
	float paso_h = valor_decimal(c, gs_largo) / (float)gesc;
	float paso_l = valor_decimal(c, g_f_ancho) / (float)gdet;
	float *escalon, *texcoord;
	GLuint *e_vert, *e_horiz;

	/* Inicialización de los índices del vertex array */
	e_vert  = (GLuint *) my_malloc(((gdet+1)*2)*sizeof(GLuint));
	e_horiz = (GLuint *) my_malloc(((gdet+1)*2)*sizeof(GLuint));
	for (i = 0; i < (gdet+1)*2; i += 2) {
		e_vert[i] = (i / 2) * 3;
		e_vert[i+1] = e_horiz[i] = (i / 2) * 3 + 1;
		e_horiz[i+1] = (i / 2) * 3 + 2;
	}
	/* Inicialización del vertex array */
	escalon  = (float *) my_malloc((((gdet+1)*3)*3)*sizeof(float));
	for (i = 0; i < (gdet+1)*3; i += 3) {
		*(escalon+i*3+X) = *(escalon+(i+1)*3+X) = *(escalon+(i+2)*3+X) =
			(i / 3) * paso_l;
		*(escalon+i*3+Y)     = *(escalon+(i+1)*3+Y) = 0.0;
		*(escalon+(i+2)*3+Y) = paso_h;
		*(escalon+i*3+Z)     = 0.0;
		*(escalon+(i+1)*3+Z) = *(escalon+(i+2)*3+Z) = paso_v;
	}
	/* Inicialización del texture coord array */
	texcoord = (float *) my_malloc((((gdet+1)*3)*2)*sizeof(float));
	for (i = 0; i < (gdet+1)*3; i += 3) {
		*(texcoord+i*2) = *(texcoord+(i+1)*2) = *(texcoord+(i+2)*2) =
			(i / 3) * paso_l;
		*(texcoord+i*2+1)     = 0.0;
		*(texcoord+(i+1)*2+1) = 0.5;
		*(texcoord+(i+2)*2+1) = 1.0;
	}
	if (!gradas_textura)
		gradas_textura = cargar_textura(c, valor_cadena(c, gs_tex));
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
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gradas_textura);
	glVertexPointer(3, GL_FLOAT, 0, escalon);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(-x, 0.0, 0.0);
	for (i = 0; i < gesc; ++i) {
		glPushMatrix();
		glTranslatef(0.0, paso_h * i, paso_v * i);
		glNormal3f(0.0, -1.0, 0.0);
		glDrawElements(GL_QUAD_STRIP, (gdet+1)*2, GL_UNSIGNED_INT,
				e_vert);
		glNormal3f(0.0, 0.0, 1.0);
		glDrawElements(GL_QUAD_STRIP, (gdet+1)*2, GL_UNSIGNED_INT,
				e_horiz);
		glPopMatrix();
	}
	glPopMatrix();
	glPopAttrib();
	glEndList();
	return lista;
}  /* }}} */


int crear_grada_lateral(config_t c)
{  /* {{{ */
	int i, j, lista;
	int gesc = valor_entero(c, gs_esc);  /* Escalones */
	int gdet = valor_entero(c, gs_det); /* Detalle (nº caras) */
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

	if (!gradas_textura)
		gradas_textura = cargar_textura(c, valor_cadena(c, gs_tex));

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
	glBindTexture(GL_TEXTURE_2D, gradas_textura);
	glColor3f(1.0, 1.0, 1.0);
	for (i = gap; i < (gdet - gap); ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		for (j = 0; j < gesc; ++j) {
			r = radio_in + paso_h*j;
			s = r*i*angulo_rad;
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

