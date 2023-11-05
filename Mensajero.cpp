#include <iostream>
#include <cstring>

using namespace std;

#include "Mensajero.h"

void Mensajero::mensajeAdvertencia(string mensaje)
{
cout << "ADVERTENCIA: " << mensaje << endl << endl;
}
void Mensajero::mensajeInformacion(string mensaje)
{
cout << "INFORMACION: " << mensaje << endl << endl;
}
void Mensajero::mensajeError(string mensaje)
{
cout << "ERROR: " << mensaje << endl << endl;
}
