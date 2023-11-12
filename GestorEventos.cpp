#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "GestorEventos.h"
#include "Menu.h"
#include "func_utiles.h"


GestorEventos::GestorEventos(string nombreArchivo, string archivoMaterias, string archivoCursadaMaterias):
    _archivo(nombreArchivo),
    gm(archivoMaterias),
    gcm(archivoCursadaMaterias, archivoMaterias)
{}

GestorEventos::~GestorEventos()
{
    //dtor
    // TODO
}

Archivo<Evento> GestorEventos::getArchivo()
{
    return _archivo;
}
void GestorEventos::setArchivo(string ruta)
{
    Archivo<Evento> ae(ruta);
    _archivo = ae;
}

void GestorEventos::iniciar()
{
    // 0. Chequear o crear archivo y revisar por eventos próximos
    if (!getArchivo().archivoExiste())
        {
            getArchivo().crearArchivo();
        }

    string alertaEventosProximos = "";
    // TODO : leer limite de días de CONFIG
    int diasDeChequeoEventosProximos = 8;
    if (hayEventoEnLosProximosDias(diasDeChequeoEventosProximos))
        {
            cout << endl;
            _mensajero.mensajeAdvertencia("Hay eventos dentro de los próximos " + to_string(diasDeChequeoEventosProximos) + " días!");
            alertaEventosProximos = " (!)";
        }

    // 1. Loop principal
    string tituloMenu = "\n========================\n** Gestión de Eventos **\n========================";
    Menu m({ "Ver eventos próximos." + alertaEventosProximos,
             "Ver eventos de este mes y el siguiente",
             "Ver todos los eventos.",
             "Ingresar nuevo evento",
             "Modificar evento existente",
             "Buscar evento por fecha",
             "Eliminar evento"},
           tituloMenu);

    int opc= 1;
    while (opc != 0)
        {
            opc = m.mostrar();
            switch (opc)
                {
                case 0:
                    break;
                // ABM
                case 1:
                    mostrarEventosProximos(diasDeChequeoEventosProximos); // TODO : pasar parámetro a lectura de config
                    break;
                case 2:
                    mostrarEventosDeEsteMesYSiguiente();
                    break;
                case 3:
                    mostrarTodosEventos();
                    break;
                case 4:
                    altaEventoPorConsola();
                    break;
                case 5:
                    modificarEvento();
                    break;
                case 6:
                    mostrarEventosEnFecha();
                    break;
                case 7:
                    eliminarEvento();
                    break;
                }
        }
}

bool GestorEventos::archivoExiste()
{
    return getArchivo().archivoExiste();
}
bool GestorEventos::crearArchivo()
{
    return getArchivo().crearArchivo();
}

int GestorEventos::seleccionarEvento()
{
    vector<Evento> ve;
    vector<Evento> eventosSeleccionados;
    int anio, mes, numEvento;
    cout << endl << "Indicar el año del evento: ";
    anio = validar<int>();
    cout << endl << "Indicar mes del evento (1-12): ";
    mes = validar<int>();
    cout << endl;
    ve = obtenerEventosActivos();

    if (ve.size()==0)
        {
            _mensajero.mensajeAdvertencia("No hay eventos registrados.");
            return 0;
        }
    for (Evento e : ve)
        {
            Fecha fechaEvento = e.getFechaHorario().getFecha();
            if ( fechaEvento.getAnio() == anio && fechaEvento.getMes() == mes)
                {
                    eventosSeleccionados.push_back(e);
                    cout << "Evento " << eventosSeleccionados.size() << ":" << endl << eventoToStringCompleto(e) << endl;
                    cout << "--------" << endl;
                }
        }
    if (eventosSeleccionados.size()==0)
        {
            _mensajero.mensajeInformacion("No hay eventos en esa fecha.");
            return 0;
        }
    while (true)
        {
            cout << endl << "Indicar el número del evento deseado (0 para cancelar): ";
            numEvento = validar<int>();;
            if (numEvento == 0 ) return 0;
            if (numEvento > 0 && numEvento <= eventosSeleccionados.size()) break;
            _mensajero.mensajeInformacion("Opción no válida.");
        }
    return eventosSeleccionados[numEvento - 1].getId();
}



bool GestorEventos::guardarNuevoEvento(Evento e)
{
    Archivo<Evento> a = getArchivo();
    if (!a.archivoExiste())
        {
            a.crearArchivo();
        }
    e.setId(a.contarRegistros()+1);
    return a.agregarRegistro(e);
}


