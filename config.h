#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "func_utiles.h"

enum TipoConfig
{
    ENTERO = 0,
    DECIMAL = 1,
    TEXTO = 2
};

class Config
{
public:
//    Config(std::string rutaConfig) : nombreArchivo(rutaConfig)
    Config(): clave(""), valor("")
    {}

    std::string getValor()
    {
        return std::string(valor);
    }
    void setValor(std::string s)
    {
        cargarCadenaConString(s, valor, sizeof(valor));
    }

    std::string getClave ()
    {
        return std::string(clave);
    }
    void setClave(std::string s)
    {
        cargarCadenaConString(s, clave, sizeof(clave));
    }

    /// Levanta valores del archivo config.
    static bool leerConfig(std::string rutaConfig);

    /// Crea archivo de config con valores por defecto.
    static bool crearConfig(std::string rutaConfig);

//    std::string getNombreArchivo()
//    {
//        return nombreArchivo;
//    }
//    void setNombreArchivo(std::string na)
//    {
//        nombreArchivo = na;
//    }

private:
    char clave[40];
    char valor[150];
    TipoConfig tipo;
//    std::string nombreArchivo;
};

/// Aquí se declaran las variables de config para estar disponibles en todos los archivos que incluyan este .h

extern int DIAS_DE_AVISO_EVENTO;

#endif // CONFIG_H_INCLUDED
