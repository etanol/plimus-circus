/*
 * test_curva.c
 *
 * Programa similar a test_superficie simplificado para las curvas en el plano.
 * 
 * $Id$
 */

#include <GL/glut.h>
#include <stdlib.h>

/* Puntos de control */
GLfloat ctrlpoints[4][3] = {{-1.5, 0.0, 0.0}, {-0.5, 0.0, 0.0},
	 {0.5, 0.0, 0.0}, {1.5, 0.0, 0.0}};

int current = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void teclado2(int tecla, int x, int y)
{
	switch (tecla) {
		case GLUT_KEY_LEFT:
			ctrlpoints[current][0] -= 0.1;
			break;
		case GLUT_KEY_RIGHT:
			ctrlpoints[current][0] += 0.1;
			break;
		case GLUT_KEY_DOWN:
			ctrlpoints[current][1] -= 0.1;
			break;
		case GLUT_KEY_UP:
			ctrlpoints[current][1] += 0.1;
			break;
	}
	glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y)
{
	int i;
	float j;

	switch (tecla) {
		case '0':
			for (i = 0, j = -1.5; i < 4; ++i, j += 1.0) {
				ctrlpoints[i][0] = j;
				ctrlpoints[i][1] = 0.0;
			}
			break;
		case ' ':
			++current;
			current %= 4;
			break;
		case 27:
			exit(0);
	}
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, ctrlpoints[0]);
	glMapGrid1f(20, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glEvalMesh1(GL_LINE, 0, 20);
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		glVertex3fv(ctrlpoints[current]);
	glEnd();
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
	glutSpecialFunc(teclado2);
	glutMainLoop();
	return 0;
}

