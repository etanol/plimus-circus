/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                            I N F O R M � T I C A                            |
 |                                G R � F I C A                                |
 |                                                                             |
 |                                                                             |
 |       Alumnos : Isaac Jurado Peinado        (etanol@telefonica.net)         |
 |                 Esteban Mart�nez Tristancho (estebanmartinez@ono.com)       |
 |       Estudios: Ingenier�a T�cnica en Inform�tica de Gesti�n (TIG2)         |
 |       Curso   : 2003/2004                                                   |
 |       Facultad: Universitat de les Illes Balears (UIB)                      |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * escena.h
 *
 * M�dulo que gestiona el manejo de la ventana: dibujar la escena, atender al
 * cambio de tama�o. S�lo se exporta una funci�n que se encarga de configurar
 * todo lo necesario para dibujar la escena en la ventana.
 *
 * $Id$
 */

#ifndef _ESCENA_H_
#define _ESCENA_H_

#include "config.h"
#include "textura.h"
#include "piezas.h"

extern void init_escena(struct config *, struct texturas *);

#endif
