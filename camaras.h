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
 * camaras.h
 *
 * Cabecera que define la localizaci�n y direcci�n de las c�maras fijas.
 *
 * $Id$
 */

#ifndef _CAMARAS_H_
#define _CAMARAS_H_

const struct {
	float angulo_h;
	float angulo_v;
	float camara_x;
	float camara_y;
	float camara_z;
} CAMARA[10] = {
	{ 0.0, 0.0, 0.0, 0.6, 0.0 },
	{ 219.23, -25.2, -9.93, 7.4, -10.166 },
	{ 207.23, 4.8, -9.93, 0.6, -10.166 },
	{ 0.0, 0.0, 0.0, 0.6, 0.0 },
	{ 0.0, 0.0, 0.0, 0.6, 0.0 },
	{ 0.0, 0.0, 0.0, 0.6, 0.0 },
	{ 0.0, 0.0, 0.0, 0.6, 0.0 },
	{ 0.0, 0.0, 0.0, 0.6, 0.0 },
	{ 0.0, 0.0, 0.0, 0.6, 0.0 },
	{ 0.0, 0.0, 0.0, 0.6, 0.0 }
};

#endif /* _CAMARAS_H_ */
