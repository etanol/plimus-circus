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










void grada_frontal(float altura, float longitud, float profundidad, int num_esc)
{
	float paso_v, paso_h;
	int i;

	paso_v = altura / (float)num_esc;
	paso_h = profundidad / (float)num_esc;
	longitud /= 2;

	glBegin(GL_QUADS);
	/* Trasero */
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-longitud, profundidad, 0.0);
	glVertex3f(-longitud, profundidad, altura);
	glVertex3f(longitud, profundidad, altura);
	glVertex3f(longitud, profundidad, 0.0);
	/* Base */
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-longitud, 0.0, 0.0);
	glVertex3f(-longitud, profundidad, 0.0);
	glVertex3f(longitud, profundidad, 0.0);
	glVertex3f(longitud, 0.0, 0.0);
	glEnd();
	for (i = 0; i < num_esc; ++i) {
		glBegin(GL_QUADS);
		/* Escalón */
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-longitud, paso_h * i, paso_v * i);
		glVertex3f(-longitud, paso_h * i, paso_v * (i+1));
		glVertex3f(longitud, paso_h * i, paso_v * (i+1));
		glVertex3f(longitud, paso_h * i, paso_v * i);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-longitud, paso_h * i, paso_v * (i+1));
		glVertex3f(-longitud, paso_h * (i+1), paso_v * (i+1));
		glVertex3f(longitud, paso_h * (i+1), paso_v * (i+1));
		glVertex3f(longitud, paso_h * i, paso_v * (i+1));
		/* Laterales */
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-longitud, paso_h * i, 0.0);
		glVertex3f(-longitud, paso_h * i, paso_v * (i+1));
		glVertex3f(-longitud, paso_h * (i+1), paso_v * (i+1));
		glVertex3f(-longitud, paso_h * (i+1), 0.0);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(longitud, paso_h * i, 0.0);
		glVertex3f(longitud, paso_h * i, paso_v * (i+1));
		glVertex3f(longitud, paso_h * (i+1), paso_v * (i+1));
		glVertex3f(longitud, paso_h * (i+1), 0.0);
		glEnd();

	}
}


void grada_lateral(float radio_in, float radio_ex, float altura, 
		int num_esc, int num_caras, int exclude)
{
	float paso_v, paso_h, angulo, angulo_rad, sin_angulo, cos_angulo, r;
	int i, j;

	paso_v = altura / (float)num_esc;
	paso_h = (radio_ex - radio_in) / (float)num_esc;
	angulo = 180.0 / num_caras;
	angulo_rad = M_PI / num_caras;
	sin_angulo = sinf(angulo_rad);
	cos_angulo = cosf(angulo_rad);

	for (i = exclude; i < (num_caras - exclude); ++i) {
		glPushMatrix();
		glRotatef(-angulo * i, 0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		/* Escalones */
		for (j = 0; j < num_esc; ++j) {
			r = radio_in + paso_h*j;
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(0.0, r, paso_v * j);
			glVertex3f(0.0, r, paso_v * (j+1));
			glNormal3f(-sin_angulo, -cos_angulo, 0.0);
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * (j+1));
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * j);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, r, paso_v * (j+1));
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * (j+1));
			r = radio_in + paso_h*(j+1);
			glVertex3f(r*sin_angulo, r*cos_angulo, paso_v * (j+1));
			glVertex3f(0.0, r, paso_v * (j+1));
		}
		/* Base */
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, radio_in, 0.0);
		glVertex3f(0.0, radio_ex, 0.0);
		glVertex3f(radio_ex*sin_angulo, radio_ex*cos_angulo, 0.0);
		glVertex3f(radio_in*sin_angulo, radio_in*cos_angulo, 0.0);
		glEnd();
		glPopMatrix();
	}
	/* Laterales */
	glPushMatrix();
	glRotatef(-angulo * exclude, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
		for (i = 0; i < num_esc; ++i) {
			r = radio_in + paso_h*i;
			glVertex3f(0.0, r, 0.0);
			glVertex3f(0.0, r, paso_v * (i+1));
			glVertex3f(0.0, r + paso_h, paso_v * (i+1));
			glVertex3f(0.0, r + paso_h, 0.0);
		}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glRotatef(angulo * exclude, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		for (i = 0; i < num_esc; ++i) {
			r = radio_in + paso_h*i;
			glVertex3f(0.0, -r, 0.0);
			glVertex3f(0.0, -r, paso_v * (i+1));
			glVertex3f(0.0, -(r + paso_h), paso_v * (i+1));
			glVertex3f(0.0, -(r + paso_h), 0.0);
		}
	glEnd();
	glPopMatrix();
	/* Trasero */
	faldon_lateral(radio_ex, altura, num_caras, exclude);
}
