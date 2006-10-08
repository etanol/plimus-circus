/*
 * calcula_normal.C
 *
 * Función para calcular la normal a un plano (vector unitario) a partir de 3
 * puntos pertenecientes a él.
 *
 * $Id$
 */

void
calcNormal (float v[3][3], float out[3])
{
        float v1[3], v2[3];
        float length;
        static const int x = 0;
        static const int y = 1;
        static const int z = 2;

        /* Calcula dos vectores con los tres puntos */
        v1[x] = v[0][x] - v[1][x];
        v1[y] = v[0][y] - v[1][y];
        v1[z] = v[0][z] - v[1][z];
        
        v2[x] = v[1][x] - v[2][x];
        v2[y] = v[1][y] - v[2][y];
        v2[z] = v[1][z] - v[2][z];

        /* 
         * Toma el producto vectorial de los dos vectores para conseguir el
         * vector normal requerido.
         */
        out[x] = v1[y]*v2[z] - v1[z]*v2[y];
        out[y] = v1[z]*v2[x] - v1[x]*v2[z];
        out[z] = v1[x]*v2[y] - v1[y]*v2[x];

        /* Normaliza el vector (reduce su longitud a uno) */
        
        /* Calcula la longitud del vector */
        length = (float)sqrt (  (out[0] * out[0])
                              + (out[1] * out[1])
                              + (out[2] * out[2]));

        /* 
         * Previene errores del programa proporcionando un valor aceptable para
         * vectores que haya que calcular muy cerca del cero.
         */
        if (length == 0.0f)
                length = 1.0f;

        /*
         * Dividimos cada elemento por la longitud resultante para obtener un
         * vector normal unidad.
         */
        out[0] /= length;
        out[1] /= length;
        out[2] /= length;
}

