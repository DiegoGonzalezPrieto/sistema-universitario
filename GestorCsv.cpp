#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#include "GestorCsv.h"
#include "func_csv.h"
#include "Menu.h"


using namespace std;

GestorCsv::GestorCsv(string archivoImportacion, string archivoMateria, string archivoCargaInicial) :
_auxArchivo(archivoMateria), _nombreArchivo(archivoImportacion), _cargaInicial(archivoCargaInicial)
{

}

GestorCsv::~GestorCsv()
{
    //dtor
}


void GestorCsv::iniciar(){


    vector<string> opcMenu = {"Instrucciones", "Generar archivo modelo de importacion CSV", "Importar datos mediante archivo modelo CSV ", "Mostrar datos importados", "Grabar datos en el sistema"};
    vector<Materia> materias;

    Menu menu(opcMenu);

    int opcion;

    while(true){


        opcion = menu.mostrar();

        switch(opcion){

        case 0:
            return;
        case 1:
            mostrarInstrucciones();
            break;
        case 2:
            if(generarArchivoModelo() == true){
                cout << "Los datos se han escrito correctamente en " << _nombreArchivo << endl;
            }
            else{
                cout << "Error al generar el archivo modelo" << endl;
            }
            break;

        case 3:
            if(importarArchivoCsv(materias) == true){

                if(materias.size() > 0){
                    cout << "Se han importado los datos en " << _nombreArchivo << endl;
                }
                else{
                    cout << "El archivo '" << _nombreArchivo << "' no tiene datos para importar" << endl;
                }
            }
            break;
        case 4:
            mostrarMaterias(materias);
            break;
        case 5:
            {
                if(grabarDatosImportados(materias) == true){
                    cout << "Se han grabado todos los registros cargados en el sistema" << endl;
                    CargaInicial datos;
                    _cargaInicial.leerRegistro(0,datos);
                    datos.aumentarcontadorDatosCargados();
                    _cargaInicial.modificarRegistro(0,datos);

                }
                cout << "Carga inicial de materias finalizada" << endl;
                return;
                break;
            }
        default:
            break;
        }


    }

}

void GestorCsv::mostrarInstrucciones(){

    cout << "El sistema le brinda la posibilidad de poder importar todas las materias mediante un archivo CSV" << endl;
    cout << "El mismo podra obtenerlo seleccionando la opcion correspondiente en el menu" << endl;
    cout << "Debe tener en cuenta las siguientes consideraciones en caso de que opte por este metodo de carga de las materias: " << endl << endl;
    cout << "- El nombre del archivo no debe ser modificado, como tampoco se debe cambiar el formato del archivo al momento de guardarlo" << endl;
    cout << "- El archivo debe encontrarse en el mismo directorio en el que es creado, caso contrario no sera posible importar los datos" << endl;
    cout << "- No deben alterarse las columnas establecidas por defecto" << endl;
    cout << "- Debe completar los datos respetando las columnas" << endl << endl;

    cin.get();

    cout << endl << endl;
    cout << "Acerca del uso del archivo modelo: " << endl;
    cout << "Los campos listados como 'Obligatorio' se deben completar (no admite campos vacios)" << endl << endl << endl;

    cin.get();

    cout << endl << endl;
    cout << "* Columna 'Nombre' (Obligatorio) corresponde al nombre de la materia" << endl << endl;
    cout << "* Columna 'Id Materia (Obligatorio) corresponde al ID que identifica a la materia" << endl << endl;
    cout << "* Columna 'Cuatrimestre Sugerido' corresponde al cuatrimestre en el que se cursaria la materia siguiendo el plan de estudios.\n  Se debe completar un numero entero" << endl << endl;
    cout << "* Columna 'Duracion Cuatrimestre (Obligatorio). Se debe completar '1' si la materia es cuatrimestral o '2' si es anual" << endl << endl;
    cout << "* Columna 'Id Materias Correlativas'. En caso de tener correlativas para cursarse, se deben asignar las ID en esta columna separadas por una coma ','\n";
    cout << "Muy importante no colocar espacios en blanco al momento de cargar las ID materias correlativas, caso contrario será informado como un error" << endl << endl;

    cout << "Si se detecta alguna discrepancia, se cancelara la importacion y se emitira un listado de errores, con el objetivo que puedan ser corregidos" << endl;

    cin.get();
}


///Creamos los encabezados del archivo CSV, de tal modo que si lo abrimos con una planilla
///de cálculo, sabemos a qué columna corresponde cada campo

///Como decido abrirlo en una planilla de cálculo, una decisión intuitiva para su carga
///es utilizar el delimitador punto y coma, ya que las planillas de cálculo abrirán el archivo
///y separarán los campos en casillas en vez de tenerlo en una sola línea
bool GestorCsv::generarArchivoModelo(){

    ofstream archivo(_nombreArchivo);

    if (archivo.is_open() == false){

        cout << "Error al crear el archivo";

        return false;
    }

    archivo << "Nombre;Id Materia;";

    archivo << "Cuatrimestre Sugerido;Duracion Cuatrimestre;";

    archivo << "Id Materia Correlativa";

    archivo.close();

    return true;
}

