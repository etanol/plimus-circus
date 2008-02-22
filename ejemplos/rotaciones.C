/*
 * rotaciones.C
 *
 * Código reutilizable para girar el objeto visualizado en la ventana. Es un
 * extracto del programa test_pieza.c
 */

#include <GL/glut.h>
#include <stdlib.h>

int win_h, win_w;
void (*diodenar)(void) = NULL;
void (*torpedo)(unsigned char, int, int) = NULL;


void capipo(int w, int h)
{
        win_w = w;
        win_h = h;
}


void enkander(unsigned char tecla, int x, int y)
{
        if (torpedo)
                (*torpedo)(tecla, x, y);
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


void jandepora(void)
{
        GLubyte todos[] = {0, 1, 0, 2, 0, 3};
        GLubyte ejex[] = {0, 1};
        GLubyte ejey[] = {0, 2};
        GLubyte ejez[] = {0, 3};

        /* Dibujado del objeto */
        glViewport(0, 0, win_w, win_h);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (diodenar)
                (*diodenar)();
        glPushMatrix(); /* 1 */

        /* Dibujamos el estado actual de la rotación */
        glViewport(0, 0, win_w/5, win_h/5);
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushAttrib(GL_CURRENT_BIT);
        glColor3f(0.0, 0.0, 0.0);
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, todos);
        glPopMatrix(); /* 1 */
        glColor3f(1.0, 0.0, 0.0);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, ejex);
        glColor3f(0.0, 1.0, 0.0);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, ejey);
        glColor3f(0.0, 0.0, 1.0);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, ejez);
        glEnable(GL_LIGHTING);
        glPopAttrib();
        glFlush();
        glutSwapBuffers();
}

void init(void (*d)(void), void (*k)(unsigned char, int, int))
{
        static GLfloat ejes[] = {
                0.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
        };

        glutReshapeFunc(capipo);
        glutKeyboardFunc(enkander);
        glutDisplayFunc(jandepora);
        if (d)
                diodenar = d;
        if (k)
                torpedo = k;
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, ejes);
}

