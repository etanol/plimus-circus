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
 * carpa.c
 *
 * Piezas necesarias para dibujar la carpa
 *
 * $Id$
 */

#include <math.h>
#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#else
#include <GL/glut.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265
#endif

#include "piezas.h"
#include "textura.h"

static int carpa_textura = 0;

static void evaluator(float *vertices, float *tex, int nu, int nv, int invert)
{  /* {{{ */
	int iv, jv, it, jt;

	if (invert) {
		iv = 12; jv = 3;
		it = 4;  jt = 2;
	} else {
		iv = 3; jv = 12;
		it = 2; jt = 4;
	}
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, iv, 4, 0.0, 1.0, jv, 4, vertices);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, it, 2, 0.0, 1.0, jt, 2, tex);
	glMapGrid2f(nu, 0.0, 1.0, nv, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glEvalMesh2(GL_FILL, 0, nu, 0, nv);
}  /* }}} */
	

int crear_faldon_frontal(config_t c)
{  /* {{{ */
	int i, j, lista;
	float control[4][4][3];
	float texcoord[8] = {0.0, 0.0, 2.5, 0.0, 0.0, 1.0, 2.5, 1.0};
	float paso_z = valor_decimal(c, c_f_alto) / 3.0;
	float paso_x = valor_decimal(c, c_fr_ancho) / 3.0;
	float x      = valor_decimal(c, c_fr_ancho) / 2.0;
	float caida  = valor_decimal(c, c_f_caida);

	if (!carpa_textura)
		carpa_textura = gen_textura_carpa();

	for (i = 0; i < 4; ++i) 
		for (j = 0; j < 4; ++j) {
			control[i][j][X] = (j * paso_x) - x;
			control[i][j][Y] = (i ? 0.0 : caida);
			control[i][j][Z] = i * paso_z;
		}

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_detv),
			valor_entero(c, c_deth), 1);
	glEndList();
	return lista;
}  /* }}} */


int crear_faldon_lateral(config_t c)
{  /* {{{ */
	int i, lista;
	float control[4][4][3];
	float texcoord[8] = {0.5, 0.0, 6.0, 0.0, 0.5, 1.0, 6.0, 1.0};
	float paso_z  = valor_decimal(c, c_f_alto) / 3.0;
	float clradio = valor_decimal(c, c_l_radio);
	float caida_y = clradio + valor_decimal(c, c_f_caida);

	if (!carpa_textura)
		carpa_textura = gen_textura_carpa();

	for (i = 0; i < 4; ++i) {
		control[i][0][Z] = control[i][1][Z] = control[i][2][Z] = 
			control[i][3][Z] = i * paso_z;
		control[i][0][Y] = control[i][1][Y] = 
			(i ? clradio : caida_y);
		control[i][2][Y] = control[i][3][Y] = 
			(i ? -clradio : -caida_y);
		control[i][0][X] = control[i][3][X] = 0.0;
		control[i][1][X] = control[i][2][X] =
			(control[i][0][Y] * 4.0) / 3.0 ;
	}

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_detv),
			valor_entero(c, c_deth), 1);
	glEndList();
	return lista;
}  /* }}} */


int crear_techo_frontal(config_t c)
{  /* {{{ */
	int i, j, lista;
	float control[4][4][3];
	float texcoord[8] = {0.0, 0.0, 2.5, 0.0, 0.0, 1.0, 2.5, 1.0};
	float caida  = valor_decimal(c, c_t_caida);
	float paso_x = valor_decimal(c, c_fr_ancho) / 3.0;
	float paso_y = valor_decimal(c, c_l_radio) / 3.0;
	float paso_z = valor_decimal(c, c_t_alto) / 3.0;
	float x      = valor_decimal(c, c_fr_ancho) / 2.0;
	float zeta[4] = {valor_decimal(c, c_t_alto), (paso_z * 2.0) - caida,
		paso_z - caida, 0.0}; 

	if (!carpa_textura)
		carpa_textura = gen_textura_carpa();

	for (i = 0; i < 4; ++i) 
		for (j = 0; j < 4; ++j) {
			control[i][j][X] = (paso_x * j) - x;
			control[i][j][Y] = i * paso_y;
			control[i][j][Z] = zeta[i];
		}
	/* Corrección para la caída entre poste y poste */
	control[0][1][Z] -= valor_decimal(c, c_t_caidap);
	control[0][2][Z] -= valor_decimal(c, c_t_caidap);

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_deth),
			valor_entero(c, c_detv), 0);
	glEndList();
	return lista;
}  /* }}} */


