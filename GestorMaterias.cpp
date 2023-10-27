#include <iostream>
using namespace std;

#include "GestorMaterias.h"
#include "Materia.h"
#include "Menu.h"

GestorMaterias::GestorMaterias(string nombre) : archivoMaterias(nombre.c_str())
{
};

bool GestorMaterias::modificarMateria()
{
    Materia datosMateria;

    if (!archivoMaterias.leerRegistro(0, datosMateria))
    {
        cout << "Error al leer el registro del Archivo materias." << endl;
        return false;
    }

std::vector<std::string> opciones = {"Modificar nombre de la materia","Modificar ID de la materia","Modificar IDs de las materias requeridas","Modificar cuatrimestre sugerido","Modificar la duracion de la materia"};
Menu MenuGM(opciones);

switch (MenuGM.mostrar())
{
case 1:
{
    string nuevoNombreMateria;
    cout << "Ingrese el nuevo nombre de la Materia: " << endl;
    std::getline(std::cin, nuevoNombreMateria);
    datosMateria.setNombreMateria(nuevoNombreMateria);
}
break;
case 2:
{
    string nuevoIDmateria;
    cout << "Ingrese el nuevo ID de la materia: " << endl;
    std::getline(std::cin, nuevoIDmateria);
    datosMateria.setIdMateria(nuevoIDmateria);
}
break;
case 3:
{
    string nuevoIDsMateriasRequeridas;
    cout << "Ingrese las nuevas IDs de materias sugeridas: " << endl;
    std::getline(std::cin, nuevoIDsMateriasRequeridas);
    datosMateria.setIdMateriasRequeridas(nuevoIDsMateriasRequeridas);
}
break;
case 4:
{
    string nuevoCuatrimestreSugerido;
    cout << "Ingrese el nuevo cuatrimestre sugerido: "<< endl;
    std::getline(std::cin, nuevoCuatrimestreSugerido);
    datosMateria.setCuatrimestreSugerido(nuevoCuatrimestreSugerido);
}
break;
default:
    cout << "Opcion invalida" << endl;
    return;
}

if (archivoMaterias.modificarRegistro(0, datosMateria))
{
    cout << "Registro modificado exitosamente." << endl;
}
else
{
    cout << "Error al modificar el registro." << endl;
}
}
/*
void GestorCarrera::asignarDatosDesdeVector(const std::vector<Carrera>& datos)
{
    if (!datos.empty())
    {
        datosCarrera = datos[0];
        if (archivoCarreraEnCurso.agregarRegistro(datosCarrera))
        {
            std::cout << "Datos de la carrera asignados exitosamente.\n";
        }
    }
    else
    {
        std::cout << "No se pudo cargar la informacion de la carrera correctamente \n";
    }
}


void GestorCarrera::cargarManual() {



Carrera datosCarrera;
std::string nuevoDato;

std::cout << "Ingrese el nombre de la Universidad: ";
std::getline(std::cin, nuevoDato);
datosCarrera.setNombreUniversidad(nuevoDato);

std::cout << "Ingrese el nombre de la Carrera: ";
std::getline(std::cin, nuevoDato);
datosCarrera.setNombreCarrera(nuevoDato);

std::cout << "Ingrese el nombre del Estudiante: ";
std::getline(std::cin, nuevoDato);
datosCarrera.setNombreEstudiante(nuevoDato);

std::cout << "Ingrese el n�mero de Legajo: ";
std::getline(std::cin, nuevoDato);
datosCarrera.setLegajo(nuevoDato);
if (archivoCarreraEnCurso.crearArchivo() && archivoCarreraEnCurso.agregarRegistro(datosCarrera))
{

    std::cout << "Registro agregado exitosamente.\n";
}
else
{
    std::cout << "Error al agregar el primer registro.\n";
}
}
*/
