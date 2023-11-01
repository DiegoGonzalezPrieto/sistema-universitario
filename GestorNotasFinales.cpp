#include <iostream>


#include "GestorNotasFinales.h"
#include "Menu.h"
#include "func_utiles.h"
#include "Mensajero.h"

GestorNotasFinales::GestorNotasFinales() : _auxArchivo("notas_finales.dat")
{

}

GestorNotasFinales::~GestorNotasFinales()
{
    //dtor
}


void GestorNotasFinales::iniciar(){

    std::vector<std::string> opcMenu = {"Listar notas finales", "Guardar registro nota final", "Eliminar registro nota final", "Modificar registro nota final", "Generar promedio"};

    Menu menu(opcMenu);

    int opcion;

    while(true){


        opcion = menu.mostrar();


        switch(opcion){

        case 0:
            return;
        case 1:
        {
            int codError = listadoNotasFinales();

            switch(codError){

            case ARCH_NO_EXISTE:
                std::cout << "Error: No existe el archivo de notas finales" << std::endl;
                break;
            case ARCH_ERROR_LECTURA:
                std::cout << "Error: No se pudo leer el archivo de notas finales" << std::endl;
                break;
            default:
                break;
            }

            break;
        }
        case 2:
            if(altaNotaFinal() == true){
                std::cout << "Se registro correctamente la nota" << std::endl;
                break;
            }
            else{
                std::cout << "Hubo un error al registrar la nota" << std::endl;
                break;
            }
        case 3:
        {

            int codError = eliminarNotaFinal();

            switch(codError){

            case ARCH_NO_EXISTE:
                std::cout << "Error: No existe el archivo de notas finales" << std::endl;
                break;
            case ARCH_ERROR_LECTURA:
                std::cout << "Error: No se pudo leer el archivo de notas finales" << std::endl;
                break;
            case SIN_COINCIDENCIAS:
                std::cout << "Error: No se encontraron registros para el ID Materia solicitado" << std::endl;
                break;
            case CANCELAR_OPERACION:
                std::cout << "Se ha cancelado la eliminacion del registro" << std::endl;
                break;
            default:
                std::cout << "Se ha eliminado el registro satisfactoriamente" << std::endl;
                break;
            }


            break;

        }
        case 4:
        {
            int codError = modificarNotaFinal();

            switch(codError){

                case ARCH_NO_EXISTE:
                    std::cout << "Error: No existe el archivo de notas finales" << std::endl;
                    break;
                case ARCH_ERROR_LECTURA:
                    std::cout << "Error: No se pudo leer el archivo de notas finales" << std::endl;
                    break;
                case SIN_COINCIDENCIAS:
                    std::cout << "Error: No se encontraron registros para el ID Materia solicitado" << std::endl;
                    break;
                case CANCELAR_OPERACION:
                    std::cout << "Se ha cancelado la modificacion del reistro" << std::endl;
                    break;
                default:
                    std::cout << "Se ha modificado satisfactoriamente el registro" << std::endl;
                    break;
            }


            break;

        }

        break;


        case 5:
            {
                int codError = generarPromedio();

                switch(codError){


                case ARCH_NO_EXISTE:
                    std::cout << "Error: No existe el archivo de notas finales" << std::endl;
                    break;
                case ARCH_ERROR_LECTURA:
                    std::cout << "Error: No se pudo leer el archivo de notas finales" << std::endl;
                    break;
                case ARCH_SIN_REGISTROS:
                    std::cout << "Error: No se encontraron registros para calcular el promedio" << std::endl;
                    break;
                default:
                    break;
                }

                break;

            }
        default:
            ///
            break;


        }

    }

}

///Opcion para cargar a mano un registro de NotaFinal interactuando con el usuario
bool GestorNotasFinales::altaNotaFinal(){


    NotaFinal notaCargada;

    std::string idMateria;
    int nota, dia, mes, anio;

    std::cout << "ID de la materia: ";
    std::cin >> idMateria;
    std::cout << "Calificacion: ";
    nota = validar<int>("Por favor, reingrese la calificacion: ");

    while(nota <= 0 || nota > 10){

        std::cout << "Opcion no valida, se espera un numero entre 1 y 10: ";
        nota = validar<int>("Por favor, reingrese la calificacion: ");
    }



    std::cout << "Ingrese el dia: ";
    dia = validar<int>("Por favor, reingrese el dia: ");
    std::cout << "Ingrese el mes: ";
    mes = validar<int>("Por favor, reingrese el mes: ");
    std::cout << "Ingrese el año: ";
    anio = validar<int>("Por favor, reingrese el año: ");

    ///Llegados a este punto, todos los datos se deberian haber validado
    ///Verificamos si la fecha es valida, caso contrario se asigna la fecha de hoy
    Fecha fecha(dia,mes,anio);

    notaCargada.setIdMateria(idMateria);
    notaCargada.setNota(nota);

    if(fecha.esFechaValida() == false){
        notaCargada.setFecha(Fecha());
    }
    else{
        notaCargada.setFecha(Fecha(dia, mes, anio));
    }

    if (_auxArchivo.agregarRegistro(notaCargada) == true){

        return true;
    }
    else{

        return false;
    }
}

