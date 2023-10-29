#include <iostream>
using namespace std;

#include <filesystem>

#include "Unidad.h"

/// Setea string vacío en _ruta para chequear validez
Unidad::Unidad()
{
    setRuta("");
}

Unidad::Unidad(string ruta)
{
    setRuta(ruta);
}

string Unidad::getRuta()
{
    string s(_ruta);
    return s;
}

void Unidad::setRuta(string r)
{
    strcpy(_ruta, r.c_str());
}

string Unidad::getRutaCompletado()
{
    return getRuta() + "/completado";
}
