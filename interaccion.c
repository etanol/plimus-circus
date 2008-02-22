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
 * interaccion.c
 *
 * Implementación de la gestión de teclado y ratón.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

#include "config.h"
#include "camaras.h"
#include "escena.h"

#define ESC 27

enum tipo_de_giro { HORIZONTAL, VERTICAL };

/* Variables exportadas */
int   modo_exterior;
float desp_cielo_h = 0.0;
float desp_cielo_v = 0.0;
float angulo_anim  = 0.0;

       float angulo_h = 0.0; /* Ángulo de rotación horizontal */
static float angulo_v = 0.0; /* Ángulo de rotación vertical */
static float camara_x = 0.0; /* Posición de la cámara */
static float camara_y = 0.6;
static float camara_z = 0.0;

/* Variables para la función idle */
static int   en_avance     = 0;
static int   en_lateral    = 0;
static int   en_vertical   = 0;
static int   movido        = 0;
static float avance        = 0.0;
static float lateral       = 0.0;
static float vertical      = 0.0;

static config_t C;
static int light_flag      = 1; /* Flags manipulados por el menú */
static int smooth_flag     = 1;
static int animation_flag  = 0;
static int fullscreen_flag = 0;
       int fog_flag        = 1; /* La niebla la controla escena.c, exportar */

/* Entradas de menú */
static const char *m_enable[] = {
        "Enable lighting", "Smooth shading (space key)",
        "Enable outdoor fog", "Enable animation",
        "Fullscreen (F5 key)"
};
static const char *m_disable[] = {
        "Disable lighting", "Flat shading (space key)",
        "Disable outdoor fog", "Disable animation",
        "Restore window (F5 key)"
};

/* Privadísimo */
static float Li_cfa, Li_cta, Li_clr, Li_cfc, Li_cfra2, Li_sel2;
static float Li_mp, Li_mg, Li_mrs, Li_cid, Li_ag;
static int   Li_av;

void
actualiza_camara (void)
{
        /*
         * Pasos:
         *    1. Trasladarnos al punto donde se encuentra la cámara.
         *    2. Girar la cámara horizontalmente (plano XZ).
         *    3. Girar la cámara verticalmente (plano ZY).
         */
        glLoadIdentity();
        glRotatef((GLfloat) -angulo_v, 1.0, 0.0, 0.0);        /* 3 */
        glRotatef((GLfloat) -angulo_h, 0.0, 1.0, 0.0);        /* 2 */
        glTranslatef((GLfloat) -camara_x,
                     (GLfloat) -camara_y,
                     (GLfloat) -camara_z);                    /* 1 */
}


/*
 * Comprueba la posición actual de la cámara para determinar si estamos dentro o
 * fuera de la carpa. Una vez averiguado este dato podemos omitir el renderizado
 * de los objetos que no queremos que se vean así como las luces activadas. Con
 * lo que ganamos un poquito en ligereza de pintado.
 *
 * El parámetro 't' no define el tipo de giro sino el tipo de desplazamiento. Si
 * hubo desplazamiento vertical hay que realizar cálculos adicionales.
 */
static void
comprueba_situacion (enum tipo_de_giro t)
{
        static float radio = 0.0;
        float x, cx, cz;

        if (t == VERTICAL) {
                if (camara_y <= Li_cfa) {
                        radio = Li_clr + Li_cfc + 0.1;
                } else if (camara_y <= (Li_cta + Li_cfa)) {
                        /* faldon_alto < cam_y <= faldon_alto + techo_alto */
                        radio = (Li_clr * (camara_y - Li_cfa - Li_cta)) /
                                -Li_cta;
                } else {
                        /* faldon_alto < faldon_alto + techo_alto < cam_y */
                        radio = 0.0;
                        modo_exterior = 1;
                        return;
                }
        }
        cx = fabsf(camara_x);
        cz = fabsf(camara_z);
        x  = Li_cfra2;
        if (cz < radio) {
                if (cx <= x) {
                        modo_exterior = 0;
                } else if (cx <= (x + radio)) {
                        /* x < cx <= x + radio */
                        modo_exterior = (hypotf(cx-x, cz) <= radio?0:1);
                } else {
                        /* x < x + radio < cx */
                        modo_exterior = 1;
                }
        } else {
                /* cz > radio */
                modo_exterior = 1;
        }
}


static void
paso_frontal (float sentido)
{
        float radianes;

        radianes  = (angulo_h * M_PI) / 180.0;
        camara_x += sinf(radianes) * Li_mp * sentido;
        camara_z += cosf(radianes) * Li_mp * sentido;
}


static void
paso_lateral (float sentido)
{
        float radianes;

        radianes  = (angulo_h * M_PI) / 180.0;
        camara_x += cosf(radianes) * Li_mp * sentido;
        camara_z += -sinf(radianes) * Li_mp * sentido;
}


