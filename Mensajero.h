#ifndef MENSAJERO_H
#define MENSAJERO_H
#include "rlutil.h"
class Mensajero
{
public:
    Mensajero() { }
    void mensajeAdvertencia(std::string mensaje);
    void mensajeInformacion(std::string mensaje);
    void mensajeError(std::string mensaje) ;

};

#endif // MENSAJERO_H
