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
        void setIdCursadaMateria(int pos, const char* idCursadaMateria);
        void setFinalizado(bool finalizado);

        int getAnio() const;
        int getPeriodo() const;
        const char* getIdsCursadaMateria(int pos) const;
        bool getFinalizado() const;

        std::string getId() const;

    private:
        int _anio;
        int _periodo;
        char _idsCursadaMateria[CANTMATERIAS][LONGMAX] ;
        bool _finalizado;
};

#endif // CUATRIMESTRE_H
