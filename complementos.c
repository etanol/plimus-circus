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
	GLUquadricObj *cilindro;
	
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	cilindro = gluNewQuadric();
	gluQuadricDrawStyle(cilindro, GLU_FILL);
	gluQuadricOrientation(cilindro, GLU_OUTSIDE);
	gluQuadricNormals(cilindro, GLU_SMOOTH);
	glNewList(lista, GL_COMPILE);
	gluCylinder(cilindro, c->poste_radio, c->poste_radio,
			c->carpa_faldon_alto + c->carpa_techo_alto +
			c->poste_extra_alto, 8, 4);
	glPushMatrix();
	glTranslatef(0.0, 0.0, c->carpa_faldon_alto + c->carpa_techo_alto +
			c->poste_extra_alto);
	gluDisk(cilindro, 0, c->poste_radio, 8, 1);
	glPopMatrix();
	glEndList();
	gluDeleteQuadric(cilindro);
	return lista;
}
