/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                            I N F O R M � T I C A                            |
 |                                G R � F I C A                                |
 |                                                                             |
 |                                                                             |
 |       Alumnos : Isaac Jurado Peinado        (etanol@telefonica.net)         |
 |                 Esteban Mart�nez Tristancho (estebanmartinez@ono.com)       |
 |       Estudios: Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)         |
 |       Curso   : 2003/2004                                                   |
 |       Facultad: Universitat de les Illes Balears (UIB)                      |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * complementos.c
 *
 * Miscel�nea de piezas para la escena.
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
