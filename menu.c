#include "menu.h"
int menuConfiguracionDeUsuario (stCelda adl[],int posCliente)
{
    int eleccion=0, flagVolver=0;
    char nuevo[30];
    system("cls");
    eleccion=sistemanavegableConfiguracionUsuario(1,1,7,1);

    switch (eleccion)
    {
    case 1:
        system("cls");
        printf("\n\t\t\tIntroduzca su nuevo nombre:  ");
        fflush(stdin);
        gets(nuevo);
        strcpy(adl[posCliente].cliente.nombre,nuevo);

        break;
    case 2:
        system("cls");
        printf("\n\t\t\tIntroduzca su nuevo apellido:  ");
        fflush(stdin);
        gets(nuevo);
        strcpy(adl[posCliente].cliente.apellido,nuevo);

        break;
    case 3:
        system("cls");
        int flag=0;
        do
        {
            printf("\n\t\t\tIntroduzca su nuevo email:  ");
            fflush(stdin);
            gets(nuevo);
            flag=verificacionEmail(nuevo);
            mailInvalido(flag);
        }
        while(flag==0);
        strcpy(adl[posCliente].cliente.mail, nuevo);

        break;
    case 4:
        system("cls");
        printf("\n\t\t\tIntroduzca su nuevo password:  ");
        fflush(stdin);
        asteriscos(nuevo);
        strcpy(adl[posCliente].cliente.password, nuevo);

        break;
    case 5:
        system("cls");
        flagVolver=darDeBajaUnUser(adl,posCliente);
        if (flagVolver==1)
        {
            MensajeUserDadoBaja();
        }
        break;
    case 6:
        system("cls");
        printf("\t\t\t\t\t =============================== ");
        mostrarCliente(adl[posCliente].cliente);
        printf("\t\t\t\t\t =============================== ");
        saltoDeLinea(4);
        printf("\t\t\t\tPor favor, ");
        system("pause");
        break;
    case 7:
        flagVolver=0;
        break;
    default:
        system("cls");
        printf("\t\t\t*===============================:C#*#ERROR#*#:D===============================\n*");
        break;
    }

    return flagVolver;
}

int menuConfiguracionDeUsuarioParaAdmin (stCelda adl[],int posCliente)
{
    int eleccion=0, flagVolver=0;
    char nuevo[30];
    system("cls");
    eleccion=sistemanavegableConfiguracionUsuarioParaAdmin(1,1,7,1);

    switch (eleccion)
    {
    case 1:
        system("cls");
        printf("\n\t\t\tIntroduzca su nuevo nombre:  ");
        fflush(stdin);
        gets(nuevo);
        strcpy(adl[posCliente].cliente.nombre,nuevo);

        break;
    case 2:
        system("cls");
        printf("\n\t\t\tIntroduzca su nuevo apellido:  ");
        fflush(stdin);
        gets(nuevo);
        strcpy(adl[posCliente].cliente.apellido,nuevo);

        break;
    case 3:
        system("cls");
        int flag=0;
        do
        {
            printf("\n\t\t\tIntroduzca su nuevo email:  ");
            fflush(stdin);
            gets(nuevo);
            flag=verificacionEmail(nuevo);
            mailInvalido(flag);
        }
        while(flag==0);
        strcpy(adl[posCliente].cliente.mail, nuevo);

        break;
    case 4:
        system("cls");
        printf("\n\t\t\tIntroduzca su nuevo password:  ");
        fflush(stdin);
        asteriscos(nuevo);
        strcpy(adl[posCliente].cliente.password, nuevo);

        break;
    case 5:
        system("cls");
        flagVolver=darDeBajaODarDeAlta(adl,posCliente);
        if (flagVolver==1)
        {
            mensajeDespedida();
        }
        break;
    case 6:
        system("cls");
        printf("\t\t\t\t\t =============================== ");
        mostrarCliente(adl[posCliente].cliente);
        printf("\t\t\t\t\t =============================== ");
        saltoDeLinea(4);
        printf("\t\t\t\tPor favor, ");
        system("pause");
        break;
    case 7:
        flagVolver=0;
        break;
    default:
        system("cls");
        printf("\t\t\t*===============================:C#*#ERROR#*#:D===============================\n*");
        break;
    }
    return flagVolver;
}
int menuUsuario (int eleccionMenu,stCelda adl[],int validos,int posCliente, nodoArbol * arbolProd, nodoArbol * arbolProdAnulados)
{

    int flag2=0;
    stPedido dato;
    switch(eleccionMenu)
    {
    case 1:
        system("cls");

        dato=hacerPedidoMagicJohnson(adl,arbolProd,posCliente);
        deCabeceraAlArchivo("CabeceraPedidos.dat",dato);
        break;
    case 2:
        system("cls");
        adl[posCliente].costoTotalDelPedido=calcularTotalPrecioProductos(adl[posCliente].listaDeProductos);
        saltoDeLinea(4);
        printf("\t\t\t\t==================================================\n");
        printf("\t\t\t\t=           Usted lleva gastado: %.2f          =\n", adl[posCliente].costoTotalDelPedido);
        printf("\t\t\t\t==================================================");
        saltoDeLinea(4);
        printf("\t\t\t\tPor favor, ");
        system("pause");

        break;
    case 3:
        system("cls");

        if(adl[posCliente].listaDeProductos==NULL)
        {
            saltoDeLinea(4);
            printf("\t\t\t\t==================================================\n");
            printf("\t\t\t\t=              No hay ningun pedido              =\n");
            printf("\t\t\t\t==================================================");
            saltoDeLinea(4);
            printf("\t\t\t\tPor favor, ");
        }
        else
        {
            mostrarListaRecursivaProductosUsuario(adl[posCliente].listaDeProductos);
        }


        system("pause");
        break;
    case 4:
        system("cls");

        flag2=menuConfiguracionDeUsuario(adl,posCliente);
        if (flag2!=0)
        {
            modificarChabonArchi("ClientesAlta.dat",adl[posCliente].cliente);
        }

        break;
    case 5:
        flag2=1;
        break;
    default:
        printf("\t\t\t*==========================:C#*#ERROR#*#:D==========================\n*");
        break;
    }

    return flag2;
}

