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
 * conf_keys.c
 *
 * Fichero que asocia las claves del fichero de configuración a nombres de
 * variables más abreviables y menos autoexplicativos. También permite cambiar
 * el nombre largo de cada parámetro sin afectar al resto del código.
 *
 * $Id$
 */

const char t_dir[] = "texturas_subdir"; /* string */

/* Parámetros iniciales de la ventana */
const char v_width[]  = "ventana_ancho_inicial"; /* int */
const char v_height[] = "ventana_alto_inicial";  /* int */
const char v_posx[]   = "ventana_posicion_x";    /* int */
const char v_posy[]   = "ventana_posicion_y";    /* int */
const char v_title[]  = "ventana_titulo";        /* string */

/* Parámetros de la cámara */
const char c_fov[]   = "camara_apertura_angular"; /* float */
const char c_znear[] = "camara_z_min_visible";    /* float */
const char c_zfar[]  = "camara_z_max_visible";    /* float */

/* Parámetros de la animación */
const char a_vel[]  = "animacion_velocidad";   /* int */
const char a_giro[] = "animacion_angulo_giro"; /* float */

/* Parámetros del movimiento de la cámara */
const char m_paso[] = "movcam_paso";               /* float */
const char m_giro[] = "movcam_angulo_giro";        /* float */
const char m_rsen[] = "movcam_sensibilidad_raton"; /* float */

/* Parámetros de las luces y la niebla */
const char l_s_radio[] = "sol_radio";                 /* float */
const char l_s_det[]   = "sol_detalle";               /* int */
const char l_f_ang[]   = "foco_interior_inclinacion"; /* float */
const char l_f_ap[]    = "foco_interior_apertura";    /* float */
const char l_f_exp[]   = "foco_interior_exponente";   /* float */
const char n_dens[]    = "niebla_exterior_densidad";  /* float */

/* Parámetros del suelo */
const char se_lado[] = "suelo_exterior_lado";    /* float */
const char se_det[]  = "suelo_exterior_detalle"; /* int */
const char se_tex[]  = "suelo_exterior_textura"; /* string */
const char si_det[]  = "suelo_interior_detalle"; /* int */
const char si_tex[]  = "suelo_interior_textura"; /* string */
const char sa_btam[] = "suelo_arena_borde";      /* float */
const char sa_gsep[] = "suelo_arena_sep_gradas"; /* float */
const char sa_psep[] = "suelo_arena_sep_postes"; /* float */
const char sa_det[]  = "suelo_arena_detalle";    /* int */
const char sa_tex[]  = "suelo_arena_textura";    /* string */

/* Parámetros del cielo */
const char ci_tex[]  = "cielo_textura";    /* string */
const char ci_desp[] = "cielo_despl_giro"; /* float */

/* Parámetros de la carpa */
const char c_f_alto[]   = "carpa_faldon_alto";     /* float */
const char c_f_caida[]  = "carpa_faldon_caida";    /* float */
const char c_t_alto[]   = "carpa_techo_alto";      /* float */
const char c_t_caida[]  = "carpa_techo_caida";     /* float */
const char c_t_caidap[] = "carpa_techo_caida_p";   /* float */
const char c_fr_ancho[] = "carpa_frontal_ancho";   /* float */
const char c_l_radio[]  = "carpa_lateral_radio";   /* float */
const char c_e_ancho[]  = "carpa_entrada_ancho";   /* float */
const char c_e_largo[]  = "carpa_entrada_largo";   /* float */
const char c_deth[]     = "carpa_detalle_horiz";   /* int */
const char c_detv[]     = "carpa_detalle_vert";    /* int */
const char c_e_det[]    = "carpa_detalle_arco";    /* int */
const char c_e_tex[]    = "carpa_entrada_textura"; /* string */

/* Parámetros de las gradas */
const char gs_alto[]   = "gradas_alto";            /* float */
const char gs_largo[]  = "gradas_largo";           /* float */
const char gs_sep[]    = "gradas_sep_carpa";       /* float */
const char gs_esc[]    = "gradas_escalones";       /* int */
const char gs_det[]    = "gradas_detalle";         /* int */
const char gs_tex[]    = "gradas_textura";         /* string */
const char g_f_ancho[] = "grada_frontal_ancho";    /* float */
const char g_l_ap[]    = "grada_lateral_apertura"; /* int */

/* Parámetros de los postes */
const char p_radio[]  = "poste_radio";            /* float */
const char p_ealto[]  = "poste_extra_alto";       /* float */
const char p_brillo[] = "poste_brillo";           /* float */
const char p_deth[]   = "poste_detalle_caras";    /* int */
const char p_detv[]   = "poste_detalle_vertical"; /* int */

/* Parámetros de las banquetas */
const char b_alto[]   = "banqueta_alto";        /* float */
const char b_rmay[]   = "banqueta_radio_mayor"; /* float */
const char b_rmen[]   = "banqueta_radio_menor"; /* float */
const char b_brillo[] = "banqueta_brillo";      /* float */
const char b_det[]    = "banqueta_detalle";     /* int */
const char b_tex[]    = "banqueta_textura";     /* string */

/* Parámetros del cartel */
const char crt_ancho[]  = "cartel_ancho";     /* float */
const char crt_largo[]  = "cartel_largo";     /* float */
const char crt_f_alto[] = "cartel_foto_alto"; /* float */
const char crt_b_alto[] = "cartel_base_alto"; /* float */
const char crt_sep[]    = "cartel_sep_carpa"; /* float (también para árbol) */
const char crt_tex[]    = "cartel_textura";   /* string */
const char crt_foto[]   = "cartel_foto";      /* string */

/* Parámetros del árbol */
const char ar_ancho[] = "arbol_ancho";   /* float */
const char ar_alto[]  = "arbol_alto";    /* float */
const char ar_tex[]   = "arbol_textura"; /* string */

/* Parámetros para el tablón */
const char t_brillo[]   = "tablon_brillo";            /* float */
const char t_b_radio[]  = "tablon_bola_radio";        /* float */
const char t_b_det[]    = "tablon_bola_detalle";      /* int */
const char t_t_grueso[] = "tablon_tabla_grueso";      /* float */
const char t_t_prop[]   = "tablon_tabla_proporcion";  /* float */
const char t_t_eancho[] = "tablon_tabla_extra_ancho"; /* float */

