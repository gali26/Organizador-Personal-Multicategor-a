# Organizador Personal Multicategoría
**Trabajo Integrador de AED2 – UNNE LSI 2025**

## Descripción
Este proyecto es un organizador personal que permite crear y gestionar categorías con sus artículos, además de establecer relaciones entre ellas. La idea es que el usuario pueda ordenar su información de manera jerárquica y con conexiones entre categorías, para encontrar y administrar datos de forma más eficiente.

## Funcionalidades
- **Crear, listar, editar y eliminar categorías.**
- **Agregar, buscar, editar, listar y eliminar elementos** dentro de cada categoría (usando un **ABB** para ordenarlos y buscarlos rápidamente).  
- **Establecer y gestionar relaciones** entre categorías.  
- **Guardar y cargar toda la información** desde archivos de texto.  
- **Menú de consola interactivo** para facilitar la navegación.

## Decisiones de diseño

**Estructuras utilizadas:**  
- **Lista enlazada simple:** para manejar la lista de categorías (`Categoria *lista`).  
- **Árbol binario de búsqueda (ABB):** para guardar los ítems de cada categoría (`NodoItem *arbolItems`).  
- **Grafo no dirigido con lista de adyacencia:** para representar relaciones entre categorías (`Relacion *adyacencias`).  

**Motivo de elección:**  
- **Lista enlazada:** flexible, permite agregar o eliminar categorías sin preocuparse por el tamaño de la lista y facilita el recorrido de todas las categorías.  
- **ABB:** permite búsquedas rápidas y mantiene los ítems ordenados alfabéticamente, ideal para listados ordenados.  
- **Grafo (lista de adyacencia):** permite múltiples relaciones entre categorías de manera eficiente en memoria cuando las relaciones son pocas.  

**Alternativas descartadas:**  
- Lista de categorías con arreglo estático: menos flexible y costosa al eliminar elementos.  
- Lista enlazada para ítems: simple pero más lenta en búsquedas; tabla hash: rápida pero no mantiene orden.  
- Matriz de adyacencia para relaciones: consume más memoria y es menos eficiente cuando hay pocas relaciones.

## Desarrollo obtenido
- **Creación, listado, edición y eliminación de categorías.**  
- **Gestión completa de ítems dentro de cada categoría** usando ABB.  
- **Establecimiento y gestión de relaciones** entre categorías.  
- **Persistencia de datos** mediante archivos de texto.  
- **Interfaz de consola** con menú interactivo que guía al usuario paso a paso.

## Compilación y ejecución
Para compilar y ejecutar en sistemas con `gcc`:

```bash
gcc organizadorMulticategoria.c -o organizador
./organizador
