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

extern int cargar_textura(const char *);
extern int gen_textura_carpa(void);

#endif

