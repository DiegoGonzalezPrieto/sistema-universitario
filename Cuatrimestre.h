#ifndef CUATRIMESTRE_H
#define CUATRIMESTRE_H
#include <string>
#include "func_utiles.h"

const int CANTMATERIASC = 16;
const int LONGMAXC = 10;

class Cuatrimestre
{
    public:
        Cuatrimestre();

        void setAnio(int anio);
        void setPeriodo(int periodo);
        void setIdCursadaMateria(const std::string& nuevoIdMateria);
        void setFinalizado(bool finalizado);

        int getAnio() const;
        int getPeriodo() const;
        std::string getIdsCursadaMateria(int pos) const;
        bool getFinalizado() const;

        std::string getIdCuatrimestre() const;
        std::string toString() const;

    private:
        int _anio;
        int _periodo;
        char _idsCursadaMateria[CANTMATERIASC][LONGMAXC];
        bool _finalizado;
};

#endif // CUATRIMESTRE_H