int GestorNotasFinales::listadoNotasFinales(){


    if(_auxArchivo.archivoExiste() == false){

        return -1;
    }

    NotaFinal auxRegistro;
    int cantRegistros = _auxArchivo.contarRegistros();

    std::vector <NotaFinal> listaNotas;

    if (_auxArchivo.leerRegistros(listaNotas) == false){

        return -2;
    }

    for(int i = 0; i< cantRegistros; i++){

        std:: cout << listaNotas[i].toString() << std::endl;

    }

    return 0;
}

int GestorNotasFinales::eliminarNotaFinal(){


    if(_auxArchivo.archivoExiste() == false){

        return -1;
    }

    std::string idMateria;

    std::cout << "Ingrese el ID de materia correspondiente al registro a eliminar: ";
    std::cin >> idMateria;


    int cantRegistros = _auxArchivo.contarRegistros();

    ///Estan todas las notas
    std::vector <NotaFinal> listaNotas;

    ///Solamente estaran las notas con el ID Solicitado
    std::vector <NotaFinal> notasIdMateriaSolicitado;

    ///Guardamos la posicion frente al listado de todas las notas
    std::vector <int> posNotasIdMateriasSolicitado;

    if (_auxArchivo.leerRegistros(listaNotas) == false){

        return -2;
    }

    ///Buscamos todas las notas para el IDMateria ingresado
    for(int i = 0; i < cantRegistros; i++){

        if(listaNotas[i].getIdMateria() == idMateria){

            notasIdMateriaSolicitado.push_back(listaNotas[i]);
            posNotasIdMateriasSolicitado.push_back(i);
        }
    }

    int cantNotasIdSolicitado = notasIdMateriaSolicitado.size();


    ///En caso de no haber coincidencias
    if(cantNotasIdSolicitado <= 0){

        return -3;
    }


    ///Mostramos las notas encontradas que coincidan con el ID ingresado
    for(int i = 0; i < cantNotasIdSolicitado; i++){

        std::cout << "#" << i+1 << ": " << notasIdMateriaSolicitado[i].toString() << std::endl;

    }

    std::cout << "Seleccione el numero de registro que desea eliminar: " << std::endl;


    int opc;
    opc = validar<int>("Opcion no valida, por favor reintente: ");

    ///En caso de que el registro no este en rango se solicita nuevamente
    while(opc <= 0 || opc > cantNotasIdSolicitado){

        std::cout << "Numero de registro no valido, por favor reingreselo nuevamente: ";
        opc = validar<int>("Opcion: ");
    }





    char decisionFinal;
    std::cout << "¿Esta seguro que desea eliminarlo? (S - si, N - no): ";
    std::cin >> decisionFinal;


    switch(decisionFinal){

    case 's':
    case 'S':

        _auxArchivo.borrarRegistro(posNotasIdMateriasSolicitado[opc-1]);
        return 0;
        break;


    case 'n':
    case 'N':

        return -4;
        break;

    default:

        return -4;
        break;

    }

    return 0;
}

int GestorNotasFinales::generarPromedio(){


    if(_auxArchivo.archivoExiste() == false){

        return -1;
    }

    std::vector <NotaFinal> listaNotas;


    if (_auxArchivo.leerRegistros(listaNotas) == false){

        return -2;
    }

    int cantRegistros = _auxArchivo.contarRegistros();
    int promedio = 0;

    for(int i = 0; i < cantRegistros; i++){

        promedio += listaNotas[i].getNota();
    }

    if(cantRegistros <= 0){
        return -5;
    }
    else{
        std::cout << "Su promedio de todas las notas registradas es: " << (float)promedio / cantRegistros << std::endl;
    }

    return 0;
}


