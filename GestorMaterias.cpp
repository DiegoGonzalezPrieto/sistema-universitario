#include <iostream>
#include <vector>
using namespace std;

#include "GestorMaterias.h"
#include "Materia.h"
#include "Menu.h"


GestorMaterias::GestorMaterias(std::string nombre) : archivoMaterias(nombre) {}

void GestorMaterias::CargarMaterias()
{
    int opCarga ;
    cout << "Cómo desea realizar la carga de materias?" << endl;
    cout << "1 - Manual" << endl;
    cout << "2 - Mediante un archivo" << endl;
    cin >> opCarga ;

    switch(opCarga)
    {
    case 1:

        while (true)
        {
            if (AgregarUnaMateria())
            {
                cout << "Materia agregada correctamente" << endl ;

                char op ;
                cout << "Desea agregar otra materia? (S/N)" << endl ;
                cin >> op ;
                if (op == 'N' || op == 'n')
                {
                    break ;
                }
            }
            else
            {
                msj.mensajeError("No se pudo agregar la materia");
                break ;
            }
        }
        break ;
    case 2:
        /// DESARROLLO DE CARGA A TRAVES DE ARCHIVO
        break;
    default:
        cout << "Opcion ingresada no valida. Por favor, ingrese 1 o 2" << endl ;
        break ;
    }
}


bool GestorMaterias::AgregarUnaMateria()
{
    if (!archivoMaterias.archivoExiste())
    {
        if (!archivoMaterias.crearArchivo())
        {
            msj.mensajeError("El archivo no existe y no puede ser creado ") ;
            return false ;
        }
    }

    Materia datosMateria;
    string datoString;
    int datoInt ;

    cout << "Ingrese el nombre de la Materia: ";
    getline(cin, datoString);
    datosMateria.setNombreMateria(datoString);

    cout << "Ingrese el ID de la Materia: ";
    getline(cin, datoString);
    datosMateria.setIdMateria(datoString);

    cout << "Ingrese la cantidad de materias requeridas: ";
    cin >> datoInt;

    if (datoInt>0)
    {
        seleccionarMateriasRequeridas(datoInt) ;
    }

    cout << "Ingrese el cuatrimestre sugerido: ";
    cin >> datoInt ;
    datosMateria.setCuatrimestreSugerido(datoInt) ;

    cout << "Ingrese la cantidad de cuatrimestres de duracion: " ;
    cin >> datoInt ;
    datosMateria.setCuatrimestreDeDuracion(datoInt) ;


    if (archivoMaterias.agregarRegistro(datosMateria))
    {
        return true ;
    }
    else
    {
        msj.mensajeError("Error al agregar el registro en el archivo.") ;
        return false ;
    }

};


void GestorMaterias::seleccionarMateriasRequeridas(int cant) ///RECIBE UN INT QUE ES LA CANTIDAD DE MATERIAS REQUERIDAS A SELECCIONAR.
{

    ///LEO EL ARCHIVO Y MUESTRO LOS NOMBRES DE TODAS LAS MATERIAS CON UN NUMERO COMO OPCION A SELECCIONAR.

    int cantMat = archivoMaterias.contarRegistros() ;
    if (archivoMaterias.leerRegistros(registros))
    {
        for (int i=0; i<cantMat; i++)
        {
            if (archivoMaterias.leerRegistro(i,datosMateria))
            {
                cout << i+1 << ".Materia: " << datosMateria.getNombreMateria() << endl ;
            }
            else
            {
                msj.mensajeError("No se pudo mostrar las materias") ;
            }
        }

    }
    else
    {
        msj.mensajeError ("No se pudo mostrar las materias");
        return ;
    }

    /// PIDO INGRESAR LOS NUMEROS QUE CORRESPONDEN A LAS MATERIAS REQUERIDAS

    string nuevoID;
    int op ;
    cout << "Seleccione las materias requeridas" << endl ;
    for (int i=0; i<cant; i++) ///ITERO POR LA CANTIDAD DE MATERIAS REQUERIDAS QUE EL USUARIO HABIA INGRESADO PREVIAMENTE
    {
        cin >> op ;
        if (op >= 1 && op <= cantMat) ///VALIDO EL NUMERO
        {

            if (archivoMaterias.leerRegistro(op-1,datosMateria)) ///ABRO EL REGISTRO DE LA MATERIA QUE EL USUARIO SELECCIONO
            {
                nuevoID = datosMateria.getIdMateria() ; ///COPIO EL ID DE ESA MATERIA SELECCIONADA
                datosMateria.setIdMateriasRequeridas(i, nuevoID); ///SETEO EL ID COMO ID DE MATERIA REQUERIDA
            }
        }
        else
        {
            msj.mensajeError("Ingreso no valido. Por favor, ingrese un numero valido.");
        }

    }
}

