#ifndef NOTAFINAL_H
#define NOTAFINAL_H

#include <string>
#include "Fecha.h"

class NotaFinal
{
    public:
        NotaFinal();

        void setIdMateria(const std::string& idMateria);
        void setNota(int nota);
        void setFecha(const Fecha& fecha);

        std::string getIdMateria() const;
        int getNota() const;
        Fecha getFecha() const;

        std::string toString() const;

    private:

        char _idMateria[30];
        int _nota;
        Fecha _fecha;
};

#endif // NOTAFINAL_H
