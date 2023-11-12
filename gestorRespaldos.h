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







class gestorRespaldos
{
private:
    Archivo<NotaFinal> respaldoNotaFinal;
    Archivo<CargaInicial> respaldoCargaInicial;
    Archivo<Carrera> respaldoCarreraEnCurso;


public:
    gestorRespaldos(std::string rutaRespaldo);



};

#endif // GESTORRESPALDOS_H
