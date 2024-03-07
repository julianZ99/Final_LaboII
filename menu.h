#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "clientes.h"

#define ESC 27
#define ENTER 13
#define FLECHAARRIBA 72
#define FLECHAABAJO 80
#define ARROBA 64

int menuConfiguracionDeUsuario (stCelda adl[],int posCliente);
int menuConfiguracionDeUsuarioParaAdmin (stCelda adl[],int posCliente);
int menuUsuario(int elecion,stCelda adl[],int validos,int posCliente, nodoArbol * arbolProd, nodoArbol * arbolProdAnulados);
int menuAdmin (int elecion,stCelda **adl,int *validos,int posCliente, nodoArbol * arbolProd, nodoArbol * arbolProdAnulados);
void menuNavegable (stCelda **adl, int * validos, int * dimension);
void borrarTodo (stCelda **adl, int * validos);

int puntosParaElegirPaso1 (int eleccionMenu, stCelda ** adl, int * validos, int *dimension,int * flag);
int sistemanavegableRegistrarse (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableIngresarOVolver (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableConfiguracionUsuario (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableConfiguracionUsuarioParaAdmin (int menu,int menuinicio,int menufin, int lineainicio);

int flechas (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaAlta (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaAltaUnUser (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaPedido (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuUsuario (int menu,int menuinicio,int menufin, int lineainicio,char nombre[]);
int sistemanavegableMenuAdmin (int menu,int menuinicio,int menufin, int lineainicio, char nombre[]);
void gotoxy (int x, int y);
void ejey (int y);
void logo();
void cargando ();
void saltoDeLinea (int lineas);
void mensajeDespedida();
void MensajeUserDadoBaja ();


#endif // MENU_H_INCLUDED
