#ifndef GESTORCARRERA_H_INCLUDED
#define GESTORCARRERA_H_INCLUDED
#include "Carrera.h"
#include "Archivo.h"
#include "Mensajero.h"
#include "CargaInicial.h"


class GestorCarrera {

public:

    GestorCarrera(std::string nombre,std::string archCargaInicial) : archivoCarreraEnCurso(nombre),archivoCargainicial(archCargaInicial) {
    };
    void modificarRegistro();
    void mostrarDatosCarrera();
    void cargarManual();
    void iniciar();
    bool archivoExiste();

private:
    Archivo<CargaInicial> archivoCargainicial;
    Archivo<Carrera> archivoCarreraEnCurso;
    Carrera _datosCarrera;
    Mensajero _mensajero;
};

#endif // GESTORCARRERA_H_INCLUDED


