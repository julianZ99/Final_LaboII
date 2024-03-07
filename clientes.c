#include "clientes.h"

int buscaPosIdClienteCelda (stCelda adl[], int idCliente,int validos)
{
    int rta=-1;
    int i=0;
    while((i<validos) && (rta==-1))
    {
        if (adl[i].cliente.idCliente==idCliente)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}


int buscarIdPorNombreAdl (stCelda adl[], char nombreUsuario [],int validos)
{
    int rta=-1;
    int i=0;
    while((i<validos) && (rta==-1))
    {
        if (strcmp(adl[i].cliente.userName,nombreUsuario)==0)
        {
            rta=adl[i].cliente.idCliente;
        }
        i++;

    }
    return rta;
}

int agregarClienteCelda (stCelda adl[], stCliente cliente, int validos)
{
    adl[validos].cliente=cliente;
    adl[validos].listaDeProductos = inicListaProducto();
    validos++;
    return validos;
}

int agrandarAdl (stCelda ** adl, int validos, int dimension)
{
    (*adl)=realloc((*adl),(validos+10)*sizeof(stCelda));
    return dimension+10;
}

void mostrarAdlAdmin(stCelda adl[], int validos)
{
    int i=0;


        while(i<validos)
        {
            mostrarCliente(adl[i].cliente);
            mostrarClienteAdmin(adl[i].cliente);
            printf("\t\t\t ============================================================== ");
            i++;
        }

}

void mostrarAdlNombreEId(stCelda adl[], int validos)
{
    int i=0;
    while(i<validos)
    {
        mostrarSoloNeI(adl[i].cliente);
        printf("\t\t\t\t\t =============================== ");
        i++;
    }
}

void mostrarAdlUser(stCelda adl[], int validos)
{
    int i=0;
    while(i<validos)
    {
        mostrarCliente(adl[i].cliente);
        i++;
    }
}

void mostrarClienteAdmin(stCliente cliente)
{
    printf("\n\t\t\t\t         Rol: %d \n",cliente.rol);
    printf("\n\t\t\t\t         Activo: %d \n",cliente.activo);
}

void mostrarCliente(stCliente cliente)
{
    printf("\n\t\t\t\t         IdCliente: %d \n",cliente.idCliente);
    printf("\n\t\t\t\t         Nombre: %s \n",cliente.nombre);
    printf("\n\t\t\t\t         Apellido: %s \n",cliente.apellido);
    printf("\n\t\t\t\t         UserName: %s \n",cliente.userName);
    printf("\n\t\t\t\t         Contrase%ca: %s \n",164,cliente.password);
    printf("\n\t\t\t\t         Email: %s \n",cliente.mail);
    printf("\n\t\t\t\t         Genero: %c \n",cliente.genero);
}
void mostrarSoloNeI(stCliente cliente)
{
    printf("\n\t\t\t\t\t         IdCliente: %d \n",cliente.idCliente);
    printf("\n\t\t\t\t\t         UserName: %s \n",cliente.userName);
    printf("\n\t\t\t\t\t         Activo: %d \n",cliente.activo);

}
int contarClientes(char archivoClientes[])
{
    int cantidad=0;
    FILE*clientes;
    clientes=fopen(archivoClientes,"rb");
    if(clientes!=NULL)
    {
        fseek(clientes,0,SEEK_END);

        cantidad= ftell(clientes)/sizeof(stCliente);
        fclose(clientes);
    }
    return cantidad;
}

int deArchivoAAdl (stCelda ADL[], char archivo [])
{
    FILE * clientes=fopen(archivo,"rb");
    stCliente aux;
    int i=0;

    if (clientes)
    {
        while(fread(&aux,sizeof(stCliente),1,clientes)>0)
        {
            i=agregarClienteCelda(ADL,aux,i);
        }
        fclose(clientes);
    }
    return i;
}

void deAdlAlArchivo(char archivoAPasar[], stCelda adl[], int validos)
{
    FILE * archivoDeClientes=fopen(archivoAPasar,"wb");

    int i=0;
    if (archivoDeClientes!=NULL)
    {
        while (i<validos)
        {
            fwrite(&adl[i].cliente,sizeof(stCliente),1,archivoDeClientes);
            i++;
        }
    }
    fclose(archivoDeClientes);
}

void deAdlAlArchivoAlFinal(char archivoAPasar[], stCliente dato)
{
    FILE * archivoDeClientes=fopen(archivoAPasar,"ab");

    if (archivoDeClientes!=NULL)
    {
        fwrite(&dato,sizeof(stCliente),1,archivoDeClientes);
    }
    fclose(archivoDeClientes);
}

void registrarse(stCelda ** adl, int * validos, int *dimension)
{

    int flag=0,i=0, flag2=0;
    char nombreUsuario [20];
    char mailcopy [100];

    i=(*validos);

    if (*dimension==*validos)
    {
        *dimension=agrandarAdl(adl, *validos, *dimension);
    }

    (*adl)[i].cliente.idCliente=buscaPosUltima((*adl),*validos)+1;

    (*adl)[i].cliente.rol= 0;


    printf("\n\t\t\tIngrese su nombre: ");
    fflush(stdin);
    gets((*adl)[i].cliente.nombre);

    printf("\n\t\t\tIngrese su apellido: ");
    fflush(stdin);
    gets((*adl)[i].cliente.apellido);

    do
    {
        printf("\n\t\t\tIngrese su nombre se usuario: ");
        fflush(stdin);
        scanf("%s", nombreUsuario);
        flag=compararUsuarios((*adl),nombreUsuario,*validos);
        usuarioRepetido(flag);

    }
    while (flag!=0);

    strcpy((*adl)[i].cliente.userName, nombreUsuario);

    printf("\n\t\t\tIngrese su genero (Solo inicial): ");
    fflush(stdin);
    scanf("%c",&((*adl))[i].cliente.genero);

    do
    {
        printf("\n\t\t\tIngrese su email: ");
        fflush(stdin);
        gets(mailcopy);
        flag2=verificacionEmail(mailcopy);
        mailInvalido(flag2);
    }
    while(flag2==0);

    strcpy((*adl)[i].cliente.mail, mailcopy);

    printf("\n\t\t\tIngrese su contrase%ca (No mas de 10 caracteres): ", 164);
    fflush(stdin);
    asteriscos((*adl)[i].cliente.password);

    (*adl)[i].cliente.activo = 1;

    agregarClienteCelda((*adl),(*adl)[i].cliente,*validos);

    i++;
    *validos = i;



    system("cls");
    saltoDeLinea(3);
    printf("\t\t\t\t====== Usted se ha registrado exitosamente ======");
    saltoDeLinea(2);
    printf("\t\t\t\tPor favor. ");
    system("pause");

}

int iniciarSesion(stCelda adl[],int validos)
{
    int idUser=0,flag1=0,flag2=0, intentoscontra=0,intentosnombre=0;
    char nombreUsuario []="NULL", password []="NULL";
    printf("\n\t\t\t\t =====Por favor ingrese su usuario y contrase%ca=====",164);

    do
    {
        printf("\n\n\t\t\t Usuario: ");
        fflush(stdin);
        gets(nombreUsuario);

        flag1=compararUsuarios(adl,nombreUsuario,validos);

        if(flag1==1)
        {
            idUser=buscarIdPorNombreAdl(adl,nombreUsuario,validos);
        }
        else
        {
            system("cls");
            printf("\n\t\t\t =====Usuario inexistente. Intentelo nuevamente.=====");
            intentosnombre++;
        }

    }
    while (flag1!=1 && intentosnombre!=3);

    if (intentosnombre==3)
    {
        system("cls");
        printf("\n\t\t Has sobrepasado el limite de intentos para el nombre. ");
        system("pause");
        idUser=0;
    }

    if (idUser!=0)
    {
        do
        {
            printf("\n\n\t\t\t Contrase%ca: ",164);
            fflush(stdin);
            asteriscos(password);
            flag2=compararPassword (adl,password,validos);
            if (flag2==0)
            {
                system("cls");
                printf("\n\t\t\t =====Contrase%ca incorrecta, por favor vuelva a intentarlo=====",164);
            }

            if(adl[buscaPosIdClienteCelda(adl,idUser,validos)].cliente.activo==0)
            {
                printf("\n\n\t\t=====Este usuario ya no se encuentra activo.Si desea activarlo comuniquese al 0800-428-7627===== \n\n\t\t\t\t\tPor favor, ");
                system("pause");
                idUser=0;
            }

            intentoscontra++;

            if (intentoscontra==3)
            {
                system("cls");
                printf("\n\t\t Has sobrepasado el limite de intentos para la contraseña. ");
                system("pause");
                idUser=0;
            }

        }
        while (flag2==0 && intentoscontra!=3 && idUser!=0);
    }
    return idUser;
}

void usuarioRepetido (int flag)
{
    if (flag==1)
    {
        system("cls");
        printf("\n\t\t\t=====Usuario ya registrado, por favor vuelva a intentarlo=====");
    }
}

int buscaPosUltima (stCelda adl[],int validos)
{
    int rta=-1;
    int i=0;
    while(i<validos-1)
    {
        i++;
    }

    rta=adl[i].cliente.idCliente;

    return rta;
}

int verificacionEmail (char email[])
{

    int flag=0;

    if ((strchr (email, 64)) != 0)
    {
        flag=1;
    }
    return flag;
}

void mailInvalido (int flag)
{
    if (flag==0)
    {
        system("cls");
        printf("\n\t\t\t=====Email invalido, por favor vuelva a intentarlo=====");
    }
}

int compararUsuarios (stCelda adl[],char usuario[], int validos)
{
    int flag=0, i=0;

    while (i<validos && flag==0)
    {
        if (strcmp (adl[i].cliente.userName, usuario) == 0)
        {
            flag=1;
        }
        i++;
    }

    return flag;
}

int compararPassword (stCelda adl[],char password[], int validos)
{
    int flag=0, i=0;
    while (i<validos && flag==0)
    {
        if (strcmp (adl[i].cliente.password, password) == 0)
        {
            flag=1;
        }
        i++;
    }
    return flag;
}

void asteriscos (char contra[])
{
    char caracter;
    int x=0;
    do
    {
        caracter=getch();
        if(caracter==13)
        {
            contra [x]='\0';
        }
        else if(caracter==8)
        {
            if(x>0)
            {
                x--;
                printf("\b \b");
            }
        }
        else if (x<10)
        {
            printf("*");
            contra[x]=caracter;
            x++;
        }
    }
    while(caracter!=13);
}

int darDeBajaUnUser (stCelda adl[],int posCliente)
{
    int flag2=0;
    int flagAPasar=0;

    flag2=sistemanavegableMenuBajaAltaUnUser(1,1,2,3);

    if(flag2==1)
    {
        if (adl[posCliente].cliente.activo==1)
        {
            adl[posCliente].cliente.activo=0;

            flagAPasar=1;
        }
        else
        {
            system("cls");
            printf("\n\t\t\t Este usuario ya esta dado de baja. ");
            system("pause");
        }
    }

    return flagAPasar;
}

int darDeBajaODarDeAlta (stCelda adl[],int pos)
{

    int flag2=0;
    int flagAPasar=0;

    flag2=sistemanavegableMenuBajaAlta(1,1,3,1);

    if(flag2==1)
    {
        if (adl[pos].cliente.activo==1)
        {
            adl[pos].cliente.activo=0;
        }
        else
        {
            system("cls");
            printf("\t\t\t\t==================================================\n");
            printf("\t\t\t\t=      Este usuario ya esta dado de baja         =\n");
            printf("\t\t\t\t==================================================");
            saltoDeLinea(4);
            printf("\t\t\t\tPor favor, ");
            system("pause");
        }
    }

    if(flag2==2)
    {
        if (adl[pos].cliente.activo==0)
        {
            adl[pos].cliente.activo=1;
        }
        else
        {
            system("cls");
            printf("\t\t\t\t==================================================\n");
            printf("\t\t\t\t=      Este usuario ya esta dado de alta         =\n");
            printf("\t\t\t\t==================================================");
            saltoDeLinea(4);
            printf("\t\t\t\tPor favor, ");
            system("pause");

        }

    }
    if(flag2==3)
    {
        flagAPasar=0;
    }


    if (pos==-1)
    {
        noExiste(adl[pos].cliente.idCliente);
    }
    return flagAPasar;
}

void noExiste (int id)
{
    system("cls");
    printf("\t\t\t\t==================================================\n");
    printf("\t\t\t\t=       No existe el ID de usuario: %d          =\n",id);
    printf("\t\t\t\t==================================================");
    saltoDeLinea(4);
    printf("\t\t\t\tPor favor, ");
    system("pause");
}

void modificarChabonArchi (char archi[],stCliente dato)
{
    FILE * clientes = fopen(archi,"r+b");
    stCliente aux;
    int flag=0;
    if(clientes)
    {
        while (!feof(clientes)&& flag==0)
        {
            fread(&aux,sizeof(stCliente),1,clientes);

            if (aux.idCliente==dato.idCliente)
            {
                flag=7;
                fseek(clientes, -1*sizeof(stCliente),SEEK_CUR);
                fwrite(&dato,sizeof(stCliente),1,clientes);
            }
        }
        fclose(clientes);
    }
}


stPedido hacerPedidoMagicJohnson(stCelda adl[], nodoArbol * arbolProductos, int pos)
{
    stPedido pedidoCliente;
    nodoArbol * aux=inicArbol();
    stProducto prod;
    int idProducto=0,verificacion=0;
    int ultimo=buscaIdUltimoPedido("CabeceraPedidos.dat");

    pedidoCliente.idCliente=adl[pos].cliente.idCliente;

    pedidoCliente.idPedido=ultimo+1;



    do
    {
        system("cls");
        inorder(arbolProductos);
        printf("\nQue producto desea agregar?: ");
        scanf("%d", &idProducto);

        aux=buscarPorID(arbolProductos, idProducto);

        if (aux==NULL)
        {
            printf("Que haces pedorro elegi un producto de verdad");
            verificacion=-1;
            system("pause");
        }
        else
        {
            verificacion=0;
        }
    }
    while(verificacion==-1);

    pedidoCliente.idProducto=idProducto;


    prod=retornaProdNodo(aux);
    adl[pos].listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDeProductos, crearNodoListaProducto(prod));
    return pedidoCliente;
}

