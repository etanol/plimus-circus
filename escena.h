/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                            I N F O R M Á T I C A                            |
 |                                G R Á F I C A                                |
 |                                                                             |
 |                                                                             |
 |       Alumnos : Isaac Jurado Peinado        (etanol@telefonica.net)         |
 |                 Esteban Martínez Tristancho (estebanmartinez@ono.com)       |
 |       Estudios: Ingeniería Técnica en Informática de Gestión (TIG2)         |
 |       Curso   : 2003/2004                                                   |
 |       Facultad: Universitat de les Illes Balears (UIB)                      |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * escena.h
 *
 * Módulo que gestiona el manejo de la ventana: dibujar la escena, atender al
 * cambio de tamaño. Sólo se exporta una función que se encarga de configurar
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
