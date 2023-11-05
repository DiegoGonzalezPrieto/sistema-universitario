#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#include "Menu.h"


Menu::Menu(const vector<string> &opciones, string titulo) : _opciones(opciones), _titulo(titulo) {}

int Menu::mostrar()
{
    int opcionElegida, tamanio = _opciones.size();
    while (true)
        {
            cout << _titulo << endl << endl;

            for (int i = 0; i < tamanio; ++i)
                {
                    cout << "Opcion " << i + 1 << ". " << _opciones[i] << endl;
                }

            cout << "Seleccione una opcion (0 para salir/volver): ";
            cin >> opcionElegida;
            cout << endl ;

            if (opcionElegida < 0 || opcionElegida > tamanio)
                {
                    cout << endl << "Opcion no valida. Vuelva a intentarlo" << endl << endl;
                }
            else
                {
                    return opcionElegida;
                }
        }
}
