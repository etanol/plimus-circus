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
	} else if (strcmp(clave, "carpa_ancho") == 0) {
		cfg->carpa_ancho = valorf;
	} else if (strcmp(clave, "carpa_largo") == 0) {
		cfg->carpa_largo = valorf;
	} else if (strcmp(clave, "faldon_alto") == 0) {
		cfg->faldon_alto = valorf;
	} else if (strcmp(clave, "techo_alto") == 0) {
		cfg->techo_alto = valorf;
	} else if (strcmp(clave, "carpa_lateral_caras") == 0) {
		cfg->carpa_lateral_caras = (int)valorf;
	} else if (strcmp(clave, "sep_gradas_carpa") == 0) {
		cfg->sep_gradas_carpa = valorf;
	} else if (strcmp(clave, "gradas_alto") == 0) {
		cfg->gradas_alto = valorf;
	} else if (strcmp(clave, "gradas_largo") == 0) {
		cfg->gradas_largo = valorf;
	} else if (strcmp(clave, "grada_frontal_ancho") == 0) {
		cfg->grada_frontal_ancho = valorf;
	} else if (strcmp(clave, "grada_lateral_apertura") == 0) {
		cfg->grada_lateral_apertura = (int)valorf;
	} else if (strcmp(clave, "gradas_escalones") == 0) {
		cfg->gradas_escalones = (int)valorf;
	} else if (strcmp(clave, "grada_lateral_caras") == 0) {
		cfg->grada_lateral_caras = (int)valorf;
	}
}


void leer_config(char *fichero, struct config *cfg)
{
	FILE *f;
	char linea[82];
	char *valor;
	int repetir;

	memset(cfg, 0, sizeof(struct config));
	linea[81] = '\n';   /* Centinela */
	f = fopen(fichero, "r");
	if (f == NULL) {
		fprintf(stderr, "Error al abrir el fichero %s.\n", fichero);
		perror("leer_config: ");
		exit(5);
	}
	do {
		valor = linea;
		fgets(linea, 80, f);
		/* Los comentarios se omiten */
		if (*valor == '#')
			continue;
		repetir = 1;
		while (repetir) {
			switch (*valor) {
				/* Casos terminales */
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
			continue; /* No contiene valor, omitir */
		/* Partimos la línea en dos cadenas: clave y valor */
		*valor = '\0';
		++valor;
		/* Saltamos espacios en blanco */
		while (*valor == ' ' || *valor == '\t')
			++valor;
		procesar_linea(linea, valor, cfg);
	} while (!feof(f));
	fclose(f);
}

