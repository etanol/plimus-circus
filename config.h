/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado        (etanol@telefonica.net)        |
 |                  Esteban Martínez Tristancho (estebanmartinez@ono.com)      |
 |      Asignatura: Informática Gráfica I                                      |
 |      Profesor  : Jose María Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingeniería Técnica en Informática de Gestión (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
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

#define SEP_GRADAS_CARPA   0.1
#define CAIDA_TECHO_POSTES 0.8
#define CAIDA_FALDON       0.5

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
#ifdef CARPA_SIMPLE
 	int   carpa_lateral_caras; 
#else
	int   carpa_detalle_horiz;
	int   carpa_detalle_vert;
#endif

	/* Gradas */
	float gradas_alto;
	float gradas_largo;
	int   gradas_escalones;
	float grada_frontal_ancho;
	int   grada_lateral_apertura;
	int   grada_lateral_caras;

	/* Poste */
	float poste_radio;
	float poste_extra_alto;
	int   poste_caras;

	/* Suelo */
	float suelo_lado;
	int suelo_detalle;
	
	/* Arena */
	int arena_detalle;
};

void leer_config(char *, struct config *);

#endif