void GestorEventos::mostrarEventosProximos(int diasLimite)
{
    cout << endl;
    cout << "****************************************" << endl;
    cout << "***   Eventos de los próximos " + to_string(diasLimite) + " días ***" << endl;
    cout << "****************************************" << endl;
    cout << endl;
    if (!hayEventoEnLosProximosDias(diasLimite))
        {
            _mensajero.mensajeInformacion("No hay eventos en los próximos " + to_string(diasLimite) + " días.");
            return;
        }

    vector<Evento> vec = obtenerEventosDeLosProximosDias(diasLimite);

    for (Evento e : vec)
        {
            cout << eventoToStringCompleto(e) << endl;
            cout << endl;
        }

}

void GestorEventos::mostrarTodosEventos()
{
    vector<Evento> ve = obtenerEventosActivos();
    if (ve.size() == 0)
        {
            _mensajero.mensajeAdvertencia("No hay eventos almacenados.");
            return;
        }

    cout << endl;
    cout << "******************************" << endl;
    cout << "***   Todos los Eventos    ***" << endl;
    cout << "******************************" << endl;
    cout << endl;

    ordenarEventosPorFecha(ve);

    for (Evento e : ve)
        {
            cout << eventoToStringCompleto(e) << endl;
            cout << "--------" << endl;
        }
}

void GestorEventos::altaEventoPorConsola()
{
    Evento e;
    cout << endl;
    cout << "********************" << endl;
    cout << "*** Nuevo Evento ***" << endl;
    cout << "********************" << endl;
    cout << endl;

    // Pedir datos y validar
    int dia, mes, anio;
    int horas, minutos;
    while (true)
        {
            Fecha f;
            Horario h;
            cout << "Ingresar fecha del evento (0 para cancelar)" << endl<< endl;
            cout << "Día: ";
            dia = validar<int>();
            if (dia==0) return;
            cout << "Mes: ";
            mes = validar<int>();
            if (mes==0) return;
            cout << "Año: ";
            anio = validar<int>();
            if (anio==0) return;
            if (Fecha::esFechaValida(dia, mes, anio))
                {
                    break;

                }
            else
                {
                    _mensajero.mensajeError("La fecha ingresada no es válida, vuelva a intentar.");
                    continue;
                }
        }
    while (true)
        {
            cout << "Ingresar horario del evento:" << endl<< endl;
            cout << "Hora: ";
            horas = validar<int>();
            cout << "Minutos: ";
            minutos = validar<int>();
            if (Horario::validarHorario(0, minutos, horas))
                {
                    break;
                }
            else
                {
                    _mensajero.mensajeError("El horario ingresado no es válido, vuelva a intentar.");
                    cout  << endl;
                }
        }
    cout << endl;
    e.setFechaHorario(FechaHorario(dia,mes,anio,0,minutos,horas));


    string descripcion;
    cout << "Ingresar descripción breve del evento: " << endl<< endl;
    getline(cin>>ws, descripcion);
    e.setDescripcion(descripcion);

    string informacion;
    cout << "Ingresar información detallada del evento" << endl<< endl;
    getline(cin>>ws, informacion);
    e.setInformacion(informacion);


    char opc;
    cout<< "Está asociado a alguna materia actualmente en curso? (S/N) ";
    cin >> opc;
    if (opc == 's' || opc == 'S')
        {
            CursadaMateria cm;
            if(!gcm.seleccionarCursadaActualmenteEnCurso(cm))
                {
                    e.setIdCursadaMateria("");
                }
            e.setIdCursadaMateria(cm.getIdCursadaMateria());
        }
    else
        {
            e.setIdCursadaMateria("");
        }

    int tipoEventoSeleccionado;
    char tipoEvento;
    Menu menu({"Examen", "Otro"}, "Seleccionar tipo de evento");
    tipoEventoSeleccionado = menu.mostrar();
    if (tipoEventoSeleccionado == 0) return;
    if (tipoEventoSeleccionado == 1)
        {
            tipoEvento = 'e';
        }
    else
        {
            tipoEvento = 'o';
        }
    e.setTipoEvento(tipoEvento);

    e.setEstado(true);


    bool guardo = false;
    guardo = guardarNuevoEvento(e);
    if (guardo)
        {
            cout << endl;
            _mensajero.mensajeInformacion("Evento guardado correctamente:\n\n" + eventoToStringCompleto(e) + "\n");
        }
    else
        {
            cout << endl;
            _mensajero.mensajeError("El evento no pudo ser guardado.");
        }
}

