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
 * piezas.c
 *
 * Implementación del dibujado de piezas con escalado (sin usar glScalef()).
 *
 * $Id$
 */

#include <GL/gl.h>
#include <math.h>

/*
 * COMENTARIOS GLOBALES:
 *
 * Las piezas se dibujan vistas en planta; es decir, la altura del objeto viene
 * determinada por el eje Z. Corresponde a los niveles superiores rotar y
 * trasladar los objetos según deseen.
 */


void faldon_frontal(float altura, float longitud)
{
	float x = longitud / 2;

	glColor3f(0.8, 0.8, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-x, 0.0, 0.0);
	glVertex3f(-x, 0.0, altura);
	glVertex3f(x, 0.0, altura);
	glVertex3f(x, 0.0, 0.0);
	glEnd();
}	


void faldon_lateral(float radio, float altura, int num_caras)
{
	float angulo, angulo_rad, cos_angulo, sin_angulo, x, y;
	int i;

	angulo     = 180.0 / num_caras;
	angulo_rad = M_PI / num_caras;
	cos_angulo = cosf(angulo_rad);
	sin_angulo = sinf(angulo_rad);
	x = radio * sin_angulo;
	y = radio * cos_angulo;

	glColor3f(0.8, 0.8, 0.0);
	for (i = 0; i < num_caras; ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, radio, 0.0);
		glVertex3f(0.0, radio, altura);
		glNormal3f(sin_angulo, cos_angulo, 0.0);
		glVertex3f(x, y, altura);
		glVertex3f(x, y, 0.0);
		glEnd();
		glPopMatrix();
	}
}


void techo_frontal(float radio, float altura, float longitud)
{
	float x = longitud / 2;

	glColor3f(0.8, 0.8, 0.0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(x, 0.0, altura);
	glVertex3f(-x, 0.0, altura);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-x, radio, 0.0);
	glVertex3f(x, radio, 0.0);
	glEnd();
}


void techo_lateral(float radio, float altura, int num_caras)
{
	float angulo, angulo_rad, cos_angulo, sin_angulo, x, y;
	int i;

	angulo     = 180.0 / num_caras;
	angulo_rad = M_PI / num_caras;
	cos_angulo = cosf(angulo_rad);
	sin_angulo = sinf(angulo_rad);
	x = radio * sin_angulo;
	y = radio * cos_angulo;

	glColor3f(0.8, 0.8, 0.0);
	for (i = 0; i < num_caras; ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, altura);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, radio, 0.0);
		glNormal3f(sin_angulo, cos_angulo, 0.0);
		glVertex3f(x, y, 0.0);
		glEnd();
		glPopMatrix();
	}
}

