/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado        (etanol@telefonica.net)        |
 |                  Esteban Mart�nez Tristancho (estebanmartinez@ono.com)      |
 |      Asignatura: Inform�tica Gr�fica I                                      |
 |      Profesor  : Jose Mar�a Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * piezas.h
 *
 * M�dulo auxiliar para dibujar cada pieza de forma independiente con un
 * escalado dado.
 *
 * $Id$
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
extern int crear_faldon_frontal(config_t);
extern int crear_faldon_lateral(config_t);
extern int crear_techo_frontal(config_t);
extern int crear_techo_lateral(config_t);

/*
 * gradas.c
 */
extern int crear_grada_frontal(config_t);
extern int crear_grada_lateral(config_t);

/*
 * suelo.c
 */
extern int crear_suelo_exterior(config_t);
extern int crear_suelo_interior(config_t);
extern int crear_suelo_arena(config_t);

/*
 * complementos.c
 */
extern int crear_poste(config_t);
extern int crear_banqueta(config_t);
extern int crear_cartel(config_t);
extern int crear_tablon(config_t);

#endif
