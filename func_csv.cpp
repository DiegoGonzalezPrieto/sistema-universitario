#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "func_csv.h"
#include "func_utiles.h"
#include "Materia.h"

using namespace std;

bool validarColumnas(string lineaColumnas, vector <string>& errores){

    /// LineaColumnas tiene el dato obtenido del csv, lo iremos separando segun el delimitador y luego
    /// Corroboraremos que no se hayan modificado los nombres, o alterado la cantidad de columnas

    vector<string> titulosEsperados = {"Nombre", "Id Materia", "Cuatrimestre Sugerido", "Duracion Cuatrimestre", "Id Materia Correlativa"};
    vector<string> titulosEncontrados;

    bool noHuboError = true;

    string casillero;

    string mensajeError = "";


    stringstream inputString(lineaColumnas);

    while(getline(inputString, casillero, ';')){


        titulosEncontrados.push_back(casillero);
    }


    if(titulosEncontrados.size() == titulosEsperados.size()){

        int tam = titulosEsperados.size();

        for(int i = 0; i < tam; i++){

            if(titulosEsperados[i] != titulosEncontrados[i]){

                noHuboError = false;

                mensajeError = "Error en columna " + to_string(i+1) + ": ";
                mensajeError += "Falta o se ha modificado la columna '" + titulosEsperados[i] + "'";

                errores.push_back(mensajeError);

            }

        }
    }


    return noHuboError;
}

/// Variante para los campos que son string (nombreMateria, idMateria)
bool validarCamposObligatoriosVacios(string campo, int nroFila, int nroColumna, vector <string>& errores, vector <Materia>& datos){

    bool noHuboError = true;

    if(campo == ""){

        string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
        mensajeError += "Este campo es obligatorio, no puede dejarse vacio";

        errores.push_back(mensajeError);

        noHuboError = false;
    }


    if(nroColumna == 1){

        if(validarNombreUnico(campo, nroFila, nroColumna, errores, datos) == false){

            noHuboError = false;
        }

    }

    else if(nroColumna == 2){

        if(validarIdMateriaUnico(campo, nroFila, nroColumna, errores, datos) == false){

            noHuboError = false;
        }
    }


    return noHuboError;
}


bool validarDuracionCuatrimestre(string campo, int nroFila, int nroColumna, vector <string>& errores){

    int aux;
    bool noHuboErrores = true;

    try{

        aux = stoi(campo);

        if(aux <= 0 || aux > 2){

            string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
            mensajeError += "El valor ingresado debe ser '1' o '2'";

            errores.push_back(mensajeError);

            noHuboErrores = false;

        }
    }
    catch(invalid_argument& e){

        string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
        mensajeError += "En este campo se espera que se complete un valor numerico entero";

        errores.push_back(mensajeError);

        noHuboErrores = false;

    }

    return noHuboErrores;

}

/// Variante para los datos que son int
bool validarCuatrimestreSugerido(string campo, int nroFila, int nroColumna, vector <string>& errores){

    int aux;
    bool noHuboErrores = true;

    try{

        aux = stoi(campo);

        if(aux <= 0){

            string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
            mensajeError += "El valor ingresado debe ser mayor que 0";

            errores.push_back(mensajeError);

            noHuboErrores = false;

        }
    }
    catch(invalid_argument& e){

        string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
        mensajeError += "En este campo se espera que se complete un valor numerico entero";

        errores.push_back(mensajeError);

        noHuboErrores = false;

    }

    return noHuboErrores;

}

///Recibe el vector de errores ya cargado, y muestra la totalidad de los mismos
void mostrarErrores(const vector <string>& errores){

    int tam = errores.size();

    for(int i = 0; i < tam; i++){

        cout << errores[i] << endl;
    }

}


bool validarNombreUnico(const std::string nombreMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <Materia>& datos){

    int cantRegistros = datos.size();

    for(int i = 0; i< cantRegistros; i++){

        if(strcmp(datos[i].getNombreMateria().c_str(), nombreMateria.c_str()) == 0){

            string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
            mensajeError += "Ya se ha cargado previamente este nombre de materia, por favor revise el archivo";

            errores.push_back(mensajeError);

            return false;
        }

    }

    return true;
}

