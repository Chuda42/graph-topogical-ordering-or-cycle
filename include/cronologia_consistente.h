
#ifndef __CRONOLOGIA_CONSISTENTE__
#define __CRONOLOGIA_CONSISTENTE__

/*
 * Módulo de definición de `cronologia_consistente.h'.
 *
 * Laboratorio de Programación 3.
 * InCo-FIng-UDELAR
 */
#include "utils.h"
#include "lista_datos.h"

/*
 * Precondiciones: 
 * - `n' indica la cantidad de personas en el conjunto P = {P1, ..., Pn} con identificadores 1 a `n'. 
 * - `tipo1' es una lista de datos de tipo (`id1', `id2'), donde `id1' e `id2' son identificadores en el rango 1 a `n', 
 *    y cada dato indica que la persona de identificador `id1' murió antes de que la persona de identificador `id2' naciera. 
 * - `tipo2' es una lista de datos de tipo (`id1', `id2'), donde `id1' e `id2' son identificadores en el rango 1 a `n', 
 *    y cada dato indica que las vidas de las personas de identificadores `id1' e `id2' se solaparon en el tiempo.
 * 
 * Postcondiciones:
 *  - Si existe una cronología de nacimientos y muertes consistente con los datos recopilados y con el orden natural de nacimiento y muerte para cada persona,
 *    entonces se retorna una `Cronología'. 
 *    Una `Cronología' es un arreglo dinámico de 2n elementos de tipo `evento' (entradas de 0 a 2n-1) 
 *    que representa una secuencia de nacimientos y muertes de las `n' personas en orden cronológico que es consistente con los datos. 
 *    Cada evento se representa mediante los campos (`id', `tipo'), 
 *    siendo `id' el identificador de la persona correspondiente y `tipo' el tipo de `evento' asociado (nace, muere). 
 *
 *    EJEMPLO: 
 *    Teniendo en cuenta el ejemplo para n=3 que se encuentra en la letra del práctico.
 *    La entrada sería: n = 3, tipo1 = [(1,3)], tipo2 = [(2,1)] 
 *    Y la cronología propuesta sería un arreglo Cronología con las 6 entradas: 
 *    indice arreglo:      0       1         2          3         4          5
 *    eventos:         (2,nace) (1,nace) (1, muere) (3, nace) (2, muere) (3, muere)
 * 
 * - Si no existe una cronología de nacimientos y muertes consistente con los datos se retorna NULL. 
 * - El tiempo de ejecucion de cronologia_consistente es O(n + m), 
 *   siendo `n' la cantidad de personas y `m' la cantidad total de datos recopilados (cardinal de `tipo1' + cardinal de `tipo2').
 * 
 * Los tipos de datos `Cronologia' y `evento' están declarados en utils.h
 */
Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2);

#endif
