#include <iostream>


#include "GestorNotasFinales.h"
#include "Menu.h"
#include "func_utiles.h"


GestorNotasFinales::GestorNotasFinales(std::string rutaNotas, std::string rutaMaterias, std::string rutaCursadaMaterias) :
    _auxArchivo(rutaNotas),
    gcm(rutaCursadaMaterias, rutaMaterias)
{


}

GestorNotasFinales::~GestorNotasFinales()
{
    //dtor
}


void GestorNotasFinales::iniciar()
{
    std::vector<std::string> opcMenu = {"Listar notas finales", "Guardar registro nota final", "Eliminar registro nota final", "Modificar registro nota final", "Generar promedio"};


    Menu menu(opcMenu, "** Notas Finales **");
    int opcion;

    while(true)
        {


            opcion = menu.mostrar();


            switch(opcion)
                {

                case 0:
                    return;
                case 1:
                {
                    int codError = listadoNotasFinales();

                    switch(codError)
                        {

                        case ARCH_NO_EXISTE:
                            _mensajero.mensajeError("No existe el archivo de notas finales");
                            break;
                        case ARCH_ERROR_LECTURA:
                            _mensajero.mensajeError("No se pudo leer el archivo de notas finales");
                            break;
                        default:
                            break;
                        }

                    break;
                }
                case 2:
                    if(altaNotaFinal() == true)
                        {
                            _mensajero.mensajeInformacion("Se registro correctamente la nota");
                            break;
                        }
                    else
                        {
                            _mensajero.mensajeError("Hubo un error al registrar la nota");
                            break;
                        }
                case 3:
                {

                    int codError = eliminarNotaFinal();

                    switch(codError)
                        {

                        case ARCH_NO_EXISTE:
                            _mensajero.mensajeError("No existe el archivo de notas finales");
                            break;
                        case ARCH_ERROR_LECTURA:
                            _mensajero.mensajeError("No se pudo leer el archivo de notas finales");
                            break;
                        case SIN_COINCIDENCIAS:
                            _mensajero.mensajeError("No se encontraron registros para el ID Materia solicitado");
                            break;
                        case CANCELAR_OPERACION:
                            _mensajero.mensajeInformacion("Se ha cancelado la eliminacion del registro");
                            break;
                        default:
                            _mensajero.mensajeInformacion("Se ha eliminado el registro satisfactoriamente");
                            break;
                        }


                    break;

                }
                case 4:
                {
                    int codError = modificarNotaFinal();

                    switch(codError)
                        {

                        case ARCH_NO_EXISTE:
                            _mensajero.mensajeError("No existe el archivo de notas finales");
                            break;
                        case ARCH_ERROR_LECTURA:
                            _mensajero.mensajeError("No se pudo leer el archivo de notas finales");
                            break;
                        case SIN_COINCIDENCIAS:
                            _mensajero.mensajeError("No se encontraron registros para el ID Materia solicitado");
                            break;
                        case CANCELAR_OPERACION:
                            _mensajero.mensajeInformacion("Se ha cancelado la modificacion del reistro");
                            break;
                        default:
                            _mensajero.mensajeInformacion("Se ha modificado satisfactoriamente el registro");
                            break;
                        }


                    break;

                }

                break;


                case 5:
                {
                    int codError = generarPromedio();

                    switch(codError)
                        {


                        case ARCH_NO_EXISTE:
                            _mensajero.mensajeError("No existe el archivo de notas finales");
                            break;
                        case ARCH_ERROR_LECTURA:
                            _mensajero.mensajeError("No se pudo leer el archivo de notas finales");
                            break;
                        case ARCH_SIN_REGISTROS:
                            _mensajero.mensajeError("No se encontraron registros para calcular el promedio");
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
bool GestorNotasFinales::altaNotaFinal()
{


    NotaFinal notaCargada;

    std::string idCursadaMateria = gcm.buscarCursadaMateria().getIdCursadaMateria();
    int nota, dia, mes, anio;

    std::cout << "Calificacion: ";
    nota = validar<int>("Por favor, reingrese la calificacion: ");

    while(nota <= 0 || nota > 10)
        {

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

    notaCargada.setIdCursadaMateria(idCursadaMateria);
    notaCargada.setNota(nota);

    if(fecha.esFechaValida() == false)
        {
            notaCargada.setFecha(Fecha());
        }
    else
        {
            notaCargada.setFecha(Fecha(dia, mes, anio));
        }

    if (_auxArchivo.agregarRegistro(notaCargada) == true)
        {

            return true;
        }
    else
        {

            return false;
        }
}

int GestorNotasFinales::listadoNotasFinales()
{


    if(_auxArchivo.archivoExiste() == false)
        {

            return -1;
        }

    NotaFinal auxRegistro;
    int cantRegistros = _auxArchivo.contarRegistros();

    std::vector <NotaFinal> listaNotas;

    if (_auxArchivo.leerRegistros(listaNotas) == false)
        {

            return -2;
        }

    for(int i = 0; i< cantRegistros; i++)
        {

            std:: cout << listaNotas[i].toString() << std::endl;

        }

    return 0;
}

int GestorNotasFinales::eliminarNotaFinal()
{


    if(_auxArchivo.archivoExiste() == false)
        {

            return -1;
        }

    std::string idCursadaMateria = gcm.buscarCursadaMateria().getIdCursadaMateria();


    int cantRegistros = _auxArchivo.contarRegistros();

    ///Estan todas las notas
    std::vector <NotaFinal> listaNotas;

    ///Solamente estaran las notas con el ID Solicitado
    std::vector <NotaFinal> notasIdCursadaMateriaSolicitado;

    ///Guardamos la posicion frente al listado de todas las notas
    std::vector <int> posNotasIdMateriasSolicitado;

    if (_auxArchivo.leerRegistros(listaNotas) == false)
        {

            return -2;
        }

    ///Buscamos todas las notas para el IDMateria ingresado
    for(int i = 0; i < cantRegistros; i++)
        {

            if(listaNotas[i].getIdCursadaMateria() == idCursadaMateria)
                {

                    notasIdCursadaMateriaSolicitado.push_back(listaNotas[i]);
                    posNotasIdMateriasSolicitado.push_back(i);
                }
        }

    int cantNotasIdSolicitado = notasIdCursadaMateriaSolicitado.size();


    ///En caso de no haber coincidencias
    if(cantNotasIdSolicitado <= 0)
        {

            return -3;
        }


    ///Mostramos las notas encontradas que coincidan con el ID ingresado
    for(int i = 0; i < cantNotasIdSolicitado; i++)
        {

            std::cout << "#" << i+1 << ": " << notasIdCursadaMateriaSolicitado[i].toString() << std::endl;

        }

    std::cout << "Seleccione el numero de registro que desea eliminar: " << std::endl;


    int opc;
    opc = validar<int>("Opcion no valida, por favor reintente: ");

    ///En caso de que el registro no este en rango se solicita nuevamente
    while(opc <= 0 || opc > cantNotasIdSolicitado)
        {

            std::cout << "Numero de registro no valido, por favor reingreselo nuevamente: ";
            opc = validar<int>("Opcion: ");
        }

    char decisionFinal;
    std::cout << "¿Esta seguro que desea eliminarlo? (S - si, N - no): ";
    std::cin >> decisionFinal;


    switch(decisionFinal)
        {

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

int GestorNotasFinales::generarPromedio()
{


    if(_auxArchivo.archivoExiste() == false)
        {

            return -1;
        }

    std::vector <NotaFinal> listaNotas;


    if (_auxArchivo.leerRegistros(listaNotas) == false)
        {

            return -2;
        }

    int cantRegistros = _auxArchivo.contarRegistros();
    int promedio = 0;

    for(int i = 0; i < cantRegistros; i++)
        {

            promedio += listaNotas[i].getNota();
        }

    if(cantRegistros <= 0)
        {
            return -5;
        }
    else
        {
            std::cout << "Su promedio de todas las notas registradas es: " << (float)promedio / cantRegistros << std::endl;
        }

    return 0;
}


int GestorNotasFinales::modificarNotaFinal()
{
    if(_auxArchivo.archivoExiste() == false)
        {

            return -1;
        }

    std::string idCursadaMateria;

    std::cout << "\n\tSeleccionar la Cursada cuya nota final desea modificar\n";
    idCursadaMateria = gcm.buscarCursadaMateria().getIdCursadaMateria();


    int cantRegistros = _auxArchivo.contarRegistros();

    ///Estan todas las notas
    std::vector <NotaFinal> listaNotas;

    ///Solamente estaran las notas con el ID Solicitado
    std::vector <NotaFinal> notasIdCursadaMateriaSolicitado;

    ///Guardamos la posicion frente al listado de todas las notas
    std::vector <int> posNotasIdCursadaMateriasSolicitado;

    if (_auxArchivo.leerRegistros(listaNotas) == false)
        {

            return -2;
        }

    ///Buscamos todas las notas para el IDMateria ingresado
    for(int i = 0; i < cantRegistros; i++)
        {

            if(listaNotas[i].getIdCursadaMateria() == idCursadaMateria)
                {

                    notasIdCursadaMateriaSolicitado.push_back(listaNotas[i]);
                    posNotasIdCursadaMateriasSolicitado.push_back(i);
                }
        }

    int cantNotasIdSolicitado = notasIdCursadaMateriaSolicitado.size();


    ///En caso de no haber coincidencias
    if(cantNotasIdSolicitado <= 0)
        {

            return -3;
        }


    ///Mostramos las notas encontradas que coincidan con el ID ingresado
    for(int i = 0; i < cantNotasIdSolicitado; i++)
        {

            std::cout << "#" << i+1 << ": " << notasIdCursadaMateriaSolicitado[i].toString() << std::endl;

        }

    std::cout << "Seleccione el numero de registro que desea modificar: " << std::endl;


    int opc;
    opc = validar<int>("Opcion no valida, por favor reintente: ");

    ///En caso de que el registro no este en rango se solicita nuevamente
    while(opc <= 0 || opc > cantNotasIdSolicitado)
        {

            std::cout << "Numero de registro no valido, por favor reingreselo nuevamente: ";
            opc = validar<int>("Opcion: ");
        }

    ///No uso la clase menu porque me da la opcion de ingresar cero para salir
    std::cout << "Indique el campo que desea modificar: " << std::endl;
    std::cout << "1 - Cursada Materia Asociada" << std::endl;
    std::cout << "2 - Fecha" << std::endl;
    std::cout << "3 - Calificacion" << std::endl;
    std::cout << "4 - Modificar todo el registro" << std::endl;
    std::cout << "Eleccion: ";

    int seleccion;
    seleccion = validar<int>("Opcion no valida, por favor reintente: ");

    ///En caso de que el registro no este en rango se solicita nuevamente
    while(seleccion <= 0 || seleccion > 4)
        {

            std::cout << "Opcion no valida, por favor reingreselo nuevamente: ";
            seleccion = validar<int>("Opcion: ");
        }

    NotaFinal auxRegistro;

    switch (seleccion)
        {

        case 1:
        {
            std::string nuevoIdCursadaMateria = gcm.buscarCursadaMateria().getIdCursadaMateria();

            auxRegistro = listaNotas[posNotasIdCursadaMateriasSolicitado[opc-1]];
            auxRegistro.setIdCursadaMateria(nuevoIdCursadaMateria);
            _auxArchivo.modificarRegistro(posNotasIdCursadaMateriasSolicitado[opc-1], auxRegistro);

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

            auxRegistro = listaNotas[posNotasIdCursadaMateriasSolicitado[opc-1]];

            Fecha fecha(dia,mes,anio);

            if(fecha.esFechaValida() == false)
                {
                    auxRegistro.setFecha(Fecha());
                }
            else
                {
                    auxRegistro.setFecha(Fecha(dia, mes, anio));
                }

            _auxArchivo.modificarRegistro(posNotasIdCursadaMateriasSolicitado[opc-1], auxRegistro);

            break;
        }
        case 3:
        {

            int nuevaCalificacion;

            std::cout << "Calificacion: ";
            nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");

            while(nuevaCalificacion <= 0 || nuevaCalificacion > 10)
                {

                    std::cout << "Opcion no valida, se espera un numero entre 1 y 10: ";
                    nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");
                }

            auxRegistro = listaNotas[posNotasIdCursadaMateriasSolicitado[opc-1]];
            auxRegistro.setNota(nuevaCalificacion);
            _auxArchivo.modificarRegistro(posNotasIdCursadaMateriasSolicitado[opc-1], auxRegistro);

            break;
        }
        case 4:
        {

            std::string nuevoIdCursadaMateria = gcm.buscarCursadaMateria().getIdCursadaMateria();
            int nuevaCalificacion, dia, mes, anio;

            std::cout << "Calificacion: ";
            nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");

            while(nuevaCalificacion <= 0 || nuevaCalificacion > 10)
                {

                    std::cout << "Opcion no valida, se espera un numero entre 1 y 10: ";
                    nuevaCalificacion = validar<int>("Por favor, reingrese la calificacion: ");
                }

            std::cout << "Ingrese el dia: ";
            dia = validar<int>("Por favor, reingrese el dia: ");
            std::cout << "Ingrese el mes: ";
            mes = validar<int>("Por favor, reingrese el mes: ");
            std::cout << "Ingrese el año: ";
            anio = validar<int>("Por favor, reingrese el año: ");

            auxRegistro = listaNotas[posNotasIdCursadaMateriasSolicitado[opc-1]];
            auxRegistro.setIdCursadaMateria(nuevoIdCursadaMateria);
            auxRegistro.setNota(nuevaCalificacion);

            Fecha fecha(dia,mes,anio);

            if(fecha.esFechaValida() == false)
                {
                    auxRegistro.setFecha(Fecha());
                }
            else
                {
                    auxRegistro.setFecha(Fecha(dia, mes, anio));
                }

            _auxArchivo.modificarRegistro(posNotasIdCursadaMateriasSolicitado[opc-1], auxRegistro);

            break;

        }
        default:
            return -4;
            break;
        }



    return 0;

}

/// Para uso del Gestor Cuatrimestre, devuelve la nota y la posición.
bool GestorNotasFinales::seleccionarNotaDeCursadaMateria(std::string idCursadaMateria, NotaFinal& nota, int &pos)
{
    if(_auxArchivo.archivoExiste() == false)
        {
            return false;
        }
    std::vector<NotaFinal> notas;
    std::vector<NotaFinal> notasDeCursadaMateria;
    std::vector<int> posicionesEnArchivo;

    if (!_auxArchivo.leerRegistros(notas)) return false;

    for (int i=0; i < notas.size();i++)
    {
        if (notas[i].getIdCursadaMateria()==idCursadaMateria)
        {
            notasDeCursadaMateria.push_back(notas[i]);
            posicionesEnArchivo.push_back(i);
        }
    }
    if (notasDeCursadaMateria.size()<1)
    {
        _mensajero.mensajeInformacion("No hay notas cargadas para la cursada con id " + idCursadaMateria);
        return false;
    }

    for (int i=0;i<notasDeCursadaMateria.size();i++)
    {
            cout << i+1 <<": " << notasDeCursadaMateria[i].toString() << endl;
    }

    cout << "Seleccionar la nota deseada: ";
    int seleccion = validar<int>();
    int cantOpciones = notasDeCursadaMateria.size();
    while (seleccion < 1 || seleccion> cantOpciones)
    {
        cout << "Ingrese un número entre 1 y " << cantOpciones;
        seleccion = validar<int>();
    }
    _mensajero.mensajeInformacion("Nota seleccionada correctamente.");

    nota = notasDeCursadaMateria[seleccion - 1];
    pos = posicionesEnArchivo[seleccion - 1];

    return true;
}


/// Para uso del Gestor Cuatrimestre
bool GestorNotasFinales::modificarNota(NotaFinal nota, int pos)
{
    return _auxArchivo.modificarRegistro(pos, nota);
}
