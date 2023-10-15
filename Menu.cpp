#include <iostream>
#include <cstring>
using namespace std;

#include "Menu.h"

void Menu::mostrar()
{
    cout << "----- MENU PRINCIPAL -----" << endl << endl;
    cout << "Opcion 1:" << endl;
    cout << "Opcion 2:" << endl;
    cout << "Opcion 3:" << endl;
    cout << "Opcion 4:" << endl;
    cout << "Opcion 5:" << endl << endl ;

}
void Menu::ejecutar()
{
    while (true)
    {
        mostrar();
        cout << "Seleccione una opcion (0 para salir): ";
        int opcion;
        cin >> opcion;
        if (opcion == 0)
        {
            break;
        }
        ejecutarOpcion(opcion);
    }

}
void Menu::ejecutarOpcion(int numero)
{
    switch (numero)
    {
    case 1:
        cout << "Se ejecuto la opcion 1." << endl;
        cout << endl ;
        system("pause") ;
        cout << endl ;
        break;
    case 2:
        cout << "Se ejecuto la opcion 2." << endl;
        cout << endl ;
        system("pause") ;
        cout << endl ;
        break;
    case 3:
        cout << "Se ejecuto la opcion 3." << endl;
        cout << endl ;
        system("pause") ;
        cout << endl ;
        break;
    case 4:
        ejecutarSubMenu(numero) ;
        cout << endl ;
        break;
    case 5:
        ejecutarSubMenu(numero) ;
        cout << endl ;
        break;
    default:
        cout << "Opcion no valida." << endl;
    }
}


void Menu::mostrarSubMenu(int numero)
{
        cout << endl ;
    switch (numero)
    {
    case 4:
        cout << "----- SUBMENU OPCION 4 -----" << endl << endl;

        cout << "Opcion 1:" << endl;
        cout << "Opcion 2:" << endl;
        cout << "Opcion 3:" << endl << endl ;
        break;

    case 5:
        cout << "----- SUBMENU OPCION 5 -----" << endl << endl;

        cout << "Opcion 1:" << endl;
        cout << "Opcion 2:" << endl;
        cout << "Opcion 3:" << endl << endl;
        break;
    default:
        cout << "Opcion no valida." << endl;
        system("pause") ;
        break;
    }
}

void Menu::ejecutarSubMenu(int numero)
{
    while (true)
    {
        mostrarSubMenu(numero);
        cout << "Seleccione una opcion (0 para volver): ";
        int opcion;
        cin >> opcion;
        if (opcion == 0)
        {
            break;
        }
        ejecutarOpcionSubMenu(opcion);
    }

}

void Menu::ejecutarOpcionSubMenu(int numero)
{
    switch (numero)
    {
    case 1:
        cout << "Se ejecuto la opcion 1." << endl;
        cout << endl ;
        system("pause") ;
        break;
    case 2:
        cout << "Se ejecuto la opcion 2." << endl;
        cout << endl ;
        system("pause") ;
        break;
    case 3:
        cout << "Se ejecuto la opcion 3" << endl;
        cout << endl ;
        system("pause") ;
        break;

    default:
        cout << "Opcion no valida." << endl;
    }
}
