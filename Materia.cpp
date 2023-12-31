#include "Materia.h"
#include "GestorCorrelativas.h"
#include "GestorMaterias.h"
#include "rutas.h"


/// Cadenas vac�as a NombreMateria e IdMateria
Materia::Materia()
{
    setNombreMateria("");
    setIdMateria("");
    ///Le coloco un valor inicial a los c�digos de materiasRequeridas para comparar contra este valor
    for(int i = 0; i < CANTMATERIAS; i++){
        cargarCadenaConString("N/A", _idMateriasRequeridas[i], LONGMAXID);
    }
}

void Materia::setNombreMateria(const std::string& nombre){

    cargarCadenaConString(nombre, _nombre, LONGMAXNOMBRE);

}


void Materia::setIdMateria(const std::string& idMateria){

    cargarCadenaConString(idMateria, _idMateria, LONGMAXID);
}


void Materia::setIdMateriasRequeridas(int pos, const std::string& idMateriaRequerida){

    cargarCadenaConString(idMateriaRequerida, _idMateriasRequeridas[pos], LONGMAXID);
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

std::vector<std::string> Materia::getIdMateriasRequeridas()
{
    std::vector<std::string> aux;
    for (int i=0;i<CANTMATERIAS; i++)
    {
        if (getIdMateriasRequeridas(i) != "N/A" && getIdMateriasRequeridas(i) != "")
        {
            aux.push_back(getIdMateriasRequeridas(i));
        }
    }
    return aux;
}

int Materia::getCuatrimestreSugerido() const{

    return _cuatrimestreSugerido;
}

int Materia::getCuatrimestreDeDuracion() const{

    return _cuatrimestresDeDuracion;
}


std::string Materia::toString() const{


///OBSERVACION: Como no hay datos por defecto en el constructor, si no seteamos datos en alg�n atributo toString() mostrar� basura
    GestorMaterias gMat(Rutas::materias);
    std::string aux = "";

    aux = "Materia: ";
    aux += getNombreMateria();
    aux += " - ID: ";
    aux += getIdMateria();

    bool hayCorrelativas = false;

    aux += "\nMaterias correlativas: ";


    for(int i = 0; i < CANTMATERIAS; i++){

        if(getIdMateriasRequeridas(i) != "N/A" && getIdMateriasRequeridas(i) != ""){

            if(i != (CANTMATERIAS -1)){

                aux += "\nID:";
                aux += getIdMateriasRequeridas(i);
                aux += " - ";
                aux += gMat.mostrarNombrePorID(getIdMateriasRequeridas(i));
                aux += "    ";
                hayCorrelativas = true;
            }
            else{

                aux += getIdMateriasRequeridas(i);
            }
        }
    }

    if(!hayCorrelativas){

        aux +="No tiene";
    }

    aux += "\nCuatrimestre sugerido: ";
    aux += std::to_string(getCuatrimestreSugerido());
    aux += "\nDuracion: ";
    aux += std::to_string(getCuatrimestreDeDuracion());
    aux += " Cuatrimestre/s";
    return aux;
}
