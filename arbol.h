#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "productos.h"

typedef struct _nodoArbol
{
    stProducto dato;
    struct _nodoArbol *izq;
    struct _nodoArbol *der;
} nodoArbol;

nodoArbol * inicArbol();
nodoArbol * cargarElArbol (nodoArbol * arbol);
nodoArbol * crearNodoArbol(stProducto dato);
nodoArbol * insertarPorId(nodoArbol * arbol, stProducto dato);
nodoArbol * buscar(nodoArbol * arbol, stProducto dato);
nodoArbol * buscarPorID(nodoArbol * arbol, int id);
nodoArbol * deArrayToArbol(stProducto dato[], int principio, int fin);
nodoArbol * borrarNodoArbol (nodoArbol * osvaldo, stProducto dato);
nodoArbol * nodoMasDerecho (nodoArbol* arbol);
nodoArbol * nodoMasIzquierdo (nodoArbol* arbol);
void preorder(nodoArbol * arbol);
void inorder(nodoArbol * arbol);
void postorder(nodoArbol * arbol);
stProducto retornaProdNodo (nodoArbol * arbol);
void anularUnProducto (nodoArbol ** arbolProdAnulados, nodoArbol ** arbolProd);
void agregarProductoAnulado (nodoArbol ** arbolProdAnulados, nodoArbol ** arbolProd);
int buscarSiExisteProductoPorID(nodoArbol * arbol, int id);

void modificarProductoArchi(char archi[], stProducto dato);

#endif // ARBOL_H_INCLUDED
