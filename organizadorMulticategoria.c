/*
   ORGANIZADOR PERSONAL MULTICATEGORIA  
   Proyecto Integrador – Algoritmos y Estructuras de Datos II

   Estructuras utilizadas:
     - Lista enlazada de categorias
     - Arbol binario de busqueda (ABB) para los items de cada categoria
     - Grafo no dirigido mediante listas de adyacencia para relaciones entre categorias

   Persistencia:
     - Archivo de texto (organizador.txt) con marcadores y corte de control
     - Archivo binario (organizador.dat) para respaldo estructurado de categorías e items

   Funcionalidades principales:
     - Crear, editar, buscar y eliminar categorias
     - Insertar, buscar, editar y eliminar ítems ordenados alfabeticamente (ABB)
     - Establecer y eliminar relaciones entre categorias (grafo)
     - Guardado y carga automatica desde archivos de texto y binarios
     - Recorridos y busquedas eficientes en estructuras dinamicas
*/

#include "organizador.h"

// MAIN
int main() {
    Categoria *listaCategorias = NULL;

    // NUEVO: intenta cargar primero desde .dat
    cargarDesdeBinario(&listaCategorias);

// Si no existe .dat, cargar desde texto
    if (!listaCategorias)
    cargarDesdeArchivo(&listaCategorias);

    menuPrincipal(&listaCategorias);

// Guardar en ambos formatos
    guardarEnArchivo(listaCategorias);
    guardarEnBinario(listaCategorias);

    return 0;
}

