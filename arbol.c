#include "arbol.h"


nodoArbol * inicArbol()
{
    return NULL;
}

nodoArbol * crearNodoArbol(stProducto dato)
{
    nodoArbol * aux = (nodoArbol*) malloc(sizeof(nodoArbol));
    aux->dato=dato;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

nodoArbol * cargarElArbol (nodoArbol * arbol)
{
    char rutaDelArchivoProdAlta []= {"ProductosAlta.dat"};
    nodoArbol * nuevoNodoArbol;
    char control ='s';
    stProducto productoExtra;
    while (control=='s')
    {
        productoExtra=cargarUnProducto();
        nuevoNodoArbol = crearNodoArbol(productoExtra);
        agregarDeArrayAArchivoFinal(rutaDelArchivoProdAlta,productoExtra);
        arbol=insertarPorId(arbol,nuevoNodoArbol->dato);

        printf("\n\t\t\t\t\tDesea agragar otro producto? (S/N): ");
        fflush(stdin);
        scanf("%c", &control);
        system("cls");
    }
    return arbol;
}

nodoArbol * insertarPorId(nodoArbol * arbol, stProducto dato)
{
    if(arbol==NULL)
        arbol = crearNodoArbol(dato);
    else
    {
        if( dato.idProducto > (arbol->dato.idProducto))
            arbol->der = insertarPorId(arbol->der, dato);
        else
            arbol->izq = insertarPorId(arbol->izq, dato);
    }
    return arbol;
}

void preorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        mostrarUnProducto(arbol->dato);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->izq);
        mostrarUnProducto(arbol->dato);
        inorder(arbol->der);
    }
}

void postorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        mostrarUnProducto(arbol->dato);
    }
}

nodoArbol * buscar(nodoArbol * arbol, stProducto dato)
{
    nodoArbol * rta = inicArbol();
    if(arbol!=NULL)
    {
        if(dato.idProducto == arbol->dato.idProducto)
            rta = arbol;
        else if(dato.idProducto > arbol->dato.idProducto)
            rta = buscar(arbol->der, dato);
        else
            rta = buscar(arbol->izq, dato);
    }
    return rta;
}

nodoArbol * buscarPorID(nodoArbol * arbol, int id)
{
    nodoArbol * rta = inicArbol();

    if(arbol!=NULL)
    {
        if(id == arbol->dato.idProducto)
        {
            rta = arbol;
        }
        else if(id > arbol->dato.idProducto)
        {
            rta = buscarPorID(arbol->der, id);

        }
        else
        {
            rta = buscarPorID(arbol->izq, id);
        }
    }
    return rta;
}

int buscarSiExisteProductoPorID(nodoArbol * arbol, int id)
{
    int rta = 0;

    if(arbol!=NULL)
    {
        if(id == arbol->dato.idProducto)
        {
            rta = arbol->dato.idProducto;
        }
        else if(id > arbol->dato.idProducto)
        {
            rta = buscarSiExisteProductoPorID(arbol->der, id);
        }
        else
        {
            rta = buscarSiExisteProductoPorID(arbol->izq, id);
        }
    }
    return rta;
}

void noExisteElProducto (int id)
{
    system("cls");
    saltoDeLinea(3);
    printf("\t\t No existe el producto con ID: %d. Porfavor, ", id);
    system("pause");
}

void anularUnProducto (nodoArbol ** arbolProdAnulados, nodoArbol ** arbolProd)
{
    int flag=0,idProducto;
    system("cls");

    inorder(*arbolProd);

    printf("Escriba el id producto a borrar: ");
    scanf("%d",&idProducto);
    flag=buscarSiExisteProductoPorID(*arbolProd,idProducto);

    if (flag==0)
    {
        noExisteElProducto(idProducto);
    }
    else
    {
        nodoArbol * nodoABorrar=inicArbol();
        nodoABorrar=buscarPorID(*arbolProd, idProducto);
        nodoABorrar->dato.productoAnulado=1;
        *arbolProdAnulados = insertarPorId(*arbolProdAnulados, nodoABorrar->dato);
        modificarProductoArchi("ProductosAlta.dat",nodoABorrar->dato);
        *arbolProd=borrarNodoArbol(*arbolProd, nodoABorrar->dato);
    }
}

