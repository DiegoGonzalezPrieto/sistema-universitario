#include "Sistema.h"

#include <iostream>
#include <vector>
using namespace std;

#include "Menu.h"
#include "func_utiles.h"
#include "func_archivos.h"

Sistema::Sistema() :
    _gestorCarrera("datos/carrera.dat"), _gestorEventos("datos/eventos.dat"), _gestorMaterias("datos/materias.dat"),
    _gestorNotasFinales("datos/notas_finales.dat"), _cargaInicial("carga_inicial.dat"),
    _gestorCsv("archivoImportacion.csv", "datos/materias.dat", "carga_inicial.dat")
{
    //ctor
}

void Sistema::iniciar()
{

    crearDirectoriosEsenciales();


    vector <string> opcMenu = {"Materias", "Cuatrimestres cursados", "Eventos", "Notas finales", "Carrera", "Configuracion"};

    Menu menu(opcMenu, "Sistema de Gestion de Carrera Universitaria");

    int opc;

    bool faltanCargarMaterias = cargaInicial();

    ///Si la carga inicial no esta finalizada
    if(faltanCargarMaterias == true)
    {

        vector <string> opcMenuInicial = {"Carga inicial manual", "Carga inicial mediante archivo csv"};

        Menu menuInicial(opcMenuInicial, "MENU Carga Inicial");

        while(faltanCargarMaterias == true)
        {

            opc = menuInicial.mostrar();

            switch(opc)
            {

                case 0:
                    return;
                    break;
                case 1:
                    _gestorMaterias.iniciarGestorMaterias();
                    break;
                case 2:
                    _gestorCsv.iniciar();
                    break;
                default:
                    break;
            }

            faltanCargarMaterias = cargaInicial();

        }
    }

    /// Una vez finalizada la carga inicial
    while(true)
    {


        opc = menu.mostrar();

        switch(opc)
        {

        case 0:
            return;
            break;
        case 1:
        {
            ///Si la carga inicial de materias ya fue completada

            cout << "1 - Materias cursadas" << endl;
            cout << "2 - Materias del plan de estudio" << endl;
            cout << "Seleccion: ";

            int seleccion = validar<int>("Por favor seleccione una opcion valida: ");
            while(seleccion < 1 || seleccion > 2)
            {

                cout << "Opcion no valida, reingrese nuevamente: ";
                seleccion = validar<int>("Opcion: ");
            }

            switch(seleccion)
            {

            case 1:
                ///LLAMAMOS AL GESTOR CURSADAMATERIA
                break;
            case 2:
                ///LLAMAMOS AL GESTOR MATERIA??? PELIGROSO, PODRIAN MODIFICAR LAS MATERIAS POSTERIOR A LA CARGA INICIAL
                break;
            default:
                break;

            }

            break;
        }
        case 2:
            /// LLAMAMOS AL GESTOR CUATRIMESTRE
            break;
        case 3:
            _gestorEventos.iniciar();
            break;
        case 4:
            _gestorNotasFinales.iniciar();
            break;
        case 5:
            ///COMO QUEREMOS MANEJAR EL GESTOR CARRERA???
            break;
        case 6:
            ///AQUI IRIA LA CONFIGURACION
            break;
        default:
            break;
        }
    }

}

///Si no existe el archivo cargaInicial lo creamos (y suponemos que estamos en esta instancia del programa)
///Si el archivo existe, pero su estado es true, significa que aun faltan cargar materias
///Si devuelve false, el usuario confirmo que finalizo la carga de todas las materias
bool Sistema::cargaInicial()
{

    CargaInicial aux;

    if(_cargaInicial.archivoExiste() == false)
    {

        aux.setEstado(true);
        _cargaInicial.agregarRegistro(aux);
        return true;
    }
    else
    {

        _cargaInicial.leerRegistro(0, aux);

        if(aux.getEstado() == true)
        {

            return true;
        }
        else
        {

            return false;
        }
    }


}

void Sistema::crearDirectoriosEsenciales(){
/*

    filesystem::crearDirectorios("datos");
    crearDirectorios("configuracion");
    crearDirectorios("cursada");
*/
    return;
}
