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
 * piezas.h
 *
 * M�dulo auxiliar para dibujar cada pieza de forma independiente con un
 * escalado dado.
 *
 * $Id$
 */

#ifndef _PIEZAS_H_H
#define _PIEZAS_H_H

extern void faldon_frontal(float altura, float longitud);
extern void faldon_lateral(float radio, float altura, int num_caras, int exclude);

extern void techo_frontal(float radio, float altura, float longitud);
extern void techo_lateral(float radio, float altura, int num_caras);

extern void grada_frontal(float altura, float longitud, float profunidad, int
		num_esc);
extern void grada_lateral(float radio_in, float radio_ex, float altura, int
		num_esc, int num_caras, int exclude);

#endif /* _PIEZAS_H_H */
