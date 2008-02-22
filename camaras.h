/*       _\|/_
         (o o)
 +----oOO-{_}-OOo--------------------------------------------------------------+
 |                                                                             |
 |                          P L I M U S   C I R C U S                          |
 |                                                                             |
 |      Alumnos   : Isaac Jurado Peinado          [C2H5OH]                     |
 |                  Esteban Martínez Tristancho   [Tito Houzy]                 |
 |      Asignatura: Informática Gráfica I                                      |
 |      Profesor  : Jose María Buades Rubio                                    |
 |      Curso     : 2003/2004                                                  |
 |      Estudios  : Ingeniería Técnica en Informática de Gestión (TIG2)        |
 |      Facultad  : Universitat de les Illes Balears (UIB)                     |
 |                                                                             |
 +----------------------------------------------------------------------------*/

/*
 * camaras.h
 *
 * Cabecera que define la localización y dirección de las cámaras fijas.
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
        { 0.0, 0.0, 0.0, 0.6, 0.0 },            /* 0 */
        { 219.23, -25.2, -12.08, 7.4, -12.8 },  /* 1 */
        { 317.93, -18.9, -6.97, 2.8, 6.61 },    /* 2 */
        { 322.13, -27.3, -15.35, 6.9, 15.6 },   /* 3 */
        { 0.0, -90.0, 0.0, 18.1, 0.0 },         /* 4 */
        { 61.8, 0.0, 12.5, 1.7, 10.25 },        /* 5 */
        { 90.0, -27.0, 10.7, 2.8, 0.0 },        /* 6 */
        { 135.23, 2.1, 16.1, 1.0, -13.206 },    /* 7 */
        { 0.0, 0.0, 0.0, 1.8, 7.1 },            /* 8 */
        { 0.0, -24.0, 0.0, 5.9, 14.6 }          /* 9 */
};

#endif /* _CAMARAS_H_ */
