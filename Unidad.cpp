#include <iostream>
using namespace std;


#include "Unidad.h"

Unidad::Unidad()
{}

string Unidad::getRuta()
{
    string s(_ruta);
    return s;
}

void Unidad::setRuta(string r)
{
    strcpy(_ruta, r.c_str());
}

float getPorcentajeCompletado(){
    /// TODO
    return 1.0f;
}
