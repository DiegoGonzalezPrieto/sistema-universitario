#ifndef GESTORCUATRIMESTRE_H
#define GESTORCUATRIMESTRE_H
#include "Cuatrimestre.h"
#include "Archivo.h"
#include "Mensajero.h"
#include "GestorCorrelativas.h"
#include "GestorMaterias.h"


class GestorCuatrimestre {

public:
    GestorCuatrimestre(std::string nombre);
    void iniciarGestorCuatrimestre();
    void iniciarCuatrimestre();
    void cerrarCuatrimestre();
    void modificarCuatrimestreActual();

private:

    Archivo<Cuatrimestre> archivoCuatrimestres;
    Mensajero msj;

};

#endif // GESTORCUATRIMESTRE_H
