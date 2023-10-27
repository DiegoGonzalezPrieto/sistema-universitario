#include <iostream>
using namespace std;

#include "DatosCursada.h"

/// Constructor vacío. Deja string vacío en _aula para poder chequear si es un dato válido.
DatosCursada::DatosCursada(){
    setAula("");
    setDiaSemana(1);
};

Horario DatosCursada::getHorario()
    {
        return _horario;
    }

void DatosCursada::setHorario(Horario h)
    {
        _horario = h;
    }

int DatosCursada::getDiaSemana()
    {
        return _diaSemana;
    }

void DatosCursada::setDiaSemana(int d)
    {
        _diaSemana = d;
    }

string DatosCursada::getNombreDiaSemana()
    {
        string dias[7] = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
        return dias[_diaSemana - 1];
    }

string DatosCursada::getAula()
    {
        string s(_aula);
        return s;
    }

void DatosCursada::setAula(string a)
    {
        strcpy(_aula, a.c_str());
    }

string DatosCursada::toString()
    {
        string horario = to_string(getHorario().getHora()) + ":" + to_string(getHorario().getMinuto()) + " hs";
        string s = getNombreDiaSemana() + " " + horario + " - Aula: " + getAula();
        return s;
    }
