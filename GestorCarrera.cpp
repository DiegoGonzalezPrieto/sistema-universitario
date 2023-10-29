#include "GestorCarrera.h"
#include "Carrera.h"
#include "Menu.h"
void GestorCarrera::modificarRegistro()
{
    Carrera datosCarrera;

//    if (!archivoCarreraEnCurso.leerRegistro(0, datosCarrera))
//    {
//        _mensajero.mensajeError("No se pudo leer el registro del Archivo Carrera.");
//        return;
//    }

    Menu m({"Nombre de la Universidad","Nombre de la Carrera", "Nombre del Estudiante", "Número de Legajo"},"Seleccione el campo que desea modificar:");
    std::cin.ignore();

    switch (m.mostrar())
        {
        case 0:
            return;
        case 1:
        {
            std::string nuevoNombreUniversidad;
            std::cout << "Ingrese el nuevo nombre de la Universidad: \n";
            std::getline(std::cin, nuevoNombreUniversidad);
            datosCarrera.setNombreUniversidad(nuevoNombreUniversidad);
        }
        break;
        case 2:
        {
            std::string nuevoNombreCarrera;
            std::cout << "Ingrese el nuevo nombre de la Carrera: \n";
            std::getline(std::cin, nuevoNombreCarrera);
            datosCarrera.setNombreCarrera(nuevoNombreCarrera);
        }
        break;
        case 3:
        {
            std::string nuevoNombreEstudiante;
            std::cout << "Ingrese el nuevo nombre del Estudiante: \n";
            std::getline(std::cin, nuevoNombreEstudiante);
            datosCarrera.setNombreEstudiante(nuevoNombreEstudiante);
        }
        break;
        case 4:
        {
            std::string nuevoLegajo;
            std::cout << "Ingrese el nuevo número de Legajo: \n";
            std::getline(std::cin, nuevoLegajo);
            datosCarrera.setLegajo(nuevoLegajo);
        }
        break;
        return;
        }

    if (archivoCarreraEnCurso.modificarRegistro(0, datosCarrera))
        {
            _mensajero.mensajeInformacion("Registro modificado exitosamente.");
        }
    else
        {
            _mensajero.mensajeError("No se pudo modificar el registro.");
        }
}

//void GestorCarrera::asignarDatosDesdeVector(const std::vector<Carrera>& datos)
//{
//    if (!datos.empty())
//        {
//            datosCarrera = datos[0];
//            if (archivoCarreraEnCurso.agregarRegistro(datosCarrera))
//                {
//                    std::cout << "Datos de la carrera asignados exitosamente.\n";
//                }
//        }
//    else
//        {
//            std::cout << "No se pudo cargar la informacion de la carrera correctamente \n";
//        }
//}

void GestorCarrera::cargarManual()
{

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

    std::cout << "Ingrese el numero de Legajo: ";
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