int menuAdmin (int elecion,stCelda **adl,int *validos,int posCliente, nodoArbol * arbolProd, nodoArbol * arbolProdAnulados)
{

    int flag2=0;
    int idUserExterno=0;
    int posUnUser=0;
    stPedido dato;

    switch(elecion)
    {

    case 1:
        system("cls");

        arbolProd=cargarElArbol(arbolProd);

        break;
    case 2:
        system("cls");
        printf("\t\t\t ============================================================== ");
        if(*validos!=1)
        {
            mostrarAdlAdmin((*adl),*validos);
        }
        else
        {
            system("cls");
            printf("\t\t\t\t==================================================\n");
            printf("\t\t\t\t=            No hay usuarios cargados            =\n");
            printf("\t\t\t\t==================================================");

        }

        saltoDeLinea(4);
        printf("\t\t\t\tPor favor, ");
        system("pause");

        break;
    case 3:
        system("cls");

        saltoDeLinea(4);
        printf("\t\t\t\t\t  [Productos en sistema]");
        saltoDeLinea(3);
        inorder(arbolProd);
        saltoDeLinea(4);
        printf("\t\t\t\t\t [Productos fuera de sistema]");
        saltoDeLinea(3);
        inorder(arbolProdAnulados);

        saltoDeLinea(4);
        printf("\t\t\t\tPor favor, ");
        system("pause");
        break;
    case 4:
        system("cls");
        dato=hacerPedidoMagicJohnson((*adl),arbolProd,posCliente);
        deCabeceraAlArchivo("CabeceraPedidos.dat",dato);
        break;
    case 5:
        system("cls");

        mostrarAdlAdmin((*adl),*validos);

        mostrarPedidosUserPorID((*adl),*validos,arbolProd,arbolProdAnulados);

        break;
    case 6:

        anularUnProducto(&arbolProdAnulados,&arbolProd);

        break;
    case 7:

        agregarProductoAnulado(&arbolProdAnulados,&arbolProd);

        break;
    case 8:
        system("cls");
        printf("\t\t\t\t\t =============================== ");
        mostrarAdlNombreEId((*adl),*validos);
        saltoDeLinea(2);
        printf("\t\t\t\t\t INGRESE EL ID DEL USUARIO: ");
        scanf("%d",&idUserExterno);


        posUnUser=buscaPosIdClienteCelda((*adl),idUserExterno,*validos);
        if(posUnUser!=-1)
        {
            flag2=menuConfiguracionDeUsuarioParaAdmin((*adl),posUnUser);

            if (flag2!=0)
            {
                modificarChabonArchi("ClientesAlta.dat",(*adl)[posUnUser].cliente);
            }
        }
        else
        {
            noExiste(idUserExterno);
        }
        break;
    case 9:
        system("cls");
        if(*validos==1)
        {
            system("cls");
            printf("\t\t\t\t==================================================\n");
            printf("\t\t\t\t=          La memoria ya fue liberada            =\n");
            printf("\t\t\t\t==================================================");
            saltoDeLinea(4);
            printf("\t\t\t\tPor favor, ");
            system("pause");
        }
        else
        {
            deAdlAlArchivo("ClientesAlta.dat",*adl,*validos);
            borrarTodo(adl, validos);
            cargando();
            system("cls");
            printf("\t\t\t\t==================================================\n");
            printf("\t\t\t\t=            Memoria liberada con exito!         =\n");
            printf("\t\t\t\t==================================================");
            saltoDeLinea(4);
            printf("\t\t\t\tPor favor, ");
            system("pause");
        }
        break;
    case 10:
        system("cls");
        *validos=deArchivoAAdl(*adl,"ClientesAlta.dat");
        cargando();
        system("cls");
        printf("\t\t\t\t==================================================\n");
        printf("\t\t\t\t=              Datos cargados con exito!         =\n");
        printf("\t\t\t\t==================================================");
        saltoDeLinea(4);
        printf("\t\t\t\tPor favor, ");
        system("pause");
        break;
    case 11:
        system("cls");
        flag2=1;
        break;
    default:
        printf("\t\t\t*==========================:C#*#ERROR#*#:D==========================\n*");
        break;
    }
    return flag2;
}
void borrarTodo (stCelda **adl, int * validos)
{
    int i=(*validos)-1;
    while (i>1)
    {
        if ((*adl)[i].listaDeProductos!=NULL)
        {
            (*adl)[i].listaDeProductos=borrarTodaLaListaProducto((*adl)[i].listaDeProductos);
        }


        i--;
    }
    free(*adl);
    *validos=i;
}





