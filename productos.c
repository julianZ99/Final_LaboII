#include "productos.h"

stProducto cargarUnProducto ()
{
    stProducto a;
    printf("\n\t\t\t\t\tIngrese nombre del producto: ");
    fflush(stdin);
    gets(a.nombreProducto);
    printf("\n\t\t\t\t\tIngrese la descripcion del producto: ");
    fflush(stdin);
    gets(a.descripcionProducto);
    printf("\n\t\t\t\t\tIngrese el precio del producto: ");
    scanf("%f", &a.valor);
    a.idProducto=buscaIdUltimoProducto("ProductosAlta.dat")+1;
    a.cantidad=100;
    a.productoAnulado=0;
    return a;
}

int buscaIdUltimoProducto(char rutaDelArchivoPedido[])
{
    int rta=-1;
    stProducto aux;
    FILE * archi = fopen(rutaDelArchivoPedido, "rb");
    if (archi)
    {
        while(fread(&aux, sizeof(stProducto), 1, archi)>0)
        {
            if(aux.idProducto>rta)
            {
                rta=aux.idProducto;
            }
        }
        fclose(archi);
    }
    return rta;
}


void mostrarUnProducto(stProducto a)
{
    puts("==================================================");
    printf("= ID del producto: %d\n",a.idProducto);
    printf("= Nombre del producto: %s\n",a.nombreProducto);
    printf("= Descripcion: %s\n",a.descripcionProducto);
    printf("= El precio del producto: %0.02f\n", a.valor);
    puts("==================================================");
}

void mostrarUnProductoAdmin(stProducto a)
{
    puts("==================================================");
    printf("= ID del producto: %d\n",a.idProducto);
    printf("= Nombre del producto: %s\n",a.nombreProducto);
    printf("= Descripcion: %s\n",a.descripcionProducto);
    printf("= El precio del producto: %0.02f\n", a.valor);
    estadoDelProducto(a.productoAnulado);
    puts("==================================================");
}


void estadoDelProducto(int numero)
{
    if (numero==1)
    {
        printf("= El producto se encuentra eliminado: %d\n", numero);
    }
    else if (numero==0)
    {
        printf("= El producto no se encuentra eliminado: %d\n", numero);
    }
    else
    {
        printf("= ERROR: %d\n", numero);
    }
}

int contarProductos(char archivoProductos[])
{
    int cantidad=0;

    FILE*productos;

    productos=fopen(archivoProductos,"rb");

    if(productos!=NULL)
    {
        fseek(productos,0,SEEK_END);

        cantidad= ftell(productos)/sizeof(stProducto);
        fclose(productos);
    }
    return cantidad;
}

void deArchivoToArrayProductos (stProducto prods[], stProducto anuls[], char archivo [], int * validosProd, int * validosAnulados)
{
    FILE * produtos=fopen(archivo,"rb");
    stProducto aux;
    int i=0, x=0;

    if (produtos)
    {
        while(fread(&aux,sizeof(stProducto),1,produtos)>0)
        {
            if(aux.productoAnulado==1)
            {
                anuls[x]=aux;
                x++;
            }
            else
            {
                prods[i]=aux;
                i++;

            }
        }
    }
    *validosProd=i;
    *validosAnulados=x;
    fclose(produtos);
}
void agregarDeArrayAArchivoFinal(char archivoAPasar[], stProducto prods)
{
    FILE * archi=fopen(archivoAPasar,"ab");
    if (archi!=NULL)
    {
        fwrite(&prods,sizeof(stProducto),1,archi);
    }
    fclose(archi);
}
void deArrayAArchivo(char archivoAPasar[], stProducto prods[], int validos)
{
    FILE * archi=fopen(archivoAPasar,"wb");

    int i=0;
    if (archi!=NULL)
    {
        while (i<validos)
        {
            fwrite(&prods[i],sizeof(stProducto),1,archi);
            i++;
        }
    }
    fclose(archi);
}

///Lista Prod.

nodoListaProducto * inicListaProducto()
{
    return NULL;
}
nodoListaProducto * crearNodoListaProducto(stProducto p)
{
    nodoListaProducto *aux = (nodoListaProducto *) malloc(sizeof(nodoListaProducto));
    aux ->p = p;
    aux ->siguiente =NULL;
    return aux;
}

nodoListaProducto * agregarAlPrincipioProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente= lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoListaProducto * agregarAlFinalProducto(nodoListaProducto * lista, nodoListaProducto * nuevo)
{
    if(lista== NULL)
    {
        lista=nuevo;
    }
    else
    {
        nodoListaProducto * ultimo = inicListaProducto();
        ultimo=buscarUltimoNodoProducto(lista);
        ultimo->siguiente=nuevo;
    }
    return lista;
}

nodoListaProducto * buscarUltimoNodoProducto(nodoListaProducto * lista)
{
    nodoListaProducto * ultimo=lista;
    if(ultimo!=NULL)
    {
        while(ultimo->siguiente != NULL)
        {
            ultimo=ultimo->siguiente;
        }
    }
    return ultimo;
}

nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo)
{

    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmp(nuevo->p.nombreProducto,lista->p.nombreProducto)<0)
        {
            lista=agregarAlPrincipioProducto(lista,nuevo);
        }
        else
        {
            nodoListaProducto * ante=lista;
            nodoListaProducto * sig=lista->siguiente;
            while(sig!=NULL && strcmp(sig->p.nombreProducto,nuevo->p.nombreProducto)<0)
            {
                ante=sig;
                sig=sig->siguiente;
            }
            ante->siguiente=nuevo;
            nuevo->siguiente=sig;
        }
    }
    return lista;
}

void mostrarListaRecursivaProductosAdmin(nodoListaProducto * lista)
{
    if(lista!=NULL)
    {
        mostrarUnProductoAdmin(lista->p);
        mostrarListaRecursivaProductosAdmin(lista->siguiente);
    }
}

void mostrarListaRecursivaProductosUsuario(nodoListaProducto * lista)
{
    if(lista!=NULL)
    {
        mostrarUnProducto(lista->p);
        mostrarListaRecursivaProductosUsuario(lista->siguiente);
    }
}

nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id)
{
    nodoListaProducto * seg=lista;
    nodoListaProducto * ante;
    while((seg!=NULL)&& (lista->p.idProducto!=id))
    {
        ante=seg;
        seg=seg->siguiente;
    }
    if(seg!=NULL)
    {
        ante->siguiente=seg->siguiente;
        free(seg);
    }
    return lista;
}

nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista)
{
    nodoListaProducto * actual=lista;
    mostrarListaRecursivaProductosAdmin(lista);
    system("pause");

    while (lista!=NULL)
    {
        actual=lista;
        mostrarListaRecursivaProductosAdmin(actual);
        system("pause");
        lista=lista->siguiente;
        free(actual);
        printf("hola\n");
    }
    return lista;
}

float calcularTotalPrecioProductos (nodoListaProducto* lista)
{
    float rta=0;
    if (lista)
    {
        rta=(lista->p.valor)+(calcularTotalPrecioProductos(lista->siguiente));
    }
    return rta;
}

int buscaIdUltimoPedido(char rutaDelArchivoPedido[])
{
    int rta=-1;
    stPedido aux;
    FILE * archi = fopen(rutaDelArchivoPedido, "rb");
    if (archi)
    {
        while(fread(&aux, sizeof(stPedido), 1, archi)>0)
        {
            if(aux.idPedido>rta)
            {
                rta=aux.idPedido;
            }
        }
        fclose(archi);
    }
    return rta;
}
