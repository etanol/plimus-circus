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
 * escena.c
 *
 * Configuración de la escena completa.
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* 
 * NOTA MENTAL: Quizá podríamos poner la configuración de las luces por
 * separado (luces.h, luces.c).
 */
#include "piezas.h"

static void actualiza_viewport(int ancho, int alto)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)ancho / (GLdouble)alto, 0.5, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, ancho, alto);
	glutPostRedisplay();
}


static void escena(void)
{
	float alto_faldon = 1.5;
	float ancho = 2.0;
	float radio = 2.3;
	int num_caras = 20;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	/*
	 * Ya que se dibuja todo visto desde arriba (como si se dibujara en
	 * planta) rotamos 90º sobre el eje X para orientarlo a la posición
	 * natural.
	 */
	glRotatef(90.0, -1.0, 0.0, 0.0);

	/* 
	 * TODO: Colocar todas las luces manteniendo las interiores apagadas y
	 * las exteriores encendidas. Dibujar el suelo exterior.
	 */

	/*
	 * Dibujamos la carpa. TODO: ¿Suelo interior?
	 */
	glPushMatrix();
	glTranslatef(0.0, radio, 0.0);
	faldon_frontal(alto_faldon, ancho);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -radio, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	faldon_frontal(alto_faldon, ancho);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho / 2, 0.0, 0.0);
	faldon_lateral(radio, alto_faldon, num_caras);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(ancho / 2), 0.0, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	faldon_lateral(radio, alto_faldon, num_caras);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, alto_faldon);
	techo_frontal(radio, alto_faldon, ancho);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, alto_faldon);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	techo_frontal(radio, alto_faldon, ancho);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho / 2, 0.0, alto_faldon);
	techo_lateral(radio, alto_faldon, num_caras);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(ancho / 2), 0.0, alto_faldon);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	techo_lateral(radio, alto_faldon, num_caras);
	glPopMatrix();

	/*
	 * Gradas
	 */
	glPushMatrix();
	glTranslatef(0.0, (radio / 2) - 0.05, 0.0);
	grada_frontal(alto_faldon - 0.2, ancho - 0.3, radio / 2, 14);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -(radio / 2) + 0.05, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	grada_frontal(alto_faldon - 0.2, ancho - 0.3, radio / 2, 14);
	glPopMatrix();

	/*
	 * TODO: Apagar las luces exteriores, encender las luces interiores y
	 * dibujar los objetos del interior de la carpa.
	 */
	glPopMatrix();
	glutSwapBuffers();
}


void init_escena(void)
{
	glutDisplayFunc(escena);
	glutReshapeFunc(actualiza_viewport);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}
