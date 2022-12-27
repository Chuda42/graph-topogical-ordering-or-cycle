/*
 *  Módulo de definición de `Lista'.
 *
 * `Lista' es una estructura lineal de elementos de tipo `nat'.
 *
 *  La lista mantiene un cursor que permite moverse en la lista y acceder
 *  al elemento que esté en la posición actual del cursor. Inicialmente 
 *  el cursor debe posicionarse al comienzo o final de la lista, y luego 
 *  puede moverse desde su posición actual hacia adelante o hacia atrás.
 *
 *  Ver: 
 *    - void comienzo(Lista lst);
 *    - void final(Lista lst);
 *    - bool existe_actual(Lista lst);
 *    - nat anterior(Lista lst);
 *    - nat siguiente(Lista lst);
 *    - nat actual(Lista lst);
 *
 *  Ejemplo:
 *    //Recorre los elementos de `lst'
 *    comienzo(lst);
 *    while (existe_actual(lst)) {
 *      nat elem = actual(lst);
 *      siguiente(lst);
 *    }
 *
 *  Laboratorio de Programación 3.
 *  InCo-FIng-UDELAR
 * 
 *  En los tiempos de ejecución `n' indica la cantidad de elementos que contiene la lista
 *  al momento de invocar a la operación, salvo que se indique lo contrario. 
 */

#ifndef _LISTA_HPP
#define _LISTA_HPP

#include "utils.h"

struct rep_lista; // representación de `Lista', definida en `lista.cpp'.
typedef rep_lista *Lista;

/* 
Devuelve la lista vacía (sin elementos).
Tiempo: O(1) 
*/
Lista crear_lista();

/* 
Devuelve una copia de `lst'. La lista devuelta no comparte memoria con `lst'. 
Tiempo: O(n)
*/
Lista copia_lista(Lista lst);

/* 
Inserta `elem' al inicio de `lst'. 
Tiempo: O(1) 
*/
void insertar_al_inicio(nat elem, Lista &lst);

/* 
Inserta `elem' al final de `lst'. 
Tiempo: O(1)
*/
void insertar_al_final(nat elem, Lista &lst);

/* 
Remueve el elemento al inicio de `lst'. Precondición: ! es_vacia_lista(lst). 
Tiempo: O(1)
*/  
void remover_al_inicio(Lista &lst);

/* 
Remueve el elemento al final de `lst'.  Precondición: ! es_vacia_lista(lst). 
Tiempo: O(1)
*/
void remover_al_final(Lista &lst);

/* 
Remueve la primera ocurrencia del elemento `elem' de `lst'. Si `elem' no pertenece a `lst' no hace nada. 
Tiempo: O(n)
*/
void remover(nat elem, Lista &lst);

/* 
Devuelve `true' si y sólo si `lst' es vacía (no tiene elementos). 
Tiempo: O(1)
*/
bool es_vacia_lista(Lista lst);

/* 
Devuelve `true' si y sólo si `elem' pertenece a `lst'. 
Tiempo: O(n)
*/
bool pertenece_a_lista(nat elem, Lista lst);

/*  
Coloca la posición actual del cursor al incio de `lst' 
Tiempo: O(1)
*/
void comienzo(Lista lst);

/*  
Coloca la posición actual del cursor al final de `lst'
Tiempo: O(1) 
*/
void final(Lista lst);

/* 
Retrocede la posición actual del cursor al elemento anterior y devuelve el elemento que estaba en la posición antes de moverlo. Precondición: existe_actual(lst). 
Tiempo: O(1)
*/
nat anterior(Lista lst);

/* 
Avanza la posición actual del cursor al elemento siguiente y devuelve el elemento que estaba en la posición antes de moverlo. Precondición: existe_actual(lst). 
Tiempo: O(1)
*/
nat siguiente(Lista lst);

/* 
Devuelve `true' si la posición actual del cursor de `lst' corresponde a un elemento 
Tiempo: O(1)
*/
bool existe_actual(Lista lst);

/* 
Devuelve el elemento en la posición actual del cursor de `lst'. Precondición: existe_actual(lst). 
Tiempo: O(1)
*/
nat actual(Lista lst);

/* 
Devuelve el primer elemento de `lst'. Precondición: ! es_vacia_lista(lst). 
Tiempo: O(1)
*/
nat primero(Lista lst);

/* 
Devuelve el último elemento de `lst'. Precondición: ! es_vacia_lista(lst). 
Tiempo: O(1)
*/
nat ultimo(Lista lst);

/* 
Devuelve la cantidad de elementos de `lst' 
Tiempo: O(n)
*/
nat cantidad_elementos(Lista lst);

/* 
Libera la memoria asignada a `lst'. 
Tiempo: O(n)
*/
void destruir_lista(Lista &lst);

/* 
Imprime `lst' en la salida estándar. Después de cada elemento se imprime un espacio en blanco. Al final se imprime un punto. 
Tiempo: O(n)
*/
void imprimir_lista(Lista lst);

/* 
Devuelve una lista leída desde la entrada estándar que cumple el formato de `imprimir_lista'. 
Tiempo: O(n), siendo n la cantidad de elementos leidos. 
*/
Lista leer_lista();

#endif
