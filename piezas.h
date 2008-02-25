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
 * piezas.h
 *
 * Módulo auxiliar para dibujar cada pieza de forma independiente con un
 * escalado dado.
 */

#ifndef _PIEZAS_H_
#define _PIEZAS_H_

#include "config.h"

#define X 0
#define Y 1
#define Z 2

/*
 * carpa.c
 */
extern int crear_faldon_frontal (config_t cfg);
extern int crear_faldon_lateral (config_t cfg);
extern int crear_techo_frontal  (config_t cfg);
extern int crear_techo_lateral  (config_t cfg);
extern int crear_entrada        (config_t cfg);

/*
 * gradas.c
 */
extern int crear_grada_frontal (config_t cfg);
extern int crear_grada_lateral (config_t cfg);

/*
 * suelo.c
 */
extern int crear_suelo_exterior (config_t cfg);
extern int crear_suelo_interior (config_t cfg);
extern int crear_suelo_arena    (config_t cfg);

/*
 * complementos.c
 */
extern int crear_poste      (config_t cfg);
extern int crear_banqueta   (config_t cfg);
extern int crear_cartel     (config_t cfg);
extern int crear_tablon     (config_t cfg);
extern int crear_arbol      (config_t cfg);
extern int crear_sol        (config_t cfg);
extern int crear_payaso     (config_t cfg);
extern int crear_payaso_ext (config_t cfg);

#endif /* _PIEZAS_H_ */
