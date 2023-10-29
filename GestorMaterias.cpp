#include <iostream>
#include <vector>
using namespace std;

#include "GestorMaterias.h"
#include "Materia.h"
#include "Menu.h"

GestorMaterias::GestorMaterias(string nombre) : archivoMaterias(nombre) {}

void GestorMaterias::CargarMaterias()
{

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
            cout << "No se pudo agregar la materia" << endl ;
            break ;
        }


    }
}

bool GestorMaterias::AgregarUnaMateria()
{

    if (!archivoMaterias.archivoExiste() && !archivoMaterias.crearArchivo())
    {
        cout << "El archivo no existe y no puede ser creado " << endl ;
        return false ;
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

    for (int i = 0; i < datoInt; i++) {
        cout << "Ingrese el ID de una materia requerida: ";
        getline(cin, datoString);
        datosMateria.setIdMateriasRequeridas(i, datoString);
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
    cout << "Error al agregar el registro en el archivo." << endl;
        return false ;
    }

};

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
            cout << "No se logro modificar la materia" << endl ;
            break ;
        }


    }
}


bool GestorMaterias::buscarMateria(const std::string& IDmateria, Materia& datosMateria)
{
    std::vector<Materia> registro;
    archivoMaterias.leerRegistros(registro);

    for (size_t i = 0; i < registro.size(); i++)
    {
        if (registro[i].getIdMateria() == IDmateria)
        {
            datosMateria = registro[i];
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

    Materia datosMateria;
    if (!buscarMateria(IDmateria, datosMateria))
    {
        cout << "No se encontró la materia con el ID proporcionado." << endl;
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

    Menu MenuMod(opciones);

    while (true)
    {
        cout << "Seleccione qué dato desea modificar: " << endl;
        switch (MenuMod.mostrar())
        {
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
            cin.ignore();
            string nuevoIDsMateriasRequeridas;
            cout << "Ingrese las nuevas IDs de materias requeridas: ";
            getline(cin, nuevoIDsMateriasRequeridas);

        }
        break;
        case 4:
        {
            int nuevoCuatrimestreSugerido;
            cout << "Ingrese el nuevo cuatrimestre sugerido: ";
            cin >> nuevoCuatrimestreSugerido;
            datosMateria.setCuatrimestreSugerido(nuevoCuatrimestreSugerido);
        }
        break;
        }
    }

    if (archivoMaterias.modificarRegistro(0, datosMateria))
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

    std::vector<Materia> registros;


    if (archivoMaterias.leerRegistros(registros))
    {
        if (registros.empty())
        {
            cout << "No hay materias para mostrar." << endl;
        }
        else
        {
            cout << "Listado de materias:" << endl;

            for (const Materia& materia : registros)
            {
                cout << "ID: " << materia.getIdMateria() << endl;
                cout << "Nombre: " << materia.getNombreMateria() << endl;
                cout << "IDs de materias requeridas: ";
                for (int i = 0; i < CANTMATERIAS; i++) {
                    const std::string IDRequerida = materia.getIdMateriasRequeridas(i);
                    if (!IDRequerida.empty()) {
                        cout << IDRequerida << " ";
                    }
                }
                cout << endl;
                cout << "Cuatrimestre sugerido: " << materia.getCuatrimestreSugerido() << endl ;
                cout << "Cuatrimestres de duracion: " << materia.getCuatrimestreDeDuracion() << endl ;

                cout << endl;
            }
        }
    }
    else
    {
        cout << "Error al leer los registros del archivo." << endl;
    }
}
