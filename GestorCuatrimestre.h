#ifndef GESTORCUATRIMESTRE_H
#define GESTORCUATRIMESTRE_H
#include "CursadaMateria.h"
#include "GestorCursadaMateria.h"
#include "Cuatrimestre.h"
#include "Archivo.h"
#include "Mensajero.h"
#include "Fecha.h"


class GestorCuatrimestre {

public:
    GestorCuatrimestre(std::string nombre);
    void iniciarGestorCuatrimestre();
    void iniciarCuatrimestre();
    void cerrarCuatrimestre();
    void modificarCuatrimestreActual();
    void mostrarInformacionCuatrimestreActual();
    void mostrarTodosCuatrimestresCursados();
    void actualizarMateriasEnCursoEnCuatrimestre();
private:

    Archivo<Cuatrimestre> archivoCuatrimestres;
    Mensajero msj;

};

#endif // GESTORCUATRIMESTRE_H