int GestorNotasFinales::modificarNotaFinal(){


    if(_auxArchivo.archivoExiste() == false){

        return -1;
    }

    std::string idMateria;

    std::cout << "Ingrese el ID de materia correspondiente al registro a modificar: ";
    std::cin >> idMateria;


    int cantRegistros = _auxArchivo.contarRegistros();

    ///Estan todas las notas
    std::vector <NotaFinal> listaNotas;

    ///Solamente estaran las notas con el ID Solicitado
    std::vector <NotaFinal> notasIdMateriaSolicitado;

    ///Guardamos la posicion frente al listado de todas las notas
    std::vector <int> posNotasIdMateriasSolicitado;

    if (_auxArchivo.leerRegistros(listaNotas) == false){

        return -2;
    }

    ///Buscamos todas las notas para el IDMateria ingresado
    for(int i = 0; i < cantRegistros; i++){

        if(listaNotas[i].getIdMateria() == idMateria){

            notasIdMateriaSolicitado.push_back(listaNotas[i]);
            posNotasIdMateriasSolicitado.push_back(i);
        }
    }

    int cantNotasIdSolicitado = notasIdMateriaSolicitado.size();


    ///En caso de no haber coincidencias
    if(cantNotasIdSolicitado <= 0){

        return -3;
    }


    ///Mostramos las notas encontradas que coincidan con el ID ingresado
    for(int i = 0; i < cantNotasIdSolicitado; i++){

        std::cout << "#" << i+1 << ": " << notasIdMateriaSolicitado[i].toString() << std::endl;

    }

    std::cout << "Seleccione el numero de registro que desea modificar: " << std::endl;


    int opc;
    opc = validar<int>("Opcion no valida, por favor reintente: ");

    ///En caso de que el registro no este en rango se solicita nuevamente
    while(opc <= 0 || opc > cantNotasIdSolicitado){

        std::cout << "Numero de registro no valido, por favor reingreselo nuevamente: ";
        opc = validar<int>("Opcion: ");
    }

    ///No uso la clase menu porque me da la opcion de ingresar cero para salir
    std::cout << "Indique el campo que desea modificar: " << std::endl;
    std::cout << "1 - ID Materia" << std::endl;
    std::cout << "2 - Fecha" << std::endl;
    std::cout << "3 - Calificacion" << std::endl;
    std::cout << "4 - Modificar todo el registro" << std::endl;
    std::cout << "Eleccion: ";

    int seleccion;
    seleccion = validar<int>("Opcion no valida, por favor reintente: ");

    ///En caso de que el registro no este en rango se solicita nuevamente
    while(seleccion <= 0 || seleccion > 4){

        std::cout << "Opcion no valida, por favor reingreselo nuevamente: ";
        seleccion = validar<int>("Opcion: ");
    }

    NotaFinal auxRegistro;

    switch (seleccion){

        case 1:
        {
            std::string nuevoIdMateria;

            std::cout << "Ingrese el nuevo Id de materia: ";
            std::cin >> nuevoIdMateria;

            auxRegistro = listaNotas[posNotasIdMateriasSolicitado[opc-1]];
            auxRegistro.setIdMateria(nuevoIdMateria);
            _auxArchivo.modificarRegistro(posNotasIdMateriasSolicitado[opc-1], auxRegistro);

            break;
        }
        case 2:
        {
            int dia, mes, anio;

            std::cout << "Ingrese el dia: ";
            dia = validar<int>("Por favor, reingrese el dia: ");
            std::cout << "Ingrese el mes: ";
            mes = validar<int>("Por favor, reingrese el mes: ");
            std::cout << "Ingrese el año: ";
            anio = validar<int>("Por favor, reingrese el año: ");

            auxRegistro = listaNotas[posNotasIdMateriasSolicitado[opc-1]];

            Fecha fecha(dia,mes,anio);

            if(fecha.esFechaValida() == false){
                auxRegistro.setFecha(Fecha());
            }
            else{
                auxRegistro.setFecha(Fecha(dia, mes, anio));
            }

            _auxArchivo.modificarRegistro(posNotasIdMateriasSolicitado[opc-1], auxRegistro);

            break;
        }
        case 3:
        {

            int nuevaCalificacion;

            std::cout << "Calificacion: ";
            nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");

            while(nuevaCalificacion <= 0 || nuevaCalificacion > 10){

                std::cout << "Opcion no valida, se espera un numero entre 1 y 10: ";
                nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");
            }

            auxRegistro = listaNotas[posNotasIdMateriasSolicitado[opc-1]];
            auxRegistro.setNota(nuevaCalificacion);
            _auxArchivo.modificarRegistro(posNotasIdMateriasSolicitado[opc-1], auxRegistro);

            break;
        }
        case 4:
        {

            std::string nuevoIdMateria;
            int nuevaCalificacion, dia, mes, anio;

            std::cout << "ID de la materia: ";
            std::cin >> nuevoIdMateria;
            std::cout << "Calificacion: ";
            nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");

            while(nuevaCalificacion <= 0 || nuevaCalificacion > 10){

                std::cout << "Opcion no valida, se espera un numero entre 1 y 10: ";
                nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");
            }

            std::cout << "Ingrese el dia: ";
            dia = validar<int>("Por favor, reingrese el dia: ");
            std::cout << "Ingrese el mes: ";
            mes = validar<int>("Por favor, reingrese el mes: ");
            std::cout << "Ingrese el año: ";
            anio = validar<int>("Por favor, reingrese el año: ");

            auxRegistro = listaNotas[posNotasIdMateriasSolicitado[opc-1]];
            auxRegistro.setIdMateria(nuevoIdMateria);
            auxRegistro.setNota(nuevaCalificacion);

            Fecha fecha(dia,mes,anio);

            if(fecha.esFechaValida() == false){
                auxRegistro.setFecha(Fecha());
            }
            else{
                auxRegistro.setFecha(Fecha(dia, mes, anio));
            }

            _auxArchivo.modificarRegistro(posNotasIdMateriasSolicitado[opc-1], auxRegistro);

            break;

        }
        default:
            return -4;
            break;
    }



    return 0;

}
