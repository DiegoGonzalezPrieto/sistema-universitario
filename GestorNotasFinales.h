#ifndef GESTORNOTASFINALES_H
#define GESTORNOTASFINALES_H

#include "NotaFinal.h"
#include "Archivo.h"
#include "Mensajero.h"
#include "GestorCursadaMateria.h"

enum TipoError{

    ARCH_NO_EXISTE = -1,
    ARCH_ERROR_LECTURA = -2,
    SIN_COINCIDENCIAS = -3,
    CANCELAR_OPERACION = -4,
    ARCH_SIN_REGISTROS = -5

};



class GestorNotasFinales
{
    public:
        GestorNotasFinales(std::string rutaNotasFinales, std::string rutaMaterias, std::string rutaCursadaMateria);
        virtual ~GestorNotasFinales();


        void iniciar();


    private:

        Archivo <NotaFinal> _auxArchivo;
        Mensajero _mensajero;
        GestorCursadaMateria gcm;

        bool altaNotaFinal();
        int listadoNotasFinales();
        int eliminarNotaFinal();
        int generarPromedio();
        int modificarNotaFinal();

        /// Para uso del Gestor Cuatrimestre, devuelve la nota y la posición.
        bool seleccionarNotaDeCursadaMateria(std::string idCursadaMateria, NotaFinal& nota, int &pos);
        /// Para uso del Gestor Cuatrimestre
        bool modificarNota(NotaFinal, int pos);

};

#endif // GESTORNOTASFINALES_H
