#ifndef DATOSCURSADA_H
#define DATOSCURSADA_H

#include <cstring>

#include "Horario.h"

class DatosCursada
{
public:
    DatosCursada();

    Horario getHorario();
    void setHorario(Horario h);

    int getDiaSemana();
    void setDiaSemana(int d);
    string getNombreDiaSemana();

    string getAula();
    void setAula(string a);

    string toString();

private:
    Horario _horario;
    int _diaSemana;
    char _aula[200];

};

#endif // DATOSCURSADA_H
