#ifndef GESTOREVENTOS_H
#define GESTOREVENTOS_H

#include "Archivo.h"
#include "Evento.h"
#include "Fecha.h"
#include "Mensajero.h"

class GestorEventos
{
public:
    GestorEventos(string nombreArchivo);
    ~GestorEventos(); // TODO

    Archivo<Evento> getArchivo();
    void setArchivo(string ruta);

    /// Loop principal
    void iniciar(); // WIP

    bool archivoExiste();
    bool crearArchivo();


    /// Listar todos los eventos.
    void mostrarTodosEventos(); // TODO : ordenar por fechaHorario

    /// Alta interactiva de Evento
    void altaEventoPorConsola(); // TODO : seleccionar materia asociada

    /// Modificación interactiva de Evento
    bool modificarEvento(); // TODO : modificación de idMateriaCursada

    /// Eliminar evento de forma interactiva
    void eliminarEvento();

    /// Mostrar eventos de este mes y del mes que viene
    void mostrarEventosProximos(); // TODO : ordenar fechas
//    void mostrarEventosEnFecha(Fecha); // TODO


    /// Guardar nuevo objeto evento en el archivo.
    bool guardarNuevoEvento(Evento);
    /// Guardar evento modificado en el archivo.
    bool guardarEventoModificado(Evento);
    /// Devuelve ID del evento seleccionado
    int seleccionarEvento();
    /// Devuelve datos del evento cuyo ID coindice
    Evento buscarPorId(int id);
    /// Obtener todos los eventos activos.
    vector<Evento> obtenerEventosActivos();
    /// Obtener Posición del Evento en el achivo, en base a su ID.
    int obtenerPosicionEnArchivo(int id);
    /// Baja lógica del evento con id
    bool bajaEvento(int id);
    /// Ordenar vector de eventos (ascendente|descendente)
    void ordenarEventos(vector<Evento>&, bool); // TODO
    /// Revisa este mes y el siguiente por algún evento.
    bool hayEventoProximo();
protected:

private:
    Archivo<Evento> _archivo;
    Mensajero _mensajero;

    /// Brinda opciones de tipos de evento y devuelve el código del tipo seleccionado
    char seleccionarTipoEvento(); // TODO


};

#endif // GESTOREVENTOS_H
