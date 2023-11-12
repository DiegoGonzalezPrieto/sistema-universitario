#ifndef GESTORCONFIG_H
#define GESTORCONFIG_H

#include "Mensajero.h"
#include "Archivo.h"
#include "config.h"

class GestorConfig
{
public:
    GestorConfig(std::string rutaConfig);

    void iniciar();
    // METODOS DE USUARIO //

    void mostrarValoresDeConfig(); // TODO

    void editarValoresDeConfig(); // TODO


    // METODOS DE SOPORTE //

protected:

private:
    Mensajero _m;
    Archivo<Config> _archivo;
};

#endif // GESTORCONFIG_H
