#ifndef MENSAJERO_H
#define MENSAJERO_H

class Mensajero
{
public:
    Mensajero() { }
    void mensajeAdvertencia(const char* mensaje);
    void mensajeInformacion(const char* mensaje);
    void mensajeError(const char* mensaje) ;

};

#endif // MENSAJERO_H
