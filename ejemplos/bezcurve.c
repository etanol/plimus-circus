/*
 * bezcurve.c
 *
 * Ejemplo de curvas de Bézier utilizando OpenGL Evaluators. Sacado del "libro
 * rojo".
 */

#include <gl_headers.h>
#include <stdlib.h>

/* Puntos de control */
GLfloat ctrlpoints[4][3] = {
        {-4.0, -4.0, 0.0}, {-2.0, 4.0, 0.0},
        {2.0, -4.0, 0.0},  {4.0, 4.0, 0.0}};


void init(void)
{
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_FLAT);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, ctrlpoints[0]);
        glEnable(GL_MAP1_VERTEX_3);
        glMapGrid1f(30, 0.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}


void display(void)
{
        int i;

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        glEvalMesh1(GL_LINE, 0, 30);
        /* Y mostramos los puntos de control */
        glPointSize(5.0);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (i = 0; i < 4; ++i)
                glVertex3fv(ctrlpoints[i]);
        glEnd();
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

