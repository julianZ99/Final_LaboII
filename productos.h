#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

typedef struct
{
	int idPedido;
	int idCliente;
	int idProducto;
} stPedido;

typedef struct
{
    int idProducto;
    char nombreProducto [30];
    char descripcionProducto [140];
    float valor;
    int cantidad;
    int productoAnulado;
} stProducto;

stProducto cargarUnProducto ();
void mostrarUnProducto(stProducto a);
void estadoDelProducto(int numero);
int contarProductos(char archivoProductos[]);
void deArchivoToArrayProductos (stProducto prods[],stProducto anuls[], char archivo [],int * validosProd,int * validosAnulados);
void deArrayAArchivo(char archivoAPasar[], stProducto prods[], int validos);
void agregarDeArrayAArchivo(char archivoAPasar[], stProducto prods);
void agregarDeArrayAArchivoFinal(char archivoAPasar[], stProducto prods);


typedef struct _nodoListaProducto
{
    stProducto p;
    struct _nodoListaProducto * siguiente;
} nodoListaProducto;


nodoListaProducto * inicListaProducto();
nodoListaProducto * crearNodoListaProducto(stProducto p);
nodoListaProducto * agregarAlPrincipioProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarAlFinalProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
nodoListaProducto * buscarUltimoNodoProducto(nodoListaProducto * lista);
nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
void mostrarListaRecursivaProductosUsuario(nodoListaProducto * lista);
void mostrarListaRecursivaProductosAdmin(nodoListaProducto * lista);
nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id);
nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista);
float calcularTotalPrecioProductos (nodoListaProducto * lista);
int buscaIdUltimoPedido(char rutaDelArchivoPedido[]);

int buscaIdUltimoProducto(char rutaDelArchivoPedido[]);
int deArchivoToArrayProductosAnulados (stProducto prods[], char archivo []);


#endif // PRODUCTOS_H_INCLUDED
