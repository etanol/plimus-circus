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

float r_horizontal = 0.0;
float r_vertical   = 0.0;
int lst_pieza;

/* Funciones auxiliares */
void teclado(unsigned char, int, int);
void rotar(int, int, int);
void display(void);


void activa_objeto(enum Pieza p, struct config *c)
{
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
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Test de piezas.");
	glutKeyboardFunc(teclado);
	glutSpecialFunc(rotar);
	glutDisplayFunc(display);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);

	activa_objeto((enum Pieza) choice, &cfg);
	glutMainLoop();
	return 0;
}

void teclado(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case '0':
			r_horizontal = 0.0;
			r_vertical   = 0.0;
			break;
		case 27:
			exit(0);
	}
	glutPostRedisplay();
}


void rotar(int tecla, int x, int y)
{
	switch (tecla) {
		case GLUT_KEY_LEFT:
			r_horizontal -= 3.0;
			break;
		case GLUT_KEY_RIGHT:
			r_horizontal += 3.0;
			break;
		case GLUT_KEY_DOWN:
			r_vertical -= 3.0;
			break;
		case GLUT_KEY_UP:
			r_vertical += 3.0;
			break;
	}
	glutPostRedisplay();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(r_horizontal, 0.0, 1.0, 0.0);
	glRotatef(r_vertical, 1.0, 0.0, 0.0);
	glCallList(lst_pieza);
	glutSwapBuffers();
}

