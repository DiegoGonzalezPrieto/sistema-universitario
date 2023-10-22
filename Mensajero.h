#ifndef MENSAJERO_H
#define MENSAJERO_H

class Mensajero
{
public:
    Mensajero() { }
    void mensajeAdvertencia(string mensaje);
    void mensajeInformacion(string mensaje);
    void mensajeError(string mensaje) ;

};

#endif // MENSAJERO_H
