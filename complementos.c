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
		{-20.0, -20.0, 0.0},
		{-20.0, 20.0, 0.0},
		{20.0, -20.0, 0.0},
		{20.0, 20.0, 0.0}};
	float textura[4][2] = {
		{0.0, 0.0},
		{0.0, 40.0},
		{40.0, 0.0},
		{40.0, 40.0}};

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
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glEndList();
	return lista;
}

