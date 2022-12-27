#include <stdio.h>

#include "../include/cronologia_consistente.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  bool existe_cr_consistente = false; 

  Cronologia cr = new evento[2*n]; 

  // Determinar si existe o no una cronología consistente con los datos, 
  // en caso de existir, construirla en cr 

  if(existe_cr_consistente) { // si existe, retornarla en cr
    return cr;
  } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
    delete[] cr;
    return NULL;
  }

} 
