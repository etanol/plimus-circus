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
#include <GL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "piezas.h"
#include "textura.h"

int crear_poste(config_t c)
{
	int lista;
	float pradio = valor_decimal(c, p_radio);
	float altura = valor_decimal(c, c_f_alto) + valor_decimal(c, c_t_alto)
		+ valor_decimal(c, p_ealto);
	float brillo[4]  = {0.3, 0.3, 0.3, 1.0};
	
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
	glFrontFace(GL_CCW);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(valor_decimal(c, c_fr_ancho) / 2.0, 0.0, 0.0);
	glColor3f(0.7, 0.7, 0.7);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillo); 
	glMaterialf(GL_FRONT, GL_SHININESS, valor_decimal(c, p_brillo));
	gluCylinder(cilindro, pradio, pradio, altura, valor_entero(c, p_deth),
			valor_entero(c, p_detv));
	glTranslatef(0.0, 0.0, altura);
	glNormal3f(0.0, 0.0, 1.0);
	gluDisk(cilindro, 0, pradio, valor_entero(c, p_deth), 1);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CW);
	glPopAttrib();
	glEndList();
	gluDeleteQuadric(cilindro);
	return lista;
}


int crear_banqueta(config_t c)
{
	int lista, textura;
	float xpos, ypos;
	float alto = valor_decimal(c, b_alto);
	float rm   = valor_decimal(c, b_rmen);
	int   det  = valor_entero(c, b_det);
	float especular[4] = {1.0, 1.0, 1.0, 1.0};
	GLUquadric *cilindro;
	
	xpos = ((valor_decimal(c, c_fr_ancho)/2.0) - valor_decimal(c, p_radio) -
			valor_decimal(c, sa_psep)) / 2.0;
	ypos = (valor_decimal(c, c_l_radio) - valor_decimal(c, gs_largo) -
			valor_decimal(c, gs_sep) - valor_decimal(c, sa_gsep)) /
			2.0;
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
	glPushAttrib(GL_LIGHTING_BIT);
	glFrontFace(GL_CCW);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(xpos, ypos, 0.0);
	glColor3f(0.6, 0.6, 1.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT, GL_SHININESS, valor_decimal(c, b_brillo));
	gluCylinder(cilindro, valor_decimal(c, b_rmay), rm, alto, det, 1);
	glTranslatef(0.0, 0.0, alto);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	gluDisk(cilindro, 0, rm, det, 1);
	glPopMatrix();
	glFrontFace(GL_CW);
	glPopAttrib();
	glEndList();
	gluDeleteQuadric(cilindro);
	return lista;
}


int crear_cartel(config_t c)
{
	int lista, i, tfoto, textura;
	float x       = valor_decimal(c, crt_ancho) / 2.0;
	float grosor  = valor_decimal(c, crt_largo);
	float c_alto  = valor_decimal(c, crt_f_alto);
	float b_alto  = valor_decimal(c, crt_b_alto);
	float grosor2 = grosor / 2.0;
	float cartel[8][3] = {{-x, -grosor2, 0.0}, {-x, grosor2, 0.0},
		{-x, -grosor2, c_alto}, {-x, grosor2, c_alto},
		{x, -grosor2, c_alto}, {x, grosor2, c_alto}, {x, -grosor2, 0.0},
		{x, grosor2, 0.0}};
	float tcartel[8][2] = {{0.0, 0.0}, {grosor, 0.0},
		{0.0, c_alto+grosor*2.0}, {grosor, c_alto+grosor},
		{x*2.0+grosor*2.0, c_alto+grosor*2.0},
		{x*2.0+grosor, c_alto+grosor}, {x*2.0+grosor*2.0, 0.0},
		{x*2.0+grosor, grosor}};
	float base[8][3] = {{-grosor2, -grosor2, 0.0}, {-grosor2, grosor2, 0.0},
		{-grosor2, -grosor2, b_alto}, {-grosor2, grosor2, b_alto},
		{grosor2, -grosor2, b_alto}, {grosor2, grosor2, b_alto},
		{grosor2, -grosor2, 0.0}, {grosor2, grosor2, 0.0}};
	float tbase[8][2] = {{0.0, 0.0}, {grosor, 0.0},
		{0.0, b_alto+grosor*2.0}, {grosor, b_alto+grosor},
		{grosor*3.0, b_alto+grosor*2.0}, {grosor*2.0, b_alto+grosor},
		{grosor*3.0, 0.0}, {grosor*2.0, grosor}};
	float normales[6][3] = {{-1.0, 0.0, 0.0}, {0.0, -1.0, 0.0},
		{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}};
	GLubyte cara[6][4] = {{0, 1, 3, 2}, {0, 2, 4, 6}, {6, 4, 5, 7},
		{5, 3, 1, 7}, {2, 3, 5, 4}, {6, 7, 1, 0}};
	float foto[4][2] = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}};

	tfoto    = cargar_textura(c, valor_cadena(c, crt_foto));
	textura = cargar_textura(c, valor_cadena(c, crt_tex));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textura);
	/* Base del cartel */
	glVertexPointer(3, GL_FLOAT, 0, base[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, tbase[0]);
	for (i = 0; i < 4; ++i) {
		glNormal3fv(normales[i]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[i]);
	}
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[3]);
	/* Marco del cartel */
	glPushMatrix();
	glTranslatef(0.0, 0.0, b_alto);
	glVertexPointer(3, GL_FLOAT, 0, cartel[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, tcartel[0]);
	for (i = 0; i < 6; ++i) {
		if (i == 1)
			continue;
		glNormal3fv(normales[i]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[i]);
	}
	/* Foto */
	glBindTexture(GL_TEXTURE_2D, tfoto);
	glNormal3fv(normales[1]);
	glBegin(GL_QUADS);
	for (i = 0; i < 4; ++i) {
		glTexCoord2fv(foto[i]);
		glVertex3fv(cartel[cara[1][i]]);
	}
	glEnd();
	glPopMatrix();
	glEndList();
	return lista;
}


