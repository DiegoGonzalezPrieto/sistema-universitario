#include <iostream>
#include <cstring>
using namespace std;
#include "Mensajero.h"

void Mensajero::mensajeAdvertencia(string mensaje)
{
    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::YELLOW);
cout << "ADVERTENCIA: " << mensaje << endl << endl;
    rlutil::resetColor();
}
void Mensajero::mensajeInformacion(string mensaje)
{   rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::GREEN);
cout << "INFORMACION: " << mensaje << endl << endl;
     rlutil::resetColor();
}
void Mensajero::mensajeError(string mensaje)
{
    rlutil::saveDefaultColor();
    rlutil::setColor(rlutil::RED);
cout << "ERROR: " << mensaje << endl << endl;
    rlutil::resetColor();
}
