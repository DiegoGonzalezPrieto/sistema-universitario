#ifndef GESTORNOTASFINALES_H
#define GESTORNOTASFINALES_H

#include "NotaFinal.h"
#include "Archivo.h"
#include "Mensajero.h"

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
        GestorNotasFinales();
        virtual ~GestorNotasFinales();


        void iniciar();


    private:

        Archivo <NotaFinal> _auxArchivo;
        Mensajero _mensajero;

        bool altaNotaFinal();
        int listadoNotasFinales();
        int eliminarNotaFinal();
        int generarPromedio();
        int modificarNotaFinal();

};

#endif // GESTORNOTASFINALES_H
