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