int crear_tablon(config_t c)
{
	int i, lista;
	int   detalle = valor_entero(c, t_b_det);
	float radio   = valor_decimal(c, t_b_radio);
	float x = valor_decimal(c, t_t_prop) * radio;
	float y = radio + valor_decimal(c, t_t_eancho);
	float z = valor_decimal(c, t_t_grueso);
	float especular[4] = {1.0, 1.0, 1.0, 1.0};
	float tabla[8][3] = {{-x, -y, 0.0}, {-x, y, 0.0}, {-x, -y, z},
		{-x, y, z}, {x, -y, z}, {x, y, z}, {x, -y, 0.0}, {x, y, 0.0}};
	float normales[6][3] = {{-1.0, 0.0, 0.0}, {0.0, -1.0, 0.0},
		{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}};
	GLubyte cara[6][4] = {{0, 1, 3, 2}, {0, 2, 4, 6}, {6, 4, 5, 7},
		{7, 5, 3, 1}, {2, 3, 5, 4}, {0, 6, 7, 1}};
	GLUquadric *bola;
	
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	bola = gluNewQuadric();
	gluQuadricDrawStyle(bola, GLU_FILL);
	gluQuadricOrientation(bola, GLU_OUTSIDE);
	gluQuadricNormals(bola, GLU_SMOOTH);
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_LIGHTING_BIT);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT, GL_SHININESS, valor_decimal(c, t_brillo));
	glPushMatrix();
	/* Bola */
	glFrontFace(GL_CCW);
	glTranslatef(0.0, 0.0, radio);
	glColor3f(0.1, 0.4, 0.1);
	gluSphere(bola, radio, detalle, detalle);
	glFrontFace(GL_CW);
	/* Tablon */
	glTranslatef(0.0, 0.0, radio); /* No importa glPushMatrix() */
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, tabla[0]);
	glColor3f(0.8, 0.3, 0.1);
	for (i = 0; i < 6; ++i) {
		glNormal3fv(normales[i]);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cara[i]);
	}
	glPopMatrix();
	glPopAttrib();
	glEndList();
	gluDeleteQuadric(bola);
	return lista;
}


int crear_arbol(config_t c)
{
	int lista, textura;
	float x = valor_decimal(c, ar_ancho) / 2.0;
	float z = valor_decimal(c, ar_alto);

	textura = cargar_textura(c, valor_cadena(c, ar_tex));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2i(0, 0); glVertex3f(-x, 0.0, 0.0);
	glTexCoord2i(0, 1); glVertex3f(-x, 0.0, z);
	glTexCoord2i(1, 1); glVertex3f(x, 0.0, z);
	glTexCoord2i(1, 0); glVertex3f(x, 0.0, 0.0);
	glEnd();
	glPopAttrib();
	glEndList();
	return lista;
}


int crear_sol(config_t c)
{
	int lista;
	GLUquadric *sol;

	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	sol = gluNewQuadric();
	gluQuadricDrawStyle(sol, GLU_FILL);
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glFrontFace(GL_CCW);
	glColor3f(1.0, 1.0, 0.0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	gluSphere(sol, valor_decimal(c, l_s_radio), valor_entero(c, l_s_det),
			valor_entero(c, l_s_det));
	glFrontFace(GL_CW);
	glPopAttrib();
	glEndList();
	gluDeleteQuadric(sol);
	return lista;
}


int crear_payaso(config_t c)
{
	int lista, textura;
	float x = valor_decimal(c, pa_ancho) / 2.0;
	float z = valor_decimal(c, pa_alto);

	/*
	 * NOTA: Lo de cambiar las normales está hecho a propósito para
	 * conseguir un efecto de iluminación curioso gracias a que colocamos
	 * el payaso justo debajo de un foco.
	 */
	textura = cargar_textura(c, valor_cadena(c, pa_i_tex));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.0 * valor_decimal(c, t_b_radio) + 
			valor_decimal(c, t_t_grueso));
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2i(1, 0); glVertex3f(x, 0.0, 0.0);
	glTexCoord2i(0, 0); glVertex3f(-x, 0.0, 0.0);
	glNormal3f(0.0, 0.0, 1.0); /* Ver NOTA */
	glTexCoord2i(0, 1); glVertex3f(-x, 0.0, z);
	glTexCoord2i(1, 1); glVertex3f(x, 0.0, z);
	glEnd();
	glPopMatrix();
	glEndList();
	return lista;
}


/* Esto es una chapuza de última hora */
int crear_payaso_ext(config_t c)
{
	int lista, textura;
	float x = valor_decimal(c, pa_ancho) / 2.0;
	float z = valor_decimal(c, pa_alto);

	textura = cargar_textura(c, valor_cadena(c, pa_e_tex));
	lista = glGenLists(1);
	if (lista == 0)
		return 0;
	glNewList(lista, GL_COMPILE);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2i(0, 0); glVertex3f(x, 0.0, 0.0);
	glTexCoord2i(1, 0); glVertex3f(-x, 0.0, 0.0);
	glTexCoord2i(1, 1); glVertex3f(-x, 0.0, z);
	glTexCoord2i(0, 1); glVertex3f(x, 0.0, z);
	glEnd();
	glPopAttrib();
	glEndList();
	return lista;
}

