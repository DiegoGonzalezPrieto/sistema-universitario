#ifndef UNIDAD_H
#define UNIDAD_H

#include <cstring>

class Unidad
{
    public:
        Unidad();
        Unidad(string);
        string getRuta();
        void setRuta(string r);

        string getRutaCompletado();

    private:
    char _ruta[100];
};

#endif // UNIDAD_H
