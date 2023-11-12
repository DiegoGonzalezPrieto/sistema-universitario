#include "GestorDirectorios.h"

using namespace std;

GestorDirectorios::GestorDirectorios()
{
    //ctor
}

bool GestorDirectorios::crearDirectorios(string ruta)
{
    return filesystem::create_directories(ruta);
}

bool GestorDirectorios::crearDirectoriosCuatrimestre(vector <CursadaMateria> materiasEnCurso, string idCuatrimestre){

    int cantMaterias = materiasEnCurso.size();

    string ruta = "Archivos/cursada/";
    ruta += idCuatrimestre + "/";

    for(int i = 0; i < cantMaterias; i++){

        if(directoriosMateriasAnualesYaCreados(materiasEnCurso[i].getIdCuatrimestreInicio(), idCuatrimestre) == false && materiasEnCurso[i].getCuatrimestreDeDuracion() == 2){

            string rutaMateria = ruta + materiasEnCurso[i].getNombreMateria() + "/";

            vector<Unidad>auxUnidad;
            auxUnidad = materiasEnCurso[i].getUnidades();
            int cantUnidades = auxUnidad.size();

            for(int j = 0; j < cantUnidades; j++){

                string rutaUnidad = rutaMateria + auxUnidad[j].getRutaCompletado();

                crearDirectorios(rutaUnidad);
            }

        }

    }

    return true;

}

/// SI LA MATERIA ES ANUAL Y YA SE CREARON LOS DIRECTORIOS, NO SE VOLVERAN A GENERAR PARA SU SEGUNDO CUATRIMESTRE DE DURACION
bool GestorDirectorios::directoriosMateriasAnualesYaCreados(string idCuatrimestreInicio, string idCuatrimestreActual){

    if(idCuatrimestreInicio == idCuatrimestreActual){

        return false;
    }

    return true;
}