bool GestorEventos::modificarEvento()
{
    cout << endl;
    cout << "************************" << endl;
    cout << "*** Modificar Evento ***" << endl;
    cout << "************************" << endl;
    cout << endl;

    int opcion = -1, idEvento;
    idEvento = seleccionarEvento();
    if (idEvento == 0) return false;
    vector<string> opciones({"Fecha", "Descripción", "Información", "Tipo de Evento", "Materia en curso asociada"});
    Menu m(opciones, "** Seleccionar dato a modificar **");

    Evento e = buscarPorId(idEvento);

    cout << "\nEvento seleccionado:\n\n" << eventoToStringCompleto(e) << endl << endl;

    while (opcion != 0)
        {
            opcion = m.mostrar();
            switch (opcion)
                {
                case 1:
                {
                    FechaHorario fh;
                    cout << "La fecha actual es " << e.getFechaHorario().toString() << endl ;
                    int dia, mes, anio, horas, minutos;
                    while (true)
                        {
                            Fecha f;
                            Horario h;
                            cout << "Ingresar nueva fecha del evento (0 para cancelar)" << endl<< endl;
                            cout << "Día: ";
                            dia = validar<int>();
                            if (dia==0) return false;
                            cout << "Mes: ";
                            mes = validar<int>();
                            if (mes==0) return false;
                            cout << "Año: ";
                            anio = validar<int>();
                            if (anio==0) return false;
                            if (Fecha::esFechaValida(dia, mes, anio))
                                {
                                    break;

                                }
                            else
                                {
                                    _mensajero.mensajeError("La fecha ingresada no es válida, vuelva a intentar.");
                                    continue;
                                }
                        }
                    while (true)
                        {
                            cout << "Ingresar horario del evento:" << endl<< endl;
                            cout << "Hora: ";
                            horas = validar<int>();
                            cout << "Minutos: ";
                            minutos = validar<int>();
                            if (Horario::validarHorario(0, minutos, horas))
                                {
                                    break;
                                }
                            else
                                {
                                    _mensajero.mensajeError("El horario ingresado no es válido, vuelva a intentar.");
                                    cout  << endl;
                                }
                        }
                    cout << endl;
                    e.setFechaHorario(FechaHorario(dia,mes,anio,0,minutos,horas));
                    bool guardo = guardarEventoModificado(e);
                    if (!guardo)
                        {
                            _mensajero.mensajeError("El evento modificado no pudo guardarse.\n");
                        }
                    else
                        {
                            _mensajero.mensajeInformacion("Fecha modificada correctamente");
                        }
                }
                break;
                case 2:
                {
                    string nuevaDescrip = "";
                    cout << "\nLa descripción actual es: " << e.getDescripcion() << endl;
                    cout << "\nIngresar nueva descripción: ";
                    getline(cin>>ws, nuevaDescrip);
                    e.setDescripcion(nuevaDescrip);
                    bool guardo = guardarEventoModificado(e);
                    if (!guardo)
                        {
                            _mensajero.mensajeError("El evento modificado no pudo guardarse.\n");
                        }
                    else
                        {
                            _mensajero.mensajeInformacion("Descripción modificada correctamente");
                        }
                }
                break;
                case 3:
                {
                    string nuevaInfo = "";
                    cout << "\nLa información actual es: " << e.getInformacion() << endl;
                    cout << "\nIngresar nueva información: ";
                    getline(cin>>ws, nuevaInfo);
                    e.setInformacion(nuevaInfo);
                    bool guardo = guardarEventoModificado(e);
                    if (!guardo)
                        {
                            _mensajero.mensajeError("El evento modificado no pudo guardarse.\n");
                        }
                    else
                        {
                            _mensajero.mensajeInformacion("Información modificada correctamente");
                        }
                }
                break;
                case 4:
                {
                    int tipoEventoSeleccionado;
                    char tipoEvento;
                    cout << "\nEl tipo de evento actual es: " << e.getCategoriaDeEvento() << endl;
                    Menu menu({"Examen", "Otro"}, "Seleccionar tipo de evento");
                    tipoEventoSeleccionado = menu.mostrar();
                    if (tipoEventoSeleccionado == 0) break;
                    if (tipoEventoSeleccionado == 1)
                        {
                            tipoEvento = 'e';
                        }
                    else
                        {
                            tipoEvento = 'o';
                        }
                    e.setTipoEvento(tipoEvento);
                    bool guardo = guardarEventoModificado(e);
                    if (!guardo)
                        {
                            _mensajero.mensajeError("El evento modificado no pudo guardarse.\n");
                        }
                    else
                        {
                            _mensajero.mensajeInformacion("Tipo de evento modificado correctamente");
                        }
                }
                break;
                case 5:
                {
                    CursadaMateria cm;
                    if(!gcm.seleccionarCursadaActualmenteEnCurso(cm))
                        {
                            e.setIdCursadaMateria("");
                        }
                    else
                        {
                            e.setIdCursadaMateria(cm.getIdCursadaMateria());
                            bool guardo = guardarEventoModificado(e);
                            if (!guardo)
                                {
                                    _mensajero.mensajeError("El evento modificado no pudo guardarse.\n");
                                }
                            else
                                {
                                    _mensajero.mensajeInformacion("Cursada asociada al evento modificada correctamente");
                                }
                        }
                }
                break;
                default:
                    break;
                }

        }

}

