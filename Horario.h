#ifndef HORA_H
#define HORA_H

#include <string>
#include <time.h>

class Horario
{
    public:
        Horario();
        Horario(int segundo, int minuto, int hora);


        void setSegundo(int segundo);
        void setMinuto(int minuto);
        void setHora(int hora);
        int getSegundo();
        int getMinuto();
        int getHora();

        bool validarHorario(int segundo, int minuto, int hora);
        std::string toString();

        bool operator <(Horario & h)
    {
        if (_hora < h.getHora()) return true;
        if (_hora > h.getHora()) return false;
        if (_minuto < h.getMinuto()) return true;
        if (_minuto > h.getMinuto()) return false;
        if (_segundo < h.getSegundo()) return true;
        return false;
    }
    bool operator >(Horario & h)
    {
        if (_hora > h.getHora()) return true;
        if (_hora < h.getHora()) return false;
        if (_minuto > h.getMinuto()) return true;
        if (_minuto < h.getMinuto()) return false;
        if (_segundo > h.getSegundo()) return true;
        return false;
    }
    bool operator ==(Horario & h)
    {
        if (_hora != h.getHora() || _minuto != h.getMinuto() || _segundo != h.getSegundo())
            {
                return false;
            }
        return true;
    }
    bool operator !=(Horario & h)
   {
        if (_hora != h.getHora() || _minuto != h.getMinuto() || _segundo != h.getSegundo())
            {
                return true;
            }
        return false;
    }

    bool operator >=(Horario & h)
    {
        if (*this == h) return true;
        if (*this > h) return true;
        return false;
    }
    bool operator <=(Horario & h)
    {
        if (*this == h) return true;
        if (*this < h) return true;
        return false;
    }
    private:
        int _segundo;
        int _minuto;
        int _hora;

};

#endif // HORA_H
