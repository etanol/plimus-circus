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
 * escena.c
 *
 * Configuraci�n de la escena completa.
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>

/* 
 * NOTA MENTAL: Quiz� podr�amos poner la configuraci�n de las luces por
 * separado (luces.h, luces.c).
 */
#include "config.h"
#include "piezas.h"


/* Objetos de la escena */
static int 
	faldon_frontal,
	faldon_lateral,
	techo_frontal,
	techo_lateral,
	grada_frontal,
	grada_lateral;

/* Configuraci�n de la escena */
static struct config conf;


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

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	/*
	 * Ya que se dibuja todo visto desde arriba (como si se dibujara en
	 * planta) rotamos 90� sobre el eje X para orientarlo a la posici�n
	 * natural.
	 */
	glRotatef(90.0, -1.0, 0.0, 0.0);

	/* 
	 * TODO: Colocar todas las luces manteniendo las interiores apagadas y
	 * las exteriores encendidas. Dibujar el suelo exterior.
	 */
	glColor3f(0.8, 0.8, 0.0);

	/*
	 * Dibujamos la carpa. TODO: �Suelo interior?
	 */
	glPushMatrix();
	glTranslatef(0.0, conf.carpa_largo/2, 0.0);
	glCallList(faldon_frontal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -conf.carpa_largo/2, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glCallList(faldon_frontal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((conf.carpa_ancho-conf.carpa_largo)/2, 0.0, 0.0);
	glCallList(faldon_lateral);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(conf.carpa_ancho-conf.carpa_largo)/2, 0.0, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glCallList(faldon_lateral);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, conf.faldon_alto);
	glCallList(techo_frontal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, conf.faldon_alto);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glCallList(techo_frontal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((conf.carpa_ancho-conf.carpa_largo)/2, 0.0, conf.faldon_alto);
	glCallList(techo_lateral);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(conf.carpa_ancho-conf.carpa_largo)/2, 0.0, conf.faldon_alto);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glCallList(techo_lateral);
	glPopMatrix();

	/*
	 * Gradas
	 */
	glColor3f(0.7, 0.0, 0.1);
	glPushMatrix();
	glTranslatef(0.0, (conf.carpa_largo/2)-(conf.sep_gradas_carpa+conf.gradas_largo), 0.0);
	glCallList(grada_frontal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, conf.sep_gradas_carpa+conf.gradas_largo-(conf.carpa_largo/2), 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glCallList(grada_frontal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((conf.carpa_ancho-conf.carpa_largo)/2, 0.0, 0.0);
	glCallList(grada_lateral);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(conf.carpa_ancho-conf.carpa_largo)/2, 0.0, 0.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glCallList(grada_lateral);
	glPopMatrix();

	/*
	 * TODO: Apagar las luces exteriores, encender las luces interiores y
	 * dibujar los objetos del interior de la carpa.
	 */
	glPopMatrix();
	glutSwapBuffers();
}


void init_escena(struct config *cfg)
{

	glutDisplayFunc(escena);
	glutReshapeFunc(actualiza_viewport);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	memcpy(&conf, cfg, sizeof(struct config));

	faldon_frontal = crear_faldon_frontal(&conf);
	faldon_lateral = crear_faldon_lateral(&conf);
	techo_frontal  = crear_techo_frontal(&conf);
	techo_lateral  = crear_techo_lateral(&conf);
	grada_frontal  = crear_grada_frontal(&conf);
	grada_lateral  = crear_grada_lateral(&conf);
}
