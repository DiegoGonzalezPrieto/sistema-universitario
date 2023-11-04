#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "func_csv.h"

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
bool validarCamposObligatoriosVacios(string campo, int nroFila, int nroColumna, vector <string>& errores){

    bool noHuboError = true;

    if(campo == ""){

        string mensajeError = "Error en la columna " + to_string(nroColumna) + ", fila " + to_string(nroFila) + ": ";
        mensajeError += "Este campo es obligatorio, no puede dejarse vacio";

        errores.push_back(mensajeError);

        noHuboError = false;
    }

    return noHuboError;
}


bool validarDuracionCuatrimestre(string campo, int nroFila, int nroColumna, vector <string>& errores){

    int aux;
    bool noHuboErrores = true;

    try{

        aux = stoi(campo);

        if(aux <= 0 || aux > 2){

            string mensajeError = "Error en la columna " + to_string(nroColumna) + ", fila " + to_string(nroFila) + ": ";
            mensajeError += "El valor ingresado debe ser '1' o '2'";

            errores.push_back(mensajeError);

            noHuboErrores = false;

        }
    }
    catch(invalid_argument& e){

        string mensajeError = "Error en la columna " + to_string(nroColumna) + ", fila " + to_string(nroFila) + ": ";
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

            string mensajeError = "Error en la columna " + to_string(nroColumna) + ", fila " + to_string(nroFila) + ": ";
            mensajeError += "El valor ingresado debe ser mayor que 0";

            errores.push_back(mensajeError);

            noHuboErrores = false;

        }
    }
    catch(invalid_argument& e){

        string mensajeError = "Error en la columna " + to_string(nroColumna) + ", fila " + to_string(nroFila) + ": ";
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
