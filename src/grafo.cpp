/*
  Módulo de implementación de `grafo'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/lista.h"
#include "../include/grafo.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctime>

typedef struct vertice_t {
  Lista adyacentes;
  Lista incidentes;
  nat ingrado;  // aristas entrantes
  nat outgrado; // aristas salientes
  // otros datos
} * Vertice;
static Vertice crear_vertice() {
  Vertice res = new vertice_t;
  res->adyacentes = crear_lista();
  res->incidentes = crear_lista();
  res->ingrado = 0;
  res->outgrado = 0;
  return res;
}

static void destruir_vertice(Vertice &v) {
  destruir_lista(v->adyacentes);
  destruir_lista(v->incidentes);
  delete v;
}

struct celda_t {
  bool existe;
  Vertice vertice;
};
static void celda_vacia(celda_t &c) {
  c.existe = false;
  c.vertice = NULL;
}
static void iniciar_celda(celda_t &c) {
  c.existe = true;
  c.vertice = crear_vertice();
}

struct rep_grafo {
  celda_t *celdas; // array de celdas
  nat max;         // identificador de vértice más alto
  nat n;           // cantidad de vértices
  nat m;           // cantidad de aristas
  bool dirigido;
};

Grafo crear_grafo(nat max, bool dirigido) {
  Grafo g = new rep_grafo;
  g->max = max;
  g->n = 0;
  g->m = 0;
  g->dirigido = dirigido;
  g->celdas = new celda_t[max + 1]; // se va a ignorar la celda 0
  for (nat i = 1; i <= max; i++)
    celda_vacia(g->celdas[i]);
  return g;
}

nat max_vertice(Grafo g) { return g->max; }

bool es_dirigido(Grafo g) { return g->dirigido; }



void agregar_vertice(nat v, Grafo &g) {
  assert((1 <= v) && (v <= g->max));
  if (!g->celdas[v].existe) {
    g->n++;
    iniciar_celda(g->celdas[v]);
  }
}

bool existe_vertice(nat v, Grafo g) {
  assert((1 <= v) && (v <= g->max));
  return g->celdas[v].existe;
}

nat out_grado(nat v, Grafo g) {
  assert(existe_vertice(v, g));
  return g->celdas[v].vertice->outgrado;
}

nat in_grado(nat v, Grafo g) {
  assert(existe_vertice(v, g));
  return g->celdas[v].vertice->ingrado;
}

Lista vertices(Grafo g) {
  Lista lst = crear_lista();
  for (nat i = g->max; i > 0; i--)
    if (existe_vertice(i, g))
      insertar_al_final(i, lst);
  return lst;
}

nat cantidad_vertices(Grafo g) { return g->n; }

void agregar_arista(nat v1, nat v2, Grafo g) {
  assert(existe_vertice(v1, g) && existe_vertice(v2, g));
  g->m++;
  g->celdas[v1].vertice->outgrado++;
  g->celdas[v2].vertice->ingrado++;
  insertar_al_final(v2, g->celdas[v1].vertice->adyacentes);
  insertar_al_final(v1, g->celdas[v2].vertice->incidentes);
  if (!g->dirigido) {
    assert(!pertenece_a_lista(v1, g->celdas[v2].vertice->adyacentes));
    g->celdas[v2].vertice->outgrado++;
    g->celdas[v1].vertice->ingrado++;
    insertar_al_final(v1, g->celdas[v2].vertice->adyacentes);
    insertar_al_final(v2, g->celdas[v1].vertice->incidentes);
    assert(g->celdas[v1].vertice->outgrado == g->celdas[v1].vertice->ingrado);
    assert(g->celdas[v2].vertice->outgrado == g->celdas[v2].vertice->ingrado);
  }
}


nat cantidad_aristas(Grafo g) { return g->m; }

Lista adyacentes(nat v, Grafo g) {
  assert(existe_vertice(v, g));
  return g->celdas[v].vertice->adyacentes;
}

Lista incidentes(nat v, Grafo g) {
  assert(existe_vertice(v, g));
  return g->celdas[v].vertice->incidentes;
}

void destruir_grafo(Grafo &g) {
  for (nat i = 1; i <= g->max; i++)
    if (existe_vertice(i, g))
      destruir_vertice(g->celdas[i].vertice);
  delete[] g->celdas;
  delete g;
}

void imprimir_grafo(Grafo g) {
  char str_dirigido[15];
  if (g->dirigido)
    strcpy(str_dirigido, "dirigido");
  else
    strcpy(str_dirigido, "no-dirigido");

  printf("%u %s\n", g->max, str_dirigido);
  for (nat i = 1; i <= g->max; i++) {
    if (existe_vertice(i, g)) {
      printf("%u: ", i);
      imprimir_lista(g->celdas[i].vertice->adyacentes);
    }
      //printf("\n");  
  }
  printf("0:\n");
  printf("Cantidad de vértices: %u\n", g->n);
  printf("Cantidad de aristas: %u\n", g->m);
  for (nat i = 1; i <= g->max; i++) {
    if (existe_vertice(i, g)) {
      printf("%u: %u, %u\n", i, out_grado(i, g), in_grado(i, g));
    }
  }
}

Grafo leer_grafo() {
  nat max;
  char str_dirigido[20];
  bool dirigido = true; // de manera predeterminada es dirigido
  int cant_scanf = scanf("%u %s", &max, str_dirigido); // cota superior de los
                                                       // identificadores de
                                                       // vértice y dirigido
  assert(cant_scanf == 2);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  if (!strcmp(str_dirigido, "no-dirigido"))
    dirigido = false;

  Grafo res = crear_grafo(max, dirigido);
  nat v;
  cant_scanf = scanf("%u:", &v);
  assert(cant_scanf == 1);
  assert(v <= max);
  // registrar vértices y guardar temporalmente las listas de adyacencia
  Lista *array_temporal = new Lista[max + 1];
  while (v != 0) {
    agregar_vertice(v, res);
    array_temporal[v] = leer_lista();

    cant_scanf = scanf("%u:", &v);
    assert(cant_scanf == 1);
    assert(v <= max);
  }
  // agregar las aristas una por una y verificar que todos los destinos de
  // aristas son vértices del grafo
  for (nat i = 1; i <= res->max; i++) {
    if (existe_vertice(i, res)) {
      // se recorre la lista que se había guardado de manera temporal
      Lista cursor = array_temporal[i];
      comienzo(cursor);
      while (existe_actual(cursor)) {
        assert((existe_vertice(actual(cursor), res)));
        agregar_arista(i, actual(cursor), res);
        siguiente(cursor);
      }
      destruir_lista(cursor);
    }
  }
  delete[] array_temporal;
  return res;
}

bool es_orden_topologico(Lista vertices, Grafo g) {
  bool res = true;
  unsigned int cant_visitados = 0;
  Lista lst = vertices;
  comienzo(lst);
  bool* visitados = new bool[g->n + 1];
  memset(visitados, 0, (g->n + 1) * sizeof(bool));
  while (res && existe_actual(lst)) {
    nat v = actual(lst);
    visitados[v] = true;
    cant_visitados++;
    Lista ady = adyacentes(v, g);
    comienzo(ady);
    while (existe_actual(ady)) {
      if (visitados[actual(ady)])
        res = false;
      siguiente(ady);
    }
    siguiente(lst);
  }
  delete [] visitados;
  return res && cant_visitados == g->n;
}

Grafo generar_grafo() {
  char str_con_ciclo[20];
  nat tamano;
  bool con_ciclo = true; // de manera predeterminada es dirigido
  int cant_scanf = scanf("%u %s", &tamano, str_con_ciclo); // cota superior de los
                                                       // identificadores de
                                                       // vértice y dirigido
  assert(cant_scanf == 2);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  if (strcmp(str_con_ciclo, "con_ciclo"))
    con_ciclo = false;
  
  Grafo res = crear_grafo(tamano, true);

  for(nat i = 1; i <= tamano; i++)
    agregar_vertice(i, res);
  
  //Agregar aristas forward
  for(nat i = 2; i <= tamano; i++)
    agregar_arista(i-1, i, res);
  
  if (con_ciclo)
    agregar_arista(tamano, 1, res);

  return res;
}
