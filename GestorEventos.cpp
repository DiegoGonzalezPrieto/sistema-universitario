#include <iostream>
#include <vector>

using namespace std;

#include "GestorEventos.h"
#include "Menu.h"


GestorEventos::GestorEventos(string nombreArchivo): _archivo(nombreArchivo)
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
    // 0. Chequear o crear archivo.
    if (!getArchivo().archivoExiste())
        {
            getArchivo().crearArchivo();
        }

    // 1. Loop principal
    string tituloMenu = "\n========================\n** Gestión de Eventos **\n========================";
    Menu m({"Ver todos los eventos.",
            "Ver eventos de este mes y el siguiente",
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
                    mostrarTodosEventos();
                    break;
                case 2:
                    mostrarEventosProximos();
                    break;
                case 3:
                    altaEventoPorConsola();
                    break;
                case 4:
                    modificarEvento();
                    break;
                case 5:
                    mostrarEventosEnFecha();
                    break;
                case 6:
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
    cin >> anio;
    cout << endl << "Indicar mes del evento (1-12): ";
    cin >> mes;
    cout << endl;
    if (!getArchivo().leerRegistros(ve))
        {
            _mensajero.mensajeError("No se pudo leer el archivo de eventos.");
            return 0;
        }
    for (Evento e : ve)
        {
            if (e.getFecha().getAnio() == anio && e.getFecha().getMes() == mes && e.getEstado())
                {
                    eventosSeleccionados.push_back(e);
                    cout << "Evento " << eventosSeleccionados.size() << ":" << endl << e.toString() << endl;
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
            cin >> numEvento;
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

void GestorEventos::mostrarTodosEventos()
{
    vector<Evento> ve = obtenerEventosActivos();
    if (ve.size() == 0) return;

    // TODO : ordenar eventos por fecha ?

    cout << endl;
    cout << "********************" << endl;
    cout << "***   Eventos    ***" << endl;
    cout << "********************" << endl;
    cout << endl;

    for (Evento e : ve)
        {
            cout << e.toString() << endl;
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
    while (true)
        {
            int dia, mes, anio;
            cout << "Ingresar fecha del evento (0 para cancelar)" << endl<< endl;
            cout << "Día: ";
            cin >> dia;
            if (dia==0) return;
            cout << "Mes: ";
            cin >> mes;
            if (mes==0) return;
            cout << "Año: ";
            cin >> anio;
            if (anio==0) return;
            if (Fecha::esFechaValida(dia, mes, anio))
                {
                    e.setFecha(Fecha(dia, mes, anio));
                    break;
                }
            else
                {
                    _mensajero.mensajeError("La fecha ingresada no es válida, vuelva a intentar.");
                    cout  << endl;
                }
        }

    string descripcion;
    cout << "Ingresar descripción breve del evento" << endl<< endl;
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
            string idCursadaMateria;
            cout << "Indicar materia asociada: ";
            getline(cin>>ws, idCursadaMateria);
            // TODO : seleccionar materia

            idCursadaMateria = "TODO";
            e.setIdCursadaMateria(idCursadaMateria);
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
            _mensajero.mensajeInformacion("Evento guardado correctamente:\n\n" + e.toString() + "\n");
        }
    else
        {

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

    cout << "\nEvento seleccionado:\n\n" << e.toString() << endl << endl;

    while (opcion != 0)
        {
            opcion = m.mostrar();
            switch (opcion)
                {
                case 1:
                {
                    // TODO: mejorar ingreso de fecha, copiar de altaNuevoEvento
                    int dia, mes, anio;
                    cout << "La fecha actual es " << e.getFecha().toString() << endl ;
                    cout <<  "Ingresar nueva fecha en formato DÍA MES AÑO (20 9 2023), o '0 0 0' para cancelar: ";
                    cin >> dia >> mes >> anio;
                    if (dia == 0) break;
                    Fecha f;
                    f.setDia(dia);
                    f.setMes(mes);
                    f.setAnio(anio);
                    cout << endl << "Nueva Fecha: " << f.toString() << endl;
                    e.setFecha(f);
                    bool guardo = guardarEventoModificado(e);
                    if (!guardo)
                        {
                            _mensajero.mensajeError("El evento modificado no pudo guardarse.");
                        }
                    else
                        {
                            _mensajero.mensajeInformacion("Fecha modificada correctamente");
                        }
                    break;
                }
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
                    cout << "\nLa información actual es: " << e.getDescripcion() << endl;
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
                    _mensajero.mensajeAdvertencia("Funcionalidad aún no implementada.");
                    // TODO: modificar materia asociada (ID cursadaMateria)
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
    if (!bajaEvento(idEvento))
        {
            _mensajero.mensajeError("No se pudo eliminar el evento seleccionado.");
            exit(1);
        }
    _mensajero.mensajeInformacion("Registro eliminado.");
}

void GestorEventos::mostrarEventosProximos()
{
    cout << endl;
    cout << "********************************************" << endl;
    cout << "**** Eventos de este mes y el siguiente ****" << endl;
    cout << "********************************************" << endl;
    cout << endl;

    Fecha hoy;
    vector<Evento> ve = obtenerEventosActivos();
    // TODO : ordenar el vector de forma ascendente
    bool mostrar;

    for (Evento e : ve)
        {
            mostrar = false;
            Fecha fechaEvento = e.getFecha();
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
            cout << e.toString() << endl;
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
    int anio, mes, dia, cantEventos=0;
    string resultado = "";
    cout << endl << "Año buscado: ";
    cin >> anio;
    cout << endl << "Mes buscado (1-12): ";
    cin >> mes;
    cout << endl << "Día buscado: ";
    cin >> dia;
    cout << endl;

    bool hayEventos = false;
    for (Evento e : ve)
        {
            if (e.getFecha().getAnio() == anio && e.getFecha().getMes() == mes && e.getFecha().getDia() == dia)
                {
                    hayEventos = true;
                    resultado += e.toString() + "\n-------------------\n";
                    cantEventos++;
                }
        }

    if (!hayEventos)
        {
            _mensajero.mensajeInformacion("\nNo hay eventos en esa fecha.\n");
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
            Fecha fechaEvento = e.getFecha();
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

void GestorEventos::ordenarEventos(vector<Evento>& vec, bool descendente=true)
{
// TODO : esperar a modificación Evento pasa a FechaHorario

}


