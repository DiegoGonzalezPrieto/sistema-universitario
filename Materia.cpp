#include "Materia.h"
#include <cstring>

Materia::Materia()
{
    //ctor
}

void Materia::setNombreMateria(const std::string& nombre){

    strcpy(_nombre, nombre.c_str());

}


void Materia::setIdMateria(const std::string& idMateria){

    strcpy(_idMateria, idMateria.c_str());
}


void Materia::setIdMateriasRequeridas(int pos, const std::string& idMateriaRequerida){

    strcpy(_idMateriasRequeridas[pos], idMateriaRequerida.c_str());
}


void Materia::setCuatrimestreSugerido(int cuatrimestreSugerido){

    _cuatrimestreSugerido = cuatrimestreSugerido;
}

void Materia::setCuatrimestreDeDuracion(int cuatrimestreDeDuracion){

    _cuatrimestresDeDuracion = cuatrimestreDeDuracion;
}

std::string Materia::getNombreMateria() const{

    return _nombre;
}

std::string Materia::getIdMateria() const{

    return _idMateria;
}


std::string Materia::getIdMateriasRequeridas(int pos) const{

    return _idMateriasRequeridas[pos];
}

int Materia::getCuatrimestreSugerido() const{

    return _cuatrimestreSugerido;
}

int Materia::getCuatrimestreDeDuracion() const{

    return _cuatrimestresDeDuracion;
}

std::string Materia::toString() const{


///OBSERVACION: Como no hay datos por defecto en el constructor, si no seteamos datos en algún atributo toString() mostrará basura

    std::string aux = "";

    aux += getNombreMateria();
    aux += " ";
    aux += getIdMateria();
    aux += " ";

    for(int i = 0; i< CANTMATERIAS; i++){

        aux += getIdMateriasRequeridas(i) + " ";
    }

    aux += std::to_string(getCuatrimestreSugerido());
    aux += " ";
    aux += std::to_string(getCuatrimestreDeDuracion());

    return aux;
}
