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
 * config.c
 *
 * Módulo para cargar la configuración de un fichero de texto.
 *
 * $Id$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"


static void procesar_linea(char *clave, char *valor, struct config *cfg)
{
	float valorf;

	valorf = (float) atof(valor);
	/* 
	 * Hay que hacerlo a lo bestia, no hay escapatoria. Si esto fuera Ada
	 * estaría chupado. 
	 */
	if (strcmp(clave, "fov") == 0) {
		cfg->fov = valorf;
	} else if (strcmp(clave, "z_near") == 0) {
		cfg->z_near = valorf;
	} else if (strcmp(clave, "z_far") == 0) {
		cfg->z_far = valorf;
	} else if (strcmp(clave, "carpa_faldon_alto") == 0) {
		cfg->carpa_faldon_alto = valorf;
	} else if (strcmp(clave, "carpa_techo_alto") == 0) {
		cfg->carpa_techo_alto = valorf;
	} else if (strcmp(clave, "carpa_frontal_ancho") == 0) {
		cfg->carpa_frontal_ancho = valorf;
	} else if (strcmp(clave, "carpa_lateral_radio") == 0) {
		cfg->carpa_lateral_radio = valorf;
#ifdef CARPA_SIMPLE
	} else if (strcmp(clave, "carpa_lateral_caras") == 0) {
		cfg->carpa_lateral_caras = (int)valorf; 
#else
	} else if (strcmp(clave, "carpa_detalle_horiz") == 0) {
		cfg->carpa_detalle_horiz = (int)valorf;
	} else if (strcmp(clave, "carpa_detalle_vert") == 0) {
		cfg->carpa_detalle_vert = (int)valorf;
#endif
	} else if (strcmp(clave, "gradas_alto") == 0) {
		cfg->gradas_alto = valorf;
	} else if (strcmp(clave, "gradas_largo") == 0) {
		cfg->gradas_largo = valorf;
	} else if (strcmp(clave, "gradas_escalones") == 0) {
		cfg->gradas_escalones = (int)valorf;
	} else if (strcmp(clave, "grada_frontal_ancho") == 0) {
		cfg->grada_frontal_ancho = valorf;
	} else if (strcmp(clave, "grada_lateral_apertura") == 0) {
		cfg->grada_lateral_apertura = (int)valorf;
	} else if (strcmp(clave, "grada_lateral_caras") == 0) {
		cfg->grada_lateral_caras = (int)valorf;
	} else if (strcmp(clave, "poste_radio") == 0) {
		cfg->poste_radio = valorf;
	} else if (strcmp(clave, "poste_extra_alto") == 0) {
		cfg->poste_extra_alto = valorf;
	} else if (strcmp(clave, "poste_caras") == 0) {
		cfg->poste_caras = (int)valorf;
	}
}


void leer_config(char *fichero, struct config *cfg)
{
	FILE *f;
	char linea[82];
	char *valor;
	int repetir, i;

	memset(cfg, 0, sizeof(struct config));
	linea[81] = '\n';   /* Centinela */
	f = fopen(fichero, "r");
	if (f == NULL) {
		fprintf(stderr, "Error al abrir el fichero %s.\n", fichero);
		perror("leer_config: ");
		exit(5);
	}
	do {
		i = 0;
		fgets(linea, 80, f);
		/* Saltamos espacios en blanco iniciales */
		while (linea[i] == ' ' || linea[i] == '\t')
			++i;
		valor = linea + i;
		/* Los comentarios y las líneas en blanco se omiten */
		if (*valor == '#' || *valor == '\n')
			continue;
		repetir = 1;
		while (repetir) {
			switch (*valor) {
				case '=':
				case '\n':
					repetir = 0;
					break;
				case ' ':
				case '\t':
					*valor = '\0';
				default:
					++valor;
			}
		}
		if (*valor == '\n')
			continue; /* Línea mal formada, omitir */
		/* Partimos la línea en dos cadenas: clave y valor */
		*valor = '\0';
		++valor;
		/* Saltamos espacios en blanco */
		while (*valor == ' ' || *valor == '\t')
			++valor;
		procesar_linea(linea + i, valor, cfg);
	} while (!feof(f));
	fclose(f);
}

