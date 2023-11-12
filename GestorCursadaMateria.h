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
        GestorCursadaMateria(std::string rutaArchivo, std::string rutaMaterias);
        virtual ~GestorCursadaMateria();
        Archivo<CursadaMateria> getArchivo();
        void setArchivo(std::string ruta);

        void iniciar();

        // ---------- ABML ------------- //

        /// Permite al usuario hacer un alta de una cursada para este cuatrimestre
        void altaCursadaMateriaPorConsola();

        /// Muestra todas las materias en dicho estado (puede mostrar anuladas)
        void mostrarCursadasMateriaPorEstado(EstadoMateria e);

        /// Muestra todos los registros, salvo anuladas
        void mostrarTodasCursadaMateria();

        /// Permite al usuario modificar una cursada luego de buscarla
        void modificarCursadaMateria(); // TODO

        /// Permite al usuario buscar una materia por el cuatrimestre de inicio y la muestra por pantalla (también la retorna)
        CursadaMateria buscarCursadaMateria();

        /// Permite al usuario marcar como anulada una cursada materia (similar a modificar pero marca como anulada)
        void eliminarCursadaMateria(); // TODO


        // ----- Métodos de apoyo ------- //
        /// Recibe una Cursada Materia y la guarda al final del archivo. Si el archivo no existe, intenta crearlo.
        bool guardarNuevaCursadaMateria(CursadaMateria);

        /// Busca CursadaMateria por su id (excepto si está ANULADA), devuelve false si no encontró nada
        bool buscarCursadaMateriaPorId(std::string idCursadaMateria, CursadaMateria&);

        /// Busca todas las cursadas del cuatrimestre indicado
        std::vector<CursadaMateria> buscarCursadasDeMateriaPorCuatrimestre(std::string idCuatrimestreInicio);

        /// Devuelve la posicion en el archivo, para sobreescribir registro (-1 si falla)
        int buscarPosicionEnArchivoPorId(std::string idCursadaMateria);

        /// Sobreescribe el registro buscándolo en base al idCursadaMateria
        bool guardarCursadaMateriaModificada(CursadaMateria);

        /// Pasa a ANULADA el registro con id ingresado en parámetro.
        bool anularRegistroCursadaMateria(std::string idCursadaMateria);

        /// Chequea que la materia se pueda cursar en este cuatrimestre (no revisa correlatividades)
        bool sePuedeCursar(std::string idMateria, std::string &mensajeError);

        /// Permite al usuario seleccionar un estado de cursada-materia, o cancelar la seleccion (false)
        bool seleccionarEstadoCursadaMateria(EstadoMateria &);
        /// Permite al usuario cargar los datos de la cursada (horario día aula), o cancelar la selección (false)
        bool cargarDatosCursada(std::vector<DatosCursada>&, int cantMax);
        /// Permite al usuario seleccionar un cuatrimestre (año + 1|2)
        bool seleccionarCuatrimestre(std::string &cuatrimestre);
        /// Para obtener una de las cursadas actualmente en curso, útil en otros gestores
        bool seleccionarCursadaActualmenteEnCurso(CursadaMateria&);
    protected:

    private:
        Archivo<CursadaMateria> _archivo;
        GestorMaterias gm; // TODO : ver si inicializar el GMaterias así trae problemas. El constructor de GMCursada lo inicializa.
        GestorCorrelativas gc;
        Mensajero _mensajero;
};

#endif // GESTORCURSADAMATERIA_H