void deCabeceraAlArchivo(char archivoAPasar[], stPedido dato)
{
    FILE * archiCabecera=fopen(archivoAPasar,"ab");

    if (archiCabecera!=NULL)
    {

        fwrite(&dato,sizeof(stPedido),1,archiCabecera);
    }
    fclose(archiCabecera);
}

void deArchivoACabecera (stCelda adl[], char archivo [], int validos, int pos, nodoArbol * arbolProductos, nodoArbol * arbolEliminados)
{
    FILE * archiCabecera=fopen(archivo,"rb");
    stPedido aux;
    nodoArbol * prodAux=inicArbol();

    if (archiCabecera)
    {
        while(fread(&aux,sizeof(stPedido),1,archiCabecera)>0)
        {

            if (aux.idCliente==adl[pos].cliente.idCliente)
            {
                prodAux=buscarPorID(arbolProductos, aux.idProducto);
                if (prodAux==NULL)
                {
                    prodAux=buscarPorID(arbolEliminados, aux.idProducto);
                }
                adl[pos].listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDeProductos, crearNodoListaProducto(prodAux->dato));
            }
        }
        fclose(archiCabecera);
    }
}

void mostrarPedidosUserPorID(stCelda adl[],int validos, nodoArbol * arbolProd, nodoArbol * arbolProdAnulados)
{
    int idUserExterno=0,posUnUser=0;

    printf("\t\t\t\t\t\n Ingrese el ID del usuario del cual desea ver sus pedidos: ");
    scanf("%d",&idUserExterno);
    system("cls");

    posUnUser=buscaPosIdClienteCelda(adl,idUserExterno,validos);

    if(posUnUser!=-1 && adl[posUnUser].cliente.idCliente!=100)
    {
        deArchivoACabecera(adl,"CabeceraPedidos.dat",validos,posUnUser,arbolProd,arbolProdAnulados);

        if(adl[posUnUser].listaDeProductos==NULL)
        {
            saltoDeLinea(5);
            printf("\t\t\tNo hay ningun pedido, ");
            system("pause");
        }
        else
        {
            mostrarListaRecursivaProductosAdmin(adl[posUnUser].listaDeProductos);
            system("pause");

        }
    }
    else if (adl[posUnUser].cliente.idCliente==100)
    {
        mostrarListaRecursivaProductosAdmin(adl[posUnUser].listaDeProductos);
        system("pause");
    }
    else
    {
        noExiste(idUserExterno);
    }
}
