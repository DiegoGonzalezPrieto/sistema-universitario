#include "CargaInicial.h"

CargaInicial::CargaInicial()
{
    _contador=0;
}

void CargaInicial::aumentarcontadorDatosCargados(){

    _contador++;
}
int CargaInicial::getdatoscargados(){

return _contador;}

void CargaInicial::disminuirDatosCargados(){

    _contador--;
}
