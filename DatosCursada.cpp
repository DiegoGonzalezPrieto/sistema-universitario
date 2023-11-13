#include <iostream>
using namespace std;

#include "DatosCursada.h"
#include "func_utiles.h"

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
        if (d > 7 || d<1) d=1;

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
        cargarCadenaConString(a, _aula, sizeof(_aula));
    }

string DatosCursada::toString()
    {
        string minutos = getHorario().getMinuto() > 9 ? to_string(getHorario().getMinuto()) : "0" + to_string(getHorario().getMinuto());
        string horario = to_string(getHorario().getHora()) + ":" + minutos + " hs";
        string s = getNombreDiaSemana() + " " + horario + " - Aula: " + getAula();
        return s;
    }
