#include <iostream>
#include <cstring>
using namespace std;


#include "CursadaMateria.h"

CursadaMateria::CursadaMateria() {}
CursadaMateria::CursadaMateria(string cuatrimestreActual) // TODO
{
}

string CursadaMateria::getIdCuatrimestreInicio()
{
    return string(_idCuatrimestreInicio);
}
void CursadaMateria::setIdCuatrimestreInicio(string id)
{
    strcpy(_idCuatrimestreInicio, id.c_str());
}
string CursadaMateria::getIdCuatrimestreActual()
{
    return string(_idCuatrimestreActual);
}
void CursadaMateria::setIdCuatrimestreActual(string id)
{
    strcpy(_idCuatrimestreActual, id.c_str());
}
string CursadaMateria::getEstadoToString()
{
    switch (getEstado())
        {
        case EN_CURSO:
            return "En curso";
            break;
        case REGULARIZADA:
            return "Regularizada";
            break;
        case APROBADA:
            return "Aprobada";
            break;
        case ANULADA:
            return "Anulada";
            break;
        default:
            return "Sin estado";
        }
}
EstadoMateria CursadaMateria::getEstado()
{
    return _estado;
}
void CursadaMateria::setEstado(EstadoMateria estado)
{
    _estado = estado;
}

/// TODO :
//        vector<DatosCursada> getDatosCursada();
//        void setDatosCursada(vector<DatosCursada>, int);
//        vector<Unidad> getUnidades();
//        void setUnidades(vector<Unidad>);



string CursadaMateria::getIdCursadaMateria() // TODO
{
//    return getId() + getIdCuatrimestreInicio();
    return "IMPLEMENTAR";
}

string CursadaMateria::toString() // TODO
{
    string aux = "";
//    aux += Materia::toString();
    aux += "\nEstado: " + getEstadoToString();
    aux += "\nCuatrimestre de Inicio: " + getIdCuatrimestreInicio();
    aux += "\nCuatrimestre Actual: " + getIdCuatrimestreActual();
//    aux += "\nHorarios de Crusada: " + getDatosCursadaToString();
    return aux;
}
