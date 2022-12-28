# graph-topogical-ordering-or-cycle
Algoritmo para resolver Ex 3.12 (Algorith design, Jon Kleinberg, Eva Tardos)

## Archivos
El archivo implementado es cronologia_consistente.cpp, los demas son las estructuras de datos proporcionadas por Fing, UdelaR.

## Descripcion del problema
A partir de una serie de entrevistas en una investigación histórica se recopilaron una serie de datos
sobre un conjunto de n personas, P = {P1, P2, . . . , Pn}, que ya no están
vivas. Los datos recopilados se refieren a pares de personas, (Pi
, Pj ), en cierto
subconjunto de P × P, y cada dato puede ser de alguno de los tipos:
1. Pi murió antes de que Pj naciera,
2. las vidas de Pi y Pj se solaparon en el tiempo.

Queremos determinar si nuestros datos son consistentes, es decir, si puede
haber existido un conjunto de n personas tales que todos los datos recopilados
se satisfacen, respetando además el orden natural de nacimiento y muerte
para cada persona. Para ello necesitamos un algoritmo cuya salida sea alguno
de los siguientes resultados:
Una cronología de nacimientos y muertes de las n personas que verifique
la consistencia de los datos recopilados.
Por ejemplo, si para n = 3 los datos recopilados indican que P1 murió
antes de que P3 naciera y que las vidas de P2 y P1 se solaparon, la salida
de nuestro algoritmo podría ser:
nace P2, nace P1, muere P1, nace P3, muere P2, muere P3.
Un mensaje indicando que tal cronología no existe y por lo tanto nuestros
datos son inconsistentes.

## Descripción de la solución

1. Construir un grafo direccionado G=(V, E) donde los nodos son, para cada persona pi hay 2 nodos un nodo npi y otro mpi, que representan nace pi y muere pi respectivamente, las aristas del grafo se desprenen de los datos recompilados:
  - Si pi murió antes de que naciera pj hay una arista (mpi, npj) en E.
  
  - Si las vids de pi y pj se solapan agregamos las aristas (npi, mpj) y (npj, mpi).
  
  - Adicionalmente para cada persona pi agregamos la arista (npi, mpi).
  
2. Corremos el algoritmo para encontrar un orden topológico del grafo G.

3. Si el algoritmo encuentra un orden topológico de todos los nodos de G, entonces existe un orden cronologico de nacimiento y muerte. Si cuando finaliza el paso 2 no estan todos los nodos de G entonces este tiene un ciclo y por lo tanto no es posible construir la cronologica y por lo tanto los datos son inconsistentes.

## Correr el programa

Compilar:
```
make
```

Comenzar a ejecutar:
```
./principal
```

Comandos:
```
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
```
Correr test:
```
make testing
```
