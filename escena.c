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
 * escena.c
 *
 * Configuración de la escena completa.
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>

/* 
 * NOTA MENTAL: Quizá podríamos poner la configuración de las luces por
 * separado (luces.h, luces.c).
 */
#include "escena.h"
#include "interaccion.h"

/* Objetos de la escena */
static int 
	faldon_frontal,
	faldon_lateral,
	techo_frontal,
	techo_lateral,
	grada_frontal,
	grada_lateral,
	poste,
	suelo,
	arena,
	banco,
	cartel;

/* Configuración de la escena */
static struct config conf;
static struct texturas texs;


static void actualiza_viewport(int ancho, int alto)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(conf.fov, (GLdouble)ancho/(GLdouble)alto, 
			conf.z_near, conf.z_far);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, ancho, alto);
	glutPostRedisplay();
}


static void escena(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	actualiza_camara();
	/*
	 * Ya que se dibuja todo visto desde arriba (como si se dibujara en
	 * planta) rotamos 90º sobre el eje X para orientarlo a la posición
	 * natural.
	 */
	glRotatef(90.0, -1.0, 0.0, 0.0);
	/*
	 * Dibujamos el suelo.
	 */
	glBindTexture(GL_TEXTURE_2D, texs.suelo_exterior);
	glCallList(suelo);
	/*
	 * Dibujamos la carpa. TODO: ¿Suelo interior?
	 */
	glBindTexture(GL_TEXTURE_1D, texs.carpa);
	glPushMatrix();
		glTranslatef(0.0, conf.carpa_lateral_radio, 0.0);
		glCallList(faldon_frontal);
	glPopMatrix();
	glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(0.0, conf.carpa_lateral_radio, 0.0);
		glCallList(faldon_frontal);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(conf.carpa_frontal_ancho/2, 0.0, 0.0);
		glCallList(faldon_lateral);
	glPopMatrix();
	glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glTranslatef(conf.carpa_frontal_ancho/2, 0.0, 0.0);
		glCallList(faldon_lateral);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, conf.carpa_faldon_alto);
		glCallList(techo_frontal);
	glPopMatrix();
	glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(0.0, 0.0, conf.carpa_faldon_alto);
		glCallList(techo_frontal);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(conf.carpa_frontal_ancho/2, 0.0,
				conf.carpa_faldon_alto);
		glCallList(techo_lateral);
	glPopMatrix();
	glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glTranslatef(conf.carpa_frontal_ancho/2, 0.0,
				conf.carpa_faldon_alto);
		glCallList(techo_lateral);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, texs.plimus);
	glPushMatrix();
		glTranslatef(0.0, -(conf.carpa_lateral_radio+2.0), 0.0);
		glCallList(cartel);
	glPopMatrix();
	/*
	 * Arena (suelo interior)
	 */
	glBindTexture(GL_TEXTURE_2D, texs.arena);
	glCallList(arena);
	/*
	 * Bancos pa los tigretones
	 */
	glCallList(banco);
	/*
	 * Gradas
	 */
	glBindTexture(GL_TEXTURE_2D, texs.grada);
	glPushMatrix();
		glTranslatef(0.0, conf.carpa_lateral_radio - conf.gradas_largo
				- SEP_GRADAS_CARPA, 0.0);
		glCallList(grada_frontal);
	glPopMatrix();

	glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(0.0, conf.carpa_lateral_radio - conf.gradas_largo
				- SEP_GRADAS_CARPA, 0.0);
		glCallList(grada_frontal);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(conf.carpa_frontal_ancho/2, 0.0, 0.0);
		glCallList(grada_lateral);
	glPopMatrix();
	glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glTranslatef(conf.carpa_frontal_ancho/2, 0.0, 0.0);
		glCallList(grada_lateral);
	glPopMatrix();
	/*
	 * Postes
	 */
	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();
		glTranslatef(conf.carpa_frontal_ancho/2, 0.0, 0.0);
		glCallList(poste);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-conf.carpa_frontal_ancho/2, 0.0, 0.0);
		glCallList(poste);
	glPopMatrix();
	/*
	 * TODO: Apagar las luces exteriores, encender las luces interiores y
	 * dibujar los objetos del interior de la carpa.
	 */
	glFlush();
	glutSwapBuffers();
}


void init_escena(struct config *cfg, struct texturas *ts)
{
	memcpy(&conf, cfg, sizeof(struct config));
	memcpy(&texs, ts, sizeof(struct texturas));

	/* Creamos una textura 1D para la carpa, para molar */
	texs.carpa = gen_textura_carpa();

	glutDisplayFunc(escena);
	glutReshapeFunc(actualiza_viewport);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	faldon_frontal = crear_faldon_frontal(&conf);
	faldon_lateral = crear_faldon_lateral(&conf);
	techo_frontal  = crear_techo_frontal(&conf);
	techo_lateral  = crear_techo_lateral(&conf);
	grada_frontal  = crear_grada_frontal(&conf);
	grada_lateral  = crear_grada_lateral(&conf);
	poste          = crear_poste(&conf);
	suelo          = crear_suelo(&conf);
	arena          = crear_arena(&conf);
	banco          = crear_banco(&conf);
	cartel         = crear_cartel(&conf);
}

