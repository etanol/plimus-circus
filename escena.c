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
 * escena.c
 *
 * Configuración de la escena completa.
 *
 * $Id$
 */

#include <string.h>
#include <GL/glut.h>

#include "config.h"
#include "interaccion.h"
#include "textura.h"
#include "piezas.h"

float sol_posicion[4];

/* Objetos de la escena */
static int tex_cielo;
static int 
	faldon_frontal,
	faldon_lateral,
	techo_frontal,
	techo_lateral,
	grada_frontal,
	grada_lateral,
	entrada_carpa,
	poste,
	suelo_exterior,
	suelo_interior,
	suelo_arena,
	banqueta,
	tablon,
	cartel,
	arbol,
	sol;

/* Configuración de la escena */
static config_t C;

/* Muy muy privado */
static float Le_cfra2, Le_clr, Le_calt, Le_crtsep;
static float Le_fov, Le_znear, Le_zfar, Le_fang;


static void actualiza_viewport(int ancho, int alto)
{ 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(Le_fov, (float)ancho / (float)alto, Le_znear, Le_zfar);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, ancho, alto);
	glutPostRedisplay();
}


static void cielo(void)
{
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, tex_cielo);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -0.5, 0.5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0 + desp_cielo_h, 0.0 + desp_cielo_v);
	glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(0.0 + desp_cielo_h, 1.0 + desp_cielo_v);
	glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(1.0 + desp_cielo_h, 1.0 + desp_cielo_v);
	glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0 + desp_cielo_h, 0.0 + desp_cielo_v);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	if (light_flag)
		glEnable(GL_LIGHTING);
}


static void init_luces_niebla(void)
{
	float ambiente_global[4] = {0.0, 0.0, 0.0, 1.0};
	float sol_ambiente[4]  = {0.25, 0.25, 0.25, 1.0};
	float sol_difusa[4]    = {1.0, 1.0, 1.0, 1.0};
	float sol_especular[4] = {0.5, 0.5, 0.5, 1.0};
	float foco_ambiente[4]   = {1.0, 1.0, 1.0, 1.0};
	float foco_difusa[4]     = {1.0, 1.0, 1.0, 1.0};
	float foco_especular[4]  = {1.0, 1.0, 1.0, 1.0};
	float foco_atenuacion[3] = {0.9, 0.4, 0.0};
	float foco_apertura      = valor_decimal(C, l_f_ap);
	float foco_exponente     = valor_decimal(C, l_f_exp);
	float interior_ambiente[4]  = {0.1, 0.1, 0.1, 1.0}; 
	float interior_difusa[4]    = {0.8, 0.8, 0.8, 1.0};
	float interior_especular[4] = {0.2, 0.2, 0.2, 1.0};
	float niebla_color[4] = {0.5, 0.72, 0.95, 0.0};
	Le_fang = valor_decimal(C, l_f_ang);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente_global);

	/* Luz solar */
	glLightfv(GL_LIGHT0, GL_AMBIENT, sol_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sol_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sol_especular);
	glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 180.0); /* Sólo si posicional */

	/* Focos interiores */
	glLightfv(GL_LIGHT1, GL_AMBIENT, foco_ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, foco_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, foco_especular);
	glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION, foco_atenuacion[0]);
	glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION, foco_atenuacion[1]);
	glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, foco_atenuacion[2]);
	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, foco_apertura);
	glLightf (GL_LIGHT1, GL_SPOT_EXPONENT, foco_exponente);

	glLightfv(GL_LIGHT2, GL_AMBIENT, foco_ambiente);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, foco_difusa);
	glLightfv(GL_LIGHT2, GL_SPECULAR, foco_especular);
	glLightf (GL_LIGHT2, GL_CONSTANT_ATTENUATION, foco_atenuacion[0]);
	glLightf (GL_LIGHT2, GL_LINEAR_ATTENUATION, foco_atenuacion[1]);
	glLightf (GL_LIGHT2, GL_QUADRATIC_ATTENUATION, foco_atenuacion[2]);
	glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, foco_apertura);
	glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, foco_exponente);

	glLightfv(GL_LIGHT3, GL_AMBIENT, foco_ambiente);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, foco_difusa);
	glLightfv(GL_LIGHT3, GL_SPECULAR, foco_especular);
	glLightf (GL_LIGHT3, GL_CONSTANT_ATTENUATION, foco_atenuacion[0]);
	glLightf (GL_LIGHT3, GL_LINEAR_ATTENUATION, foco_atenuacion[1]);
	glLightf (GL_LIGHT3, GL_QUADRATIC_ATTENUATION, foco_atenuacion[2]);
	glLightf (GL_LIGHT3, GL_SPOT_CUTOFF, foco_apertura);
	glLightf (GL_LIGHT3, GL_SPOT_EXPONENT, foco_exponente);

	/* Luz ambiente interior */
	glLightfv(GL_LIGHT5, GL_AMBIENT, interior_ambiente);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, interior_difusa);
	glLightfv(GL_LIGHT5, GL_SPECULAR, interior_especular);
	glLightf (GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf (GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.15);
	glLightf (GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightf (GL_LIGHT5, GL_SPOT_CUTOFF, 180.0);

	/* Niebla exterior */
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, niebla_color);
	glFogf(GL_FOG_DENSITY, valor_decimal(C, n_dens));
}


