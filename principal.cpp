
/*
  Módulo principal de la tarea 2.

Intérprete de comandos para probar los módulos.

Cada comando tiene un nombre y una lista (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido;
- se cumplen las precondiciones de las operaciones invocadas.

Descripción de los comandos:

Fin
   Termina el programa.
# comentario
   Imprime el resto de la línea.
crear_personas <n>
   Crea un conjunto de `n' personas sin restricciones.
leer_lista_muertes
   Lee una lista de pares en formato a1 b1 ... ak bk . 
   Crea el conjunto de restricciones de tipo1:
   Cada entrada ai bi indica que la persona `ai' murió antes que la persona `bi' naciera.
leer_lista_convivencias
   Lee una lista de pares en formato a1 b1 ... ak bk . 
   Crea el conjunto de restricciones de tipo2:
   Cada entrada ai bi indica que las personas `ai' y `bi' convivieron.
imprimir_cronologia
   Imprime la cronología de nacimientos y muertes retornada por la función
   `cronologia_consistente' (en caso de retornar una).
existe_cronologia
   retorna un mensaje indicando si la salida de `cronologia_consistente'
   indicó que no hay una cronología, si retornó una cronología incorrecta,
   o si retornó una cronología y es consistente con las restricciones.
crear_personas_stress <n>
   Crea un conjunto de `n' personas con las siguientes restricciones:
   toda persona i murió antes que la persona i+2 naciera, y convivió
   con la persona i+1
destruir_estructuras
   Destruye las estructuras (liberando la memoria asignada).

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/lista.h"
#include "include/grafo.h"
#include "include/lista_datos.h"
#include "include/cronologia_consistente.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_crear_personas,
  cmd_leer_lista_muertes,
  cmd_leer_lista_convivencias,
  cmd_imprimir_cronologia,
  cmd_existe_cronologia,
  cmd_destruir_estructuras,
  cmd_crear_personas_stress,
  no_reconocido
};
const int cant_com = no_reconocido;

struct enum_nombre_cmd {
  const enum_cmd_t enum_cmd;
  const char *nombre_cmd;
};

/* Asociación entre nombre de comando y enumerado. */
const enum_nombre_cmd cmds[] = {
    {cmd_fin, "Fin"},
    {cmd_comentario, "#"},
    {cmd_crear_personas, "crear_personas"},
    {cmd_leer_lista_muertes, "leer_lista_muertes"},
    {cmd_leer_lista_convivencias, "leer_lista_convivencias"},
    {cmd_imprimir_cronologia, "imprimir_cronologia"},
    {cmd_existe_cronologia, "existe_cronologia"},
    {cmd_destruir_estructuras, "destruir_estructuras"},
    {cmd_crear_personas_stress, "crear_personas_stress"}};

/*  Devuelve el identificador de comando leido desde la entrada estándar. */
enum_cmd_t identificador_comando();

/*  Incrementa el contador de comandos y muestra el prompt. */
void mostrar_prompt(int &cont_comandos);

/* Devuelve en `str_numero' la conversión de ´nat' a  string. */
void nat_a_string(char *str_numero, nat nat);

/*** Función auxiliar para verificar si una cronología es consistente ***/ 
bool es_cronologia_consistente(Cronologia cr, nat n, ListaDatos tipo1, ListaDatos tipo2);