void GestorEventos::eliminarEvento()
{
    cout << endl;
    cout << "*************************" << endl;
    cout << "**** Eliminar Evento ****" << endl;
    cout << "*************************" << endl;
    cout << endl;

    int idEvento = seleccionarEvento();
    if (idEvento==0)
        {
            return;
        }
    if (!bajaEvento(idEvento))
        {
            _mensajero.mensajeError("No se pudo eliminar el evento seleccionado.");
            exit(1);
        }
    cout << endl;
    _mensajero.mensajeInformacion("Registro eliminado.");
}

void GestorEventos::mostrarEventosDeEsteMesYSiguiente()
{
    cout << endl;
    cout << "********************************************" << endl;
    cout << "**** Eventos de este mes y el siguiente ****" << endl;
    cout << "********************************************" << endl;
    cout << endl;

    Fecha hoy;
    vector<Evento> ve = obtenerEventosActivos();
    ordenarEventosPorFecha(ve);

    bool mostrar;

    for (Evento e : ve)
        {
            mostrar = false;
            Fecha fechaEvento = e.getFechaHorario().getFecha();
            // Chequear año
            if (hoy.getAnio() > fechaEvento.getAnio()) continue;
            if (hoy.getAnio() < fechaEvento.getAnio() && hoy.getMes() != 12) continue;

            if (hoy.getMes() == fechaEvento.getMes())
                {
                    mostrar = true;
                }
            else if (hoy.getMes() + 1 == fechaEvento.getMes())
                {
                    mostrar = true;
                }
            else if (hoy.getMes() == 12 && fechaEvento.getMes() == 1)
                {
                    mostrar = true;
                }
            if (!mostrar) continue;

            cout << "------------------------------" << endl;
            cout << eventoToStringCompleto(e) << endl;
            cout << "------------------------------" << endl;
        }

}

void GestorEventos::mostrarEventosEnFecha()
{
    cout << endl;
    cout << "**********************************" << endl;
    cout << "**** Buscar Eventos Por Fecha ****" << endl;
    cout << "**********************************" << endl;
    cout << endl;

    vector<Evento> ve = obtenerEventosActivos();
    ordenarEventosPorFecha(ve);

    int anio, mes, dia, cantEventos=0;
    bool buscarPorDia = true;
    string resultado = "";

    while (true)
        {
            cout << endl << "Año buscado (0 para cancelar): ";
            anio = validar<int>();
            if (anio==0) return;
            cout << endl << "Mes buscado (1-12): ";
            mes = validar<int>();
            if (mes==0) return;
            cout << endl << "Día buscado (0 busca en todo el mes): ";
            dia = validar<int>();
            if (dia==0 && Fecha::esFechaValida(1, mes, anio))
                {
                    dia = 1;
                    buscarPorDia = false;
                    break;
                }
            cout << endl;
            if (Fecha::esFechaValida(dia, mes, anio))
                {
                    break;
                }
            else
                {
                    _mensajero.mensajeError("Fecha inválida, intente nuevamente.");
                }
        }


    bool hayEventos = false;
    for (Evento e : ve)
        {
            Fecha fechaEvento = e.getFechaHorario().getFecha();
            if (fechaEvento.getAnio() == anio && fechaEvento.getMes() == mes)
                {
                    if (!buscarPorDia)
                        {
                            hayEventos = true;
                            resultado += eventoToStringCompleto(e) + "\n-------------------\n";
                            cantEventos++;

                        }
                    else if (fechaEvento.getDia() == dia)
                        {
                            hayEventos = true;
                            resultado += eventoToStringCompleto(e) + "\n-------------------\n";
                            cantEventos++;
                        }
                }
        }

    if (!hayEventos)
        {
            _mensajero.mensajeInformacion("No hay eventos en esa fecha.\n");
            return;
        }
    cout << "\nSe encontraron " << cantEventos << " Eventos en la fecha seleccionada:\n" << endl;
    cout << resultado;
}

