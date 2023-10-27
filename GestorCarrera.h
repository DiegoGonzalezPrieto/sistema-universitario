#ifndef GESTORCARRERA_H_INCLUDED
#define GESTORCARRERA_H_INCLUDED
#include "Carrera.h"
#include "Archivo.h"

class GestorCarrera {

public:

    GestorCarrera(string nombre) : archivoCarreraEnCurso(nombre.c_str()) {
    };
    void modificarRegistro();
    void asignarDatosDesdeVector(const std::vector<Carrera>& datos);
    void cargarManual();

private:

    Archivo<Carrera> archivoCarreraEnCurso;
    Carrera datosCarrera;
};

#endif // GESTORCARRERA_H_INCLUDED


