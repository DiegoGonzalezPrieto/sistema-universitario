#ifndef GESTOREVENTOS_H
#define GESTOREVENTOS_H

#include "Archivo.h"
#include "Evento.h"
#include "Fecha.h"
#include "Mensajero.h"
#include "GestorMaterias.h"
#include "GestorCursadaMateria.h"

class GestorEventos
{
public:
    GestorEventos(std::string nombreArchivo, std::string archivoMaterias, std::string archivoCursadaMaterias);
    ~GestorEventos(); // TODO

    Archivo<Evento> getArchivo();
    void setArchivo(std::string ruta);

    /// Loop principal
    void iniciar(); // WIP

    bool archivoExiste();
    bool crearArchivo();


    /// Muestra los eventos próximos, según el limite definido en parámetro (TODO : en config).
    void mostrarEventosProximos(int);

    /// Listar todos los eventos.
    void mostrarTodosEventos();

    /// Mostrar eventos de este mes y del mes que viene
    void mostrarEventosDeEsteMesYSiguiente();

    /// Alta interactiva de Evento
    void altaEventoPorConsola(); // TODO : seleccionar materia asociada

    /// Modificación interactiva de Evento
    bool modificarEvento(); // TODO : modificación de idMateriaCursada

    /// Pide una fecha al usuario y muestra los eventos que ocurren en ese día
    void mostrarEventosEnFecha();

    /// Eliminar evento de forma interactiva
    void eliminarEvento();


    // --------- METODOS DE APOYO --------------//

    /// Guardar nuevo objeto evento en el archivo.
    bool guardarNuevoEvento(Evento);
    /// Guardar evento modificado en el archivo.
    bool guardarEventoModificado(Evento);
    /// Devuelve ID del evento seleccionado
    int seleccionarEvento();
    /// Devuelve datos del evento cuyo ID coindice
    Evento buscarPorId(int id);
    /// Obtener todos los eventos activos.
    std::vector<Evento> obtenerEventosActivos();
    /// Obtener Posición del Evento en el achivo, en base a su ID.
    int obtenerPosicionEnArchivo(int id);
    /// Baja lógica del evento con id
    bool bajaEvento(int id);
    /// Ordenar vector de eventos (descendente|ascendente)
    void ordenarEventosPorFecha(std::vector<Evento>&, bool descendente=true);
    /// Revisa este mes y el siguiente por algún evento.
    bool hayEventoProximo();

    /// Confirma si hay algún evento activo en los próximos N días
    bool hayEventoEnLosProximosDias(int dias);
    /// Devuelve los eventos activos de los próximos N días
    std::vector<Evento> obtenerEventosDeLosProximosDias(int dias);
    /// Devuelve un string con la información del evento y el nombre de la materia asociada
    std::string eventoToStringCompleto(Evento e);
protected:

private:
    Archivo<Evento> _archivo;
    Mensajero _mensajero;
    GestorMaterias gm;
    GestorCursadaMateria gcm;
    /// Brinda opciones de tipos de evento y devuelve el código del tipo seleccionado
    char seleccionarTipoEvento(); // TODO


};

#endif // GESTOREVENTOS_H