static void luces_niebla(void)
{
	float foco_posicion[4]  = {0.0, 0.0, 0.0, 1.0};
	float foco_direccion[4] = {0.0, 0.0, -1.0, 0.0};
	float interior_posicion[4] = {0.0, 0.0, Le_calt, 1.0};

	if (modo_exterior) {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT5);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, sol_posicion);
		if (fog_flag)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
	} else {
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT5); 
		glPushMatrix(); /* 1 */
		glTranslatef(0.0, 0.0, Le_calt);
		glPushMatrix(); /* 2 */
		glRotatef(angulo_anim*3.0, 0.0, 0.0, 1.0);
		glPushMatrix(); /* 3 */
		glRotatef(Le_fang, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT1, GL_POSITION, foco_posicion);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, foco_direccion);
		glPopMatrix(); /* 3 */
		glRotatef(-Le_fang, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT2, GL_POSITION, foco_posicion);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, foco_direccion);
		glPopMatrix(); /* 2 */
		glLightfv(GL_LIGHT3, GL_POSITION, foco_posicion);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, foco_direccion);
		glPopMatrix(); /* 1 */
		glLightfv(GL_LIGHT5, GL_POSITION, interior_posicion);
		glDisable(GL_FOG);
	}
}


static void escena(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if (modo_exterior) 
		cielo(); 
	actualiza_camara();
	/*
	 * Ya que se dibuja todo visto desde arriba (como si se dibujara en
	 * planta) rotamos 90º sobre el eje X para orientarlo a la posición
	 * natural.
	 */
	glRotatef(90.0, -1.0, 0.0, 0.0);
	luces_niebla();

	/* Postes */
	glCallList(poste);
	glPushMatrix();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glCallList(poste);
	glPopMatrix();
	if (modo_exterior) {
		/* Suelo */
		glCallList(suelo_exterior);
		/* Carpa */
		glCallList(faldon_frontal);
		glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glCallList(faldon_frontal);
		glPopMatrix();
		glCallList(faldon_lateral);
		glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glCallList(faldon_lateral);
		glPopMatrix();
		glCallList(techo_frontal);
		glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glCallList(techo_frontal);
		glPopMatrix();
		glCallList(techo_lateral);
		glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glCallList(techo_lateral);
		glPopMatrix();
		glCallList(entrada_carpa);
		glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glCallList(entrada_carpa);
		glPopMatrix();
		/* Cartel */
		glPushMatrix();
		glTranslatef(-(Le_cfra2 + Le_clr), -(Le_clr + Le_crtsep), 0.0);
		glRotatef(angulo_anim, 0.0, 0.0, 1.0);
		glCallList(cartel);
		glPopMatrix();
		/* Arbolitos */
		glPushMatrix();
		glTranslatef(Le_cfra2 + Le_clr, Le_clr + Le_crtsep, 0.0);
		glRotatef(angulo_h, 0.0, 0.0, 1.0);
		glCallList(arbol);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-(Le_cfra2 + Le_clr), Le_clr + Le_crtsep, 0.0);
		glRotatef(angulo_h, 0.0, 0.0, 1.0);
		glCallList(arbol);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(Le_cfra2 + Le_clr, -(Le_clr + Le_crtsep), 0.0);
		glRotatef(angulo_h, 0.0, 0.0, 1.0);
		glCallList(arbol);
		glPopMatrix();
		/* Sol */
		glPushMatrix();
		glTranslatef(sol_posicion[0], sol_posicion[1], sol_posicion[2]);
		glCallList(sol);
		glPopMatrix();
		if (fog_flag)
			glEnable(GL_FOG);
		if (light_flag)
			glEnable(GL_LIGHTING);
	} else {
		/* Suelo */
		glCallList(suelo_interior);
		/* Arena */
		glCallList(suelo_arena);
		/* Bola y tablón */
		glCallList(tablon);
		/* Bancos pa los tigretones */
		glCallList(banqueta);
		glPushMatrix();
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glCallList(banqueta);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glCallList(banqueta);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glCallList(banqueta);
		glPopMatrix();
		/* Gradas */
		glCallList(grada_frontal);
		glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glCallList(grada_frontal);
		glPopMatrix();
		glCallList(grada_lateral);
		glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		glCallList(grada_lateral);
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
} 


void init_escena(config_t cfg)
{
	C = cfg;

	/* Copiamos valores de la configuración localmente para ahorrarnos
	 * algunas consultas */
	Le_cfra2  = valor_decimal(C, c_fr_ancho) / 2.0;
	Le_clr    = valor_decimal(C, c_l_radio);
	Le_calt   = valor_decimal(C, c_f_alto) + valor_decimal(C, c_t_alto);
	Le_crtsep = valor_decimal(C, crt_sep);
	Le_fov    = valor_decimal(C, c_fov);
	Le_znear  = valor_decimal(C, c_znear);
	Le_zfar   = valor_decimal(C, c_zfar);

	/* Textura para el cielo */
	tex_cielo = cargar_textura(C, valor_cadena(C, ci_tex));

	init_luces_niebla();

	glutDisplayFunc(escena);
	glutReshapeFunc(actualiza_viewport);

	faldon_frontal = crear_faldon_frontal(C);
	faldon_lateral = crear_faldon_lateral(C);
	techo_frontal  = crear_techo_frontal(C);
	techo_lateral  = crear_techo_lateral(C);
	grada_frontal  = crear_grada_frontal(C);
	grada_lateral  = crear_grada_lateral(C);
	entrada_carpa  = crear_entrada(C);
	poste          = crear_poste(C);
	suelo_exterior = crear_suelo_exterior(C);
	suelo_interior = crear_suelo_interior(C);
	suelo_arena    = crear_suelo_arena(C);
	banqueta       = crear_banqueta(C);
	tablon         = crear_tablon(C);
	cartel         = crear_cartel(C);
	arbol          = crear_arbol(C);
	sol            = crear_sol(C);
}

