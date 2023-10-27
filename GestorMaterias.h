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
    bool guardarMateria();
    bool modificarMateria();
    void mostrarMaterias();

};

#endif // GESTORMATERIAS_H
