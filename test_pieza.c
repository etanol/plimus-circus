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
 * test_pieza.c
 *
 * Programa para testear piezas individuales que se programen como funciones
 * del módulo "piezas.o".
 *
 * $Id$
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "piezas.h"

const char menu[] = 
"Piezas disponibles:\n\
\t(1) Faldón frontal\n\
\t(2) Faldón lateral\n\
\t(3) Techo frontal\n\
\t(4) Techo lateral\n\n\
Selecciona (1 .. 4): ";

enum Pieza {
	FALDON_FRONTAL = 1,
	FALDON_LATERAL,
	TECHO_FRONTAL,
	TECHO_LATERAL
};

static float r_horizontal = 0.0;
static float r_vertical   = 0.0;
static enum Pieza p;

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
	switch (p) {
		case FALDON_FRONTAL:
			faldon_frontal(7.0, 4.0);
			break;
		case FALDON_LATERAL:
			faldon_lateral(4.0, 4.0, 25);
			break;
		case TECHO_FRONTAL:
//			techo_frontal(0.0, 0.0, 0.0);
			break;
		case TECHO_LATERAL:
			techo_lateral(4.0, 4.0, 25);
			break;
		default:
			printf("Pieza no reconocida.\n");
			exit(1);
	}
	glutSwapBuffers();
}


int main(int argc, char **argv)
{
	int choice;

	fwrite(menu, 1, sizeof(menu)-1, stdout);
	scanf("%d", &choice);
	p = (enum Pieza) choice;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Test de fichas.");
	glutKeyboardFunc(teclado);
	glutSpecialFunc(rotar);
	glutDisplayFunc(display);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
	return 0;
}

