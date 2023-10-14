#ifndef NOTAFINAL_H
#define NOTAFINAL_H

#include "Fecha.h"

class NotaFinal
{
    public:
        NotaFinal();

        void setIdMateria(const char* idMateria);
        void setNota(int nota);
        void setFecha(const Fecha& fecha);

        const char* getIdMateria() const;
        int getNota() const;
        Fecha getFecha() const;

    private:

        char _idMateria[30];
        int _nota;
        Fecha _fecha;
};

#endif // NOTAFINAL_H
