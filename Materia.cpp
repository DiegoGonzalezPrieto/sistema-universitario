#include "Materia.h"
#include <cstring>

Materia::Materia()
{
    //ctor
}

void Materia::setNombreMateria(const char* nombre){

    strcpy(_nombre, nombre);

}


void Materia::setIdMateria(int idMateria){

    _idMateria = idMateria;
}

void Materia::setIdMateriasRequeridas(int* idMateriasRequeridas, int cantMateriasRequeridas){

    for(int i = 0; i< cantMateriasRequeridas; i++){

        _idMateriasRequeridas[i] = idMateriasRequeridas[i];
    }
}

void Materia::setIdMateriasRequeridas(int pos, int idMateriaRequerida){

    _idMateriasRequeridas[pos] = idMateriaRequerida;
}


void Materia::setCuatrimestreSugerido(int cuatrimestreSugerido){

    _cuatrimestreSugerido = cuatrimestreSugerido;
}

void Materia::setCuatrimestreDeDuracion(int cuatrimestreDeDuracion){

    _cuatrimestresDeDuracion = cuatrimestreDeDuracion;
}

const char* Materia::getNombreMateria() const{

    return _nombre;
}

int Materia::getIdMateria() const{

    return _idMateria;
}

int* Materia::getMateriasRequeridas(){

    return _idMateriasRequeridas;
}

int Materia::getMateriasRequeridas(int pos) const{

    return _idMateriasRequeridas[pos];
}

int Materia::getCuatrimestreSugerido() const{

    return _cuatrimestreSugerido;
}

int Materia::getCuatrimestreDeDuracion() const{

    return _cuatrimestresDeDuracion;
}
