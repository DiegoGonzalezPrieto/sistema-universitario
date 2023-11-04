#ifndef GESTORCURSADAMATERIA_H
#define GESTORCURSADAMATERIA_H

#include "CursadaMateria.h"
#include "Archivo.h"
#include "Mensajero.h"



class GestorCursadaMateria
{
    public:
        GestorCursadaMateria(string rutaArchivo);
        virtual ~GestorCursadaMateria();
        Archivo<CursadaMateria> getArchivo();
        void setArchivo(string ruta);

        void iniciar();

        // ---------- ABML ------------- //

        void altaCursadaMateriaPorConsola(); // WIP
        void mostrarTodasCursadaMateria(); // TODO
        void mostrarCursadasMateriaEnCurso(); // TODO
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
    protected:

    private:
        Archivo<CursadaMateria> _archivo;
        Mensajero _mensajero;
};

#endif // GESTORCURSADAMATERIA_H