// MENU PRINCIPAL
void menuPrincipal(Categoria **lista) {
    int opcion;
    char nombre[100];
    char info[500];

    do {
        printf("\n========== ORGANIZADOR PERSONAL ==========\n");
        printf("1. Crear nueva categoria\n");
        printf("2. Listar categorias\n");
        printf("3. Eliminar categoria\n");
        printf("4. Agregar item a categoria\n");
        printf("5. Listar items de una categoria\n");
        printf("6. Buscar item por nombre (recorre ABBs)\n");
        printf("7. Editar item\n");
        printf("8. Editar categoria\n");
        printf("9. Relacionar categorias\n");
        printf("10. Ver relaciones de una categoria\n");
        printf("11. Eliminar relacion entre categorias\n");
        printf("12. Guardar y salir\n");
        printf("Seleccione: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch(opcion) {
            case 1:
                printf("Nombre de la nueva categoria: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                crearCategoria(lista, nombre);
                break;

            case 2:
                listarCategorias(*lista);
                break;

            case 3:
                printf("Nombre de la categoría a eliminar: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                if(eliminarCategoria(lista, nombre))
                    printf("Eliminada.\n");
                else
                    printf("No existe.\n");
                break;

            case 4: {
                printf("Nombre de la categoria: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;

                Categoria *cat = buscarCategoria(*lista, nombre);
                if(!cat) { printf("No existe.\n"); break; }

                char nomItem[100];
                printf("Nombre del item: ");
                fgets(nomItem, 100, stdin);
                nomItem[strcspn(nomItem, "\n")] = 0;

                printf("Informacion adicional: ");
                fgets(info, 500, stdin);
                info[strcspn(info, "\n")] = 0;

                insertarItemABB(&cat->arbolItems, nomItem, info);
                break;
            }

            case 5:
                printf("Nombre de la categoria: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;

                Categoria *cat = buscarCategoria(*lista, nombre);
                if(cat) inorderPrint(cat->arbolItems);
                else printf("No existe.\n");
                break;

            case 6:
                printf("Nombre del item: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;

                {
                    Categoria *aux = *lista;
                    int found = 0;

                    while(aux) {
                        NodoItem *ni = buscarItemABB(aux->arbolItems, nombre);
                        if(ni) {
                            printf("Encontrado en: %s\n", aux->nombre);
                            printf("Info: %s\n", ni->info);
                            found = 1;
                        }
                        aux = aux->sig;
                    }

                    if(!found) printf("No encontrado.\n");
                }
                break;

            case 7: {
                printf("Categoria: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;

                Categoria *c = buscarCategoria(*lista, nombre);
                if(!c) { printf("No existe.\n"); break; }

                char nom[100];
                printf("Item a editar: ");
                fgets(nom, 100, stdin);
                nom[strcspn(nom, "\n")] = 0;

                NodoItem *it = buscarItemABB(c->arbolItems, nom);
                if(!it) { printf("No existe.\n"); break; }

                printf("Nuevo nombre (enter para dejar): ");
                char nuevoN[100]; fgets(nuevoN,100,stdin); nuevoN[strcspn(nuevoN,"\n")] = 0;

                printf("Nueva info (enter para dejar): ");
                char nuevaI[500]; fgets(nuevaI,500,stdin); nuevaI[strcspn(nuevaI,"\n")]=0;

                c->arbolItems = eliminarNodoABB(c->arbolItems, it->nombre);

                if(strlen(nuevoN) == 0) strcpy(nuevoN, nom);
                if(strlen(nuevaI) == 0) strcpy(nuevaI, it->info);

                insertarItemABB(&c->arbolItems, nuevoN, nuevaI);
                break;
            }

            case 8:
                printf("Categoria: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;

                Categoria *c2 = buscarCategoria(*lista, nombre);
                if(c2) editarCategoria(c2);
                else printf("No existe.\n");
                break;


            case 9: {
                char a[100], b[100];
                printf("Categoria A: "); fgets(a,100,stdin); a[strcspn(a,"\n")]=0;
                printf("Categoria B: "); fgets(b,100,stdin); b[strcspn(b,"\n")]=0;

                Categoria *A = buscarCategoria(*lista, a);
                Categoria *B = buscarCategoria(*lista, b);

                if(!A || !B) { printf("Alguna no existe.\n"); break; }

                if(agregarRelacion(A,B)) printf("Relacion agregada.\n");
                else printf("La relacion ya existe.\n");
                break;
            }

            case 10:
                printf("Categoria: ");
                fgets(nombre,100,stdin); nombre[strcspn(nombre,"\n")]=0;

                Categoria *cx = buscarCategoria(*lista, nombre);
                if(cx) listarRelaciones(cx);
                else printf("No existe.\n");
                break;

            case 11: {
                char a[100], b[100];
                printf("Categoria A: "); fgets(a,100,stdin); a[strcspn(a,"\n")]=0;
                printf("Categoria B: "); fgets(b,100,stdin); b[strcspn(b,"\n")]=0;

                Categoria *A = buscarCategoria(*lista, a);
                Categoria *B = buscarCategoria(*lista, b);

                if(!A || !B) { printf("Alguna no existe.\n"); break; }

                if(eliminarRelacion(A,B)) printf("Relacion eliminada.\n");
                else printf("La relacion no existia.\n");
                break;
            }
             case 12:
                printf("Guardando...\n");
                break;
                
            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 9);
}

// CATEGORIAS
Categoria* crearCategoria(Categoria **lista, char nombre[]) {
    Categoria *nuevo = (Categoria*) malloc(sizeof(Categoria));
    strcpy(nuevo->nombre, nombre);
    nuevo->arbolItems = NULL;
    nuevo->adyacencias = NULL;
    nuevo->sig = *lista;
    *lista = nuevo;
    return nuevo;
}

void listarCategorias(Categoria *lista) {
    printf("\nCATEGORIAS:\n");
    while(lista) {
        printf(" - %s\n", lista->nombre);
        lista = lista->sig;
    }
}

int eliminarCategoria(Categoria **lista, char nombre[]) {
    Categoria *act = *lista, *ant = NULL;

    while(act) {
        if(strcmp(act->nombre, nombre) == 0) {

            Categoria *c = *lista;
            while(c) {
                if(c != act)
                    eliminarRelacion(c, act);
                c = c->sig;
            }

            if(ant) ant->sig = act->sig;
            else *lista = act->sig;

            liberarABB(act->arbolItems);

            Relacion *r = act->adyacencias;
            while(r) {
                Relacion *t = r->sig;
                free(r);
                r = t;
            }

            free(act);
            return 1;
        }

        ant = act;
        act = act->sig;
    }

    return 0;
}

Categoria* buscarCategoria(Categoria *lista, char nombre[]) {
    while(lista) {
        if(strcmp(lista->nombre, nombre) == 0)
            return lista;
        lista = lista->sig;
    }
    return NULL;
}

void editarCategoria(Categoria *cat) {
    char nuevo[100];
    printf("Nuevo nombre: ");
    fgets(nuevo,100,stdin);
    nuevo[strcspn(nuevo,"\n")] = 0;

    if(strlen(nuevo) > 0)
        strcpy(cat->nombre, nuevo);
}

// RELACIONES
int existeRelacion(Categoria *a, Categoria *b) {
    Relacion *r = a->adyacencias;
    while(r) {
        if(r->destino == b) return 1;
        r = r->sig;
    }
    return 0;
}

int agregarRelacion(Categoria *a, Categoria *b) {
    if(existeRelacion(a,b)) return 0;

    Relacion *r1 = (Relacion*) malloc(sizeof(Relacion));
    r1->destino = b;
    r1->sig = a->adyacencias;
    a->adyacencias = r1;

    Relacion *r2 = (Relacion*) malloc(sizeof(Relacion));
    r2->destino = a;
    r2->sig = b->adyacencias;
    b->adyacencias = r2;

    return 1;
}

void listarRelaciones(Categoria *cat) {
    printf("Relaciones de %s:\n", cat->nombre);

    Relacion *r = cat->adyacencias;
    if(!r) { printf(" (ninguna)\n"); return; }

    while(r) {
        printf(" - %s\n", r->destino->nombre);
        r = r->sig;
    }
}

int eliminarRelacion(Categoria *a, Categoria *b) {
    int eliminado = 0;

    Relacion *r = a->adyacencias, *ant = NULL;
    while(r) {
        if(r->destino == b) {
            if(ant) ant->sig = r->sig;
            else a->adyacencias = r->sig;

            free(r);
            eliminado = 1;
            break;
        }
        ant = r;
        r = r->sig;
    }

    r = b->adyacencias; 
    ant = NULL;
    while(r) {
        if(r->destino == a) {
            if(ant) ant->sig = r->sig;
            else b->adyacencias = r->sig;

            free(r);
            break;
        }
        ant = r;
        r = r->sig;
    }

    return eliminado;
}

// ITEMS
NodoItem* crearNodoItem(char nombre[], char info[]) {
    NodoItem *n = (NodoItem*) malloc(sizeof(NodoItem));
    strcpy(n->nombre, nombre);
    strcpy(n->info, info);
    n->izq = n->der = NULL;
    return n;
}

void insertarItemABB(NodoItem **raiz, char nombre[], char info[]) {
    if(!(*raiz)) {
        *raiz = crearNodoItem(nombre, info);
        return;
    }

    int cmp = strcmp(nombre, (*raiz)->nombre);

    if(cmp < 0)
        insertarItemABB(&(*raiz)->izq, nombre, info);
    else if(cmp > 0)
        insertarItemABB(&(*raiz)->der, nombre, info);
    else
        strcpy((*raiz)->info, info);
}

NodoItem* buscarItemABB(NodoItem *raiz, char nombre[]) {
    if(!raiz) return NULL;
    int cmp = strcmp(nombre, raiz->nombre);
    if(cmp == 0) return raiz;
    if(cmp < 0) return buscarItemABB(raiz->izq, nombre);
    return buscarItemABB(raiz->der, nombre);
}

void inorderPrint(NodoItem *raiz) {
    if(!raiz) return;
    inorderPrint(raiz->izq);
    printf(" - %s\n   %s\n", raiz->nombre, raiz->info);
    inorderPrint(raiz->der);
}

NodoItem* minimo(NodoItem *r) {
    while(r && r->izq) r = r->izq;
    return r;
}

NodoItem* eliminarNodoABB(NodoItem *raiz, char nombre[]) {
    if(!raiz) return NULL;

    int cmp = strcmp(nombre, raiz->nombre);

    if(cmp < 0)
        raiz->izq = eliminarNodoABB(raiz->izq, nombre);
    else if(cmp > 0)
        raiz->der = eliminarNodoABB(raiz->der, nombre);
    else {
        if(!raiz->izq) {
            NodoItem *der = raiz->der;
            free(raiz);
            return der;
        }
        if(!raiz->der) {
            NodoItem *izq = raiz->izq;
            free(raiz);
            return izq;
        }

        NodoItem *m = minimo(raiz->der);
        strcpy(raiz->nombre, m->nombre);
        strcpy(raiz->info, m->info);
        raiz->der = eliminarNodoABB(raiz->der, m->nombre);
    }

    return raiz;
}

void liberarABB(NodoItem *raiz) {
    if(!raiz) return;
    liberarABB(raiz->izq);
    liberarABB(raiz->der);
    free(raiz);
}

// ARCHIVOS
void guardarEnArchivo(Categoria *lista) {
    FILE *f = fopen("organizador.txt", "w");
    if(!f) return;

    Categoria *c = lista;
    while(c) {
        fprintf(f, "#CAT=%s\n", c->nombre);

        Relacion *r = c->adyacencias;
        while(r) {
            fprintf(f, "#REL=%s\n", r->destino->nombre);
            r = r->sig;
        }

        void escribir(NodoItem *root) {
            if(!root) return;
            escribir(root->izq);
            fprintf(f, "#ITEM=%s\n", root->nombre);
            fprintf(f, "%s\n", root->info);
            fprintf(f, "#ENDITEM\n");
            escribir(root->der);
        }
        escribir(c->arbolItems);

        fprintf(f, "#ENDCAT\n");
        c = c->sig;
    }

    fclose(f);
}

void cargarDesdeArchivo(Categoria **lista) {
    FILE *f = fopen("organizador.txt", "r");
    if(!f) return;

    char linea[600];
    Categoria *actual = NULL;

    while(fgets(linea, 600, f)) {
        linea[strcspn(linea, "\n")] = 0;

        if(strncmp(linea, "#CAT=", 5) == 0) {
            char nombre[100];
            strcpy(nombre, linea + 5);
            actual = crearCategoria(lista, nombre);
        }

        else if(strncmp(linea, "#REL=", 5) == 0) {
            char nomRel[100];
            strcpy(nomRel, linea + 5);

            Categoria *dest = buscarCategoria(*lista, nomRel);

            if(actual && dest)
                agregarRelacion(actual, dest);
        }

        else if(strncmp(linea, "#ITEM=", 6) == 0) {
            char nombreItem[100];
            strcpy(nombreItem, linea + 6);

            char info[500] = "";
            char buf[500];

            while(fgets(buf, 500, f)) {
                buf[strcspn(buf, "\n")] = 0;
                if(strcmp(buf, "#ENDITEM") == 0) break;

                strcat(info, buf);
                strcat(info, "\n");
            }

            if(actual)
                insertarItemABB(&actual->arbolItems, nombreItem, info);
        }

    }

    fclose(f);
}

// Guarda categorias e items en archivo binario .dat
void guardarEnBinario(Categoria *lista) {
    FILE *f = fopen("organizador.dat", "wb");
    if (!f) return;

    // Contar categorías
    int cantCat = 0;
    Categoria *c = lista;
    while (c) {
        cantCat++;
        c = c->sig;
    }

    fwrite(&cantCat, sizeof(int), 1, f);

    c = lista;
    while (c) {
        // Escribir nombre de categoria
        fwrite(c->nombre, sizeof(char), 100, f);

        // Contar items del ABB
        int cantItems = 0;
        void contar(NodoItem *n) {
            if (!n) return;
            cantItems++;
            contar(n->izq);
            contar(n->der);
        }
        contar(c->arbolItems);

        fwrite(&cantItems, sizeof(int), 1, f);

        // Escribir items en inorder
        void escribir(NodoItem *n) {
            if (!n) return;
            escribir(n->izq);
            fwrite(n->nombre, sizeof(char), 100, f);
            fwrite(n->info, sizeof(char), 500, f);
            escribir(n->der);
        }
        escribir(c->arbolItems);

        c = c->sig;
    }

    fclose(f);
}

// Carga categorias e items desde archivo binario .dat
void cargarDesdeBinario(Categoria **lista) {
    FILE *f = fopen("organizador.dat", "rb");
    if (!f) return;

    int cantCat;
    fread(&cantCat, sizeof(int), 1, f);

    for (int i = 0; i < cantCat; i++) {
        char nombreCat[100];
        fread(nombreCat, sizeof(char), 100, f);

        Categoria *nuevo = crearCategoria(lista, nombreCat);

        int cantItems;
        fread(&cantItems, sizeof(int), 1, f);

        for (int j = 0; j < cantItems; j++) {
            char nombreItem[100];
            char infoItem[500];

            fread(nombreItem, sizeof(char), 100, f);
            fread(infoItem, sizeof(char), 500, f);

            insertarItemABB(&nuevo->arbolItems, nombreItem, infoItem);
        }
    }

    fclose(f);
}

// UTILIDADES
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
