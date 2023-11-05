#include "GestorCarrera.h"
#include "Carrera.h"
#include "Menu.h"
void GestorCarrera::modificarRegistro()
{


    if (!archivoCarreraEnCurso.leerRegistro(0, _datosCarrera))
   {
       _mensajero.mensajeError("No se pudo leer el registro del Archivo Carrera.");
        return;
  }

    Menu m({"Nombre de la Universidad","Nombre de la Carrera", "Nombre del Estudiante", "Número de Legajo"},"Seleccione el campo que desea modificar:");

    switch (m.mostrar())
        {
        case 0:
            return;
        case 1:
        {
            std::string nuevoNombreUniversidad;
            _mensajero.mensajeInformacion("Ingrese el nuevo nombre de la Universidad: ");
            std::getline(std::cin, nuevoNombreUniversidad);
            _datosCarrera.setNombreUniversidad(nuevoNombreUniversidad);
        }
        break;
        case 2:
        {
            std::string nuevoNombreCarrera;
            _mensajero.mensajeInformacion("Ingrese el nuevo nombre de la Carrera: ");
            std::getline(std::cin, nuevoNombreCarrera);
            _datosCarrera.setNombreCarrera(nuevoNombreCarrera);
        }
        break;
        case 3:
        {
            std::string nuevoNombreEstudiante;
            _mensajero.mensajeInformacion("Ingrese el nuevo nombre del Estudiante: ");
            std::getline(std::cin, nuevoNombreEstudiante);
            _datosCarrera.setNombreEstudiante(nuevoNombreEstudiante);
        }
        break;
        case 4:
        {
            std::string nuevoLegajo;
            _mensajero.mensajeInformacion("Ingrese el nuevo número de Legajo: ");
            std::getline(std::cin, nuevoLegajo);
            _datosCarrera.setLegajo(nuevoLegajo);
        }
        break;
        }

    if (archivoCarreraEnCurso.modificarRegistro(0, _datosCarrera))
        {
            _mensajero.mensajeInformacion("Registro modificado exitosamente.");
        }
    else
        {
            _mensajero.mensajeError("No se pudo modificar el registro.");
        }
}


void GestorCarrera::cargarManual()
{

    _datosCarrera;
    std::string nuevoDato;

    _mensajero.mensajeInformacion("Ingrese el nombre de la Universidad: ");
    std::getline(std::cin, nuevoDato);
    _datosCarrera.setNombreUniversidad(nuevoDato);

    _mensajero.mensajeInformacion("Ingrese el nombre de la Carrera: ");
    std::getline(std::cin, nuevoDato);
    _datosCarrera.setNombreCarrera(nuevoDato);

    _mensajero.mensajeInformacion("Ingrese el nombre del Estudiante: ");
    std::getline(std::cin, nuevoDato);
    _datosCarrera.setNombreEstudiante(nuevoDato);

    _mensajero.mensajeInformacion("Ingrese el numero de Legajo: ");
    std::getline(std::cin, nuevoDato);
    _datosCarrera.setLegajo(nuevoDato);
    if (archivoCarreraEnCurso.crearArchivo() && archivoCarreraEnCurso.agregarRegistro(_datosCarrera))
        {

            _mensajero.mensajeInformacion("Registro agregado exitosamente. ");
        }
    else
        {
             _mensajero.mensajeError( "Error al agregar el primer registro. " );
        }
}

void GestorCarrera::mostrarDatosCarrera(){

archivoCarreraEnCurso.leerRegistro(0,_datosCarrera);

std::cout<<_datosCarrera.toString();
}


