#include "Cuatrimestre.h"
#include <cstring>


Cuatrimestre::Cuatrimestre()
{
    ///TODO: Ver si tendrá valores por defecto
}

void Cuatrimestre::setAnio(int anio){

    _anio = anio;
}

void Cuatrimestre::setPeriodo(int periodo){

    _periodo = periodo;
}

void Cuatrimestre::setIdCursadaMateria(int pos, const char* idCursadaMateria){

    strcpy(_idsCursadaMateria[pos], idCursadaMateria);
}

void Cuatrimestre::setFinalizado(bool finalizado){

    _finalizado = finalizado;
}

int Cuatrimestre::getAnio() const{

    return _anio;
}

int Cuatrimestre::getPeriodo() const{

    return _periodo;
}

const char* Cuatrimestre::getIdsCursadaMateria(int pos) const{

    return _idsCursadaMateria[pos];
}

bool Cuatrimestre::getFinalizado() const{

    return _finalizado;
}

std::string Cuatrimestre::getId() const{

    std::string aux = "";

    aux = std::to_string(getAnio());

    aux += "0";

    aux += std::to_string(getPeriodo());

    return aux;
}
