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
 * textura.h
 *
 * Utilidades para cargar texturas desde ficheros TGA sin comprimir.
 *
 * $Id$
 */

#ifndef _TEXTURA_H_
#define _TEXTURA_H_

struct texturas {
	int suelo_exterior;
	int suelo_interior;
	int grada;
	int carpa;
};

int cargar_textura(const char *);

#endif

