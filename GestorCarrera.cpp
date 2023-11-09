#include "GestorCarrera.h"
#include "Carrera.h"
#include "Menu.h"
#include "func_utiles.h"
void GestorCarrera::modificarRegistro()
{


    if (!archivoCarreraEnCurso.leerRegistro(0, _datosCarrera))
   {
       _mensajero.mensajeError("No se pudo leer el registro del Archivo Carrera.");
        return;
  }

    Menu m({"Nombre de la Universidad","Nombre de la Carrera", "Nombre del Estudiante", "Numero de Legajo"},"Seleccione el campo que desea modificar:");

    switch (m.mostrar())
        {
        case 0:
            return;
        case 1:
        {
            std::string nuevoNombreUniversidad;
            std::cout<<"Ingrese el nuevo nombre de la Universidad: ";
            std::getline(std::cin, nuevoNombreUniversidad);
            _datosCarrera.setNombreUniversidad(nuevoNombreUniversidad);
        }
        break;
        case 2:
        {
            std::string nuevoNombreCarrera;
            std::cout<<"Ingrese el nuevo nombre de la Carrera: ";
            std::getline(std::cin, nuevoNombreCarrera);
            _datosCarrera.setNombreCarrera(nuevoNombreCarrera);
        }
        break;
        case 3:
        {
            std::string nuevoNombreEstudiante;
            std::cout<<"Ingrese el nuevo nombre del Estudiante: ";
            std::getline(std::cin, nuevoNombreEstudiante);
            _datosCarrera.setNombreEstudiante(nuevoNombreEstudiante);
        }
        break;
        case 4:
        {
            std::string nuevoLegajo;
            std::cout<<"Ingrese el nuevo numero de Legajo: ";
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

    std::cout<<"Ingrese el nombre de la Universidad: ";
    std::getline(std::cin, nuevoDato);
    _datosCarrera.setNombreUniversidad(nuevoDato);

    std::cout<<"Ingrese el nombre de la Carrera: ";
    std::getline(std::cin, nuevoDato);
    _datosCarrera.setNombreCarrera(nuevoDato);

    std::cout<<"Ingrese el nombre del Estudiante: ";
    std::getline(std::cin, nuevoDato);
    _datosCarrera.setNombreEstudiante(nuevoDato);

    std::cout<<"Ingrese el numero de Legajo: ";
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

void GestorCarrera::iniciar()
{
    bool a = true;
    while (a) {
        Menu menuiniciador({"Cargar los datos de la universidad y la carrera", "Modificar datos de la universidad o carrera", "Mostrar los datos de la universidad o carrera"}, "Gestionar informacion de la Carrera y la Universidad");

        switch (menuiniciador.mostrar()) {
            case 0:
                a = false;
                return;
            case 1: {
                if(!archivoCarreraEnCurso.archivoExiste()&& !archivoCarreraEnCurso.contarRegistros()){
                cargarManual();
                }
                else {
                    std::cout<<"> Ya realizó el ingreso de los datos, si deseas modificar los datos  "<<std::endl;
                    std::cout<<"seleccione la opcion correspondiente a modificar registros."<<std::endl;
                }
                std::cout<<std::endl;
                std::cout << "-- Desea modificar otro registro? (s/n)" << std::endl;
                std::cin.clear();
                char respuesta;
                do {
                    respuesta = validar<char>();
                    if (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N') {
                        std::cout << "Por favor, ingrese una respuesta valida ";
                    }
                } while (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N');

                if (respuesta == 'n' || respuesta == 'N') {
                    a = false;
                }
            }
            break;
            case 2: {
                modificarRegistro();
                std::cout<<std::endl;
                std::cout << "-- Desea modificar otro registro? (s/n)" << std::endl;
                std::cin.clear();
                char respuesta;
                do {
                    respuesta = validar<char>();
                    if (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N') {
                        std::cout << "Por favor, ingrese una respuesta valida  ";
                    }
                } while (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N');

                if (respuesta == 'n' || respuesta == 'N') {
                    a = false;
                }
            }
            break;
            case 3: {
                mostrarDatosCarrera();
                std::cout<<std::endl;
                std::cout << "-- Desea modificar otro registro? (s/n)" << std::endl;
                std::cin.clear();
                char respuesta;
                do {
                    respuesta = validar<char>();
                    if (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N') {
                        std::cout << "Por favor, ingrese una respuesta valida  ";
                    }
                } while (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N');


                if (respuesta == 'n' || respuesta == 'N') {
                    a = false;
                }
            }
            break;
        }
    }
}
