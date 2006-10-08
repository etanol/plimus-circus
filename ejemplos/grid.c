/*
 * grid.c
 *
 * Un ejemplo para probar glMap2 () con superfícies de orden 2x2.
 *
 * $Id$
 */

#include "rotaciones.C"

void
display (void)
{
        glColor3f (0.0, 0.0, 0.0);
        glEvalMesh2 (GL_LINE, 0, 20, 0, 20);
}

int
main (int argc, char **argv)
{
        float puntos[4][3] = {
                {-0.9, -0.9, 0.0},
                {0.9, -0.9, 0.0},
                {-0.9, 0.9, 0.0},
                {0.9, 0.9, 0.0}};

        glutInit (&argc, argv);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize (500, 500);
        glutInitWindowPosition (100, 100);
        glutCreateWindow (argv[0]);
        init (display, NULL);
        glShadeModel (GL_FLAT);
        glClearColor (1.0, 1.0, 1.0, 1.0);
        glEnable (GL_MAP2_VERTEX_3);
        glDisable (GL_AUTO_NORMAL);
        glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 6, 2, 0.0, 1.0, 3, 2, puntos[0]);
        glMapGrid2f (20, 0.0, 1.0, 20, 0.0, 1.0);
        glutMainLoop ();
        return 0;
}

