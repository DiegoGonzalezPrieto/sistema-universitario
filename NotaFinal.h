#ifndef NOTAFINAL_H
#define NOTAFINAL_H

#include <string>
#include "Fecha.h"
#include "func_utiles.h"

const int LONGMAX = 17; // 10 ID materia + 6 ID cuatrimestre + 1 \0

class NotaFinal
{
    public:
        NotaFinal();

        void setIdCursadaMateria(const std::string& idMateria);
        void setNota(int nota);
        void setFecha(const Fecha& fecha);

        std::string getIdCursadaMateria() const;
        int getNota() const;
        Fecha getFecha() const;

        std::string toString() const;

    private:

        char _idCursadaMateria[LONGMAX];
        int _nota;
        Fecha _fecha;
};

#endif // NOTAFINAL_H
