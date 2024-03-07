#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>


#include "arbol.h"
#include "productos.h"
#include "menu.h"
#include "clientes.h"
#include "sonidos.h"

int alta (stCelda adl[], stCliente cliente, int validos);


int main()
{
    char rutaDelArchivoClienteAlta []= {"ClientesAlta.dat"};

    int validos=0, dimension=0;

    logo();

    jingleIntro();

    dimension=contarClientes(rutaDelArchivoClienteAlta);

    stCelda * adl = (stCelda*) malloc(dimension*sizeof(stCelda));

    validos=deArchivoAAdl(adl, rutaDelArchivoClienteAlta);

    menuNavegable(&adl,&validos,&dimension);

    return 0;
}

int alta (stCelda adl[], stCliente cliente, int validos) ///Por temas de librerias se debe dejar en el main o rompe
{
    nodoListaProducto * aux = inicListaProducto();

    int pos = buscaPosIdClienteCelda(adl, cliente.idCliente, validos);
    if(pos==-1)
    {
        validos=agregarClienteCelda(adl,cliente, validos);
        pos=validos-1;
    }
    adl[pos].listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDeProductos, aux);
    return validos;
}






















