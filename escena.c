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

#include <string.h>
#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif

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
static struct config *C;
static struct texturas *T;


static void actualiza_viewport(int ancho, int alto)
{   /* {{{ */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(C->fov, (GLdouble)ancho / (GLdouble)alto, 
			C->z_near, C->z_far);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, ancho, alto);
	glutPostRedisplay();
}  /* }}} */


static void escena(void)
{   /* {{{ */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	actualiza_camara();
	/*
	 * Ya que se dibuja todo visto desde arriba (como si se dibujara en
	 * planta) rotamos 90º sobre el eje X para orientarlo a la posición
	 * natural.
	 */
	glRotatef(90.0, -1.0, 0.0, 0.0);

	/* Suelo */
	glBindTexture(GL_TEXTURE_2D, T->suelo_exterior);
	glCallList(suelo);
	if (modo_exterior) {
		/* Carpa */
		glBindTexture(GL_TEXTURE_1D, T->carpa);
		glPushMatrix();
		glTranslatef(0.0, C->carpa_lateral_radio, 0.0);
		glCallList(faldon_frontal);
		glPopMatrix();
		glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(0.0, C->carpa_lateral_radio, 0.0);
		glCallList(faldon_frontal);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(C->carpa_frontal_ancho / 2.0, 0.0, 0.0);
		glCallList(faldon_lateral);
		glPopMatrix();
		glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glTranslatef(C->carpa_frontal_ancho / 2.0, 0.0, 0.0);
		glCallList(faldon_lateral);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0, C->carpa_faldon_alto);
		glCallList(techo_frontal);
		glPopMatrix();
		glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(0.0, 0.0, C->carpa_faldon_alto);
		glCallList(techo_frontal);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(C->carpa_frontal_ancho / 2.0, 0.0,
				C->carpa_faldon_alto);
		glCallList(techo_lateral);
		glPopMatrix();
		glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glTranslatef(C->carpa_frontal_ancho / 2.0, 0.0,
				C->carpa_faldon_alto);
		glCallList(techo_lateral);
		/* Cartel */
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, T->plimus);
		glPushMatrix();
		glTranslatef(0.0, -(C->carpa_lateral_radio + 2.0), 0.0);
		glCallList(cartel);
		glPopMatrix();
	} else {
		/* Arena (suelo interior) */
		glBindTexture(GL_TEXTURE_2D, T->arena);
		glCallList(arena);
		/* Bancos pa los tigretones */
		glCallList(banco);
		/* Gradas */
		glBindTexture(GL_TEXTURE_2D, T->grada);
		glPushMatrix();
		glTranslatef(0.0, C->carpa_lateral_radio - C->gradas_largo
				- SEP_GRADAS_CARPA, 0.0);
		glCallList(grada_frontal);
		glPopMatrix();
		glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(0.0, C->carpa_lateral_radio - C->gradas_largo
				- SEP_GRADAS_CARPA, 0.0);
		glCallList(grada_frontal);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(C->carpa_frontal_ancho / 2.0, 0.0, 0.0);
		glCallList(grada_lateral);
		glPopMatrix();
		glPushMatrix();
		glScalef(-1.0, 1.0, 1.0);
		glTranslatef(C->carpa_frontal_ancho / 2.0, 0.0, 0.0);
		glCallList(grada_lateral);
		glPopMatrix();
	}
	/* Postes */
	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslatef(C->carpa_frontal_ancho / 2.0, 0.0, 0.0);
	glCallList(poste);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-C->carpa_frontal_ancho / 2.0, 0.0, 0.0);
	glCallList(poste);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}   /* }}} */


void init_escena(struct config *cfg, struct texturas *ts)
{  /* {{{ */
	C = cfg;
	T = ts;

	/* Creamos una textura 1D para la carpa, para molar */
	T->carpa = gen_textura_carpa();

	glutDisplayFunc(escena);
	glutReshapeFunc(actualiza_viewport);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	faldon_frontal = crear_faldon_frontal(C);
	faldon_lateral = crear_faldon_lateral(C);
	techo_frontal  = crear_techo_frontal(C);
	techo_lateral  = crear_techo_lateral(C);
	grada_frontal  = crear_grada_frontal(C);
	grada_lateral  = crear_grada_lateral(C);
	poste          = crear_poste(C);
	suelo          = crear_suelo(C);
	arena          = crear_arena(C);
	banco          = crear_banco(C);
	cartel         = crear_cartel(C);
}  /* }}} */

