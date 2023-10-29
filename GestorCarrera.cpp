#include "GestorCarrera.h"
#include "Carrera.h"
void GestorCarrera::modificarRegistro()
{
    Carrera datosCarrera;

    if (!archivoCarreraEnCurso.leerRegistro(0, datosCarrera))
    {
        std::cout << "Error al leer el registro del Archivo Carrera.\n";
        return;
    }

    int opcion;
    std::cout << "Seleccione el campo que desea modificar:\n";
    std::cout << "1. Nombre de la Universidad\n";
    std::cout << "2. Nombre de la Carrera\n";
    std::cout << "3. Nombre del Estudiante\n";
    std::cout << "4. Número de Legajo\n";

    std::cin >> opcion;
    std::cin.ignore();

    switch (opcion)
    {
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
    default:
        std::cout << "Opción invalida.\n";
        return;
    }

    if (archivoCarreraEnCurso.modificarRegistro(0, datosCarrera))
    {
        std::cout << "Registro modificado exitosamente.\n";
    }
    else
    {
        std::cout << "Error al modificar el registro.\n";
    }
}

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

    std::cout << "Ingrese el numero de Legajo: ";
    std::getline(std::cin, nuevoDato);
    datosCarrera.setLegajo(nuevoDato);
    if (archivoCarreraEnCurso.crearArchivo() && archivoCarreraEnCurso.agregarRegistro(datosCarrera)) {

        std::cout << "Registro agregado exitosamente.\n";
    } else {
        std::cout << "Error al agregar el primer registro.\n";
    }
}
