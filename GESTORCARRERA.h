#ifndef GESTORCARRERA_H_INCLUDED
#define GESTORCARRERA_H_INCLUDED
#include "CLASECARRERA.h"
#include "Archivo.h"

class GESTORCARRERA {

public:

    GESTORCARRERA(string nombre) : archivoCarreraEnCurso(nombre.c_str()) {
        // Aquí puedes agregar más inicializaciones si es necesario
    }

    bool agregarTodoslosDatosdeLaCarreraEnCurso(CLASECARRERA& carrera);
    void mostrarCarreraEnCurso();
    void modificarNombreCarreraEnCurso(std::string& nuevoNombre);
    void modificarNombreUniversidad(std::string& nuevoNombre);
    void modificarIdMaterias(std::vector<std::string>& nuevosIds);
    void mostrarNombreUniversidad();
    void mostrarIdMaterias();
    void modificarNombreEstudiante(std::string& nuevoNombre);
    void modificarLegajo(std::string& nuevoLegajo);
    void mostrarNombreEstudiante();
    void mostrarLegajo();
    string tostring();

private:
    Archivo<CLASECARRERA> archivoCarreraEnCurso;
};

#endif // GESTORCARRERA_H_INCLUDED
