#include "Materia.h"
#include <cstring>

Materia::Materia()
{
    ///Le coloco un valor inicial a los códigos de materiasRequeridas para comparar en el setIdCursadaMateria contra este valor
    for(int i = 0; i < CANTMATERIAS; i++){
        strcpy(_idMateriasRequeridas[i], "N/A");
    }
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

    aux = "Materia: ";
    aux += getNombreMateria();
    aux += ", ID: ";
    aux += getIdMateria();

    bool hayCorrelativas = false;

    aux += "\nID materias correlativas: ";

    for(int i = 0; i < CANTMATERIAS; i++){

        if(getIdMateriasRequeridas(i) != "N/A"){

            if(i != (CANTMATERIAS -1)){

                aux += getIdMateriasRequeridas(i);
                aux += "    ";
                hayCorrelativas = true;
            }
            else{

                aux += getIdMateriasRequeridas(i);
            }
        }
    }

    if(hayCorrelativas == false){

        aux +="no tiene\n";
    }

    aux += "\nCuatrimestre sugerido: ";
    aux += std::to_string(getCuatrimestreSugerido());
    aux += ", la materia tiene una duracion de ";
    aux += std::to_string(getCuatrimestreDeDuracion());
    aux += " cuatrimestre/s";
    return aux;
}
