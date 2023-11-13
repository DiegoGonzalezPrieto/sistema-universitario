#ifndef GESTORRESPALDOS_H
#define GESTORRESPALDOS_H


#include "Archivo.h"
#include "GestorCarrera.h"
#include "GestorConfig.h"
#include "GestorCorrelativas.h"
#include "GestorCuatrimestre.h"
#include "GestorCursadaMateria.h"
#include "GestorEventos.h"
#include "GestorMaterias.h"
#include "GestorNotasFinales.h"



class GestorRespaldos
{
private:
    Archivo<NotaFinal> respaldoNotaFinal;
    Archivo<CargaInicial> respaldoCargaInicial;
    Archivo<Carrera> respaldoCarrera;
    Archivo<Evento> respaldoEventos;
    Archivo<Materia> respaldoMaterias;
    Archivo<Cuatrimestre> respaldoCuatrimestre;
    Archivo<Config> respaldoConfiguracion;

    Mensajero msj ;


public:
    GestorRespaldos();
    void iniciar();

    void menuBackups();
    void backupTotal();
    void menuRestores();
    void restoreTotal();
    void menuPorDefecto();
    void porDefectoTotal();


    bool backupNotaFinal();
    bool backupCargaInicial();
    bool backupCarrera();
    bool backupEventos();
    bool backupMaterias();
    bool backupCuatrimestre();
    bool backupConfiguracion();


    bool restoreNotaFinal();
    bool restoreCargaInicial();
    bool restoreCarrera();
    bool restoreEventos();
    bool restoreMaterias();
    bool restoreCuatrimestre();
    bool restoreConfiguracion();


};

#endif // GESTORRESPALDOS_H
