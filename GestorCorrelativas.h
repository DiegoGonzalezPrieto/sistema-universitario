#ifndef GESTORCORRELATIVAS_H_INCLUDED
#define GESTORCORRELATIVAS_H_INCLUDED
#include "Archivo.h"
#include "Materia.h"
#include "CursadaMateria.h"
#include "Mensajero.h"

class GestorCorrelativas
{

public:
GestorCorrelativas(std::string materiasd, std::string cursadamateriad) : archivoMaterias(materiasd), archivoCursadaMateria(cursadamateriad) {
};
bool validarSisepuedeCursar(std::string codigoMateria);

std::vector<std::string> getNoAprobadas(std::string idMateria);

void mostrarCorrelativas(std::string codigoMateria);

/// Muestra las correlativas con el estado de las mismas en la última cursada registrada de cada correlativa
void mostrarCorrelativasConEstado(std::string codigoMateria);

private:

Archivo<Materia> archivoMaterias;
Archivo<CursadaMateria> archivoCursadaMateria;
Mensajero m;

};

#endif // GESTORCORRELATIVAS_H_INCLUDED
