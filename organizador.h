#ifndef ORGANIZADOR_H
#define ORGANIZADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nodo del Árbol Binario de Búsqueda para almacenar ítems.
// Los ítems se guardan ordenados alfabéticamente por nombre.
typedef struct nodoItem {
    char nombre[100];
    char info[500];
    struct nodoItem *izq;   // Subárbol izquierdo
    struct nodoItem *der;   // Subárbol derecho
} NodoItem;

/* Adelanto para detectar los punteros*/
struct categoria;

typedef struct relacion {
    struct categoria *destino;
    struct relacion *sig;
} Relacion;

// Representa una categoría del organizador.
// Implementada como nodo de lista enlazada.
typedef struct categoria {
    char nombre[100];
    NodoItem *arbolItems;   // Árbol con los ítems de esta categoría
    Relacion *adyacencias;
    struct categoria *sig;   // Siguiente categoría (lista enlazada)
} Categoria;

// PROTOTIPOS

// Menu
void menuPrincipal(Categoria **lista);

// Categorias
Categoria* crearCategoria(Categoria **lista, char nombre[]);
void listarCategorias(Categoria *lista);
int eliminarCategoria(Categoria **lista, char nombre[]);
Categoria* buscarCategoria(Categoria *lista, char nombre[]);
void editarCategoria(Categoria *cat);

// Relaciones
int agregarRelacion(Categoria *a, Categoria *b);
void listarRelaciones(Categoria *cat);
int eliminarRelacion(Categoria *a, Categoria *b);
int existeRelacion(Categoria *a, Categoria *b);

// Items
NodoItem* crearNodoItem(char nombre[], char info[]);
void insertarItemABB(NodoItem **raiz, char nombre[], char info[]);
NodoItem* buscarItemABB(NodoItem *raiz, char nombre[]);
void inorderPrint(NodoItem *raiz);
NodoItem* eliminarNodoABB(NodoItem *raiz, char nombre[]);
NodoItem* minimo(NodoItem *r);
void liberarABB(NodoItem *raiz);

// Archivo
void guardarEnArchivo(Categoria *lista);
void cargarDesdeArchivo(Categoria **lista);

// Utilidad
void limpiarBuffer();

#endif
