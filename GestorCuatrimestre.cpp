#include <iostream>
#include "GestorCuatrimestre.h"
#include "Menu.h"
#include "func_utiles.h"

GestorCuatrimestre::GestorCuatrimestre(std::string nombre) : archivoCuatrimestres(nombre) {}

void GestorCuatrimestre::iniciarGestorCuatrimestre()
{
    std::vector<std::string> opciones =
    {
        "Iniciar cuatrimestre",
        "Cerrar cuatrimestre",
        "Modificar Actual Cuatrimestre"
    };

    Menu menuPrincipal(opciones, "------ GESTION CUATRIMESTRE ------");

    int op;
    do
    {
        op = menuPrincipal.mostrar();
        switch (op)
        {
        case 0:
            break;
        case 1:
            iniciarCuatrimestre();
            break;
        case 2:
            cerrarCuatrimestre();
            break;
        case 3:
            modificarCuatrimestreActual();
        default:
            msj.mensajeError("Opcion no valida. Por favor, ingrese una opcion valida");
            break;
        }
        std::cout << std::endl;
    }
    while (op != 0);
}

void GestorCuatrimestre::iniciarCuatrimestre()
{
    Cuatrimestre datosCuatrimestre;
    datosCuatrimestre.setFinalizado(true);
    if(archivoCuatrimestres.archivoExiste()){
    int cantregistros=archivoCuatrimestres.contarRegistros();
    archivoCuatrimestres.leerRegistro(cantregistros-1,datosCuatrimestre);
   }

    if(datosCuatrimestre.getFinalizado()){
    Cuatrimestre nuevoCuatrimestre;
    GestorCorrelativas correlativas("Archivos/datos/materias.dat","Archivos/datos/cursadamateria.dat");
    GestorMaterias materias("Archivos/datos/materias.dat");

    std::cout << "Ingrese el anio del nuevo cuatrimestre:     ------> /Ejemplo 2020";
    int nuevoAnio = validar<int>();
    nuevoCuatrimestre.setAnio(nuevoAnio);

    std::cout << "Ingrese el período del nuevo cuatrimestre (1 o 2): ";
    int nuevoPeriodo = validar<int>();
    nuevoCuatrimestre.setPeriodo(nuevoPeriodo);
    bool cargaMatCuatrimestre=true;
    while(cargaMatCuatrimestre)
    {
        std::cout << "Seleccione la Materia a cursar : "<<endl;
        std::string id = materias.seleccionarIdMateria();

        if(correlativas.validarSisepuedeCursar(id))
        {
            nuevoCuatrimestre.setIdCursadaMateria(id);
            cout<<" Materia Agregada al Cuatrimestre Exitosamente "<<endl;
        }

        else
        {
            msj.mensajeAdvertencia("Hay correlativas de esta materia que no están aprobadas.");
            msj.mensajeAdvertencia("Le sugerimos para proporcionarle una información exacta");
            msj.mensajeAdvertencia("que no agregue materias al cuatrimestre que no puede cursar.");
             std::cout << "¿Desea continuar y agregar esta materia al cuatrimestre actual? (S/N): ";
             bool continuar= true;
            do
            {
                char respuesta = validar<char>();
                if (respuesta == 'S' || respuesta == 's')
                {
                    nuevoCuatrimestre.setIdCursadaMateria(id);
                    std::cout << "Materia agregada al cuatrimestre exitosamente." << std::endl;
                    continuar = false;
                }
                else if (respuesta == 'N' || respuesta == 'n')
                {
                    std::cout << "No se agregará la materia al cuatrimestre." << std::endl;
                    continuar = false;
                }
                else
                {
                    std::cout << "Respuesta no válida. Por favor, ingrese 'S' o 'N'." << std::endl;
                }

            }
            while (continuar);


        }
        limpiarPantalla();
        std::cout << "¿Termino la carga de Materias? : "<<endl;
            bool continuar= true;
            do
            {
                char respuesta = validar<char>();

                if (respuesta == 'S' || respuesta == 's')
                {
                    continuar = false;
                    cargaMatCuatrimestre=false;
                }
                else if (respuesta == 'N' || respuesta == 'n')
                {
                    continuar = false;
                }
                else
                {
                    std::cout << "Respuesta no válida. Por favor, ingrese 'S' o 'N'." << std::endl;
                }

            }
            while (continuar);



    }
            nuevoCuatrimestre.setFinalizado(false);

         if (archivoCuatrimestres.agregarRegistro(nuevoCuatrimestre))
            {
                std::cout << "Cuatrimestre iniciado correctamente." << std::endl;
            }
            else
            {
                msj.mensajeError("Error al iniciar el cuatrimestre. Inténtelo nuevamente.");
            }
        }
        else {

            msj.mensajeInformacion("SOLO PODRA CREAR UN NUEVO CUATRIMESTRE SI CIERRA/ TERMINA EL ANTERIOR");

        }

    }

        void GestorCuatrimestre::cerrarCuatrimestre()
        {
           cout<< "EN DESARROLLO"<<endl;
            // ...

            // Ejemplo:
            // Obtener el cuatrimestre que se va a cerrar
            Cuatrimestre cuatrimestreACerrar;
            // Configurar la información del cuatrimestre
            // ...
            // Actualizar el cuatrimestre en el archivo
            //archivoCuatrimestres.modificarRegistro(pos, cuatrimestreACerrar);

            std::cout << "Cuatrimestre cerrado correctamente." << std::endl;
        }

        void GestorCuatrimestre::modificarCuatrimestreActual()
        {
            cout<< "EN DESARROLLO"<<endl;
            // ...

            // Ejemplo:
            // Obtener el cuatrimestre que se va a cerrar
            Cuatrimestre cuatrimestreACerrar;
            // Configurar la información del cuatrimestre
            // ...
            // Actualizar el cuatrimestre en el archivo
            //archivoCuatrimestres.modificarRegistro(pos, cuatrimestreACerrar);

            std::cout << "Cuatrimestre cerrado correctamente." << std::endl;
        }