int crear_techo_lateral(config_t c)
{  /* {{{ */
	int i, lista;
	float control[4][4][3]; 
	float texcoord[8] = {0.5, 0.0, 6.0, 0.0, 0.5, 1.0, 6.0, 1.0};
	float caida  = valor_decimal(c, c_t_caida);
	float paso_y = valor_decimal(c, c_l_radio) / 3.0;
	float paso_z = valor_decimal(c, c_t_alto) / 3.0;
	float zeta[4] = { valor_decimal(c, c_t_alto), (paso_z * 2.0) - caida,
		paso_z - caida, 0.0 }; 

	if (!carpa_textura)
		carpa_textura = gen_textura_carpa();

	for (i = 0; i < 4; ++i) {
		control[i][0][Z] = control[i][1][Z] = control[i][2][Z] =
			control[i][3][Z] = zeta[i];
		control[i][0][Y] = control[i][1][Y] = (i ? paso_y*i : 0.0001);
		control[i][2][Y] = control[i][3][Y] = (i ? -paso_y*i : -0.0001);
		control[i][0][X] = control[i][3][X] = 0.0;
		control[i][1][X] = control[i][2][X] =
			(control[i][0][Y] * 4.0) / 3.0 ;
	}

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_deth),
			valor_entero(c, c_detv), 0);
	glEndList();
	return lista;
}  /* }}} */


int crear_entrada(config_t c)
{  /* {{{ */
	int lista, i, textura;
	float radio = valor_decimal(c, c_e_ancho) / 2.0;
	float largo = -valor_decimal(c, c_e_largo);
	float alto  = valor_decimal(c, c_f_alto) - radio;
	float talto = alto / valor_decimal(c, c_f_alto);
	int   caras = valor_entero(c, c_e_det);
	float angulo      = 180.0 / (float)caras;
	float angulo_rad  = M_PI / (float)caras;
	float cos_angulo  = cosf(angulo_rad);
	float sin_angulo  = sinf(angulo_rad);
	float rcos_angulo = radio * cos_angulo;
	float rsin_angulo = radio * sin_angulo;
	float tx, ty, txo, tyo;

	textura = cargar_textura(c, valor_cadena(c, c_e_tex));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glColor3f(0.8, 0.8, 0.0);
	glDisable(GL_TEXTURE_2D);
	/* Laterales de la entrada */
	for (i = 0; i < 2; ++i) {
		tx = (i ? -1.0 : 1.0);
		glNormal3f(tx, 0.0, 0.0);
		glBegin(GL_QUADS);
		glVertex3f(tx * radio, 0.0, 0.0);
		glVertex3f(tx * radio, largo, 0.0);
		glVertex3f(tx * radio, largo, alto);
		glVertex3f(tx * radio, 0.0, alto);
		glEnd();
	}
	/* Arco superior */
	glPushMatrix();
	glTranslatef(0.0, 0.0, alto);
	for (i = 0; i < caras; ++i) {
		glPushMatrix();
		glRotatef(angulo * (float)i, 0.0, -1.0, 0.0);
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(radio, 0.0, 0.0);
		glVertex3f(radio, largo, 0.0);
		glNormal3f(cos_angulo, 0.0, sin_angulo);
		glVertex3f(rcos_angulo, largo, rsin_angulo);
		glVertex3f(rcos_angulo, 0.0, rsin_angulo);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	/* Puerta */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, -1.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-radio, largo, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(radio, largo, 0.0);
	glTexCoord2f(1.0, talto); glVertex3f(radio, largo, alto);
	glTexCoord2f(0.0, talto); glVertex3f(-radio, largo, alto);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0, 0.0, alto);
	txo = 1.0; tyo = talto;
	for (i = 0; i < caras; ++i) {
		tx = cosf(angulo_rad * (i+1)) / 2.0 + 0.5;
		ty = sinf(angulo_rad * (i+1)) * (1 - talto) + talto;
		glPushMatrix();
		glRotatef(angulo * i, 0.0, -1.0, 0.0);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5, talto); glVertex3f(0.0, largo, 0.0);
		glTexCoord2f(txo, tyo);   glVertex3f(radio, largo, 0.0);
		glTexCoord2f(tx, ty);
		glVertex3f(rcos_angulo, largo, rsin_angulo);
		glEnd();
		glPopMatrix();
		txo = tx;
		tyo = ty;
	}
	glPopMatrix();
	glEndList();
	return lista;
}  /* }}} */

