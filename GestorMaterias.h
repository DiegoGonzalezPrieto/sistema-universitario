#ifndef GESTORMATERIAS_H
#define GESTORMATERIAS_H

#include "Materia.h"
#include "Archivo.h"

class GestorMaterias {

private:

    Archivo<Materia> archivoMaterias;
    Materia datosMateria;

public:

    GestorMaterias(string nombre);
    void CargarMaterias();
    void modificarMaterias();
    void mostrarMaterias();

    bool AgregarUnaMateria();
    bool buscarMateria(const std::string& IDmateria, Materia& datosMateria) ;
    bool modificarUnaMateria();

};

#endif // GESTORMATERIAS_H
