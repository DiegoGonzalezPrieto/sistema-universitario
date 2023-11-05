#include "Horario.h"

using namespace std;

Horario::Horario()
{
    ///Creamos una variable del tipo time_T
    ///Le asignamos nuestros datos del sistema con localtime
    ///Creamos un struct tm para acceder a todas las funciones de <time.h>

    time_t t = time(NULL);
    localtime(&t);
    struct tm date = *localtime(&t);

    setHora(date.tm_hour);
    setMinuto(date.tm_min);
    setSegundo(date.tm_sec);

}

Horario::Horario(int segundo, int minuto, int hora)
{

    if(validarHorario(segundo, minuto, hora) == false)
        {

            time_t t = time(NULL);
            localtime(&t);
            struct tm date = *localtime(&t);

            setHora(date.tm_hour);
            setMinuto(date.tm_min);
            setSegundo(date.tm_sec);
        }
    else
        {

            setSegundo(segundo);
            setMinuto(minuto);
            setHora(hora);
        }

}

void Horario::setSegundo(int segundo)
{

    _segundo = segundo;
}

void Horario::setMinuto(int minuto)
{

    _minuto = minuto;
}

void Horario::setHora(int hora)
{

    _hora = hora;
}

int Horario::getSegundo()
{

    return _segundo;
}

int Horario::getMinuto()
{

    return _minuto;
}

int Horario::getHora()
{

    return _hora;
}

bool Horario::validarHorario(int segundo, int minuto, int hora)
{

    if(segundo >= 60 || segundo < 0 || minuto >= 60 || minuto < 0 || hora < 0 || hora > 23)
        {

            return false;
        }

    return true;
}

string Horario::toString()
{

    string segundos, minutos, horas, resultado;

    if(getSegundo() < 10)
        {

            segundos = "0" + to_string(getSegundo());
        }
    else
        {

            segundos = to_string(getSegundo());
        }

    if(getMinuto() < 10)
        {

            minutos = "0" + to_string(getMinuto());
        }
    else
        {

            minutos = to_string(getMinuto());
        }

    if(getHora() < 10)
        {

            horas = "0" + to_string(getHora());
        }
    else
        {

            horas = to_string(getHora());
        }

    resultado = horas + ":" + minutos + ":" + segundos;

    return resultado;
}
