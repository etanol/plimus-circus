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
 * test_pieza.c
 *
 * Programa para testear piezas individuales que se programen como funciones
 * del m�dulo "piezas.o".
 *
 * $Id$
 */

#define TEST_CONFIG "medidas_testpieza.cfg"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "piezas.h"

const char menu[] = 
"Piezas disponibles:\n\
\t(1) Fald�n frontal\n\
\t(2) Fald�n lateral\n\
\t(3) Techo frontal\n\
\t(4) Techo lateral\n\
\t(5) Grada frontal\n\
\t(6) Grada lateral\n\
Selecciona un n�mero: ";

enum Pieza {
	FALDON_FRONTAL = 1,
	FALDON_LATERAL,
	TECHO_FRONTAL,
	TECHO_LATERAL,
	GRADA_FRONTAL,
	GRADA_LATERAL
};

int lst_pieza;
int win_h, win_w;

/* Funciones auxiliares */
void teclado(unsigned char, int, int);
void display(void);
void ventana(int, int);


void activa_objeto(enum Pieza p, struct config *c)
{
	static GLfloat ejes[] = {
		0.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};
	switch (p) {
		case FALDON_FRONTAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_faldon_frontal(c);
			break;
		case FALDON_LATERAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_faldon_lateral(c);
			break;
		case TECHO_FRONTAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_techo_frontal(c);
			break;
		case TECHO_LATERAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_techo_lateral(c);
			break;
		case GRADA_FRONTAL:
			glColor3f(0.7, 0.0, 0.2);
			lst_pieza = crear_grada_frontal(c);
			break;
		case GRADA_LATERAL:
			glColor3f(0.7, 0.0, 0.2);
			lst_pieza = crear_grada_lateral(c);
			break;
		default:
			fputs("Pieza no reconocida.\n", stderr);
			exit(1);
	}
	if (lst_pieza == 0) {
		fputs("No se pudo crear la pieza.\n", stderr);
		exit(3);
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ejes);
}


int main(int argc, char **argv)
{
	int choice;
	struct config cfg;

	leer_config(TEST_CONFIG, &cfg);
	
	glutInit(&argc, argv);

	fwrite(menu, 1, sizeof(menu)-1, stdout);
	scanf("%d", &choice);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Test de piezas.");
	glutKeyboardFunc(teclado);
	glutDisplayFunc(display);
	glutReshapeFunc(ventana);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	activa_objeto((enum Pieza) choice, &cfg);
	glutMainLoop();
	return 0;
}


void ventana(int w, int h)
{
	win_w = w;
	win_h = h;
}


void teclado(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case '0':
			glLoadIdentity();
			break;
		case 'x':
			glRotatef(3.0, 1.0, 0.0, 0.0);
			break;
		case 'X':
			glRotatef(-3.0, 1.0, 0.0, 0.0);
			break;
		case 'y':
			glRotatef(3.0, 0.0, 1.0, 0.0);
			break;
		case 'Y':
			glRotatef(-3.0, 0.0, 1.0, 0.0);
			break;
		case 'z':
			glRotatef(3.0, 0.0, 0.0, 1.0);
			break;
		case 'Z':
			glRotatef(-3.0, 0.0, 0.0, 1.0);
			break;
		case 27:
			exit(0);
	}
	glutPostRedisplay();
}


void display(void)
{
	GLubyte todos[] = {0, 1, 0, 2, 0, 3};
	GLubyte ejex[] = {0, 1};
	GLubyte ejey[] = {0, 2};
	GLubyte ejez[] = {0, 3};

	/* Dibujamos la pieza */	
	glViewport(0, 0, win_w, win_h);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glCallList(lst_pieza);
	glPushMatrix(); /* 1 */

	/* Dibujamos el estado actual de la rotaci�n */
	glViewport(0, 0, win_w/5, win_h/5);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, todos);
	glPopMatrix(); /* 1 */
	glColor3f(1.0, 0.0, 0.0);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, ejex);
	glColor3f(0.0, 1.0, 0.0);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, ejey);
	glColor3f(0.0, 0.0, 1.0);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, ejez);
	glPopAttrib();
	glFlush();
	glutSwapBuffers();
}

