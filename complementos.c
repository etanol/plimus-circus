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

#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "piezas.h"
#include "textura.h"

int crear_poste(config_t c)
{  /* {{{ */
	int lista;
	float pradio = valor_decimal(c, p_radio);
	float altura = valor_decimal(c, c_f_alto) + valor_decimal(c, c_t_alto)
		+ valor_decimal(c, p_ealto);
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
	glColor3f(0.7, 0.7, 0.7);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillo); 
	glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
	gluCylinder(cilindro, pradio, pradio, altura, valor_entero(c, p_deth),
			valor_entero(c, p_detv));
	glPushMatrix();
	glTranslatef(0.0, 0.0, altura);
	gluDisk(cilindro, 0, pradio, valor_entero(c, p_deth), 1);
	glPopMatrix();
	glPopAttrib();
	glEndList();
	gluDeleteQuadric(cilindro);
	return lista;
}  /* }}} */


int crear_banqueta(config_t c)
{  /* {{{ */
	int lista, textura;
	float alto = valor_decimal(c, b_alto);
	float rm = valor_decimal(c, b_rmen);
	int  det = valor_entero(c, b_det);
	GLUquadric *cilindro;
	
	textura = cargar_textura(c, valor_cadena(c, b_tex));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	cilindro = gluNewQuadric();
	gluQuadricDrawStyle(cilindro, GLU_FILL);
	gluQuadricOrientation(cilindro, GLU_OUTSIDE);
	gluQuadricNormals(cilindro, GLU_SMOOTH);
	gluQuadricTexture(cilindro, GL_TRUE);
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glColor3f(0.6, 0.6, 1.0);
	gluCylinder(cilindro, valor_decimal(c, b_rmay), rm, alto, det, 1);
	glPushMatrix();
	glTranslatef(0.0, 0.0, alto);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	gluDisk(cilindro, 0, rm, det, 1);
	glPopMatrix();
	glPopAttrib();
	glEndList();
	gluDeleteQuadric(cilindro);
	return lista;
}  /* }}} */


int crear_cartel(config_t c)
{  /* {{{ */
	int lista, i, textura;
	float faldon_alto = valor_decimal(c, c_f_alto);
	float cartel[4][3] = {
		{-2.0, 0.05, 0.0},
		{-2.0, 0.05, 3.0},
		{2.0, 0.05, 3.0},
		{2.0, 0.05, 0.0}};
	float foto[4][2] = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}};

	textura = cargar_textura(c, valor_cadena(c, crt_foto));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cartel[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, foto[0]);
	/* Foto y marco */
	glPushMatrix();
		glTranslatef(0.0, 0.0, faldon_alto);
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(0.0, -1.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glDrawArrays(GL_QUADS, 0, 4);
		glPopMatrix();
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glColor3f(0.4, 0.2, 0.0);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDrawArrays(GL_QUADS, 0, 4);
		glBegin(GL_QUAD_STRIP);
		for (i = 0; i < 4; ++i) {
			glVertex3fv(cartel[i]);
			glVertex3f(cartel[i][0], -0.05, cartel[i][2]);
		}
		glEnd();
	glPopMatrix();
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-0.05, -0.05, 0.0);
	glVertex3f(-0.05, -0.05, faldon_alto);
	glVertex3f(0.05, -0.05, 0.0);
	glVertex3f(0.05, -0.05, faldon_alto);
	glVertex3f(0.05, 0.05, 0.0);
	glVertex3f(0.05, 0.05, faldon_alto);
	glVertex3f(-0.05, 0.05, 0.0);
	glVertex3f(-0.05, 0.05, faldon_alto);
	glVertex3f(-0.05, -0.05, 0.0);
	glVertex3f(-0.05, -0.05, faldon_alto);
	glEnd();
	glPopAttrib();
	glEndList();
	return lista;
}  /* }}} */


int crear_tablon(config_t c)
{  /* {{{ */
	int lista;
	float radio = 0.2;
	GLUquadric *bola;
	
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	bola = gluNewQuadric();
	gluQuadricDrawStyle(bola, GLU_FILL);
	gluQuadricOrientation(bola, GLU_OUTSIDE);
	gluQuadricNormals(bola, GLU_SMOOTH);
	glNewList(lista, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.0, 0.0, radio);
	glColor3f(0.1, 0.4, 0.1);
	gluSphere(bola, radio, 20, 10);
	glColor3f(0.8, 0.3, 0.1);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-1.0, radio, radio);
	glVertex3f(-1.0, -radio, radio);
	glVertex3f(1.0, -radio, radio);
	glVertex3f(1.0, radio, radio);
	glEnd();
	glPopMatrix();
	glEndList();
	gluDeleteQuadric(bola);
	return lista;
}  /* }}} */

int crear_arbol(config_t c)
{  /* {{{ */
	int lista, textura;
	float x = valor_decimal(c, ar_ancho) / 2.0;
	float z = valor_decimal(c, ar_alto);

	textura = cargar_textura(c, valor_cadena(c, ar_tex));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, textura);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2i(0, 0); glVertex3f(-x, 0.0, 0.0);
	glTexCoord2i(0, 1); glVertex3f(-x, 0.0, z);
	glTexCoord2i(1, 1); glVertex3f(x, 0.0, z);
	glTexCoord2i(1, 0); glVertex3f(x, 0.0, 0.0);
	glEnd();
	glEndList();
	return lista;
}  /* }}} */

