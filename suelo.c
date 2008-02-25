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
 * suelo.c
 *
 * Objetos para dibujar el suelo.
 */

#include "gl_headers.h"

#include "piezas.h"
#include "textura.h"


static void suelo (float *limites, float *tex, int detalle)
{
        glDisable(GL_AUTO_NORMAL);
        glEnable(GL_MAP2_VERTEX_3);
        glEnable(GL_MAP2_TEXTURE_COORD_2);
        glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 6, 2, 0.0, 1.0, 3, 2, limites);
        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, tex);
        glMapGrid2f(detalle, 0.0, 1.0, detalle, 0.0, 1.0);
        glNormal3f(0.0, 0.0, 1.0);
        glColor3f(1.0, 1.0, 1.0);
        glEvalMesh2(GL_FILL, 0, detalle, 0, detalle);
}


int crear_suelo_exterior (config_t c)
{
        int   lista, textura;
        float l = valor_decimal(c, se_lado) / 2.0;
        float limites[4][3]  = { {-l, -l, 0.0}, {-l, l, 0.0},
                                 { l, -l, 0.0}, { l, l, 0.0} };
        float texcoord[4][2] = { {0.0, 0.0}, {0.0, l*2},
                                 {l*2, 0.0}, {l*2, l*2} };

        textura = cargar_textura(c, valor_cadena(c, se_tex));
        lista = glGenLists(1);
        if (lista == 0)
                return 0;
        glNewList(lista, GL_COMPILE);
        glBindTexture(GL_TEXTURE_2D, textura);
        suelo(limites[0], texcoord[0], valor_entero(c, se_det));
        glEndList();
        return lista;
}


int crear_suelo_interior (config_t c)
{
        int   lista, textura;
        float x = (valor_decimal(c, c_fr_ancho) / 2.0)
                  + valor_decimal(c, c_l_radio);
        float y = valor_decimal(c, c_l_radio);
        float limites[4][3]  = { {-x, -y, 0.0}, {-x, y, 0.0},
                                 { x, -y, 0.0}, { x, y, 0.0}};
        float texcoord[4][2] = { {0.0, 0.0}, {0.0, y*2},
                                 {x*2, 0.0}, {x*2, y*2} };

        textura = cargar_textura(c, valor_cadena(c, si_tex));
        lista = glGenLists(1);
        if (lista == 0)
                return 0;
        glNewList(lista, GL_COMPILE);
        glBindTexture(GL_TEXTURE_2D, textura);
        suelo(limites[0], texcoord[0], valor_entero(c, si_det));
        glPopAttrib();
        return lista;
}


/*
 * Ésta es un poco más larga porque también pintamos un marco alrededor de los
 * límites. Para el marco usamos Vertex Arrays.
 */
int crear_suelo_arena (config_t c)
{
        int   lista, i, j, textura;
        float b = valor_decimal(c, sa_btam) / 2.0;
        float x = valor_decimal(c, c_fr_ancho) / 2
                  - valor_decimal(c, p_radio) - valor_decimal(c, sa_psep);
        float y = valor_decimal(c, c_l_radio) - valor_decimal(c, gs_largo)
                  - valor_decimal(c, gs_sep) - valor_decimal(c, sa_gsep);
        float limites[4][3]   = { {-x, -y, 0.01}, {-x, y, 0.01},
                                  { x, -y, 0.01}, { x, y, 0.01} };
        float b_frontal[4][3] = { {-(x+b),   -b,  -b}, {-(x+b),   -b,   b},
                                  {  x+b,    -b,   b}, {  x+b,    -b,  -b} };
        float b_lateral[4][3] = { {    b, -(y+b), -b}, {    b, -(y+b),  b},
                                  {    b,   y+b,   b}, {    b,   y+b,  -b} };
        float texcoord[4][2]  = { {0.0, 0.0}, {0.0, y*2},
                                  {x*2, 0.0}, {x*2, y*2} };

        textura = cargar_textura(c, valor_cadena(c, sa_tex));
        lista = glGenLists(1);
        if (lista == 0)
                return 0;
        glNewList(lista, GL_COMPILE);
        /* Bordes de la arena */
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.8, 0.8, 0.8);
        glInterleavedArrays(GL_V3F, 0, b_frontal[0]);
        for (i = 0; i < 2; ++i) {
                glPushMatrix();
                glTranslatef(0.0, (i?y:-y), 0.0);
                for (j = 0; j < 3; ++j) {
                        glPushMatrix();
                        glRotatef(-90.0 * j, 1.0, 0.0, 0.0);
                        glNormal3f(0.0, -1.0, 0.0);
                        glDrawArrays(GL_QUADS, 0,
                                     sizeof(b_frontal) / (3 * sizeof(float)));
                        glPopMatrix();
                }
                glPopMatrix();
        }
        glInterleavedArrays(GL_V3F, 0, b_lateral[0]);
        for (i = 0; i < 2; ++i) {
                glPushMatrix();
                glTranslatef((i?x:-x), 0.0, 0.0);
                for (j = 0; j < 3; ++j) {
                        glPushMatrix();
                        glRotatef(-90.0 * j, 0.0, 1.0, 0.0);
                        glNormal3f(1.0, 0.0, 0.0);
                        glDrawArrays(GL_QUADS, 0,
                                     sizeof(b_lateral) / (3 * sizeof(float)));
                        glPopMatrix();
                }
                glPopMatrix();
        }
        /* Textura de arena */
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        suelo(limites[0], texcoord[0], valor_entero(c, sa_det));
        glEndList();
        return lista;
}

