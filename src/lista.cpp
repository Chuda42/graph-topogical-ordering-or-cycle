/*
  Módulo de implementación de `lista'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct nodo_lista {
  nodo_lista *sig;
  nodo_lista *ant;
  nat elem;
};

struct rep_lista {
  nodo_lista *ini;
  nodo_lista *ult;
  nodo_lista *actual;
};

static nodo_lista* crear_nodo(nat elem, nodo_lista* ant, nodo_lista* sig) {
  nodo_lista* nuevo = new nodo_lista;
  nuevo->elem = elem;
  nuevo->sig = sig;
  nuevo->ant = ant;
  if (sig != NULL)
    sig->ant = nuevo;
  if (ant != NULL)
    ant->sig = nuevo;
  return nuevo;
}

Lista crear_lista() {
  Lista res = new rep_lista;
  res->ini = NULL;
  res->ult = NULL;
  res->actual = NULL;
  return res;
}

Lista copia_lista(Lista lst) {
  Lista res = crear_lista();
  nodo_lista* cursor_lst = lst->ini;
  nodo_lista** ptr_nuevo = &res->ini;
  nodo_lista* anterior = NULL;
  while (cursor_lst != NULL) {
    nodo_lista* nuevo = crear_nodo(cursor_lst->elem, anterior, NULL);
    *ptr_nuevo = nuevo;
    anterior   = nuevo;
    res->ult   = nuevo;
    ptr_nuevo  = &(nuevo->sig);
    cursor_lst = cursor_lst->sig;
  }
  return res;
}

void insertar_al_inicio(nat elem, Lista &lst) {
  nodo_lista *nuevo = crear_nodo(elem, NULL, lst->ini);
  lst->ini = nuevo;
  if (lst->ult == NULL)
    lst->ult = nuevo;
}

void insertar_al_final(nat elem, Lista &lst) {
  nodo_lista *nuevo = crear_nodo(elem, lst->ult, NULL);
  if (lst->ini == NULL)
    lst->ini = nuevo;
  else
    lst->ult->sig = nuevo;
  lst->ult = nuevo;
}

void remover(nat elem, Lista &lst) {
  nodo_lista** cursor_lst = &lst->ini;
  nodo_lista* anterior = NULL;
  nodo_lista* a_borrar = NULL;
  while (*cursor_lst != NULL) {
    if ((*cursor_lst)->elem == elem) {
      a_borrar = *cursor_lst;
      *cursor_lst = a_borrar->sig;
      if (*cursor_lst != NULL)
        (*cursor_lst)->ant = anterior;
      else {
        lst->ult = a_borrar->ant;
        if (lst->ult == NULL)
          lst->ini = NULL;
      }
      if (lst->actual == a_borrar)
         lst->actual = NULL;
      delete a_borrar;
      return;
    }
    anterior = *cursor_lst;
    cursor_lst  = &((*cursor_lst)->sig);
  }
}

void remover_al_inicio(Lista &lst) {
  assert(!es_vacia_lista(lst));
  if (lst->ini != NULL) {
    nodo_lista* a_borrar = lst->ini;
    lst->ini = a_borrar->sig;
    if (lst->ini != NULL)
        lst->ini->ant = NULL;
    else
      lst->ult = NULL;
    if (lst->actual == a_borrar)
         lst->actual = NULL;
    delete a_borrar;
 }
}

void remover_al_final(Lista &lst) {
  assert(!es_vacia_lista(lst));
  if (lst->ult != NULL) {
    nodo_lista* a_borrar = lst->ult;
    lst->ult = a_borrar->ant;
    if (lst->ult != NULL)
        lst->ult->sig = NULL;
    else
        lst->ini = NULL;
    if (lst->actual == a_borrar)
         lst->actual = NULL;
    delete a_borrar;
  }
}

bool es_vacia_lista(Lista lst) {
  return (lst->ini == NULL || lst->ult == NULL);
}

bool pertenece_a_lista(nat elem, Lista lst) {
  nodo_lista *cursor = lst->ini;
  while ((cursor != NULL) && (cursor->elem != elem)) {
    cursor = cursor->sig;
  }
  return (cursor != NULL);
}

void destruir_lista(Lista &lst) {
  nodo_lista *cursor = lst->ini;
  while (cursor != NULL) {
    nodo_lista *a_borrar = cursor;
    cursor = cursor->sig;
    delete a_borrar;
  }
  delete lst;
}

nat cantidad_elementos(Lista lst) {
    nat cantidad = 0;
    nodo_lista *cursor = lst->ini;
    while (cursor != NULL) {
        cantidad++;
        cursor = cursor->sig;
    }
    return cantidad;
}

void comienzo(Lista lst) {
 lst->actual = lst->ini;
}

void final(Lista lst) {
  lst->actual = lst->ult;
}

nat anterior(Lista lst) {
  assert(existe_actual(lst));
  nat elem = lst->actual->elem;
  lst->actual = lst->actual->ant;
  return elem;
}

nat siguiente(Lista lst) {
  assert(existe_actual(lst));
  nat elem = lst->actual->elem;
  lst->actual = lst->actual->sig;
  return elem;
}

bool existe_actual(Lista lst) {
  return lst->actual != NULL;
}

nat actual(Lista lst) {
  assert(existe_actual(lst));
  return lst->actual->elem;
}

nat primero(Lista lst) {
  assert(!es_vacia_lista(lst));
  return lst->ini->elem;
}

nat ultimo(Lista lst) {
 assert(!es_vacia_lista(lst));
 return lst->ult->elem;
}

void imprimir_lista(Lista lst) {
  comienzo(lst);
  while (existe_actual(lst)) {
    printf("%d ", actual(lst));
    siguiente(lst);
  }
  printf(".\n");
}

Lista leer_lista() {
  Lista res = crear_lista();
  char strnum[10]; // suficiente espacio para enteros de 32 bits
  int cant_scanf = scanf("%s", strnum);
  assert(cant_scanf == 1);
  (void)(cant_scanf); // para evitar el warning al compilar con -NDEBUG
  nat elem;
  while (strcmp(strnum, ".")) {
    elem = atoi(strnum);
    //  insertar al final de la lista
    insertar_al_final(elem, res);
    cant_scanf = scanf("%s", strnum);
    assert(cant_scanf == 1);
    (void)(cant_scanf);
  };
  return res;
}
