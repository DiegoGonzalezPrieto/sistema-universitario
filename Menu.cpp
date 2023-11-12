#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#include "rlutil.h"
#include "Menu.h"
#include "func_utiles.h"
#include "Mensajero.h"


Menu::Menu(const vector<string> &opciones, string titulo) : _opciones(opciones), _titulo(titulo) {}

int Menu::mostrar()
{
    Mensajero msj;
    int opcionElegida, tamanio = _opciones.size();
    limpiarPantalla();
    while (true)
        {
            rlutil::saveDefaultColor();
            rlutil::setBackgroundColor(rlutil::WHITE);
            rlutil::setColor(rlutil::LIGHTMAGENTA);
            cout << _titulo << endl << endl;
            rlutil::resetColor();

            for (int i = 0; i < tamanio; ++i)
                {   rlutil::saveDefaultColor();
                    rlutil::setBackgroundColor(rlutil::WHITE);
                    rlutil::setColor(rlutil::LIGHTMAGENTA);
                    cout << "\t" << i + 1 << ". ";
                    rlutil::resetColor();
                    cout<<" ";
                    cout<< _opciones[i] << endl;

                }

            cout << "\nSeleccione una opcion (0 para salir/volver): ";


            opcionElegida=validar<int>();

            if (opcionElegida < 0 || opcionElegida > tamanio)
                {
                  msj.mensajeError("Opcion no valida. Vuelva a intentarlo");
                  limpiarPantalla();
                }
            else
                {
                    return opcionElegida;
                }
        }
}
