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
\t(4) Techo lateral\n\
\t(5) Grada frontal\n\
\t(6) Grada lateral\n\
Selecciona un número: ";

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

/* Parámetros para dibujar las piezas */
const float altura      = 7.0;
const float longitud    = 9.0;
const float profundidad = 10.0;
const float radio_ext   = 9.0;
const float radio_int   = 3.0;
int caras     = 25;
int escalones = 14;
int omitir    = 0;

/* Funciones auxiliares */
void teclado(unsigned char, int, int);
void rotar(int, int, int);
void display(void);


void activa_objeto(enum Pieza p)
{
	switch (p) {
		case FALDON_FRONTAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_faldon_frontal(altura, longitud);
			break;
		case FALDON_LATERAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_faldon_lateral(radio_ext, altura,
					caras);
			break;
		case TECHO_FRONTAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_techo_frontal(radio_ext, altura,
					longitud);
			break;
		case TECHO_LATERAL:
			glColor3f(0.8, 0.8, 0.0);
			lst_pieza = crear_techo_lateral(radio_ext, altura,
					caras);
			break;
		case GRADA_FRONTAL:
			glColor3f(0.7, 0.0, 0.2);
			lst_pieza = crear_grada_frontal(altura, longitud,
					profundidad, escalones);
			break;
		case GRADA_LATERAL:
			glColor3f(0.7, 0.0, 0.2);
			lst_pieza = crear_grada_lateral(radio_int, radio_ext,
					altura, caras, escalones);
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

	glutInit(&argc, argv);
	if (argc > 1) {
		choice = strtol(argv[1], (char **)NULL, 10);
		if (choice > 0)
			caras = choice;
		--argc;
	}
	if (argc > 1) {
		choice = strtol(argv[2], (char **)NULL, 10);
		if (choice > 0)
			escalones = choice;
		--argc;
	}
	if (argc > 1) 
		omitir = strtol(argv[3], (char **)NULL, 10);

	fwrite(menu, 1, sizeof(menu)-1, stdout);
	scanf("%d", &choice);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Test de fichas.");
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

	activa_objeto((enum Pieza) choice);
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

