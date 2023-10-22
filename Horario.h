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

    private:
        int _segundo;
        int _minuto;
        int _hora;

};

#endif // HORA_H
