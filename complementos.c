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
 * complementos.c
 *
 * Miscelánea de piezas para la escena.
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>

#include "piezas.h"


int crear_poste(struct config *c)
{
	int lista;
	float brillo[3] = {0.3, 0.3, 0.3};
	GLUquadricObj *cilindro;
	
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	cilindro = gluNewQuadric();
	gluQuadricDrawStyle(cilindro, GLU_FILL);
	gluQuadricOrientation(cilindro, GLU_OUTSIDE);
	gluQuadricNormals(cilindro, GLU_SMOOTH);
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_LIGHTING_BIT);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillo); 
	glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
	gluCylinder(cilindro, c->poste_radio, c->poste_radio,
			c->carpa_faldon_alto + c->carpa_techo_alto +
			c->poste_extra_alto, c->poste_caras, 4);
	glPushMatrix();
	glTranslatef(0.0, 0.0, c->carpa_faldon_alto + c->carpa_techo_alto +
			c->poste_extra_alto);
	gluDisk(cilindro, 0, c->poste_radio, c->poste_caras, 1);
	glPopMatrix();
	glPopAttrib();
	glEndList();
	gluDeleteQuadric(cilindro);
	return lista;
}


int crear_suelo(struct config *c)
{
	int lista;
	float limites[4][3] = {
		{-c->suelo_lado, -c->suelo_lado, 0.0},
		{-c->suelo_lado, c->suelo_lado, 0.0},
		{c->suelo_lado, -c->suelo_lado, 0.0},
		{c->suelo_lado, c->suelo_lado, 0.0}};
	float textura[4][2] = {
		{0.0, 0.0},
		{0.0, c->suelo_lado*2},
		{c->suelo_lado*2, 0.0},
		{c->suelo_lado*2, c->suelo_lado*2}};

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 6, 2, 0.0, 1.0, 3, 2, limites[0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
			textura[0]);
	glMapGrid2f(c->suelo_detalle, 0.0, 1.0, c->suelo_detalle, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, c->suelo_detalle, 0, c->suelo_detalle);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glEndList();
	return lista;
}


int crear_arena(struct config *c)
{
	int lista, i, j;
	float x = (c->carpa_frontal_ancho/2) - c->poste_radio - 0.1;
	float y = (c->carpa_lateral_radio) - c->gradas_largo-SEP_GRADAS_CARPA-0.5;
	float limites[4][3] = {
		{-x, -y, 0.001},
		{-x, y, 0.001},
		{x, -y, 0.001},
		{x, y, 0.001}};
	float textura[4][2] = {
		{0.0, 0.0},
		{0.0, y*4},
		{x*4, 0.0},
		{x*4, y*4}};
	float b_frontal[4][3] = {
		{-(x+0.05), -0.05, -0.05}, {-(x+0.05), -0.05, 0.05},
		{x+0.05, -0.05, 0.05}, {x+0.05, -0.05, -0.05}};
	float b_lateral[4][3] = {
		{0.05, y+0.05, -0.05}, {0.05, y+0.05, 0.05},
		{0.05, -(y+0.05), 0.05}, {0.05, -(y+0.05), -0.05}};

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 6, 2, 0.0, 1.0, 3, 2, limites[0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
			textura[0]);
	glMapGrid2f(c->arena_detalle, 0.0, 1.0, c->arena_detalle, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, c->arena_detalle, 0, c->arena_detalle);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glColor3f(0.8, 0.8, 0.8);
	glInterleavedArrays(GL_V3F, 0, b_frontal[0]);
	for (i = 0; i < 2; ++i) {
		glPushMatrix();
		glTranslatef(0.0, (i?y:-y), 0.0);
		for (j = 0; j < 3; ++j) {
			glPushMatrix();
			glRotatef(-90.0*j, 1.0, 0.0, 0.0);
			glNormal3f(0.0, -1.0, 0.0);
			glDrawArrays(GL_QUADS, 0, sizeof(b_frontal)/(3*sizeof(float)));
			glPopMatrix();
		}
		glPopMatrix();
	}
	glInterleavedArrays(GL_V3F, 0, b_lateral[0]);
	for (i = 0; i < 2; ++i) {
		glPushMatrix();
		glTranslatef((i?x:-x), 0.0, 0.0);
		for (j = 0; j < 3; ++j) {
			glPushMatrix();
			glRotatef(-90.0*j,0.0, 1.0, 0.0);
			glNormal3f(1.0, 0.0, 0.0);
			glDrawArrays(GL_QUADS, 0, sizeof(b_lateral)/(3*sizeof(float)));
			glPopMatrix();
		}
		glPopMatrix();
	}
	glEndList();
	return lista;
}

