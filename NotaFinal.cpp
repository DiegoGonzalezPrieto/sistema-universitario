#include "NotaFinal.h"
#include <cstring>

NotaFinal::NotaFinal()
{
    //ctor
}

void NotaFinal::setIdMateria(const std::string& idMateria){

    cargarCadenaConString(idMateria, _idMateria, LONGMAX);
}

void NotaFinal::setNota(int nota){

    _nota = nota;
}

void NotaFinal::setFecha(const Fecha& fecha){

    _fecha = fecha;
}

std::string NotaFinal::getIdMateria() const{

    return _idMateria;
}

int NotaFinal::getNota() const{

    return _nota;
}

Fecha NotaFinal::getFecha() const{

    return _fecha;
}

std::string NotaFinal::toString() const{

    ///OBSERVACION: Como no hay datos por defecto en el constructor, si no seteamos datos en algún atributo toString() mostrará basura

    std::string aux = "";

    aux = "ID Materia: ";
    aux += getIdMateria();
    aux += " --- Nota: ";
    aux += std::to_string(getNota());
    aux += " --- Fecha: ";
    aux += getFecha().toString();

    return aux;

}
