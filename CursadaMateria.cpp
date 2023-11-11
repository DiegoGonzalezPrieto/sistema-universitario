#include <iostream>
#include <cstring>
using namespace std;


#include "CursadaMateria.h"
#include "func_utiles.h"

/// Asigna cadenas vacias a _idCuatrimestreInicio
CursadaMateria::CursadaMateria(): Materia(), _idCuatrimestreInicio("") {
}
/// Recibe Materia como parámetro. Asigna cadenas vacias a _idCuatrimestreInicio
CursadaMateria::CursadaMateria(Materia m): _idCuatrimestreInicio("") {
 setNombreMateria(m.getNombreMateria());
 setIdMateria(m.getIdMateria());
 setCuatrimestreSugerido(m.getCuatrimestreSugerido());
 setCuatrimestreDeDuracion(m.getCuatrimestreDeDuracion());

// TODO : Ver cómo asignar id materias correlativas
// setIdMateriasRequeridas(int pos, const std::string& idMateriaRequerida)
}

const int CursadaMateria::getMaxUnidades()
{
    return MAX_UNIDADES;
}
const int CursadaMateria::getMaxDatosCursada()
{
    return MAX_DATOS_CURSADA;
}

string CursadaMateria::getIdCuatrimestreInicio()
{
    return string(_idCuatrimestreInicio);
}
void CursadaMateria::setIdCuatrimestreInicio(string id)
{
    cargarCadenaConString(id, _idCuatrimestreInicio, 7);
}
string CursadaMateria::getEstadoToString()
{
    switch (getEstado())
        {
        case MAT_EN_CURSO:
            return "En curso";
            break;
        case MAT_REGULARIZADA:
            return "Regularizada";
            break;
        case MAT_APROBADA:
            return "Aprobada";
            break;
        case MAT_ANULADA:
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

string CursadaMateria::getDatosCursadaToString()
{
    string aux = "";
    for (DatosCursada dc : getDatosCursada())
        {
            if (dc.getAula() != "")
                {
                    aux += dc.toString() + "\n\n";
                }
        }
    return aux;
}
vector<DatosCursada> CursadaMateria::getDatosCursada()
{
    vector<DatosCursada> v;
    for (int i=0; i< getMaxDatosCursada(); i++)
        {
            if (_datosCursada[i].getAula() != "")
                {
                    v.push_back(_datosCursada[i]);
                }
        }
        return v;
}

/// TODO: el GestorCursadaMateria debe validar la cantidad de datos ingresados o dar error/mensaje
void CursadaMateria::setDatosCursada(vector<DatosCursada> v)
{
    if (v.size() > getMaxDatosCursada())
        {
            return;
        }
    for (int i=0; i< v.size(); i++)
        {
            _datosCursada[i] = v[i];
        }
}

vector<Unidad> CursadaMateria::getUnidades()
{
    vector<Unidad> v;
    for (int i=0; i<getMaxUnidades(); i++)
        {
            if (_unidades[i].getRuta() != "")
                {
                    v.push_back(_unidades[i]);
                }
        }
    return v;
}

void CursadaMateria::setUnidades(vector<Unidad> v)
{
        if (v.size() > getMaxUnidades())
        {
            return;
        }
    for (int i=0; i< v.size(); i++)
        {
            _unidades[i] = v[i];
        }
}

void CursadaMateria::agregarDatoCursada(DatosCursada datoCursada){
    vector<DatosCursada> v = getDatosCursada();
    if (v.size() >= getMaxDatosCursada()) return;

    v.push_back(datoCursada);
    setDatosCursada(v);
}

void CursadaMateria::agregarUnidad(Unidad unidad)
{
vector<Unidad> v = getUnidades();
    if (v.size() >= getMaxUnidades()) return;

    v.push_back(unidad);
    setUnidades(v);
}

string CursadaMateria::getIdCursadaMateria()
{
    return getIdMateria() + getIdCuatrimestreInicio();
}

string CursadaMateria::toFullString()
{
    string aux = "";
    aux += Materia::toString();
    aux += "\n\nDatos de Cursada:\n";
    aux += "\nEstado: " + getEstadoToString();
    aux += "\nCuatrimestre de Inicio: " + getIdCuatrimestreInicio();
    aux += "\nHorarios de Cursada: " + getDatosCursadaToString() + "\n";
    return aux;
}
string CursadaMateria::toString()
{
    string aux = "";
    aux += getIdMateria() +" - " +getNombreMateria();
    aux += "\nEstado: " + getEstadoToString();
    aux += "\nCuatrimestre de Inicio: " + getIdCuatrimestreInicio();
    aux += "\nHorarios de Cursada:\n" + getDatosCursadaToString() + "\n";
    return aux;
}
