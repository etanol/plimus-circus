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


struct config {
	/* Dimensiones de la carpa */
	float carpa_ancho;
	float carpa_largo;
	float faldon_alto;
	float techo_alto;
	int   carpa_lateral_caras;

	/* Gradas */
	float sep_gradas_carpa;
	float gradas_alto;
	float gradas_largo;
	float grada_frontal_ancho;
	int   grada_lateral_apertura;
	int   gradas_escalones;
	int   grada_lateral_caras;
};

void leer_config(char *, struct config *);

#endif
