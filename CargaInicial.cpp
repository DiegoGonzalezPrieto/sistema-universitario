#include "CargaInicial.h"

CargaInicial::CargaInicial()
{
    _contador=0;
    materiasCargadas=false;
    carreraCargada=false;
}

void CargaInicial::aumentarcontadorDatosCargados(){

    _contador++;
}
int CargaInicial::getdatoscargados(){

return _contador;}

void CargaInicial::disminuirDatosCargados(){

    _contador--;
}

bool CargaInicial::getCarreraCargada()
{
    return carreraCargada;
}
        bool CargaInicial::getMateriasCargadas()
        {
            return materiasCargadas;
        }
        void CargaInicial::setCarreraCargada(bool cc)
        {
            carreraCargada = cc;
        }
        void CargaInicial::setMateriasCargadas(bool mc)
        {
            materiasCargadas = mc;
        }
