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
 * test_pieza.c
 *
 * Programa para testear piezas individuales que se programen como funciones
 * del módulo "piezas.o".
 *
 * $Id$
 */

#define TEST_CONFIG "test_pieza.cfg"

#include <stdio.h>
#include <stdlib.h>
#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif

#include "config.h"
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

int lst_pieza;
int win_h, win_w;

/* Funciones auxiliares */
void teclado(unsigned char, int, int);
void display(void);
void ventana(int, int);


void activa_objeto(enum Pieza p, config_t c)
{
	static GLfloat ejes[] = {
		0.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};
	switch (p) {
		case FALDON_FRONTAL:
			lst_pieza = crear_faldon_frontal(c);
			break;
		case FALDON_LATERAL:
			lst_pieza = crear_faldon_lateral(c);
			break;
		case TECHO_FRONTAL:
			lst_pieza = crear_techo_frontal(c);
			break;
		case TECHO_LATERAL:
			lst_pieza = crear_techo_lateral(c);
			break;
		case GRADA_FRONTAL:
			lst_pieza = crear_grada_frontal(c);
			break;
		case GRADA_LATERAL:
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
	config_t cfg;
	int bits[5];

	cfg = leer_config(TEST_CONFIG);
	
	glutInit(&argc, argv);

	fwrite(menu, 1, sizeof(menu)-1, stdout);
	scanf("%d", &choice);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(valor_entero(cfg, v_width),
			valor_entero(cfg, v_height));
	glutInitWindowPosition(valor_entero(cfg, v_posx),
			valor_entero(cfg, v_posy));
	glutCreateWindow(valor_cadena(cfg, v_title));
	glutKeyboardFunc(teclado);
	glutDisplayFunc(display);
	glutReshapeFunc(ventana);

	glGetIntegerv(GL_RED_BITS, bits);
	glGetIntegerv(GL_GREEN_BITS, bits + 1);
	glGetIntegerv(GL_BLUE_BITS, bits + 2);
	glGetIntegerv(GL_ALPHA_BITS, bits + 3);
	glGetIntegerv(GL_DEPTH_BITS, bits + 4);
	printf("R: %2d, G: %2d, B: %2d, A: %2d, Prof: %2d\n", bits[0], bits[1],
		bits[2], bits[3], bits[4]);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	activa_objeto((enum Pieza) choice, cfg);
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glCallList(lst_pieza);
	glPushMatrix(); /* 1 */

	/* Dibujamos el estado actual de la rotación */
	glViewport(0, 0, win_w/5, win_h/5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushAttrib(GL_CURRENT_BIT|GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
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

