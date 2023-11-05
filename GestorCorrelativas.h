#ifndef GESTORCORRELATIVAS_H_INCLUDED
#define GESTORCORRELATIVAS_H_INCLUDED
#include "Archivo.h"
#include "Materia.h"
#include "CursadaMateria.h"

class GestorCorrelativas
{

public:
GestorCorrelativas() : archivoMaterias("materias.dat"), archivoCursadaMateria("cursadaMateria.dat") {
};
int validarSisepuedeCursar(std::string codigoMateria);
void mostrarCorrelativas(std::string codigoMateria);

private:

Archivo<Materia> archivoMaterias;
Archivo<CursadaMateria> archivoCursadaMateria;

};

#endif // GESTORCORRELATIVAS_H_INCLUDED
