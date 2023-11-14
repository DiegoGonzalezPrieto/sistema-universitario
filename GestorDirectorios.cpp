#include "GestorDirectorios.h"


#include <algorithm>
#include <unordered_map>

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

        string auxNombre = materiaEnCurso.getNombreMateria();
        string nombreMateria = validarCaracteresEspeciales(auxNombre);

        string rutaMateria = ruta + nombreMateria + "/";

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

    string auxNombre = materia.getNombreMateria();
    string nombreMateria = validarCaracteresEspeciales(auxNombre);

    rutaMateria += idCuatrimestre + "/" + nombreMateria;

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

///SE ENCARGA DE CREAR LAS CARPETAS, Y ELIMINAR CARACTERES CONFLICTIVOS PARA FILESYSTEM
string GestorDirectorios::validarCaracteresEspeciales(string nombreMateria){


    unordered_map<char, char> caracteresDeReemplazo {

        {'á', 'a'},
        {'Á', 'A'},
        {'é', 'e'},
        {'É', 'E'},
        {'í', 'i'},
        {'Í', 'I'},
        {'ó', 'o'},
        {'Ó', 'O'},
        {'ú', 'u'},
        {'Ú', 'U'},
        {'ñ', 'n'},
        {'Ñ', 'N'},
        {'/', '_'}

    };


    for(auto& par : caracteresDeReemplazo){

        ///Replace recibe 4 parámetros: El inicio y el final del string a recorrer, el valor "viejo" a buscar, y el valor "nuevo" a reemplazar
        ///También se podría haber pensado con una matriz de char o 2 vectores paralelos para crear los pares de reemplazo
        replace(nombreMateria.begin(), nombreMateria.end(), par.first, par.second);
    }

    return nombreMateria;

}

///DADA UNA RUTA, BUSCA LOS TIPOS DE ARCHIVOS PARA IR ALMACENANDOLOS. SI ENCUENTRA UNA CARPETA, SE LLAMA A SI MISMA DE FORMA RECURSIVA
void GestorDirectorios::almacenarExtensionesDetectadas(vector <string>& extensiones, vector <int>& contadorDeExtensiones, string ruta){

    for (const auto& entrada : fs::directory_iterator(ruta)) {

        string auxTipoArchivo = entrada.path().extension().string();

        if((is_regular_file(entrada) == true)){

            if(extensionYaDetectada(extensiones,auxTipoArchivo) == false){

                extensiones.push_back(auxTipoArchivo);
                contadorDeExtensiones.push_back(1);
            }
            else{

                contadorDeExtensiones[buscarPosicionExtension(extensiones, auxTipoArchivo)]++;
            }

        }
        else if(is_directory(entrada)){

            almacenarExtensionesDetectadas(extensiones, contadorDeExtensiones, entrada.path().string());
        }
    }

}

///VALIDAMOS SI LA EXTENSION YA FUE ENCONTRADA PREVIAMENTE
bool GestorDirectorios::extensionYaDetectada(vector <string>& extensiones, string tipoArchivo){

    int tam = extensiones.size();

    for(int i = 0; i < tam; i++){

        if(extensiones[i] == tipoArchivo){

            return true;
        }
    }

    return false;

}

///DEVOLVEMOS LA POSICION DE UNA EXTENSION QUE YA SABEMOS FUE ALMACENADA PREVIAMENTE
int GestorDirectorios::buscarPosicionExtension(vector <string>& extensiones, string tipoArchivo){

    int tam = extensiones.size();

    for(int i = 0; i < tam; i++){

        if(extensiones[i] == tipoArchivo){

            return i;
        }
    }

    ///Nunca llegara a este punto, pues nos aseguramos desde antes que la extension exista
    return -1;
}


///DEVUELVE EL TOTAL DE ELEMENTOS COMPLETADOS DE TODOS LOS CUATRIMESTRES, O DE UN CUATRIMESTRE ESPECIFICO SEGUN LA RUTA
int GestorDirectorios::contarTotalElementosCompletados(string ruta){

    int cantElementosCompletados = 0;

    string nombreCarpetasBuscadas = "completado";

    for (const auto& entrada : fs::directory_iterator(ruta)) {

        if((entrada.path().filename() == nombreCarpetasBuscadas) && is_directory(entrada) == true){

            cantElementosCompletados += contarElementosEnDirectorio(entrada.path().string());
        }

        else if(is_regular_file(entrada) == false){

            cantElementosCompletados += contarTotalElementosCompletados(entrada.path().string());
        }
    }

    return cantElementosCompletados;
}

///DEVUELVE EL TOTAL DE ELEMENTOS DE TODOS LOS CUATRIMESTRES, O DE UN CUATRIMESTRE ESPECIFICO SEGUN LA RUTA
int GestorDirectorios::contarTotalElementos(string ruta){

    int cantElementosTotales = 0;

    for (const auto& entrada : fs::directory_iterator(ruta)) {

        if (is_regular_file(entrada)) {

            cantElementosTotales++;

        } else if (is_directory(entrada)) {

            cantElementosTotales += contarTotalElementos(entrada.path().string());
        }
    }

    return cantElementosTotales;
}

int GestorDirectorios::contarTotalElementosPendientes(string ruta){

    int cantElementosCompletados = contarTotalElementosCompletados(ruta);

    int cantElementosTotales = contarTotalElementos(ruta);

    int cantElementosPendientes = cantElementosTotales - cantElementosCompletados;

    return cantElementosPendientes;
}
