/*
 * test_superficie.c
 *
 * Programa para deformar superficies manualmente. Hay 16 puntos de control que
 * se pueden desplazar por el eje z con las teclas 'a' y 'z'. Para cambiar de
 * punto activo utilizar la tecla espacio.
 *
 * $Id$
 */

#include "rotaciones.C"  /* Movimiento del objeto */

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


void teclado(unsigned char tecla, int x, int y)
{
	switch (tecla) {
		case ' ':
			++current;
			current %= 16;
			break;
		case 'q':
			ctrlpoints[0][current][2] += 0.1;
			break;
		case 'a':
			ctrlpoints[0][current][2] -= 0.1;
			break;
	}
}


void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, ctrlpoints[0][0]);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	/* Init */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);

	initlights();
	init(display, teclado);

	glutMainLoop();
	return 0;
}

