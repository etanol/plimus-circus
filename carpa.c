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
 * carpa.c
 *
 * Piezas necesarias para dibujar la carpa
 *
 * $Id$
 */

#include <GL/gl.h>
#include <math.h>

#include "piezas.h"


int crear_faldon_frontal(float altura, float longitud)
{
	int lista;
	float x = longitud / 2;
	float normal[][3] = {
		{0.0, 1.0, 0.0}
	};
	float datos[] = {
		normal[0][X], normal[0][Y], normal[0][Z],
		-x, 0.0, 0.0,
		normal[0][X], normal[0][Y], normal[0][Z],
		-x, 0.0, altura,
		normal[0][X], normal[0][Y], normal[0][Z],
		x, 0.0, altura,
		normal[0][X], normal[0][Y], normal[0][Z],
		x, 0.0, 0.0
	};

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glInterleavedArrays(GL_N3F_V3F, 0, datos);
	glDrawArrays(GL_QUADS, 0, sizeof(datos)/(6*sizeof(float)));
	glEndList();
	return lista;
}	


int crear_faldon_lateral(float radio, float altura, int num_caras)
{
	int i, lista;
	float angulo     = 180.0 / num_caras;
	float angulo_rad = M_PI  / num_caras;
	float cos_angulo = cosf(angulo_rad);
	float sin_angulo = sinf(angulo_rad);
	float normal[][3] = {
		{0.0, 1.0, 0.0},
		{sin_angulo, cos_angulo, 0.0}
	};
	float datos[] = {
		normal[0][X], normal[0][Y], normal[0][Z],
		0.0, radio, 0.0,
		normal[0][X], normal[0][Y], normal[0][Z],
		0.0, radio, altura,
		normal[1][X], normal[1][Y], normal[1][Z],
		radio*sin_angulo, radio*cos_angulo, altura,
		normal[1][X], normal[1][Y], normal[1][Z],
		radio*sin_angulo, radio*cos_angulo, 0.0
	};

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glInterleavedArrays(GL_N3F_V3F, 0, datos);
	for (i = 0; i < num_caras; ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glDrawArrays(GL_QUADS, 0, sizeof(datos)/(6*sizeof(float)));
		glPopMatrix();
	}
	glEndList();
	return lista;
}


int crear_techo_frontal(float radio, float altura, float longitud)
{
	int lista;
	float x = longitud / 2;
	float hipotenusa = hypotf(altura, radio);
	float normal[][3] = {
		{0.0, altura/hipotenusa, radio/hipotenusa}
	};
	float datos[] = {
		normal[0][X], normal[0][Y], normal[0][Z],
		x, 0.0, altura,
		normal[0][X], normal[0][Y], normal[0][Z],
		-x, 0.0, altura,
		normal[0][X], normal[0][Y], normal[0][Z],
		-x, radio, 0.0,
		normal[0][X], normal[0][Y], normal[0][Z],
		x, radio, 0.0
	};

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glInterleavedArrays(GL_N3F_V3F, 0, datos);
	glDrawArrays(GL_QUADS, 0, sizeof(datos)/(6*sizeof(float)));
	glEndList();
	return lista;
}


int crear_techo_lateral(float radio, float altura, int num_caras)
{
	int i, lista;
	float angulo     = 180.0 / num_caras;
	float angulo_rad = M_PI  / num_caras;
	float cos_angulo = cosf(angulo_rad);
	float sin_angulo = sinf(angulo_rad);
	float hipotenusa = hypotf(altura, radio);
	float altDhip    = altura / hipotenusa;
	float radDhip    = radio  / hipotenusa;
	float normal[][3] = {
		{altDhip*sinf(angulo_rad/2), altDhip*cosf(angulo_rad/2), radDhip},
		{0.0, altDhip, radDhip},
		{altDhip*sin_angulo, altDhip*cos_angulo, radDhip}
	};
	float datos[] = {
		normal[0][X], normal[0][Y], normal[0][Z],
		0.0, 0.0, altura,
		normal[1][X], normal[1][Y], normal[1][Z],
		0.0, radio, 0.0,
		normal[2][X], normal[2][Y], normal[2][Z],
		radio*sin_angulo, radio*cos_angulo, 0.0
	};

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glInterleavedArrays(GL_N3F_V3F, 0, datos);
	for (i = 0; i < num_caras; ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(datos)/(6*sizeof(float)));
		glPopMatrix();
	}
	glEndList();
	return lista;
}

