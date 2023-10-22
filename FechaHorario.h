#ifndef FECHAHORARIO_H
#define FECHAHORARIO_H

#include <string>

#include "Fecha.h"
#include "Horario.h"

class FechaHorario
{
    public:

        FechaHorario();
        FechaHorario(const Fecha& fecha, const Horario& horario);
        FechaHorario(int dia, int mes, int anio, int segundo, int minuto, int horas);


        void setFecha(const Fecha& fecha);
        void setFecha(int dia, int mes, int anio);
        void setHorario(const Horario& horario);
        void setHorario(int segundos, int minutos, int horas);


        Fecha getFecha() const;
        Horario getHorario() const;

        std::string toString() const;


    private:
        Fecha _fecha;
        Horario _horario;
};

#endif // FECHAHORARIO_H
