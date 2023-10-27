#include <iostream>
#include <vector>

using namespace std;

#include "GestorEventos.h"


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

bool GestorEventos::archivoExiste()
{
    return getArchivo().archivoExiste();
}
bool GestorEventos::crearArchivo()
{
    return getArchivo().crearArchivo();
}

bool GestorEventos::guardarEvento(Evento e)
{
    Archivo<Evento> a = getArchivo();
    if (!a.archivoExiste())
        {
            a.crearArchivo();
        }
    return a.agregarRegistro(e);
}

void GestorEventos::mostrarTodosEventos()
{
    vector<Evento> ve = obtenerEventos();
    if (ve.size() == 0) return;

    // TODO : ordenar eventos por fecha ?

    cout << "*************************" << endl;
    cout << "Eventos:" << endl;
    cout << "*************************" << endl;
    for (const Evento e : ve)
        {
            cout << e.toString() << endl;
            cout << "--------" << endl;
        }
}

//    bool GestorEventos::modificarEvento(Evento)
//    void GestorEventos::mostrarEventosProximos();
//    void GestorEventos::mostrarEventosEnFecha(Fecha);
//    bool GestorEventos::hayEventoProximo();

vector<Evento> GestorEventos::obtenerEventos()
{
    vector<Evento> ve;
    if (!getArchivo().leerRegistros(ve))
        {
            _mensajero.mensajeError("No se pudo leer el archivo de Eventos.");
        }
    return ve;
}