bool GestorEventos::hayEventoProximo()
{
    vector<Evento> ve = obtenerEventosActivos();
    Fecha hoy;
    for (Evento e : ve)
        {
            Fecha fechaEvento = e.getFechaHorario().getFecha();
            // Chequear año
            if (hoy.getAnio() > fechaEvento.getAnio()) continue;
            if (hoy.getAnio() < fechaEvento.getAnio() && hoy.getMes() != 12) continue;

            if (hoy.getMes() == fechaEvento.getMes())
                {
                    return true;
                }
            else if (hoy.getMes() + 1 == fechaEvento.getMes())
                {
                    return true;
                }
            else if (hoy.getMes() == 12 && fechaEvento.getMes() == 1)
                {
                    return true;
                }
        }
    return false;
}

Evento GestorEventos::buscarPorId(int id)
{
    vector<Evento> ve = obtenerEventosActivos();

    for (Evento e : ve)
        {
            if (e.getId()==id)
                {
                    return e;
                }
        }
    _mensajero.mensajeError("El evento buscado no existe.");
    exit(1);
}

vector<Evento> GestorEventos::obtenerEventosActivos()
{
    vector<Evento> ve;
    vector<Evento> result;
    if (!getArchivo().leerRegistros(ve))
        {
            _mensajero.mensajeError("No se pudo leer el archivo de Eventos.");
            exit(1);
        }
    for (int i=0; i< ve.size(); i++)
        {
            if (ve[i].getEstado())
                {
                    result.push_back(ve[i]);
                }
        }
    return result;
}

int GestorEventos::obtenerPosicionEnArchivo(int id)
{
    Archivo<Evento> a = getArchivo();
    int cantidadEventos = a.contarRegistros();
    Evento e;
    for (int i=0; i<cantidadEventos; i++)
        {
            a.leerRegistro(i, e);
            if (e.getId()==id)
                {
                    return i;
                }
        }
}

bool GestorEventos::guardarEventoModificado(Evento e)
{
    int pos = obtenerPosicionEnArchivo(e.getId());
    bool guardo = getArchivo().modificarRegistro(pos, e);
    return guardo;
}

bool GestorEventos::bajaEvento(int id)
{
    Evento e = buscarPorId(id);
    e.setEstado(false);
    if (!guardarEventoModificado(e)) return false;
    return true;
}

void GestorEventos::ordenarEventosPorFecha(vector<Evento>& vec, bool descendente)
{
    // Algoritmo de ordenamiento por Burbujeo
    int i,j,cantEventos = vec.size();
    Evento aux;

    for (i=0; i<cantEventos-1; i++)
        {
            for (j=0; j < cantEventos - i - 1; j++)
                {
                    FechaHorario izq = vec[j].getFechaHorario();
                    FechaHorario der = vec[j+1].getFechaHorario();

                    if (izq < der)
                        {
                            aux = vec[j];
                            vec[j] = vec[j+1];
                            vec[j+1] = aux;

                        }
                }
        }

    if (!descendente)
        {
            // Invertimos el vector
            reverse(begin(vec), end(vec));
        }

}

bool GestorEventos::hayEventoEnLosProximosDias(int dias)
{
    Fecha hoy, limite;
    limite.agregarDias(dias);

    vector<Evento> aux = obtenerEventosActivos();

    if (aux.size()==0) return false;

    for (Evento e : aux)
        {
            if (e.getFechaHorario().getFecha() >= hoy && e.getFechaHorario().getFecha() <= limite)
                {
                    return true;
                }
        }
    return false;
}

/// Devuelve los eventos activos de los próximos N días
std::vector<Evento> GestorEventos::obtenerEventosDeLosProximosDias(int dias)
{
    Fecha hoy, limite;
    limite.agregarDias(dias);

    vector<Evento> aux, eventos = obtenerEventosActivos();

    if (eventos .size()==0) return aux;

    for (Evento e : eventos)
        {
            if (e.getFechaHorario().getFecha() >= hoy && e.getFechaHorario().getFecha() <= limite)
                {
                    aux.push_back(e);
                }
        }
    return aux;
}

string GestorEventos::eventoToStringCompleto(Evento e)
{
    string materia, aux = e.toString();
    CursadaMateria cm;
    if (gcm.buscarCursadaMateriaPorId(e.getIdCursadaMateria(), cm))
        {
            aux += "\n\nCursada vinculada: " + cm.getNombreMateria() + " - Cuatrimestre: " + cm.getIdCuatrimestreInicio() + "\n";
        }
    return aux;
}