int main() {
  nat n = 0;
  ListaDatos lista_muertes = crear_lista_datos();
  ListaDatos lista_convivencias = crear_lista_datos();

  const int MAX_LINEA = 100;
  char restolinea[MAX_LINEA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {

    mostrar_prompt(cont_comandos);
    enum_cmd_t enum_com = identificador_comando();

    // procesar el comando
    switch (enum_com) {
    case cmd_fin: {
      salir = true;
      printf("Fin.\n");
      break;
    }

    case cmd_comentario: {
      fgets(restolinea, MAX_LINEA, stdin);
      printf("%s", restolinea);
      ungetc('\n', stdin);
      break;
    }

    case cmd_crear_personas: {
      int cant_scanf = scanf("%u", &n);
      assert(cant_scanf == 1);
      (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
      destruir_lista_datos(lista_muertes);
      destruir_lista_datos(lista_convivencias);
      break;
    }

    case cmd_leer_lista_muertes: {
      destruir_lista_datos(lista_muertes);
      lista_muertes = leer_lista_datos();
      break;
    }

    case cmd_leer_lista_convivencias: {
      destruir_lista_datos(lista_convivencias);
      lista_convivencias = leer_lista_datos();
      break;
    }

    case cmd_imprimir_cronologia: {
      Cronologia crono = cronologia_consistente(n, lista_muertes, lista_convivencias);
      if (crono == NULL) {
        printf("No hay una cronología para estas restricciones.\n");
        break;
      }

      for (nat i = 0; i < 2*n; i++) {
        nat persona = crono[i].id;
        if (crono[i].tipo == 0) {
          printf("(%u,nace) ", persona);
        } else {
          printf("(%u,muere) ", persona);
        }
      }
      printf(".\n");

      delete [] crono;
      break;
    }

    case cmd_existe_cronologia: {
      Cronologia crono = cronologia_consistente(n, lista_muertes, lista_convivencias);
      if (crono == NULL) {
        printf("No hay una cronología para estas restricciones.\n");
        break;
      }

      if (es_cronologia_consistente(crono, n, lista_muertes, lista_convivencias)) {
        printf("Hay una cronología consistente.\n");
      } else {
        printf("ERROR: se retornó una cronología que no es consistente");
      }

      delete [] crono;
      break;
    }

    case cmd_crear_personas_stress: {
      int cant_scanf = scanf("%u", &n);
      assert(cant_scanf == 1);
      (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
      destruir_lista_datos(lista_muertes);
      destruir_lista_datos(lista_convivencias);
      
      for (nat i = 1; i <= n - 2; i++) {
        nat id1 = i;
        nat id2 = i+2;
        dato d = { id1, id2 };
        insertar_dato(d, lista_muertes);
      }
      for (nat i = 1; i <= n - 1; i++) {
        nat id1 = i;
        nat id2 = i+1;
        dato d = { id1, id2 };
        insertar_dato(d, lista_convivencias);
      }

      break;
    }

    case cmd_destruir_estructuras: {
      destruir_lista_datos(lista_muertes);
      destruir_lista_datos(lista_convivencias);
      break;
    }

    default:
      printf("Comando No Reconocido.\n");
      break;
    } // switch
    fgets(restolinea, MAX_LINEA, stdin);
  } // while

  destruir_lista_datos(lista_muertes);
  destruir_lista_datos(lista_convivencias);
  return 0;
} 

enum_cmd_t identificador_comando() {
  enum_cmd_t res = no_reconocido;

  const int MAX_NOMBRE = 50;
  char nom_com[MAX_NOMBRE];
  int cant_scanf = scanf("%s", nom_com);
  assert(cant_scanf == 1);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  bool encontrado = false;
  int i = cmd_fin; // = 0
  while ((!encontrado) && (i < cant_com)) {
    if (0 == strcmp(nom_com, cmds[i].nombre_cmd)) {
      res = cmds[i].enum_cmd;
      encontrado = true;
    } else {
      i++;
    }
  }
  return res;
} // identificador_comando

/*
  Incrementa el contador de comandos y muestra el prompt.
 */
void mostrar_prompt(int &cont_comandos) {
  cont_comandos++;
  printf("%u>", cont_comandos);
} // mostrar_prompt


/* Devuelve en `str_numero' la conversión de ´nat' a  string. */
void nat_a_string(char *str_numero, nat nat) {
  if (nat == UINT_MAX)
    strcpy(str_numero, "NO");
  else
    sprintf(str_numero, "%u", nat);
} // nat_a_string

/*** Función auxiliar para verificar si una cronología es consistente ***/ 
bool es_cronologia_consistente(Cronologia cr, nat n, ListaDatos tipo1, ListaDatos tipo2) {

  bool consistente = true; 
  
  nat* nacimientos = new nat[n+1];
  nat* muertes = new nat[n+1]; 
  //para verificar que aparecen nacimientos y muertes de todas las personas 
  bool* nacio = new bool[n+1]; 
  bool* murio = new bool[n+1];

  for(nat i = 1; i <= n; i++) {
    nacimientos[i] = 0;
    muertes[i] = 0;
    nacio[i] = false;  
    murio[i] = false;
  }
  
  for(nat i = 0; i < 2*n; i++) {
    if(cr[i].tipo == nace) {
      nacimientos[cr[i].id] = i;
      nacio[cr[i].id] = true;
    } else {
      muertes[cr[i].id] = i;
      murio[cr[i].id] = true;
    }
  }

  for(nat i = 1; i <= n; i++) {
    if (!nacio[i] || !murio[i]) {
      consistente = false;
      goto end;
    }
  }

  // Verificación orden natural de nacimiento y muerte para cada persona
  for(nat i = 1; i <= n; i++) {
    if (nacimientos[i] >= muertes[i]) {
      consistente = false;
      goto end;
    } 
  } 

  // Verificación consistencia datos de tipo 1
  while(!es_vacia_lista_datos(tipo1)) {
    dato d = primer_dato(tipo1);
    if(muertes[id1(d)] >= nacimientos[id2(d)]) {
     consistente = false;
     goto end;
    }
    tipo1 = resto_datos(tipo1);
  }

  // Verificación consistencia datos de tipo 2
  while(!es_vacia_lista_datos(tipo2)) {
    dato d = primer_dato(tipo2);
    if( (nacimientos[id1(d)] >= muertes[id2(d)]) || (nacimientos[id2(d)] >= muertes[id1(d)])) {
     consistente = false;
     goto end;
    }
    tipo2 = resto_datos(tipo2);
  }

  end:
  delete[] nacio;
  delete[] murio;
  delete[] nacimientos;
  delete[] muertes;
  return consistente;
}
