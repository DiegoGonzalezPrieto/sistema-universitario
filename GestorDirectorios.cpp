#include "GestorDirectorios.h"

using namespace std;
namespace fs = filesystem;

GestorDirectorios::GestorDirectorios()
{
    //ctor
}

bool GestorDirectorios::crearDirectorios(string ruta)
{
    return filesystem::create_directories(ruta);
}

bool GestorDirectorios::crearDirectoriosCuatrimestre(CursadaMateria materiaEnCurso, string idCuatrimestre){

    string ruta = "Archivos/cursada/";
    ruta += idCuatrimestre + "/";


    if(directoriosMateriasAnualesYaCreados(materiaEnCurso.getIdCuatrimestreInicio(), idCuatrimestre) == false && materiaEnCurso.getCuatrimestreDeDuracion() == 1){

        string rutaMateria = ruta + materiaEnCurso.getNombreMateria() + "/";

        vector<Unidad>auxUnidad;
        auxUnidad = materiaEnCurso.getUnidades();
        int cantUnidades = auxUnidad.size();

        for(int i = 0; i < cantUnidades; i++){

            string rutaUnidad = rutaMateria + auxUnidad[i].getRutaCompletado();

            crearDirectorios(rutaUnidad);
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


int GestorDirectorios::contarElementosEnDirectorio(string ruta){

    int cantidadElementos = 0;

    for (const auto& entrada : fs::directory_iterator(ruta)) {

        if((is_regular_file(entrada) == true)){
            cantidadElementos++;
        }
    }

    return cantidadElementos;


}

float GestorDirectorios::calcularProgresoUnidad(string rutaUnidad){

    int cantElementosPendientes, cantElementosCompletados, cantElementosTotales;
    float porcentajeProgreso;

    cantElementosPendientes = contarElementosEnDirectorio(rutaUnidad);

    rutaUnidad += "/completado";

    cantElementosCompletados = contarElementosEnDirectorio(rutaUnidad);

    cantElementosTotales = cantElementosCompletados + cantElementosPendientes;

    if(cantElementosTotales == 0){

        porcentajeProgreso = 100;

    }
    else{

        porcentajeProgreso = cantElementosCompletados * 100 / cantElementosTotales;
    }

    ///cout << "En base a los archivos que dispone, usted ha completado un " << porcentajeProgreso << "% de la unidad" << endl;
    return porcentajeProgreso;

}

void GestorDirectorios::calcularProgresoMateria(CursadaMateria materia, string idCuatrimestre){

    string rutaMateria = "Archivos/cursada/";
    rutaMateria += idCuatrimestre + "/" + materia.getNombreMateria();

    vector<Unidad>auxUnidad;
    auxUnidad = materia.getUnidades();
    int cantUnidades = auxUnidad.size();

    int cantElementosPendientes = 0;
    int cantElementosCompletados = 0;
    int cantElementosTotales = 0;

    float porcentajeProgreso;


    ///CONTAMOS LOS ELEMENTOS EN LAS CARPETAS COMPLETADO DE CADA UNIDAD
    for(int i = 0; i < cantUnidades; i++){

        string rutaUnidadCompletados = rutaMateria + "/" + auxUnidad[i].getRutaCompletado();

        cantElementosCompletados += contarElementosEnDirectorio(rutaUnidadCompletados);

    }

    ///CONTAMOS LOS ELEMENTOS PENDIENTES DE COMPLETAR DE CADA UNIDAD
    for(int i = 0; i < cantUnidades; i++){

        string rutaUnidadPendientes = rutaMateria + "/Unidad " + to_string(i+1);

        cantElementosPendientes += contarElementosEnDirectorio(rutaUnidadPendientes);

    }

    cantElementosTotales = cantElementosPendientes + cantElementosCompletados;

    if(cantElementosTotales == 0){

        porcentajeProgreso = 100;

    }
    else{

        porcentajeProgreso = cantElementosCompletados * 100 / cantElementosTotales;
    }

    cout << "Su progreso para la materia " << materia.getNombreMateria() << " en base a la cantidad de elementos completados es: ";
    cout << porcentajeProgreso << "%" << endl;

    if (cantElementosPendientes > 0){

        cout << "Le quedan un total de " << cantElementosPendientes << " elementos por completar para alcanzar el 100% de progreso en esta materia" << endl;
    }
}
