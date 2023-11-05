#ifndef GESTORCORRELATIVAS_H_INCLUDED
#define GESTORCORRELATIVAS_H_INCLUDED
#include "Archivo.h"
#include "Materia.h"
#include "CursadaMateria.h"

class GestorCorrelativas
{

public:
GestorCorrelativas(std::string materiasd, std::string cursadamateriad) : archivoMaterias(materiasd), archivoCursadaMateria(cursadamateriad) {
};
int validarSisepuedeCursar(std::string codigoMateria);
void mostrarCorrelativas(std::string codigoMateria);

private:

Archivo<Materia> archivoMaterias;
Archivo<CursadaMateria> archivoCursadaMateria;

};

#endif // GESTORCORRELATIVAS_H_INCLUDED
