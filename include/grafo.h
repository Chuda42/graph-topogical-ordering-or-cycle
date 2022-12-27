/*
 *  Módulo de definición de `Grafo'.
 *
 * `Grafo' representa a los grafos dirigidos o no dirigidos.
 *
 *  Los vértices se identifican con enteros entre 1 y un cierto número `max'
 *  establecido al crearlo. No todos los números entre 1 y `max' tienen que ser
 *  vértices del grafo.

 *  En las funciones que tienen un parámetro `v' que es un identificador de
 *  vértice se asume la precondición implícita `1 <= v <= max'.
 *  
 *  Laboratorio de Programación 3.
 *  InCo-FIng-UDELAR
 *
 *  En los tiempos de ejecución `n' indica la cantidad de vértices que contiene el grafo
 *  al momento de invocar a la operación, mientras que `m' indica la cantidad de aristas
 *  en dicho momento. 
 */

#ifndef _GRAFO_HPP
#define _GRAFO_HPP

#include "utils.h"
#include "lista.h"

struct rep_grafo; // representación de `Grafo', definida en `grafo.cpp'.
typedef rep_grafo *Grafo;

/*
Devuelve un grafo vacío (sin aristas ni vértices) que podrá tener hasta `max'
vértices.
Tiempo: O(max) 
*/
Grafo crear_grafo(nat max, bool dirigido);

/* 
Devuelve la cantidad máxima de vértices que puede tener `g'. 
Tiempo: O(1)
*/
nat max_vertice(Grafo g);

/* 
Devuelve `true' si y sólo si `g' es dirigido. 
Tiempo: O(1) 
*/
bool es_dirigido(Grafo g);

/* 
Agrega `v' al conjunto de identificadores de vértices de `g'.
Si `existe_vertice(v, g)' no se hace nada.
Tiempo: O(1) 
*/
void agregar_vertice(nat v, Grafo &g);

/* 
Devuelve `true' si y sólo si `v' pertenece al conjunto de identificadores de
vértices de `g'. 
Tiempo: O(1) 
*/
bool existe_vertice(nat v, Grafo g);

/* 
Devuelve la cantidad de aristas salientes en `v'.
Tiempo: O(1) 
*/
nat out_grado(nat v, Grafo g);

/* 
Devuelve la cantidad de aristas entrantes en `v'. 
Tiempo: O(1)
*/
nat in_grado(nat v, Grafo g);

/* 
Devuelve una lista con los identificadores de vértices de `g' 
Tiempo: O(max) 
*/
Lista vertices(Grafo g);

/* 
Devuelve la cantidad de vértices de `g'. 
Tiempo: O(1) 
*/
nat cantidad_vertices(Grafo g);

/* 
Agrega una arista desde `v1' hacia `v2'.
Si ya había una ariste desde `v1' hacia `v2', *la agrega nuevamente*.
Precondición: existe_vertice(v1, g) && existe_vertice(v2, g). 
Tiempo: O(1)
*/
void agregar_arista(nat v1, nat v2, Grafo g);

/* 
Devuelve la cantidad de aristas de `g'. 
Tiempo: O(1)
*/
nat cantidad_aristas(Grafo g);

/* 
Devuelve una lista con los identificadores de vértices adyacentes a `v'.
Precondición: existe_vertice(v, g).
La lista devuelta comparte memoria con `g'. 
Tiempo: O(1)
*/
Lista adyacentes(nat v, Grafo g);

/*
Devuelve una lista con los identificadores de vértices indicentes a `v'.
Precondición: existe_vertice(v, g).
La lista devuelta comparte memoria con `g'. 
Tiempo: O(1) 
*/
Lista incidentes(nat v, Grafo g);

/* 
Libera la memoria asignada a `g'. 
Tiempo: O(max + m)
*/
void destruir_grafo(Grafo &g);

/* Devuelve un grafo leído desde la entrada estándar.
   En la primera línea lee el valor máximo posible de vértice y si es dirigido o
   no dirigido.
   Luego, lee el identifcador de un vértice por línea.
   Para cada vértice se lee:
   identificador: lista_de_adyacentes
   donde `lista_de_adyacentes' cumple el formato descrito en
   `imprimir_lista'. 
   Termina leyendo una línea con "0:". */
Grafo leer_grafo();

/* Imprime `g' en la salida estándar.
   Cumple el formato de leer_grafo.
   Luego agrega una línea con la cantidad de vértices, otra con la cantidad
   de aristas y una línea para cada vértice, con la cantidad de arisrtas 
   salientes y la cantidad de aristas entrantes. */
void imprimir_grafo(Grafo g);

/* Genera un grafo con un tamaño que lee de la entrada estándar. 
El valor de "con_ciclo" determina si el grafo tiene un ciclo o no.*/
Grafo generar_grafo();

/* Retorna true si `vertices´ es un orden topológico de g */
bool es_orden_topologico(Lista vertices, Grafo g);

#endif
