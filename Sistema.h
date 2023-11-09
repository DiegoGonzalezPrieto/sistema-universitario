#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>


#include "GestorCarrera.h"
#include "GestorMaterias.h"
#include "GestorNotasFinales.h"
#include "GestorEventos.h"
#include "GestorCsv.h"
///FALTA GESTORCUATRIMESTRE
///FALTA GESTORCURSADAMATERIA
///FALTAN LOS DIRECTORIOS
///FALTA LA CONFIGURACION
#include "CargaInicial.h"

#include "Mensajero.h"
#include "Archivo.h"

class Sistema
{
    public:
        Sistema();

        void iniciar();
        void menuCargaInicial();
        bool cargaInicial();
        void crearDirectoriosEsenciales();

    private:
        GestorCarrera _gestorCarrera;
        GestorMaterias _gestorMaterias;
        GestorNotasFinales _gestorNotasFinales;
        GestorEventos _gestorEventos;
        GestorCsv _gestorCsv; ///VER SI SE INICIALIZA AQUI, O EN GESTOR MATERIAS

        Mensajero _mensajero;
        Archivo <CargaInicial> _cargaInicial;

};

#endif // SISTEMA_H