void GestorMaterias::modificarMaterias()
{
    while (true)
    {
        if (modificarUnaMateria())
        {
            cout << "Materia modificada correctamente" << endl ;
            char op ;
            cout << "Desea modificar otra materia? (S/N)" << endl ;
            cin >> op ;
            if (op == 'N' || op == 'n')
            {
                break ;
            }
        }
        else
        {
            msj.mensajeError("No se logro modificar la materia") ;
            break ;
        }


    }
}


bool GestorMaterias::buscarMateria(std::string& IDmateria, Materia& datosMateria, int &pos)
{
    archivoMaterias.leerRegistros(registros);
    int tam = archivoMaterias.contarRegistros() ;

    for (int i = 0; i < tam; i++)
    {
        if (registros[i].getIdMateria() == IDmateria)
        {

            datosMateria = registros[i];
            pos = i ;
            return true;
        }
    }

    return false;

}

bool GestorMaterias::modificarUnaMateria()
{

    string IDmateria;

    cout << "Ingrese el ID de la materia a modificar: ";
    getline(cin, IDmateria);

    int pos ;

    if (!buscarMateria(IDmateria, datosMateria, pos))
    {
        msj.mensajeError("No se encontró la materia con el ID proporcionado.");
        return false;
    }

    std::vector<std::string> opciones =
    {
        "Nombre de la materia",
        "ID de la materia",
        "IDs de las materias requeridas",
        "Cuatrimestre sugerido",
        "Duracion de la materia"
    };

    Menu MenuMod(opciones,"Seleccione qué dato desea modificar: ");

    while (true)
    {

        switch (MenuMod.mostrar())
        {
        case 0:
        {
            break ;
        }
        case 1:
        {
            string nuevoNombreMateria;
            cout << "Ingrese el nuevo nombre de la Materia: ";
            getline(cin, nuevoNombreMateria);
            datosMateria.setNombreMateria(nuevoNombreMateria);
        }
        break;
        case 2:
        {
            string nuevoIDmateria;
            cout << "Ingrese el nuevo ID de la materia: ";
            getline(cin, nuevoIDmateria);
            datosMateria.setIdMateria(nuevoIDmateria);
        }
        break;
        case 3:
        {
            int cant;
            cout << "Ingrese la cantidad de IDs de materias requeridas: ";
            cin >> cant;
            seleccionarMateriasRequeridas(cant) ;

        }
        break;
        case 4:
        {
            int nuevoCuatrimestreSugerido;
            cout << "Ingrese el nuevo cuatrimestre sugerido: ";
            cin >> nuevoCuatrimestreSugerido;
            datosMateria.setCuatrimestreSugerido(nuevoCuatrimestreSugerido);
        }
        }
        char op ;
        cout << "Desea modificar otro dato de esta materia? (S/N)" << endl ;
        cin >> op ;
        if (op == 'N' || op == 'n')
        {
            break ;
        }
    }

    if (archivoMaterias.modificarRegistro(pos, datosMateria))
    {
        return true;
    }
    else
    {
        cout << "Error al modificar el registro en el archivo." << endl;
        return false;
    }
}

void GestorMaterias::mostrarMaterias()
{
    if (archivoMaterias.leerRegistros(registros))
    {
        if (registros.empty())
        {
            msj.mensajeError("No hay materias para mostrar.") ;
        }
        else
        {
            int cantMat = archivoMaterias.contarRegistros() ;
            for (int i=0; i<cantMat; i++)
            {

                if (archivoMaterias.leerRegistro(i,datosMateria))
                {
                    cout << datosMateria.toString();
                }
                else
                {
                    msj.mensajeError("No se pudo leer el registro") ;
                }
            }
        }
    }

    else
    {
        cout << "Error al leer los registros del archivo." << endl;
    }
}