static void
giro_camara (float sentido, enum tipo_de_giro g)
{
        float *angulo;
        float *despl;

        switch (g) {
        case VERTICAL:
                angulo = &angulo_v;
                despl  = &desp_cielo_v;
                break;
        case HORIZONTAL:
                angulo = &angulo_h;
                despl  = &desp_cielo_h;
                break;
        default:
                angulo = NULL;
                return;
        }
        *angulo += Li_mg * sentido;
        *despl  += Li_cid * (g == HORIZONTAL ? -sentido : sentido);
        if (*angulo < -360.0)
                *angulo += 360.0;
        else if (*angulo > 360.0)
                *angulo -= 360.0;
        if (*despl < 0.0)
                *despl += 1.0;
        else if (*despl > 1.0)
                *despl -= 1.0;
}


static void
teclado_especial (int tecla, int x, int y)
{
        switch (tecla) {
        case GLUT_KEY_UP:        /* Paso hacia adelante */
                avance = -1.0;
                en_avance++;
                break;
        case GLUT_KEY_DOWN:      /* Paso hacia atrás */
                avance = 1.0;
                en_avance++;
                break;
        case GLUT_KEY_LEFT:      /* Paso hacia la izquierda */
                lateral = -1.0;
                en_lateral++;
                break;
        case GLUT_KEY_RIGHT:     /* Paso hacia la derecha */
                lateral = 1.0;
                en_lateral++;
                break;
        case GLUT_KEY_PAGE_UP:   /* Elevación */
                vertical = Li_mp;
                en_vertical++;
                break;
        case GLUT_KEY_PAGE_DOWN: /* Descenso */
                vertical = -Li_mp;
                en_vertical++;
                break;
        case GLUT_KEY_F5:        /* Pantalla completa */
                if (fullscreen_flag) {
                        glutReshapeWindow(valor_entero(C, v_width),
                                          valor_entero(C, v_height));
                        glutChangeToMenuEntry(6, m_enable[4], 5);
                } else {
                        glutFullScreen();
                        glutChangeToMenuEntry(6, m_disable[4], 5);
                }
                fullscreen_flag = !fullscreen_flag;
                movido++;
                break;
        default:
                return;
        }
}


static void
teclado_especial_up (int tecla, int x, int y)
{
        switch (tecla) {
        case GLUT_KEY_UP:        /* Paso hacia adelante */
        case GLUT_KEY_DOWN:      /* Paso hacia atrás */
                en_avance = 0;
                break;
        case GLUT_KEY_LEFT:      /* Paso hacia la izquierda */
        case GLUT_KEY_RIGHT:     /* Paso hacia la derecha */
                en_lateral = 0;
                break;
        case GLUT_KEY_PAGE_UP:   /* Elevación */
        case GLUT_KEY_PAGE_DOWN: /* Descenso */
                en_vertical = 0;
        default:
                break;
        }
}


static void
teclado (unsigned char tecla, int x, int y)
{
        int i;
        int a[2];

        switch (tecla) {
        case ' ': /* Cambio entre GL_FLAT y GL_SMOOTH */
                if (smooth_flag) {
                        glShadeModel(GL_FLAT);
                        glutChangeToMenuEntry(2, m_enable[1], 1);
                } else {
                        glShadeModel(GL_SMOOTH);
                        glutChangeToMenuEntry(2, m_disable[1], 1);
                }
                smooth_flag = !smooth_flag;
                break;
        case 'A':
        case 'a':  /* Desplazamiento del sol en la coordenada X */
                sol_posicion[0] += Li_mp;
                break;
        case 'Z':
        case 'z':
                sol_posicion[0] -= Li_mp;
                break;
        case 'S':
        case 's':  /* Desplazamiento del sol en la coordenada Y */
                sol_posicion[2] += Li_mp;
                break;
        case 'X':
        case 'x':
                sol_posicion[2] -= Li_mp;
                break;
        case 'D':
        case 'd':  /* Desplazamiento del sol en la coordenada Z */
                sol_posicion[1] += Li_mp;
                break;
        case 'C':
        case 'c':
                sol_posicion[1] -= Li_mp;
                break;
        case 'Q':
        case 'q':  /* Posición inicial del sol */
                sol_posicion[0] = sol_posicion[1] = -Li_sel2;
                sol_posicion[2] = 0.7 * Li_sel2;
                sol_posicion[3] = 0.0;
                break;
        case 'W':
        case 'w':  /* Conmutar entre sol posicional o direccional */
                sol_posicion[3] = (sol_posicion[3] == 0.0 ? 1.0 : 0.0);
                break;
        case 'p':
        case 'P':
                glGetIntegerv(GL_POLYGON_MODE, (GLint *)a);
                if (a[1] == GL_FILL)
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                else
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
        case ESC:  /* Salimos del programa */
                exit(EXIT_SUCCESS);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                i = (int)tecla - (int)'0';
                angulo_h = CAMARA[i].angulo_h;
                angulo_v = CAMARA[i].angulo_v;
                camara_x = CAMARA[i].camara_x;
                camara_y = CAMARA[i].camara_y;
                camara_z = CAMARA[i].camara_z;
                comprueba_situacion(VERTICAL);
                break;
        default:   /* Cualquier otra tecla, ignorada */
                return;
        }
        movido++;
}


