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
extern int crear_faldon_frontal(struct config *);
extern int crear_faldon_lateral(struct config *);
extern int crear_techo_frontal(struct config *);
extern int crear_techo_lateral(struct config *);

/*
 * gradas.c
 */
extern int crear_grada_frontal(struct config *);
extern int crear_grada_lateral(struct config *);

/*
 * complementos.c
 */
extern int crear_poste(struct config *);
extern int crear_suelo(struct config *);
extern int crear_arena(struct config *);
extern int crear_banco(struct config *);
extern int crear_cartel(struct config *);

#endif
