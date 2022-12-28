#include <stdio.h>

#include "../include/cronologia_consistente.h"
#include "../include/grafo.h"
#include "../include/lista.h"


/*Crear el grafo dirigido con los nodos y las aristas que representan las relaciones, el nodo i representa a la persona de indice i nace, y el nodo i + n representa la persona de inidice i muere*/
static void noExisteVerticeAgregar(nat naceV, nat muereV, Grafo &G){
    if(!existe_vertice(naceV, G)){
      agregar_vertice(naceV, G);
      agregar_vertice(muereV, G);
      agregar_arista(naceV, muereV, G);
    }
};

static Grafo crearGrafoDirigido(nat n, ListaDatos tipo1, ListaDatos tipo2){
  Grafo G = crear_grafo(2*n, true);
  ListaDatos iter = tipo1;
  dato agregar;
  nat nacePi, nacePj, muerePi, muerePj;
  if(!es_vacia_lista_datos(tipo1)){
    agregar = primer_dato(iter);
    while(iter != NULL){
      nacePi  = id1(agregar);
      muerePi = id1(agregar) + n;
      nacePj  = id2(agregar);
      muerePj = id2(agregar) + n;
      /*Agrego los nodos a G*/
      //nacimiento y muerte de Pi
      noExisteVerticeAgregar(nacePi, muerePi, G);
      //nacimiento y muerte Pj
      noExisteVerticeAgregar(nacePj, muerePj, G);
      //agrego las aristas (muerePi, nacePj)
      agregar_arista(muerePi, nacePj, G);

      iter = resto_datos(iter);
      if(iter != NULL)
        agregar = primer_dato(iter);
    }
  }
  if (!es_vacia_lista_datos(tipo2)){
    iter = tipo2;
    agregar = primer_dato(iter);
    while (iter != NULL){
      nacePi = id1(agregar);
      muerePi = id1(agregar) + n;
      nacePj = id2(agregar);
      muerePj = id2(agregar) + n;
      /*Agrego los nodos a G*/
      // nacimiento y muerte de Pi
      noExisteVerticeAgregar(nacePi, muerePi, G);
      // nacimiento y muerte Pj
      noExisteVerticeAgregar(nacePj, muerePj, G);
      // agrego las aristas (nacePi, muerePj) y (nacePi, muerePj)
      agregar_arista(nacePi, muerePj, G);
      agregar_arista(nacePj, muerePi, G);

      iter = resto_datos(iter);
      if(iter != NULL)
        agregar = primer_dato(iter);
    }
  }
  return G;
}


Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  bool existe_cr_consistente = false; 

  Cronologia cr = new evento[2*n];
  nat indiceCr = 0;
  
  //////////PARTE 1 CONSTRUIR EL GRAFO DIRIGIDO/////////////
  Grafo G = crearGrafoDirigido(n, tipo1, tipo2);

  ////////////////PARTE 2: ALGORITMO ORDEN TOPOLOGICO////////////////
  //inicializamos un arreglo para llevar cuantas aristas entrantes tiene un cierto nodo v y que todavia no fue chequeado
  //Tambien inicializo una estructura para llevar los nodos activos llamada S
  //Mantendremos un conjunto tambien que inidique si el nodo ya se visito
  nat cantidadInsertados = 0;
  Lista S = crear_lista();
  nat* cantIncoming = new nat[2*n + 1];
  cantIncoming[0] = 0;
  for (nat i = 1; i < 2*n + 1; i++){
    cantIncoming[i] = in_grado(i, G);
    if(in_grado(i, G) ==  0){
      insertar_al_inicio(i, S);
      cantidadInsertados++;
    }
  }
  Lista iterAdyacentes;
  nat v;
  while(!es_vacia_lista(S)){
    v = ultimo(S);
    if(v <= n){
      cr[indiceCr] = {v, nace};
    }else{
      cr[indiceCr] = {v - n, muere};
    }
    indiceCr++;
    iterAdyacentes  = adyacentes(v, G);
    comienzo(iterAdyacentes);
    while(existe_actual(iterAdyacentes)){
      cantIncoming[actual(iterAdyacentes)]--;
      if(cantIncoming[actual(iterAdyacentes)] == 0){
        insertar_al_inicio(siguiente(iterAdyacentes), S);
        cantidadInsertados++;
      }else{
        siguiente(iterAdyacentes);
      }
      
    }
    remover_al_final(S);
  }
  existe_cr_consistente = cantidadInsertados == 2*n;

  delete[] cantIncoming;
  destruir_grafo(G);
  destruir_lista(S);
  


  // Determinar si existe o no una cronología consistente con los datos, 
  // en caso de existir, construirla en cr 

  if(existe_cr_consistente) { // si existe, retornarla en cr
    return cr;
  } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
    delete[] cr;
    return NULL;
  }

} 