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
 * test_config.c
 *
 * Pequeño test para verificar la carga correcta del fichero de configuración.
 *
 * $Id$
 */

#include <stdio.h>
#include "config.h"

const char *claves[10] = {
        "carpa_lateral_radio",
        "carpa_faldon_alto",
        "poste_radio",
        "ventana_posicion_x",
        "ventana_titulo",
        "movcam_sensibilidad_raton",
        "suelo_exterior_textura",
        "suelo_arena_textura",
        "carpa_detalle_vert",
        "grada_frontal_ancho"
};

int
main (int argc, char **argv)
{ 
        int          i;
        config_t     c;
        struct item *d;

        c = leer_config(argv[1]);
        for (i = 0; i < 10; ++i) {
                d = consulta(c, claves[i]);
                printf("Clave: %s\n", claves[i]);
                switch (d->t) {
                case CFG_ENTERO:
                        printf("Entero: %d\n\n", d->v.entero);
                        break;
                case CFG_DECIMAL:
                        printf("Decimal: %f\n\n", d->v.decimal);
                        break;
                case CFG_CADENA:
                        printf("Cadena: %s\n\n", d->v.cadena);
                        break;
                default:
                        printf("¿¿??\n\n");
                }
        }
        return 0;
}

