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
 * interaccion.h
 *
 * M�dulo que gestiona la interacci�n con el usuario (respuestas a eventos de
 * teclado y rat�n). Al igual que en escena.h, s�lo se exporta una funci�n para
 * configurarlo todo.
 *
 * $Id$
 */

#ifndef _INTERACT_H_
#define _INTERACT_H_

#include "config.h"

extern int   modo_exterior;
extern float desp_cielo_h;
extern float desp_cielo_v;
extern float angulo_anim;

extern void init_interaccion(struct config *);
extern void actualiza_camara(void);

#endif 
