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
 * carpa.c
 *
 * Piezas necesarias para dibujar la carpa
 *
 * $Id$
 */

#if !defined CARPA_SIMPLE

#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#else
#include <GL/glut.h>
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
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_detv),
			valor_entero(c, c_deth), 1);
	glPopAttrib();
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
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_detv),
			valor_entero(c, c_deth), 1);
	glPopAttrib();
	glEndList();
	return lista;
}  /* }}} */


int crear_techo_frontal(config_t c)
{  /* {{{ */
	int i, j, lista;
	float control[4][4][3];
	float texcoord[8] = {0.0, 0.0, 2.5, 0.0, 0.0, 1.0, 2.5, 1.0};
	float paso_x = valor_decimal(c, c_fr_ancho) / 3.0;
	float paso_y = valor_decimal(c, c_l_radio) / 3.0;
	float paso_z = valor_decimal(c, c_t_alto) / 3.0;
	float x      = valor_decimal(c, c_fr_ancho) / 2.0;
	float zeta[4] = {valor_decimal(c, c_t_alto), paso_z + (paso_z/2.0),
		paso_z/2.0, 0.0};

	if (!carpa_textura)
		carpa_textura = gen_textura_carpa();

	for (i = 0; i < 4; ++i) 
		for (j = 0; j < 4; ++j) {
			control[i][j][X] = (paso_x * j) - x;
			control[i][j][Y] = i * paso_y;
			control[i][j][Z] = zeta[i];
		}
	/* Correcci�n para la ca�da entre poste y poste */
	control[0][1][Z] -= valor_decimal(c, c_t_caidap);
	control[0][2][Z] -= valor_decimal(c, c_t_caidap);

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_deth),
			valor_entero(c, c_detv), 0);
	glPopAttrib();
	glEndList();
	return lista;
}  /* }}} */


int crear_techo_lateral(config_t c)
{  /* {{{ */
	int i, lista;
	float control[4][4][3]; 
	float texcoord[8] = {0.5, 0.0, 6.0, 0.0, 0.5, 1.0, 6.0, 1.0};
	float paso_y = valor_decimal(c, c_l_radio) / 3.0;
	float paso_z = valor_decimal(c, c_t_alto) / 3.0;
	float zeta[4] = { valor_decimal(c, c_t_alto), paso_z + (paso_z/2.0),
		paso_z/2.0, 0.0 };

	if (!carpa_textura)
		carpa_textura = gen_textura_carpa();

	for (i = 0; i < 4; ++i) {
		control[i][0][Z] = control[i][1][Z] = control[i][2][Z] =
			control[i][3][Z] = zeta[i];
		control[i][0][Y] = control[i][1][Y] = (i?paso_y * i:0.0001);
		control[i][2][Y] = control[i][3][Y] = (i?-paso_y * i:-0.0001);
		control[i][0][X] = control[i][3][X] = 0.0;
		control[i][1][X] = control[i][2][X] =
			(control[i][0][Y] * 4.0) / 3.0 ;
	}

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, carpa_textura);
	evaluator(control[0][0], texcoord, valor_entero(c, c_deth),
			valor_entero(c, c_detv), 0);
	glPopAttrib();
	glEndList();
	return lista;
}  /* }}} */

#endif /* !CARPA_SIMPLE */