static void
raton (int x, int y)
{
        static int ox = 0, oy = 0;

        if (x > ox)
                giro_camara(-Li_mrs, HORIZONTAL);
        else if (x < ox)
                giro_camara(Li_mrs, HORIZONTAL);
        ox = x;
        if (y > oy)
                giro_camara(-Li_mrs, VERTICAL);
        else if (y < oy)
                giro_camara(Li_mrs, VERTICAL);
        oy = y;
        movido++;
}


static void
menu (int valor)
{
        switch (valor) {
        case 0:
                if (light_flag) {
                        glDisable(GL_LIGHTING);
                        glutChangeToMenuEntry(1, m_enable[0], 0);
                } else {
                        glEnable(GL_LIGHTING);
                        glutChangeToMenuEntry(1, m_disable[0], 0);
                }
                light_flag = !light_flag;
                glutPostRedisplay();
                break;
        case 1:
                teclado(' ', 0, 0);
                break;
        case 2:
                if (fog_flag)
                        glutChangeToMenuEntry(3, m_enable[2], 2);
                else
                        glutChangeToMenuEntry(3, m_disable[2], 2);
                fog_flag = !fog_flag;
                glutPostRedisplay();
                break;
        case 3:
                if (animation_flag)
                        glutChangeToMenuEntry(4, m_enable[3], 3);
                else
                        glutChangeToMenuEntry(4, m_disable[3], 3);
                animation_flag = !animation_flag;
                break;
        case 4:
                angulo_anim = 0.0;
                break;
        case 5:
                teclado_especial(GLUT_KEY_F5, 0, 0);
                break;
        }
}


static void
refrescar (void)
{
        enum tipo_de_giro t = HORIZONTAL;

        if (en_avance) {
                paso_frontal(avance);
                movido++;
        }
        if (en_lateral) {
                paso_lateral(lateral);
                movido++;
        }
        if (en_vertical && (vertical > 0.0 || camara_y > 0.65)) {
                camara_y += vertical;
                movido++;
                t = VERTICAL;
        }
        if (animation_flag) {
                angulo_anim += Li_ag;
                if (angulo_anim > 360.0)
                        angulo_anim -= 360.0;
                movido++;
        }
        if (movido) {
                comprueba_situacion(t);
                glutPostRedisplay();
                movido = 0;
        }
}


void
init_interaccion (config_t conf)
{
        C = conf;

        /* Cacheamos algunas consultas (ver init_escena() en escena.c) */
        Li_cfa   = valor_decimal(C, c_f_alto);
        Li_cta   = valor_decimal(C, c_t_alto);
        Li_clr   = valor_decimal(C, c_l_radio);
        Li_cfc   = valor_decimal(C, c_f_caida);
        Li_cfra2 = valor_decimal(C, c_fr_ancho) / 2.0;
        Li_sel2  = valor_decimal(C, se_lado)    / 2.0;
        Li_mp    = valor_decimal(C, m_paso);
        Li_mg    = valor_decimal(C, m_giro);
        Li_mrs   = valor_decimal(C, m_rsen);
        Li_cid   = valor_decimal(C, ci_desp);
        Li_ag    = valor_decimal(C, a_giro);
        Li_av    = valor_entero (C, a_vel);

        sol_posicion[0] = sol_posicion[1] = -Li_sel2;
        sol_posicion[2] = 0.7 * Li_sel2;
        sol_posicion[3] = 0.0;

        glutIdleFunc(refrescar);
        glutIgnoreKeyRepeat(1);
        glutKeyboardFunc(teclado);
        glutSpecialFunc(teclado_especial);
        glutSpecialUpFunc(teclado_especial_up);
        glutMotionFunc(raton);
        glutCreateMenu(menu);
        glutAddMenuEntry(m_disable[0], 0);
        glutAddMenuEntry(m_disable[1], 1);
        glutAddMenuEntry(m_disable[2], 2);
        glutAddMenuEntry(m_enable[3], 3);
        glutAddMenuEntry("Reste animation", 4);
        glutAddMenuEntry(m_enable[4], 5);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        comprueba_situacion(VERTICAL);
}

