/*
 * simple.c
 *
 * El planeta de los quemaos.
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static int planeta = 0, radio = 3.0, velocidad = 50;
float w[4] = {0.0, 0.0, 0.0, 1.0};      /* Posición de la luz solar */


void init(void)
{
        glClearColor(0.5, 0.72, 0.95, 0.0);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}


void display(void)
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* Rotamos el universo */
        glLoadIdentity();
        gluLookAt(-4.5, 5.5, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);

        /* Sol */
        glPushMatrix();
                glColor3f(1.0, 1.0, 0.0);
                glDisable(GL_LIGHTING);
                glLightfv(GL_LIGHT0, GL_POSITION, w);
                glutSolidSphere(1.0, 30, 30);
                glEnable(GL_LIGHTING);
        glPopMatrix();

        /* Planeta */
        glPushMatrix();
                glRotatef((GLfloat) planeta, 0.0, 0.0, 1.0);
                glTranslatef(radio, 0.0, 0.0);
                glRotatef((GLfloat) planeta, 0.0, 0.0, 1.0);
                glColor3f(0.2, 0.8, 0.2);
                glutSolidSphere(0.5, 30, 30);

                /* Luna */
                glPushMatrix();
                        glRotatef((GLfloat) planeta * 2, 0.0, 0.0, 1.0);
                        glTranslatef(radio/2, 0.0, 0.0);
                        glRotatef((GLfloat) planeta, 0.0, 0.0, 1.0);
                        glColor3f(0.8, 0.8, 0.8);
                        glutSolidSphere(0.2, 10, 10);
                glPopMatrix();
        glPopMatrix();
        glutSwapBuffers();
}


void reshape(int ancho, int alto)
{
        glViewport(0, 0, ancho, alto);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(65.0, (GLfloat) ancho /(GLfloat) alto, 1.0, 20.0);
        glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char tecla, int x, int y)
{
        switch (tecla) {
                case 's':
                        planeta = (planeta + 5) % 360;
                        break;
                case 'f':
                        planeta = (planeta - 5) % 360;
                        break;
                case '-':
                        velocidad += 5;
                        break;
                case '+':
                        if (velocidad > 5)
                                velocidad -= 5;
                        break;
                case 27: /* Tecla ESC */
                        exit(0);
                        break;
                default:
                        break;
        }
        glutPostRedisplay();
}


void timer(int a)
{
        keyboard('s', 0, 0);
        glutTimerFunc(velocidad, timer, 0);
}


int main(int argc, char **argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(argv[0]);
        init();
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutTimerFunc(velocidad, timer, 0);
        glutMainLoop();
        return 0;
}