int puntosParaElegirPaso1 (int eleccionMenu, stCelda ** adl, int * validos, int *dimension, int * flag)
{
    int idUser=0, posCliente=-2;

    printf("\n\n\n\n");
    switch (eleccionMenu)
    {
    case 1:
        system("cls");
        registrarse(adl,validos,dimension);
        deAdlAlArchivoAlFinal("ClientesAlta.dat", (*adl)[(*validos)-1].cliente);
        *flag=1;
        break;
    case 2:
        system("cls");

        idUser=iniciarSesion((*adl),*validos);
        posCliente=buscaPosIdClienteCelda((*adl), idUser,*validos);
        break;
    case 3:
        mensajeDespedida();
        *flag=0;
        break;
    default:
        printf("\t\t\t*==========================:C#*#ERROR#*#:D==========================\n*");
        break;
    }
    return posCliente;
}

int sistemanavegableRegistrarse (int menu,int menuinicio,int menufin, int lineainicio)
{
    printf("\t\t\t===============================\n");
    printf("\t\t\t\t1-Registrarse         =\n");
    printf("\t\t\t\t2-Iniciar sesion      =\n");
    printf("\t\t\t\t3-Salir               =\n");
    printf("\t\t\t===============================\n");
    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableConfiguracionUsuario (int menu,int menuinicio,int menufin, int lineainicio)
{
    printf("\t\t\t====================================================\n");
    printf("\t\t\t\t1-Cambiar nombre                           =\n");
    printf("\t\t\t\t2-Cambiar apellido                         =\n");
    printf("\t\t\t\t3-Cambiar Email                            =\n");
    printf("\t\t\t\t4-Cambiar contrase%ca                       =\n",164);
    printf("\t\t\t\t5-Darse de baja                            =\n");
    printf("\t\t\t\t6-Ver datos                                =\n");
    printf("\t\t\t\t7-Volver                                   =\n");
    printf("\t\t\t====================================================");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableConfiguracionUsuarioParaAdmin (int menu,int menuinicio,int menufin, int lineainicio)
{
    printf("\t\t\t====================================================\n");
    printf("\t\t\t\t1-Cambiar nombre                           =\n");
    printf("\t\t\t\t2-Cambiar apellido                         =\n");
    printf("\t\t\t\t3-Cambiar Email                            =\n");
    printf("\t\t\t\t4-Cambiar contrase%ca                       =\n",164);
    printf("\t\t\t\t5-Dar de baja o dar de alta                =\n");
    printf("\t\t\t\t6-Ver datos                                =\n");
    printf("\t\t\t\t7-Volver                                   =\n");
    printf("\t\t\t====================================================");
    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int flechas (int menu,int menuinicio,int menufin, int lineainicio)
{
    int opcion=0;

    ejey(lineainicio);
    printf("\t\t\t----->");

    do
    {
        Sleep(100);
        opcion=getch();
        if(opcion==224)
        {
            opcion=getch();

            if (opcion==FLECHAARRIBA)
            {
                if (menu==menuinicio)
                {
                    menu=menufin;
                }
                else
                {
                    --menu;
                }
                printf("\r                               ");
                ejey(lineainicio + menu-1);
                printf("\t\t\t----->");
            }
            else if (opcion==FLECHAABAJO)
            {
                if(menu==menufin)
                {
                    menu=menuinicio;
                }
                else
                {
                    ++menu;
                }
                printf("\r                               ");
                ejey(lineainicio + menu-1);
                printf("\t\t\t----->");
            }
        }
    }
    while(opcion !=ENTER);

    return menu;
}

int sistemanavegableMenuBajaAlta (int menu,int menuinicio,int menufin, int lineainicio)
{
    system("cls");
    printf("\t\t\t====================================================\n");
    printf("\t\t\t\t1-Dar de baja                              =\n");
    printf("\t\t\t\t2-Dar de alta                              =\n");
    printf("\t\t\t\t3-Volver                                   =\n");
    printf("\t\t\t====================================================\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableMenuBajaAltaUnUser (int menu,int menuinicio,int menufin, int lineainicio)
{
    system("cls");

    printf("\t\t\t============================ATENCION=============================\n");
    printf("\t\t\t=====================USTED POR DARSE DE BAJA=====================\n");
    printf("\t\t\t============NO PODRA VOLVER A INGRESAR CON ESTE USUARIO==========\n");
    printf("\t\t\t\t1-Darse de baja                                         =\n");
    printf("\t\t\t\t2-Volver                                                =\n");
    printf("\t\t\t=================================================================\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableMenuUsuario (int menu,int menuinicio,int menufin, int lineainicio,char nombre[])
{
    system("cls");

    printf("\t\t\t=========================== Bienvenido %s ===========================\n",nombre);
    printf("\t\t\t\t1-Hacer un Pedido                                              =\n");
    printf("\t\t\t\t2-Todo lo gastado                                              =\n");
    printf("\t\t\t\t3-Mostrar pedidos                                              =\n");
    printf("\t\t\t\t4-Configuracion de usuario                                     =\n");
    printf("\t\t\t\t5-Cerrar sesion                                                =\n");
    printf("\t\t\t========================================================================\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableMenuAdmin (int menu,int menuinicio,int menufin, int lineainicio,char nombre[])
{
    system("cls");

    printf("\t\t\t=========================== Bienvenido ADMIN ===========================\n");
    printf("\t\t\t\t1-Agregar productos                                            =\n");
    printf("\t\t\t\t2-Mostrar usuarios registrados                                 =\n");
    printf("\t\t\t\t3-Mostrar productos cargados en sistema                        =\n");
    printf("\t\t\t\t4-Hacer un pedido                                              =\n");
    printf("\t\t\t\t5-Buscar pedidos de un usuario                                 =\n");
    printf("\t\t\t\t6-Anular un producto                                           =\n");
    printf("\t\t\t\t7-Agregar producto anulado                                     =\n");
    printf("\t\t\t\t8-Modificar/ver datos de un usuario                            =\n");
    printf("\t\t\t\t9-Guardar datos y liberar memoria                              =\n");
    printf("\t\t\t\t10-Cargar datos                                                =\n");
    printf("\t\t\t\t11-Cerrar sesion                                               =\n");
    printf("\t\t\t========================================================================\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}



void menuNavegable (stCelda **adl, int * validos, int * dimension)
{
    int flag=0;
    int eleccionMenu=0;
    int posCliente=-1;
    int fin=0;
    int finAnulados=0;
    stProducto prodAnulados[100];
    stProducto prod[100];

    nodoArbol * arbolProd=inicArbol();

    nodoArbol * arbolProdAnulados=inicArbol();

    deArchivoToArrayProductos(prod, prodAnulados,"ProductosAlta.dat", &fin, &finAnulados);

    arbolProd=deArrayToArbol(prod,0,fin-1);

    arbolProdAnulados=deArrayToArbol(prodAnulados,0,finAnulados-1);

    do
    {
        system("cls");

        eleccionMenu = sistemanavegableRegistrarse(1,1,3,1);

        posCliente= puntosParaElegirPaso1(eleccionMenu,adl,validos,dimension,&flag);

        deArchivoACabecera((*adl),"CabeceraPedidos.dat",*validos,posCliente,arbolProd,arbolProdAnulados);

        system("cls");

        if (posCliente==-1)
        {
            flag=1;
        }
        else if ((*adl)[posCliente].cliente.rol==1 && posCliente!=-2)
        {
            do
            {

                eleccionMenu=sistemanavegableMenuAdmin(1,1,11,1,(*adl)[posCliente].cliente.nombre);

                flag=menuAdmin(eleccionMenu,adl,validos,posCliente,arbolProd,arbolProdAnulados);
            }
            while(flag==0);
        }
        else if (posCliente!=-2)
        {
            do
            {

                eleccionMenu=sistemanavegableMenuUsuario(1,1,5,1,(*adl)[posCliente].cliente.nombre);

                flag=menuUsuario(eleccionMenu,(*adl),*validos,posCliente,arbolProd,arbolProdAnulados);


            }
            while(flag==0);
        }
    }
    while(flag==1);
}

void gotoxy (int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion;
    posicion.X=x;
    posicion.Y=y;
    SetConsoleCursorPosition(hCon,posicion);
}

void ejey (int y)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X=0;
    pos.Y=y;

    SetConsoleCursorPosition(hConsole, pos);
}

void logo()
{

    puts("                            :=========:====     ====:====-       -==== ========-:        :-=====-:  ");
        Sleep(200);
    puts("                            #@@@@@@@@*#@@@*    :@@@@=@@@@@      =@@@@@.@@@@@@@@@@@+   :+*********##+.       ");
            Sleep(200);

    puts("                           #####@@@@=@@@@-    +@@@%*@@@@@+    +@@@@@*=@@@%***%@@@@: =********######*.      ");
            Sleep(200);

    puts("                               :@@@@=@@@@     %@@@+%@@@@@@   +@@@@@@-#@@@+   =@@@% =******=  =######+      ");
            Sleep(200);

    puts("                               +@@@#*@@@#    .@@@@=@@@%@@@= +@@@@@@@.@@@@%###@@@+ .******=    *#####*      ");
            Sleep(200);

    puts("                               %@@@=@@@@=    =@@@@+@@@-%@@%*@@@-@@@#=@@@@@@@@@@@= :******-    *####**   ");
            Sleep(200);

    puts("                              .@@@@-@@@@:    %@@@+%@@@ =@@@@@%.=@@@=#@@@*:::=@@@@::******+   -####**=      ");
            Sleep(200);

    puts("                              +@@@%.@@@@#-:-%@@@%:@@@*  @@@@@. #@@@.@@@@-  .+@@@@: +******+:+##****+       ");
            Sleep(200);

    puts("                        *-  .%@@@+ *@@@@@@@@@@#.=@@@-  *@@%.  @@@%-@@@@@@@@@@@@+   +*************=        ");
            Sleep(200);

    puts("                      .%@@@%@@@@@.  -#@@@@@%*:  #@@@    ..   -@@@+*@@@@@@@@@#+.     :=********+-.         ");
            Sleep(200);

    puts("                       +@@@@@@@*.      ...              PATACON                                ....       ");
            Sleep(200);

    puts("                          -===-                                                                     ");

}

void saltoDeLinea (int lineas)
{
    for (int i=0; i<lineas; i++)
    {
        printf("\n");
    }
}
void MensajeUserDadoBaja ()
{
    system("cls");
    saltoDeLinea(5);
    printf("\t\t\t *==================== USTED SE HA DADO DE BAJA CON EXITO ====================*");
    saltoDeLinea(4);
    printf("\t\t\t\t  Por favor, ");
    system("pause");

}
void mensajeDespedida ()
{
    system("cls");
    saltoDeLinea(5);
    printf("\t\t\t *==================== GRACIAS VUELVA PRONTO ====================*");
    saltoDeLinea(4);
    printf("\t\t\t\t  Por favor, ");
    system("pause");

    saltoDeLinea(12);
}

void cargando ()
{
    system("cls");
    printf("\t\t\t\t==================================================\n");
    printf("\t\t\t\t=                    CARGANDO.                   =\n");
    printf("\t\t\t\t==================================================");
    saltoDeLinea(4);
    Sleep(1000);
    system("cls");
    printf("\t\t\t\t==================================================\n");
    printf("\t\t\t\t=                    CARGANDO..                  =\n");
    printf("\t\t\t\t==================================================");
    saltoDeLinea(4);
    Sleep(1000);
    system("cls");
    printf("\t\t\t\t==================================================\n");
    printf("\t\t\t\t=                    CARGANDO...                 =\n");
    printf("\t\t\t\t==================================================");
    Sleep(1000);
}
