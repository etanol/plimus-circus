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
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 45.0, 45.0, 1.0, 3.0, 1.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 }
};

#endif /* _CAMARAS_H_ */