void agregarProductoAnulado (nodoArbol ** arbolProdAnulados, nodoArbol ** arbolProd)
{
    nodoArbol * nodoAAgregar = inicArbol();

    int flag=0,idProducto;
    system("cls");

    inorder(*arbolProdAnulados);

    printf("Escriba el id producto  que desea volver a agregar: ");
    scanf("%d",&idProducto);
    flag=buscarSiExisteProductoPorID(*arbolProdAnulados,idProducto);

    if (flag==0)
    {
        noExisteElProducto(idProducto);
    }
    else
    {
        nodoAAgregar = buscarPorID(*arbolProdAnulados, idProducto);
        nodoAAgregar->dato.productoAnulado=0;
        *arbolProd = insertarPorId(*arbolProd, nodoAAgregar->dato);
        modificarProductoArchi("ProductosAlta.dat",nodoAAgregar->dato);
        *arbolProdAnulados=borrarNodoArbol(*arbolProdAnulados, nodoAAgregar->dato);

    }
}


nodoArbol * deArrayToArbol(stProducto dato[], int principio, int fin)
{
    int mitad=0;
    nodoArbol * raiz=inicArbol();

    if (principio > fin)
    {
        raiz=NULL;
    }
    else
    {
        mitad = (principio + fin)/2;

        raiz = insertarPorId(raiz,dato[mitad]);

        raiz->izq =  deArrayToArbol(dato, principio, mitad-1);

        raiz->der = deArrayToArbol(dato, mitad+1, fin);
    }

    return raiz;
}

nodoArbol * nodoMasDerecho (nodoArbol* arbol)
{
    nodoArbol * resp;

    if (arbol)
    {
        if (arbol->der)
        {
            resp=nodoMasDerecho(arbol->der);
        }
        else
        {
            resp=arbol;
        }
    }
    return resp;
}

nodoArbol * nodoMasIzquierdo (nodoArbol* arbol)
{
    nodoArbol * resp;

    if (arbol)
    {
        if (arbol->izq)
        {
            resp=nodoMasIzquierdo(arbol->izq);
        }
        else
        {
            resp=arbol;
        }
    }
    return resp;
}

nodoArbol * borrarNodoArbol (nodoArbol * osvaldo, stProducto dato)
{
    if (osvaldo)
    {
        if (osvaldo->dato.idProducto==dato.idProducto)
        {
            if (osvaldo->izq)
            {
                nodoArbol * masDer = nodoMasDerecho(osvaldo->izq);
                osvaldo->dato = masDer->dato;
                osvaldo->izq = borrarNodoArbol(osvaldo->izq, masDer->dato);
            }
            else if (osvaldo->der)
            {
                nodoArbol * masIzq = nodoMasIzquierdo(osvaldo->der);
                osvaldo->dato = masIzq->dato;
                osvaldo->der = borrarNodoArbol(osvaldo->der, masIzq->dato);
            }
            else
            {
                free(osvaldo);
                osvaldo=NULL;
            }
        }
        else if (dato.idProducto>osvaldo->dato.idProducto)
        {
            osvaldo->der=borrarNodoArbol(osvaldo->der, dato);
        }
        else
        {
            osvaldo->izq=borrarNodoArbol(osvaldo->izq, dato);
        }
    }

    return osvaldo;
}

stProducto retornaProdNodo (nodoArbol * arbol)
{
    stProducto aux=arbol->dato;
    return aux;
}


void modificarProductoArchi(char archi[], stProducto dato)
{
    FILE * productos = fopen(archi,"r+b");
    stProducto aux;
    int flag=0;
    if(productos)
    {
        while (!feof(productos)&& flag==0)
        {
            fread(&aux,sizeof(stProducto),1,productos);

            if (aux.idProducto==dato.idProducto)
            {
                flag=7;
                fseek(productos, -1*sizeof(stProducto),SEEK_CUR);
                fwrite(&dato,sizeof(stProducto),1,productos);
            }
        }
        fclose(productos);
    }
}
