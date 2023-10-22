#include "FechaHorario.h"

FechaHorario::FechaHorario()
{
    //ctor
}

FechaHorario::FechaHorario(const Fecha& fecha, const Horario& horario){

    _fecha = fecha;
    _horario = horario;
}

FechaHorario::FechaHorario(int dia, int mes, int anio, int segundo, int minuto, int horas){

    _fecha = Fecha(dia, mes, anio);
    _horario = Horario(segundo, minuto, horas);

}

void FechaHorario::setFecha(const Fecha& fecha){

    _fecha = fecha;
}

void FechaHorario::setFecha(int dia, int mes, int anio){

    _fecha = Fecha(dia, mes, anio);
}

void FechaHorario::setHorario(const Horario& horario){

    _horario = horario;
}

void FechaHorario::setHorario(int segundos, int minutos, int horas){

    _horario = Horario(segundos, minutos, horas);
}

Fecha FechaHorario::getFecha() const{

    return _fecha;
}

Horario FechaHorario::getHorario() const{

    return _horario;
}

std::string FechaHorario::toString() const{

    std::string aux;

    Fecha auxFecha;
    Horario auxHorario;

    auxFecha = _fecha;
    auxHorario = _horario;

    aux = auxFecha.toString();
    aux += " ";
    aux += auxHorario.toString();

    return aux;
}
