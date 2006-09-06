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

#include "conf_keys.h" /* Las variables que definen se hacen visibles aquí */

/* Tipos privados */
struct nodo;

enum tipo { CFG_NODO, CFG_ENTERO, CFG_DECIMAL, CFG_CADENA };

union valor {
	struct nodo *sig;
	int   entero;
	float decimal;
	char *cadena;
};

struct item {
	char c;
	enum tipo t;
	union valor v;
};

struct nodo {
	struct item *d;
	int tam;
	int ult;
};


/* Tipos exportados */
typedef struct nodo *config_t;

/* Primitivas */
extern config_t leer_config(char *);
extern char *   valor_cadena(config_t, const char *);
extern int      valor_entero(config_t, const char *);
extern float    valor_decimal(config_t, const char *);

/* Sólo para debug */
extern struct item *consulta(config_t, const char *);

#endif
