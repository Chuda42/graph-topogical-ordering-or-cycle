/*
  Módulo de implementación de `lista_datos'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista_datos.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

nat id1(dato d) { return d.id1; };

nat id2(dato d) { return d.id2; };

struct rep_lista_datos {
  dato elem;
  rep_lista_datos *sig;
};

ListaDatos crear_lista_datos() { return NULL; }

void insertar_dato(dato elem, ListaDatos &lst) {
  rep_lista_datos *nuevo = new rep_lista_datos;
  nuevo->elem = elem;
  nuevo->sig = lst;
  lst = nuevo;
}

void remover_dato(dato d, ListaDatos &lst) {
  if ((lst != NULL) && (id1(d) == lst->elem.id1) && (id2(d) == lst->elem.id2)) {
    rep_lista_datos *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  } else if (lst != NULL) {
    rep_lista_datos *cursor = lst;
    while ((cursor->sig != NULL) && ((id1(d) != cursor->sig->elem.id1) || (id2(d) != cursor->sig->elem.id2))) {
      cursor = cursor->sig;
    }
    if (cursor->sig != NULL) {
      rep_lista_datos *aborrar = cursor->sig;
      cursor->sig = cursor->sig->sig;
      delete aborrar;
    } // else no está elem en lst, no se hace nada
  } // else lst == NULL, no se hace nada
}

ListaDatos copia_lista_datos(ListaDatos lst) {
  ListaDatos res;
  if (lst == NULL)
    res = NULL;
  else {
    res = new rep_lista_datos;
    rep_lista_datos * ultimo = res;
    ultimo->elem = lst->elem;
    while (lst->sig != NULL) {
      lst = lst->sig;
      ultimo->sig = new rep_lista_datos;
      ultimo = ultimo->sig;
      ultimo->elem = lst->elem;
    }
    ultimo->sig = NULL;
  }
  return res;
}

bool es_vacia_lista_datos(ListaDatos lst) { return (lst == NULL); }

bool pertenece_a_lista_datos(dato d, ListaDatos lst) {
  while ((lst != NULL) && ((id1(d) != lst->elem.id1)||(id2(d) != lst->elem.id2))) {
    lst = lst->sig;
  }
  return (lst != NULL);
}

dato primer_dato(ListaDatos lst) {
  assert(!es_vacia_lista_datos(lst));
  return lst->elem;
}

ListaDatos resto_datos(ListaDatos lst) {
  assert(!es_vacia_lista_datos(lst));
  return lst->sig;
}

ListaDatos leer_lista_datos() {
  ListaDatos res = crear_lista_datos();
  char strnum1[10], strnum2[10]; // suficiente espacio datoa enteros de 32 bits
  int cant_scanf, cant_scanf2;
  cant_scanf = scanf("%s", strnum1);
  (void)(cant_scanf); // para evitar el warning al compilar con -NDEBUG
  nat id1, id2;
  while (strcmp(strnum1, ".")) {
    cant_scanf2 = scanf("%s", strnum2);
    id1 = atoi(strnum1);
    id2 = atoi(strnum2);
    //  insertar al final de la lista
    dato d = {id1, id2};
    insertar_dato(d, res);
    cant_scanf = scanf("%s", strnum1);
    (void)(cant_scanf);
    (void)(cant_scanf2);
  }
  return res;
}

void imprimir_dato(dato dato) { printf("(%u,%u) ", dato.id1, dato.id2); }

void imprimir_lista_datos(ListaDatos lst) {
  while (!es_vacia_lista_datos(lst)) {
    imprimir_dato(primer_dato(lst));
    lst = resto_datos(lst);
  }
  printf(".");
}

nat cantidad(ListaDatos lst) {
  nat cant = 0;
  while (!es_vacia_lista_datos(lst)) {
    cant++;
    lst = resto_datos(lst);
  }
  return cant;
}

void destruir_lista_datos(ListaDatos &lst) {
  while (lst != NULL) {
    rep_lista_datos *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
}
