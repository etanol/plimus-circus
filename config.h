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
 * config.h
 *
 * Definición de los parámetros configurables del circo.
 *
 * $Id$
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define SEP_GRADAS_CARPA 0.05

struct config {
	/* Campo de visión */
	float fov;
	float z_near;
	float z_far;
	
	/* Carpa */
	float carpa_faldon_alto;
	float carpa_techo_alto;
	float carpa_frontal_ancho;
	float carpa_lateral_radio;
	int   carpa_lateral_caras;

	/* Gradas */
	float gradas_alto;
	float gradas_largo;
	int   gradas_escalones;
	float grada_frontal_ancho;
	int   grada_lateral_apertura;
	int   grada_lateral_caras;
};

void leer_config(char *, struct config *);

#endif
