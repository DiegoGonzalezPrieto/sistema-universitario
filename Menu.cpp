#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#include "Menu.h"


Menu::Menu(const vector<string> &opciones) : opciones(opciones){}

int Menu::mostrar()
{
    int opcionElegida;
    while (true) {
    cout << "Menu:" << endl;
    for (size_t i = 0; i < opciones.size(); ++i)
    {
        cout << "Opcion " << i + 1 << ". " << opciones[i] << endl;
    }

    cout << "Seleccione una opcion:(0 para salir/volver) ";
    cin >> opcionElegida;

    if (opcionElegida < 0 || opcionElegida > opciones.size())
    {
        cout << endl << "Opcion no valida.Vuelva a intentarlo" << endl << endl;
    }
    else
        if (opcionElegida == 0)
    {
        return 0 ;
    }
    else return opcionElegida;
    }
}
