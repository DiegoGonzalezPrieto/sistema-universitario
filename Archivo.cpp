#include <iostream>
#include <cstring>
#include <filesystem>
using namespace std;

#include "Archivo.h"

Archivo::Archivo() {};
Archivo::Archivo(string nombre)
{
    setNombre(nombre);
}

string Archivo::getNombre()
{
    string nombre(_nombre);
    return string(nombre);
}
void Archivo::setNombre(string n)
{
    strcpy(_nombre, n.c_str());
}


bool Archivo::crearArchivo()
{
   FILE* p = fopen(getNombre().c_str(),"wb");
              if (p == NULL)
        {
            return false;
        }
    fclose(p);
    return true;
}

bool Archivo::archivoExiste(){
    if (FILE *file = fopen(_nombre, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

template <typename T>
T Archivo::leerRegistro(int pos)
{
    T registro;
    return registro;
}
