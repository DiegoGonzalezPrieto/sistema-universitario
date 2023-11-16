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
    Archivo<Config> respaldoConfiguracion;
    Archivo<CargaInicial> respaldoCargaInicial;
    Archivo<Carrera> respaldoCarrera;
    Archivo<Materia> respaldoMaterias;
    Archivo<CursadaMateria> respaldoCursadaMateria;
    Archivo<Cuatrimestre> respaldoCuatrimestre;
    Archivo<Evento> respaldoEventos;
    Archivo<NotaFinal> respaldoNotaFinal;

    Mensajero msj ;


public:
    GestorRespaldos();
    void PrimerInicio();
    void iniciar();

    void menuBackups();
    void backupTotal();
    void menuRestores();
    void restoreTotal();
    void menuPorDefecto();
    void porDefectoTotal();

    void primerInicioMenuBackups();
    void primerInicioBackupTotal();
    void primerInicioMenuRestores();
    void primerInicioRestoreTotal();
    void primerInicioMenuPorDefecto();
    void primerInicioPorDefectoTotal();

};

#endif // GESTORRESPALDOS_H
