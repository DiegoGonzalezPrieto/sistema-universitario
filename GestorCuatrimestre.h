#ifndef GESTORCUATRIMESTRE_H
#define GESTORCUATRIMESTRE_H
#include "GestorCursadaMateria.h"
#include "GestorNotasFinales.h"
#include "Cuatrimestre.h"
#include "Archivo.h"
#include "Mensajero.h"
#include "Fecha.h"


class GestorCuatrimestre {

public:
    GestorCuatrimestre(std::string archivoCuatrimestre, std::string archivoCursadas, std::string archivoMaterias, std::string archivoNotas);
    void iniciarGestorCuatrimestre();
    void iniciarCuatrimestre();
    void cerrarCuatrimestre();
    void cerrarCuatrimestreYCursadas();
    void modificarCuatrimestreActual();
    void mostrarInformacionCuatrimestreActual();
    void mostrarTodosCuatrimestresCursados();
    void actualizarMateriasEnCursoEnCuatrimestre();
    void informesCuatrimestres();

    /// Chequea si una materia en curso se puede seguir cursando más allá del cuatrimestre de cierre
    bool sePuedeSeguirCursando(CursadaMateria cursada, Cuatrimestre cuatriCierre);
private:

    Archivo<Cuatrimestre> archivoCuatrimestres;
    Mensajero msj;
    GestorCursadaMateria gcm;
    GestorNotasFinales gnf;

};

#endif // GESTORCUATRIMESTRE_H
