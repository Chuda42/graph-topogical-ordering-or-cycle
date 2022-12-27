/*
 *  Módulo de definición de `utils'.
 *
 *  Se define tipos para los naturales y el tipo
 *  Cronología.
 *
 *  Laboratorio de Programación 3.
 *  InCo-FIng-UDELAR
 */

#ifndef _UTILS_HPP
#define _UTILS_HPP

typedef unsigned int nat; // naturales

enum tipo_evento{nace, muere};

struct evento {
    nat id;
    tipo_evento tipo;
};
typedef evento* Cronologia;

#endif
