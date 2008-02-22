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
 * interaccion.h
 *
 * Módulo que gestiona la interacción con el usuario (respuestas a eventos de
 * teclado y ratón). Al igual que en escena.h, sólo se exporta una función para
 * configurarlo todo.
 */

#ifndef _INTERACT_H_
#define _INTERACT_H_

#include "config.h"

extern int   fog_flag;
extern int   modo_exterior;
extern float desp_cielo_h;
extern float desp_cielo_v;
extern float angulo_anim;
extern float angulo_h;

extern void init_interaccion (config_t cfg);
extern void actualiza_camara (void);

#endif /* _INTERACT_H_ */
