/*
 * bezcurve.c
 *
 * Ejemplo de superficies de Bézier con iluminación utilizando OpenGL
 * Evaluators. Sacado del "libro rojo"
 *
 * $Id$
 */

#include <GL/glut.h>
#include <stdlib.h>

/* Puntos de control */
GLfloat ctrlpoints[4][4][3] = {
	{{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
	 {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
	{{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
	 {0.5, -0.5, 0.0},  {1.5, -0.5, -1.0}},
	{{-1.5, 0.5, 4.0},  {-0.5, 0.5, 0.0},
	 {0.5, 0.5, 3.0},   {1.5, 0.5, 4.0}},
	{{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
	 {0.5, 1.5, 0.0},   {1.5, 1.5, -1.0}}
};


void initlights(void)
{
	GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
	GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
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
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, ctrlpoints[0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	initlights();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(85.0, 1.0, 1.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	glPopMatrix();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

