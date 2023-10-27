#ifndef GESTORNOTASFINALES_H
#define GESTORNOTASFINALES_H

#include "NotaFinal.h"

class GestorNotasFinales
{
    public:
        GestorNotasFinales();
        virtual ~GestorNotasFinales();


        void iniciar();


    private:
        bool altaNotaFinal();
        int listadoNotasFinales();
        int eliminarNotaFinal();
        int generarPromedio();
        int modificarNotaFinal();

};

#endif // GESTORNOTASFINALES_H
