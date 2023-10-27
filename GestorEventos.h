#ifndef GESTOREVENTOS_H
#define GESTOREVENTOS_H

#include "Archivo.h"
#include "Evento.h"
#include "Fecha.h"
#include "Mensajero.h"

class GestorEventos
{
public:
    GestorEventos(string nombreArchivo); //TODO
    ~GestorEventos(); // TODO

    Archivo<Evento> getArchivo();
    void setArchivo(string ruta);

    bool archivoExiste();
    bool crearArchivo();
    bool guardarEvento(Evento);
    void mostrarTodosEventos();
    bool modificarEvento(Evento);
    void mostrarEventosProximos();
    void mostrarEventosEnFecha(Fecha);
    bool hayEventoProximo();

protected:

private:
    Archivo<Evento> _archivo;
    Mensajero _mensajero;

    /// Método interno para uso dentro de la clase GestorEvento.
    vector<Evento> obtenerEventos();
};

#endif // GESTOREVENTOS_H
