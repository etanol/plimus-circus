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
 * escena.h
 *
 * Módulo que gestiona el manejo de la ventana: dibujar la escena, atender al
 * cambio de tamaño. Sólo se exporta una función que se encarga de configurar
 * todo lo necesario para dibujar la escena en la ventana.
 */

#ifndef _ESCENA_H_
#define _ESCENA_H_

#include "config.h"

extern float sol_posicion[4];

extern void init_escena (config_t cfg);

#endif

