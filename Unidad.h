#ifndef UNIDAD_H
#define UNIDAD_H

#include <cstring>

class Unidad
{
    public:
        Unidad();
        string getRuta();
        void setRuta(string r);

        float getPorcentajeCompletado();

    protected:

    private:
    char _ruta[100];
};

#endif // UNIDAD_H
