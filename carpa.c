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

#ifndef CARPA_SIMPLE

#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#else
#include <glut.h>
#endif

#include "piezas.h"

#ifdef WIRED_CARPA
#define TIPO_RELLENO GL_LINE
#else
#define TIPO_RELLENO GL_FILL
#endif


int crear_faldon_frontal(struct config *c)
{
	int i, j, lista;
	float control[4][4][3];
	float texcoord[4] = {0.0, 2.5, 0.0, 2.5};
	float paso_z = c->carpa_faldon_alto / 3.0;
	float paso_x = c->carpa_frontal_ancho / 3.0;
	float x      = c->carpa_frontal_ancho / 2.0;
	
	for (i = 0; i < 4; ++i) 
		for (j = 0; j < 4; ++j) {
			control[i][j][X] = (j * paso_x) - x;
			control[i][j][Y] = (i ? 0.0 : CAIDA_FALDON);
			control[i][j][Z] = i * paso_z;
		}

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_1);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 12, 4, 0.0, 1.0, 3, 4,
			control[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_1, 0.0, 1.0, 0, 2, 0.0, 1.0, 1, 2,
			texcoord);
	glMapGrid2f(c->carpa_detalle_vert, 0.0, 1.0, c->carpa_detalle_horiz,
			0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glEvalMesh2(TIPO_RELLENO, 0, c->carpa_detalle_vert, 0,
			c->carpa_detalle_horiz);
	glDisable(GL_TEXTURE_1D);
	glEndList();
	return lista;
}	


int crear_faldon_lateral(struct config *c)
{
	int i, lista;
	float control[4][4][3];
	float texcoord[4] = {0.5, 6.0, 0.5, 6.0};
	float paso_z  = c->carpa_faldon_alto / 3.0;
	float caida_y = c->carpa_lateral_radio + CAIDA_FALDON; 

	for (i = 0; i < 4; ++i) {
		control[i][0][Z] = control[i][1][Z] = control[i][2][Z] = 
			control[i][3][Z] = i * paso_z;
		control[i][0][Y] = control[i][1][Y] = 
			(i ? c->carpa_lateral_radio : caida_y);
		control[i][2][Y] = control[i][3][Y] = 
			(i ? -c->carpa_lateral_radio : -caida_y);
		control[i][0][X] = control[i][3][X] = 0.0;
		control[i][1][X] = control[i][2][X] =
			(control[i][0][Y] * 4.0) / 3.0 ;
	}

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_1);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 12, 4, 0.0, 1.0, 3, 4,
			control[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_1, 0.0, 1.0, 0, 2, 0.0, 1.0, 1, 2,
			texcoord);
	glMapGrid2f(c->carpa_detalle_vert, 0.0, 1.0, c->carpa_detalle_horiz,
			0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glEvalMesh2(TIPO_RELLENO, 0, c->carpa_detalle_vert, 0,
			c->carpa_detalle_horiz);
	glDisable(GL_TEXTURE_1D);
	glEndList();
	return lista;
}


int crear_techo_frontal(struct config *c)
{
	int i, j, lista;
	float control[4][4][3];
	float texcoord[4] = {0.0, 2.5, 0.0, 2.5};
	float paso_x = c->carpa_frontal_ancho / 3.0;
	float paso_y = c->carpa_lateral_radio / 3.0;
	float paso_z = c->carpa_techo_alto    / 3.0;
	float x      = c->carpa_frontal_ancho / 2.0;
	float zeta[4] =
		{c->carpa_techo_alto, paso_z + (paso_z/2.0), paso_z/2.0, 0.0};

	for (i = 0; i < 4; ++i) 
		for (j = 0; j < 4; ++j) {
			control[i][j][X] = (paso_x * j) - x;
			control[i][j][Y] = i * paso_y;
			control[i][j][Z] = zeta[i];
		}
	/* Corrección para la caída entre poste y poste */
	control[0][1][Z] -= CAIDA_TECHO_POSTES;
	control[0][2][Z] -= CAIDA_TECHO_POSTES;

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_1);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4,
			control[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_1, 0.0, 1.0, 1, 2, 0.0, 1.0, 0, 2,
			texcoord);
	glMapGrid2f(c->carpa_detalle_horiz, 0.0, 1.0, c->carpa_detalle_vert,
			0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glEvalMesh2(TIPO_RELLENO, 0, c->carpa_detalle_horiz, 0,
			c->carpa_detalle_vert);
	glDisable(GL_TEXTURE_1D);
	glEndList();
	return lista;
}


int crear_techo_lateral(struct config *c)
{
	int i, lista;
	float control[4][4][3]; 
	float texcoord[4] = {0.5, 6.0, 0.5, 6.0};
	float paso_y = c->carpa_lateral_radio / 3.0;
	float paso_z = c->carpa_techo_alto    / 3.0;
	float zeta[4] = 
		{c->carpa_techo_alto, paso_z + (paso_z/2.0), paso_z/2.0, 0.0};

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
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_1);
	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4,
			control[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_1, 0.0, 1.0, 1, 2, 0.0, 1.0, 0, 2,
			texcoord);
	glMapGrid2f(c->carpa_detalle_horiz, 0.0, 1.0, c->carpa_detalle_vert,
			0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glEvalMesh2(TIPO_RELLENO, 0, c->carpa_detalle_horiz, 0,
			c->carpa_detalle_vert);
	glDisable(GL_TEXTURE_1D);
	glEndList();
	return lista;
}

#endif /* !CARPA_SIMPLE */
