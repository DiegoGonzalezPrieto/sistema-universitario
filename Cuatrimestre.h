#ifndef CUATRIMESTRE_H
#define CUATRIMESTRE_H

#include <string>

const int CANTMATERIAS = 16;
const int LONGMAX = 30;

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
        char _idsCursadaMateria[CANTMATERIAS][LONGMAX];
        bool _finalizado;
};

#endif // CUATRIMESTRE_H
