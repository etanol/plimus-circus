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
 * textura.c
 *
 * Función para cargar una textura de un fichero TGA y realizar algunas tareas
 * rutinarias en OpenGL.
 *
 * $Id$
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef THIS_IS_UNIX
#include <GL/gl.h>
#else
#include <GL/glut.h>
#endif

#define CHECK_ERROR(condicion) do {\
	if ((condicion)) { \
		perror("Error durante la carga de la textura"); \
		exit(4); \
	}} while (0)

const GLubyte TGA_tipo[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int cargar_textura(const char *fichero)
{
	FILE *f;
	int textura;	/* Valor de retorno */
	int e;		/* Comodín para comprobar errores */
	int bytespp;	/* BYTES por pixel (3 ó 4) */
	unsigned int  ancho, alto, tam_imagen, i;
	unsigned char cabecera_tipo[sizeof(TGA_tipo)];
	unsigned char cabecera_tga[6];
	GLubyte *imagen;

	/*
	 * Primero cargamos el fichero en memoria.
	 */
	f = fopen(fichero, "rb"); 
	CHECK_ERROR(f == NULL);
	e = fread(cabecera_tipo, 1, sizeof(TGA_tipo), f);
	CHECK_ERROR(e < sizeof(TGA_tipo));
	e = memcmp(TGA_tipo, cabecera_tipo, sizeof(TGA_tipo));
	CHECK_ERROR(e != 0);
	e = fread(cabecera_tga, 1, sizeof(cabecera_tga), f);
	CHECK_ERROR(e < sizeof(cabecera_tga));
	ancho = cabecera_tga[1] * 256 + cabecera_tga[0];
	alto  = cabecera_tga[3] * 256 + cabecera_tga[2];
	bytespp = (cabecera_tga[4] == 24 ? 3 : (cabecera_tga[4] == 32 ? 4 : 0));
	CHECK_ERROR((ancho <= 0) || (alto <= 0) || (bytespp == 0));
	tam_imagen = ancho * alto * bytespp;
	imagen = (GLubyte *)malloc(tam_imagen);
	CHECK_ERROR(imagen == NULL);
	e = fread(imagen, 1, tam_imagen, f);
	CHECK_ERROR((unsigned int)e < tam_imagen);
        for (i = 0; i < tam_imagen; i += bytespp)
            imagen[i] ^= imagen[i+2] ^= imagen[i] ^= imagen[i+2];
	fclose(f);

	/*
	 * Ahora le pasamos la información a OpenGL y preparamos algunos
	 * parámetros.
	 */
	glGenTextures(1, (unsigned int *)&textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, bytespp, ancho, alto, 0, (bytespp == 3 ?
		GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, imagen);
	free(imagen);
	return textura;
}


int gen_textura_carpa(void)
{
	int textura;
	float cols_carpa[6] = {0.8, 0.8, 0.0, 0.8, 0.0, 0.0};

	glGenTextures(1, (unsigned int *)&textura);
	glBindTexture(GL_TEXTURE_1D, textura);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage1D(GL_TEXTURE_1D, 0, 3, 2, 0, GL_RGB, GL_FLOAT, cols_carpa);
	return textura;
}

