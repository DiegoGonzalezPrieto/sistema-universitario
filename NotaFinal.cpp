#include "NotaFinal.h"
#include <cstring>

NotaFinal::NotaFinal()
{
    //ctor
}

void NotaFinal::setIdMateria(const char* idMateria){

    strcpy(_idMateria, idMateria);
}

void NotaFinal::setNota(int nota){

    _nota = nota;
}

void NotaFinal::setFecha(const Fecha& fecha){

    _fecha = fecha;
}

const char* NotaFinal::getIdMateria() const{

    return _idMateria;
}

int NotaFinal::getNota() const{

    return _nota;
}

Fecha NotaFinal::getFecha() const{

    return _fecha;
}
