#include "Cuatrimestre.h"
#include <cstring>
#include <iostream>


Cuatrimestre::Cuatrimestre()
{

    ///Le coloco un valor inicial a los códigos de cursadaMateria para comparar en el setIdCursadaMateria contra este valor
    for(int i = 0; i < CANTMATERIAS; i++){
        strcpy(_idsCursadaMateria[i], "N/A");
    }

}

void Cuatrimestre::setAnio(int anio){

    _anio = anio;
}

void Cuatrimestre::setPeriodo(int periodo){

    _periodo = periodo;
}

void Cuatrimestre::setIdCursadaMateria(const std::string& nuevoIdMateria){

    // Buscar el primer espacio disponible
    int index = -1;

    for (int i = 0; i < CANTMATERIAS; ++i) {

        if (strcmp(_idsCursadaMateria[i], "N/A") == 0) {

            index = i;

            break;
        }
    }
    // Verificar si se encontró un espacio disponible
    if (index != -1) {

        strcpy(_idsCursadaMateria[index], nuevoIdMateria.c_str());
        std::cout<<"MATERIA AGREGADA CORRECTAMENTE"<<std::endl;

    } else {

        // Manejar el caso cuando no hay espacio disponible
        std::cout << "Error: No hay espacio disponible para agregar más materias" << std::endl;
    }

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

std::string Cuatrimestre::getIdsCursadaMateria(int pos) const{

    if(pos >= 0 && pos <= CANTMATERIAS){

        // Verificar que el índice esté dentro del rango
        return _idsCursadaMateria[pos];
    }
    else{
        // Devolver un valor por defecto o manejar el error según sea necesario
        return "Índice fuera de rango";

    }

}

bool Cuatrimestre::getFinalizado() const{

    return _finalizado;
}

std::string Cuatrimestre::getIdCuatrimestre() const{

    std::string aux = "";

    aux = std::to_string(getAnio());

    aux += "0";

    aux += std::to_string(getPeriodo());

    return aux;
}

std::string Cuatrimestre::toString() const{

    ///OBSERVACION: Como no hay datos por defecto en el constructor, si no seteamos datos en algún atributo toString() mostrará basura

    std::string aux = "";

    aux = "Anio: ";
    aux += std::to_string(getAnio());
    aux += ", periodo: ";
    aux += std::to_string(getPeriodo());
    aux += "\nID materias cursadas: ";

    bool hayMaterias = false;

    for(int i = 0; i < CANTMATERIAS; i++){

        if(getIdsCursadaMateria(i) != "N/A"){

            if(i != CANTMATERIAS-1){

                aux += getIdsCursadaMateria(i);
                aux += "    ";

                if(hayMaterias == false){
                    hayMaterias = true;
                }
            }
            else{

                aux += getIdsCursadaMateria(i);

            }
        }
    }

    if(hayMaterias == false){

        aux += "no hay materias cursadas en este cuatrimestre";
    }

    return aux;
}
