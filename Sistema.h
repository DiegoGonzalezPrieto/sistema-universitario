#ifndef SISTEMA_H
#define SISTEMA_H
#include <string>
#include "config.h"
#include "GestorCarrera.h"
#include "GestorMaterias.h"
#include "GestorNotasFinales.h"
#include "GestorEventos.h"
#include "GestorCsv.h"
#include "GestorCuatrimestre.h"
#include "GestorConfig.h"
#include "GestorRespaldos.h"
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
        bool preInicio();
        void menuCargaInicial();
        bool cargaInicial();
        void crearDirectoriosEsenciales();

    private:
        GestorCarrera _gestorCarrera;
        GestorMaterias _gestorMaterias;
        GestorNotasFinales _gestorNotasFinales;
        GestorEventos _gestorEventos;
        GestorCsv _gestorCsv; ///VER SI SE INICIALIZA AQUI, O EN GESTOR MATERIAS
        GestorCuatrimestre _gestorCuatrimestre;
        GestorConfig _gestorConfig;
        GestorRespaldos _gestorRespaldos;

        Mensajero _mensajero;
        Archivo <CargaInicial> _cargaInicial;

};

#endif // SISTEMA_H
