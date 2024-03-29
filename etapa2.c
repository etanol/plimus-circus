/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado          [C2H5OH]                     |
 |                  Esteban Martínez Tristancho   [Tito Houzy]                 |
 |      Asignatura: Informática Gráfica I                                      |
 |      Profesor  : Jose María Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingeniería Técnica en Informática de Gestión (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * etapa2.c
 */

#include "gl_headers.h"

/* Tamaño incial de la ventana */
const int W_WIDTH = 500;
const int W_HEIGHT = 500;

/* Variable que indica el ángulo de rotación de los ejes. */
GLfloat fAngulo;


void Display (void)
{
        /* Borramos la escena */
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        /* Rotamos las proximas primitivas */
        glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
        /* Creamos a continuación dibujamos los tres poligonos */
        glBegin(GL_POLYGON);
            glColor3f (1.0f, 1.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glColor3f (0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glColor3f (0.0f, 1.0f, 0.0f);
            glVertex3f(-0.5f, 0.866f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f (1.0f, 1.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glColor3f (1.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glColor3f (0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5f, -0.866f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f (1.0f, 1.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glColor3f (0.0f, 1.0f, 1.0f);
            glVertex3f(-0.5f, 0.866f, 0.0f);
            glColor3f (0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5f, -0.866f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex3f(-0.3f, 0.3f, 0.0f);
            glVertex3f(0.3f, 0.3f, 0.0f);
            glVertex3f(0.3f, -0.3f, 0.0f);
            glVertex3f(-0.3f, -0.3f, 0.0f);
        glEnd();

        glPopMatrix();
        glFlush();
        glutSwapBuffers();
}


void Idle (void)
{
        /* Incrementamos el ángulo */
        fAngulo += 0.3f;
        /* Si es mayor que dos pi la decrementamos */
        if (fAngulo > 360)
                fAngulo -= 360;
        /* Indicamos que es necesario repintar la pantalla */
        glutPostRedisplay();
}


void Reshape (int ancho, int alto)
{
        int lado, x, y;

        if (ancho < alto) {
                lado = ancho;
                x = 0;
                y = (alto - ancho) / 2;
        } else {
                lado = alto;
                x = (ancho - alto) / 2;
                y = 0;
        }
        glViewport(x, y, lado, lado);
}


int main (int argc, char **argv)
{
        /* Inicializamos la librería GLUT */
        glutInit(&argc, argv);

        /* Indicamos como ha de ser la nueva ventana */
        glutInitWindowPosition(100,100);
        glutInitWindowSize(W_WIDTH, W_HEIGHT);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

        /* Creamos la nueva ventana */
        glutCreateWindow("Ventana principal");

        /* Indicamos cuales son las funciones de redibujado e idle */
        glutDisplayFunc(Display);
        glutIdleFunc(Idle);
        glutReshapeFunc(Reshape);

        /* El color de fondo será el blanco (RGBA, RGB + Alpha channel) */
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        /* Comienza la ejecución del core de GLUT */
        glutMainLoop();
        return 0;
}

