#include <iostream>


using namespace std;

#include "Mensajero.h"

void Mensajero::mensajeAdvertencia(const char* mensaje)
{
cout << "ADVERTENCIA: " << mensaje << endl;
}
void Mensajero::mensajeInformacion(const char* mensaje)
{
cout << "INFORMACION: " << mensaje << endl;
}
void Mensajero::mensajeError(const char* mensaje)
{
cout << "ERROR: " << mensaje << endl;
}
