#ifndef GESTORCURSADAMATERIA_H
#define GESTORCURSADAMATERIA_H

#include "CursadaMateria.h"
#include "Archivo.h"
#include "Mensajero.h"
#include "GestorMaterias.h"
#include "GestorCorrelativas.h"


class GestorCursadaMateria
{
    public:
        GestorCursadaMateria(string rutaArchivo, string rutaMaterias);
        virtual ~GestorCursadaMateria();
        Archivo<CursadaMateria> getArchivo();
        void setArchivo(string ruta);

        void iniciar();

        // ---------- ABML ------------- //

        /// Permite al usuario hacer un alta de una cursada para este cuatrimestre
        void altaCursadaMateriaPorConsola();

        /// Muestra todas las materias en dicho estado
        void mostrarCursadasMateriaPorEstado(EstadoMateria e); // Funciona?
        void mostrarTodasCursadaMateria(); // TODO
        void buscarCursadaMateria(); // TODO
        void modificarCursadaMateria(); // TODO
        void eliminarCursadaMateria(); // TODO


        // ----- Métodos de apoyo ------- //
        /// Recibe una Cursada Materia y la guarda al final del archivo. Si el archivo no existe, intenta crearlo.
        bool guardarNuevaCursadaMateria(CursadaMateria);

        CursadaMateria buscarCursadaMateriaPorId(string idCursadaMateria); // TODO
        int buscarPosicionEnArchivoPorId(string idCursadaMateria); // TODO
        bool guardarCursadaMateriaModificada(CursadaMateria); // TODO
        bool anularRegistroCursadaMateria(); // TODO

        /// Permite al usuario seleccionar un estado de cursada-materia, o cancelar la seleccion (false)
        bool seleccionarEstadoCursadaMateria(EstadoMateria &);
        /// Permite al usuario cargar los datos de la cursada (horario día aula), o cancelar la selección (false)
        bool cargarDatosCursada(vector<DatosCursada>&, int cantMax);
        /// Permite al usuario seleccionar un cuatrimestre (año + 1|2)
        bool seleccionarCuatrimestre(string &cuatrimestre);
    protected:

    private:
        Archivo<CursadaMateria> _archivo;
        GestorMaterias gm; // TODO : ver si inicializar el GMaterias así trae problemas. El constructor de GMCursada lo inicializa.
        GestorCorrelativas gc;
        Mensajero _mensajero;
};

#endif // GESTORCURSADAMATERIA_H
