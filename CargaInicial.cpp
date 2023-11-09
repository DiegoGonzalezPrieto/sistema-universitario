#include "CargaInicial.h"

CargaInicial::CargaInicial()
{
    //ctor
}

void CargaInicial::setEstado(bool estado){

    _estado = estado;
}

bool CargaInicial::getEstado() const{

    return _estado;
}
