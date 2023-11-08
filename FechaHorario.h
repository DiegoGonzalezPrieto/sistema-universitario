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

        bool operator <(FechaHorario & fh)
    {
        if (_fecha < fh._fecha) return true;
        if (_fecha > fh._fecha) return false;
        if (_horario < fh._horario) return true;
        return false;
    }
    bool operator >(FechaHorario & fh)
    {
        if (_fecha > fh._fecha) return true;
        if (_fecha < fh._fecha) return false;
        if (_horario > fh._horario) return true;
        return false;
    }
    bool operator ==(FechaHorario & fh)
    {
        if (_fecha != fh._fecha || _horario != fh._horario)
            {
                return false;
            }
        return true;
    }
    bool operator !=(FechaHorario & fh)
    {
        if (_fecha != fh._fecha || _horario != fh._horario)
            {
                return true;
            }
        return false;
    }

    bool operator >=(FechaHorario & fh)
    {
        if (*this == fh) return true;
        if (*this > fh) return true;
        return false;
    }
    bool operator <=(FechaHorario & fh)
    {
        if (*this == fh) return true;
        if (*this < fh) return true;
        return false;
    }

    private:
        Fecha _fecha;
        Horario _horario;
};

#endif // FECHAHORARIO_H
