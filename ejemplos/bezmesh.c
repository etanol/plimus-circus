/*
 * bezmesh.c
 *
 * Ejemplo de superficies de Bézier con iluminación utilizando OpenGL
 * Evaluators. Sacado del "libro rojo"
 */

#include "rotaciones.C"  /* Movimiento del objeto */

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

int   dopoints = 0;


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
        if (tecla == ' ')
                dopoints = !dopoints;
}


void display(void)
{
        int i, j;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
        glMatrixMode(GL_MODELVIEW);
        glEvalMesh2(GL_FILL, 0, 20, 0, 20);
        if (dopoints) {
                glPointSize(5.0);
                glPushAttrib(GL_CURRENT_BIT);
                glColor3f(1.0, 1.0, 0.0);
                glDisable(GL_LIGHTING);
                glBegin(GL_POINTS);
                for (i = 0; i < 4; ++i)
                        for (j = 0; j < 4; ++j)
                                glVertex3fv(ctrlpoints[i][j]);
                glEnd();
                glEnable(GL_LIGHTING);
                glPopAttrib();
        }
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
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, ctrlpoints[0][0]);
        glEnable(GL_MAP2_VERTEX_3);
        glEnable(GL_AUTO_NORMAL);
        glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

        initlights();
        init(display, teclado);

        glutMainLoop();
        return 0;
}

