/*
 * test_superficie.c
 *
 * Programa para deformar superficies manualmente. Hay 16 puntos de control que
 * se pueden desplazar por el eje z con las teclas 'a' y 'z'. Para cambiar de
 * punto activo utilizar la tecla espacio.
 *
 * $Id$
 */

#include <GL/glut.h>
#include <stdlib.h>

/* Puntos de control */
GLfloat ctrlpoints[4][4][3] = {
	{{-1.5, -1.5, 0.0}, {-0.5, -1.5, 0.0},
	 {0.5, -1.5, 0.0}, {1.5, -1.5, 0.0}},
	{{-1.5, -0.5, 0.0}, {-0.5, -0.5, 0.0},
	 {0.5, -0.5, 0.0},  {1.5, -0.5, 0.0}},
	{{-1.5, 0.5, 0.0},  {-0.5, 0.5, 0.0},
	 {0.5, 0.5, 0.0},   {1.5, 0.5, 0.0}},
	{{-1.5, 1.5, 0.0}, {-0.5, 1.5, 0.0},
	 {0.5, 1.5, 0.0},   {1.5, 1.5, 0.0}}
};

float r_horizontal = 0.0;
float r_vertical   = 0.0;
int   dopoints = 0;
int   current = 0;

void initlights(void)
{
	GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
	GLfloat mat_diffuse[] = {0.8, 0.2, 1.0, 1.0};
	GLfloat mat_specular[] = {1.0, 0.6, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	initlights();
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

void teclado(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case '0':
			r_horizontal = 0.0;
			r_vertical   = 0.0;
			break;
		case ' ':
			++current;
			current %= 16;
			break;
		case 'a':
			ctrlpoints[0][current][2] += 0.1;
			break;
		case 'z':
			ctrlpoints[0][current][2] -= 0.1;
			break;
		case 27:
			exit(0);
	}
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, ctrlpoints[0][0]);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glLoadIdentity();
	glRotatef(r_horizontal, 0.0, 1.0, 0.0);
	glRotatef(r_vertical, 1.0, 0.0, 0.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
		glVertex3fv(*(*ctrlpoints+current));
	glEnd();
	glEnable(GL_LIGHTING);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(rotar);
	glutMainLoop();
	return 0;
}

