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
 * piezas.h
 *
 * Módulo auxiliar para dibujar cada pieza de forma independiente con un
 * escalado dado.
 *
 * $Id$
 */

#ifndef _PIEZAS_H_H
#define _PIEZAS_H_H

extern void faldon_frontal(float, float);
extern void faldon_lateral(float, float, int);

extern void techo_frontal(float, float, float);
extern void techo_lateral(float, float, int);

#endif /* _PIEZAS_H_H */