bool GestorCsv::importarArchivoCsv(vector <Materia>& datos){


    vector <string> errores; /// Almacenaremos los errores en caso de haber

    ifstream archivoImportacion;
    archivoImportacion.open(_nombreArchivo.c_str());

    if (archivoImportacion.is_open() == false){

        cout << "Error al leer el archivo. Verifique que el archivo exista, y que el nombre sea " << _nombreArchivo <<  endl;

        return false;
    }

    string linea = "";

    getline(archivoImportacion, linea); /// Tomamos la linea con los nombres de las columnas del archivo

    if(validarColumnas(linea, errores) == false){

        mostrarErrores(errores);
        archivoImportacion.close();
        return false;
    }

    bool noHuboErrores = true;
    int cantErrores = 0;
    int nroFila = 2;


    /// Si se completaron datos fuera de cualquier columna, como romperia toda la estructura, evitamos que se procese el archivo
    if(validarDatosFueraDeLasColumnas(linea, errores) == false){

        mostrarErrores(errores);
        archivoImportacion.close();
        return false;

    }

    linea = "";

    while(getline(archivoImportacion, linea)){

        int nroColumna = 1;

        string nombreMateria;
        string idMateria;
        string aux = "";
        int camposEnteros;

        Materia reg;

        ///Guarda la linea completa del archivo csv, para que luego la recorramos según el delimitador punto y coma, o coma
        stringstream inputString(linea);

        ///Obtenemos el nombre en un string, y lo almacenamos en el objeto
        getline(inputString, nombreMateria, ';');

        if(validarCamposObligatoriosVacios(nombreMateria, nroFila, nroColumna, errores, datos) != false){

            reg.setNombreMateria(nombreMateria.c_str());
        }
        else{

            noHuboErrores = false;
            cantErrores++;
        }


        nroColumna++;

        ///Obtenemos el ID de la materia en un string, y lo almacenamos en el objeto
        getline(inputString, idMateria, ';');

        if(validarCamposObligatoriosVacios(idMateria, nroFila, nroColumna, errores, datos) != false){

            reg.setIdMateria(idMateria.c_str());
        }
        else{

            noHuboErrores = false;
            cantErrores++;
        }


        nroColumna++;

        ///Obtenemos el cuatrimestre sugerido en un string, lo convertimos a int y lo almacenamos en el objeto
        getline(inputString, aux, ';');

        if(validarCuatrimestreSugerido(aux, nroFila, nroColumna, errores) != false){

            camposEnteros = atoi(aux.c_str());
            reg.setCuatrimestreSugerido(camposEnteros);
            aux = "";
        }
        else{

            noHuboErrores = false;
            cantErrores++;
        }


        nroColumna++;

        ///Obtenemos la duración de cuatrimestre en un string, lo convertimos a int y lo almacenamos en el objeto
        getline(inputString, aux, ';');


        if(validarDuracionCuatrimestre(aux, nroFila, nroColumna, errores) != false){

            camposEnteros = atoi(aux.c_str());
            reg.setCuatrimestreDeDuracion(camposEnteros);

        }
        else{

            noHuboErrores = false;
            cantErrores++;
        }

        nroColumna++;

        vector<string> auxCorrelativas;
        bool coincidencias = false;

        for(int i = 0; i < 10; i++){


            getline(inputString, aux, ',');

            if(validarEspaciosEnBlanco(aux, nroFila, nroColumna, errores) != true){

                cantErrores++;
            }

            if(validarSiYaSeCargaronIdMateriasRequeridas(aux, nroFila, nroColumna, errores, datos) != true){

                cantErrores++;
            }

            if(validarIdMateriasRequeridasNoRepetidas(aux, nroFila, nroColumna, errores, auxCorrelativas) != true){

                cantErrores++;
            }

            if((coincidencias == false) && (validarIdMateriasRequeridasNoSeanIdMateriaPropia(idMateria,nroFila, nroColumna, errores, auxCorrelativas)) != true){

                cantErrores++;
                coincidencias = true;
            }

            reg.setIdMateriasRequeridas(i, aux.c_str());

            aux = "";
        }

        auxCorrelativas.clear();

        linea = "";

        if(noHuboErrores == true){

            datos.push_back(reg);
        }

        nroFila++;


    }



    if(cantErrores > 0){

        cout << "Se han encontrado los siguientes errores:" << endl << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
        mostrarErrores(errores);
        cout << "-----------------------------------------------------------------------------------" << endl<<endl;
        cout << "No se han importado los datos. En total se detectaron " << cantErrores << " errores" << endl;
        archivoImportacion.close();

        datos.clear();

        return false;


    }


    archivoImportacion.close();

    return true;
}

bool GestorCsv::mostrarMaterias(const std::vector <Materia>& datos){

    int tam = datos.size();

    if (tam == 0){

        cout << "No hay datos cargados en el sistema" << endl;
        return false;
    }

    for (int i = 0; i < tam; i++) {

        Materia reg;

        reg = datos[i];

        cout << "---------------------------------------------------------------" << endl << endl;

        cout << "Nombre: " << reg.getNombreMateria() << endl;
        cout << "ID: " << reg.getIdMateria() << endl;
        cout << "idMateriasRequeridas: ";

        for (int i = 0; i < 10; i++) {
            cout << reg.getIdMateriasRequeridas(i) << " ";
        }

        cout << endl << "Cuatrimestre Sugerido: " << reg.getCuatrimestreSugerido() << endl;
        cout << "Cuatrimestres de Duracion: " << reg.getCuatrimestreDeDuracion() << endl;
    }

    return true;
}

bool GestorCsv::grabarDatosImportados(const vector <Materia>& datos){

    int tam = datos.size();

    if(tam == 0){

        cout << "No hay datos para ser grabados. Verifique en el menu los datos e intente nuevamente" << endl;
        return false;
    }

    bool noHuboError = true;

    for(int i = 0; i < tam; i++){

        if(_auxArchivo.agregarRegistro(datos[i]) == false){

            noHuboError = false;
        }
    }

    return noHuboError;


}
