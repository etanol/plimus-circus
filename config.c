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
/* Visual C++ no consigue linkar conf_keys.c como objeto independiente */
#ifndef THIS_IS_UNIX
#include "conf_keys.cpp"
#endif

#define GROW_STEP 4


static void *my_malloc(size_t tam)
{
	void *ret;

	ret = malloc(tam);
	if (ret == NULL) {
		fprintf(stderr, "Error al intentar reservar memoria.\n");
		exit(9);
	}
	return ret;
}


static void *my_realloc(void *old, size_t n_tam)
{
	void *ret;

	ret = realloc(old, n_tam);
	if (ret == NULL) {
		fprintf(stderr, "Error al intentar reservar más memoria.\n");
		exit(9);
	}
	return ret;
}


static void inserta(config_t cfg, char *k, enum tipo t, char *val)
{
	int i;
	struct nodo *n;

	n = (struct nodo *)cfg;

	while (*k != '\0') {
		for (i = 0; i < n->ult && *k != n->d[i].c; ++i) 
			/* Búsqueda */;
		if (n->ult >= 0 && *k == n->d[i].c) {
			/* Encontrado: descenso en el árbol */
			n = n->d[i].v.sig;
		} else {
			/* No encontrado: Hay que crear una entrada en el nodo
			 * actual y un nuevo nodo hijo */
			++n->ult;
			if (n->ult >= n->tam) {
				/* Quizá necesitemos agrandar el nodo actual */
				n->tam += GROW_STEP;
				n->d = (struct item *) my_realloc(n->d,
						sizeof(struct item)*n->tam);
			}
			n->d[n->ult].c = *k;
			n->d[n->ult].t = CFG_NODO;
			n->d[n->ult].v.sig = (struct nodo *)
				my_malloc(sizeof(struct nodo));
			n = n->d[n->ult].v.sig;
			n->d = (struct item *)
				my_malloc(sizeof(struct item)*GROW_STEP);
			n->tam = GROW_STEP;
			n->ult = -1;
		}
		++k;
	}
	/* *k == '\0' y n apunta al nodo adecuado */
	for (i = 0; i < n->ult && *k != n->d[i].c; ++i)
		/* Una búsqueda más */;
	if (n->ult < 0 || *k != n->d[i].c) {
		/* No encontrado: asignamos valor y tipo */
		++n->ult;
		if (n->ult >= n->tam) {
			/* Agrandar nodo */
			n->tam += GROW_STEP;
			n->d = (struct item *) my_realloc(n->d,
					sizeof(struct item)*n->tam);
		}
		n->d[n->ult].c = *k;
		n->d[n->ult].t = t;
		switch (t) {
			case CFG_CADENA:
				n->d[n->ult].v.cadena = (char *)
					my_malloc(strlen(val));
				strcpy(n->d[n->ult].v.cadena, val);
				break;
			case CFG_ENTERO:
				n->d[n->ult].v.entero = atoi(val);
				break;
			case CFG_DECIMAL:
				n->d[n->ult].v.decimal = (float)
					strtod(val, (char **)NULL);
				break;
			default:
				n->d[n->ult].v.entero = 0;
		}
	}
}


struct item *consulta(config_t cfg, const char *k)
{ 
	int i;
	struct nodo *n;
	const char *x = k;

	n = (struct nodo *)cfg;
	while (*k != '\0') {
		for (i = 0; i < n->ult && *k != n->d[i].c; ++i)
			/* Búsqueda */;
		if (*k != n->d[i].c) {
			/* No existe parte de la clave: error */
			fprintf(stderr, "No se asignó valor a la clave '%s'.\n",
					x);
			exit(10);
		}
		n = n->d[i].v.sig;
		++k;
	}
	/* *k == '\0' */
	for (i = 0; i < n->ult && *k != n->d[i].c; ++i)
		/* Una búsqueda más */;
	if (*k != n->d[i].c) {
		/* No existe la clave: error */
		fprintf(stderr, "No se asignó valor a la clave '%s'.\n", x);
		exit(10);
	}
	return n->d + i;
}


char *valor_cadena(config_t cfg, const char *k)
{
	struct item *d;

	d = consulta(cfg, k);
	if (d->t != CFG_CADENA) {
		fprintf(stderr, "Se esperaba un string para '%s'.\n", k);
		exit(10);
	}
	return d->v.cadena;
}


int valor_entero(config_t cfg, const char *k)
{
	struct item *d;

	d = consulta(cfg, k);
	if (d->t != CFG_ENTERO) {
		fprintf(stderr, "Se esperaba un número entero para '%s'.\n", k);
		exit(10);
	}
	return d->v.entero;
}


float valor_decimal(config_t cfg, const char *k)
{
	struct item *d;

	d = consulta(cfg, k);
	if (d->t != CFG_DECIMAL) {
		fprintf(stderr, "Se esperaba un número con decimales para '%s'.\n", k);
		exit(10);
	}
	return d->v.decimal;
}


config_t leer_config(char *fichero)
{
	FILE *f;
	char linea[82];
	char *c, *valor;
	int repetir, i;
	struct nodo *cfg;
	enum tipo t;

	cfg    = (struct nodo *)my_malloc(sizeof(struct nodo));
	cfg->d = (struct item *)my_malloc(sizeof(struct item) * 4);
	cfg->tam = GROW_STEP;
	cfg->ult = -1;
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
		c = linea + i;
		/* Los comentarios y las líneas en blanco se omiten */
		if (*c == '#' || *c == '\n')
			continue;
		repetir = 1;
		while (repetir) {
			switch (*c) {
				case '=':
				case '\n':
					repetir = 0;
					break;
				case ' ':
				case '\t':
					*c = '\0';
				default:
					++c;
			}
		}
		if (*c == '\n')
			continue; /* Línea mal formada, omitir */
		/* Partimos la línea en dos cadenas: clave y valor */
		*c = '\0';
		++c;
		/* Saltamos espacios en blanco */
		while (*c == ' ' || *c == '\t')
			++c;
		/* Comprobamos el tipo de valor asociado a la clave */
		if (*c == '"') {
			valor = c + 1;
			do {
				++c;
			} while (*c != '"');
			*c = '\0';
			t = CFG_CADENA;
		} else {
			valor = c;
			c = strchr(valor, '.');
			t = (c == NULL ? CFG_ENTERO : CFG_DECIMAL);
		}
		inserta((config_t)cfg, linea, t, valor);
	} while (!feof(f));
	fclose(f);
	return cfg;
}

