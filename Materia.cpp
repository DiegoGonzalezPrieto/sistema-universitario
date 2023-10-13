#include "Materia.h"
#include <cstring>

Materia::Materia()
{
    //ctor
}

void Materia::setNombreMateria(const char* nombre){

    strcpy(_nombre, nombre);

}


void Materia::setIdMateria(const char* idMateria){

    strcpy(_idMateria, idMateria);
}


void Materia::setIdMateriasRequeridas(int pos, const char* idMateriaRequerida){

    strcpy(_idMateriasRequeridas[pos], idMateriaRequerida);
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

const char* Materia::getIdMateria() const{

    return _idMateria;
}


const char* Materia::getIdMateriasRequeridas(int pos) const{

    return _idMateriasRequeridas[pos];
}

int Materia::getCuatrimestreSugerido() const{

    return _cuatrimestreSugerido;
}

int Materia::getCuatrimestreDeDuracion() const{

    return _cuatrimestresDeDuracion;
}