bool validarIdMateriaUnico(const std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <Materia>& datos){

    int cantRegistros = datos.size();


    for(int i = 0; i< cantRegistros; i++){

        if(strcmp(datos[i].getIdMateria().c_str(), idMateria.c_str()) == 0){

            string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
            mensajeError += "Ya se ha cargado previamente este ID de materia, por favor revise el archivo";

            errores.push_back(mensajeError);

            return false;
        }

    }

    return true;


}


bool validarSiYaSeCargaronIdMateriasRequeridas(const std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <Materia>& datos){


    int cantRegistros = datos.size();
    bool noHuboErrores = true;
    bool coincidencias = false;

    ///Significa que no se cargaron IDCorrelativa, no hay validaciones por hacer
    if(strcmp(idMateria.c_str(), "") == 0){
        return true;
    }


    for(int i = 0; i < cantRegistros; i++){

        if(strcmp(datos[i].getIdMateria().c_str(), idMateria.c_str()) == 0){

            coincidencias = true;
        }
    }

    /*
    for(int i = 0; i < cantRegistros; i++){

        for(int j = 0; j < 10; j++){

            if(strcmp(datos[j].getIdMateriasRequeridas(j).c_str(), idMateria.c_str()) == 0){

                coincidencias = true;

            }

        }
    }
    */
    if(coincidencias == false){

        string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
        mensajeError += "No se cargo previamente la materia con la ID '" + idMateria + "'";

        errores.push_back(mensajeError);

        noHuboErrores = false;
    }



    return noHuboErrores;
}

bool validarDatosFueraDeLasColumnas(string linea, vector<string>& errores){

    int cantColumnas = 0;
    string casillero;

    stringstream inputString(linea);

    while(getline(inputString, casillero, ';')){

        cantColumnas++;
    }

    if(cantColumnas == 5){

        return true;
    }
    else{

        string mensajeError = "Error en el archivo: Se han agregado datos por fuera de las columnas establecidas. ";
        mensajeError += "Por favor, verifique los datos cargados e intente nuevamente";

        errores.push_back(mensajeError);

        return false;
    }

}

bool validarIdMateriasRequeridasNoRepetidas(std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <std::string>& auxCorrelativas){

    //////Significa que no se cargaron IDCorrelativa, no hay validaciones por hacer
    if(strcmp(idMateria.c_str(), "") == 0){

        return true;
    }

    bool noHuboErrores = true;

    auxCorrelativas.push_back(idMateria);

    int cant = auxCorrelativas.size();

    ///Recorro cant-1 pues cant equivale al ultimo id cargado, y no queremos compararlo consigo mismo
    for(int i = 0; i < cant-1; i++){

        if(strcmp(auxCorrelativas[i].c_str(), idMateria.c_str()) == 0){

            noHuboErrores = false;
        }

    }

    if(noHuboErrores == false){

        string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
        mensajeError += "La ID de la materia '" + idMateria + "' esta repetida, por favor verifique los datos";

        errores.push_back(mensajeError);
    }

    return noHuboErrores;

}

bool validarIdMateriasRequeridasNoSeanIdMateriaPropia(string idMateria, int nroFila, int nroColumna, vector <string>& errores, vector <string>& auxCorrelativas){


    //////Significa que no se cargaron IDCorrelativa, no hay validaciones por hacer
    if(strcmp(idMateria.c_str(), "") == 0){

        return true;
    }

    bool noHuboErrores = true;

    int cant = auxCorrelativas.size();


    for(int i = 0; i < cant; i++){

        if(strcmp(auxCorrelativas[i].c_str(), idMateria.c_str()) == 0){

            noHuboErrores = false;

        }

    }

    if(noHuboErrores == false){

        string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
        mensajeError += "Una ID materia requerida no puede coincidir con el ID de la materia propiamente a cargar";

        errores.push_back(mensajeError);
    }

    return noHuboErrores;
}

bool validarEspaciosEnBlanco(std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores){

    if(strcmp(idMateria.c_str(), "") == 0){

        return true;
    }

    bool noHuboErrores = true;

    char aux[10];
    cargarCadenaConString(idMateria, aux, 10);

    if(aux[0] == ' '){

        string mensajeError = "Error en la fila " + to_string(nroFila) + ", columna " + to_string(nroColumna) + ": ";
        mensajeError += "No deben dejarse espacios en blanco al momento de separar las ID de las materias requeridas";

        errores.push_back(mensajeError);

        noHuboErrores = false;
    }



    return noHuboErrores;
}
