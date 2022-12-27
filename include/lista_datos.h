/*
 * Módulo de definición de `ListaDatos'.
 *
 * `ListaDatos' es una estructura lineal de elementos de tipo dato.
 * El tipo dato es una dupla de identificadores de personas (id1, id2).
 *
 * Laboratorio de Programación 3.
 * InCo-FIng-UDELAR
 *
 * En los tiempos de ejecución `n' indica la cantidad de elementos que contiene la lista
 * al momento de invocar a la operación, salvo que se indique lo contrario. 
 */

#ifndef _LISTA_DATOS_H
#define _LISTA_DATOS_H

#include "utils.h"

struct dato {
  nat id1;
  nat id2;
}; // par de naturales

// Retrona el campo id1 del dato d.
nat id1(dato d);

// Retorna el campo id2 del dato d.
nat id2(dato d);

// representación de `ListaDatos', definida en `lista_datos.cpp'.
struct rep_lista_datos; 
typedef rep_lista_datos *ListaDatos;

/* 
Devuelve la lista vacía (sin elementos). 
Tiempo: O(1)
*/
ListaDatos crear_lista_datos();

/*
Devuelve una copia de `lst'. La lista devuelta no comparte memoria con `lst'.
Tiempo: O(n)
*/
ListaDatos copia_lista_datos(ListaDatos lst);

/* 
Inserta `elem' al inicio de `lst'. 
Tiempo: O(1)
*/
void insertar_dato(dato elem, ListaDatos &lst);

/* 
Remueve la primera ocurrencia del dato `d' de `lst'. Si `d' no pertenece a `lst' no hace nada. 
Tiempo: O(n)
*/
void remover_dato(dato d, ListaDatos &lst);

/* 
Devuelve `true' si y sólo si `lst' es vacía (no tiene elementos). 
Tiempo: O(1)
*/
bool es_vacia_lista_datos(ListaDatos lst);

/*
Devuelve la cantidad de elementos de lst. 
Tiempo: O(n)
*/
nat cantidad(ListaDatos lst);

/* 
Devuelve `true' si y sólo si `d' está en `lst'. 
Tiempo: O(n) 
*/
bool pertenece_a_lista_datos(dato d, ListaDatos lst);

/* 
Devuelve el primer elemento de `lst'.
Precondición: ! es_vacia_lista(lst). 
Tiempo: O(1) 
*/
dato primer_dato(ListaDatos lst);

/* 
Devuelve el resto de `lst'.
Precondición: ! es_vacia_lista(lst). 
Tiempo: O(1)
*/
ListaDatos resto_datos(ListaDatos lst);

/* 
Libera la memoria asignada a `lst'. 
Tiempo: O(n) 
*/
void destruir_lista_datos(ListaDatos &lst);

/* 
Lee una lista datos desde la entrada estándar.
Formato: d1_id1 d1_id2 d1_id1 d2_id2 ... `.'
*/
ListaDatos leer_lista_datos();

/* 
Imprime `lst' en la salida estándar.
Formato: (d1_id1,d1_id2) (d2_id1,d2_id2) ... `.'
   Después de cada elemento se imprime un espacio en
   blanco. 
   Al final se imprime un punto. 
*/
void imprimir_lista_datos(ListaDatos lst);

#endif
