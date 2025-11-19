# Organizador-Personal-Multicategoria
Trabajo Integrador de AED2 Unne LSI 2025.

## Descripción
Este proyecto es un **organizador personal** que permite crear y gestionar categorías con sus ítems, además de establecer relaciones entre ellas. La idea es que el usuario pueda ordenar su información de manera jerárquica y con conexiones entre categorías, para encontrar y administrar datos de forma más eficiente.


## Funcionalidades (objectivo)
- Crear, listar, editar y eliminar categorías.
- Agregar, buscar, editar, listar y eliminar ítems dentro de cada categoría (usando un ABB para ordenarlos y buscarlos rápido).
- Relacionar categorías entre sí y gestionar esas relaciones.
- Guardar y cargar toda la información desde archivos de texto.
- Menú de consola interactivo.

## Decisiones de diseño
**¿Qué estructuras eligieron y para qué parte del sistema?**
-**Lista enlazada simple** → para manejar la lista de categorías (Categoria *lista).
-**Árbol binario de búsqueda (ABB)** → para guardar los ítems de cada categoría (NodoItem *arbolItems).
-**Grafo no dirigido con lista de adyacencia** → para representar relaciones entre categorías (Relacion *adyacencias).


**¿Por qué esa estructura es adecuada para ese problema?**
-**Lista enlazada:** es simple y permite agregar o eliminar categorías sin preocuparse por el tamaño de la lista. Además, recorrerla para mostrar todas las categorías es rápido y fácil.
-**ABB:** facilita encontrar ítems rápidamente y mantiene los nombres ordenados alfabéticamente, lo que hace más sencillo mostrarlos en orden.
-**Grafo (lista de adyacencia):** permite crear múltiples relaciones entre categorías de forma flexible y no gasta tanta memoria si las relaciones son pocas comparadas con el número de categorías.

**¿Qué alternativas consideraron y por qué las descartaron?**
Para la lista de categorías: un arreglo estático sería menos flexible y habría que mover elementos cada vez que se eliminara uno.
**Para los ítems:** una lista enlazada es más simple, pero buscar ítems sería más lento; una tabla hash habría sido eficiente en búsqueda, pero no mantiene los ítems ordenados.
**Para relaciones:** una matriz de adyacencia consume más memoria y es menos práctica cuando hay pocas relaciones entre muchas categorías.

## Desarrollo obtenido
-Se puede crear, listar, editar y eliminar categorías.
-Se pueden agregar, buscar, editar, listar y eliminar ítems dentro de cada categoría usando ABB.
-Se pueden establecer relaciones entre categorías y gestionarlas (listar, editar o eliminar).
-Toda la información se guarda y carga desde archivos de texto, garantizando persistencia.
-Interfaz de consola con menú interactivo que guía al usuario paso a paso.

## Compilación y ejecución
Para compilar y ejecutar en un sistema con `gcc`:

```bash
gcc organizadorMulticategoria.c -o organizador
./organizador
