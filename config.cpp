#include <iostream>
#include <vector>
#include "config.h"
#include "Archivo.h"
#include "Mensajero.h"
using namespace std;


/// Aquí van las variables con sus valores por defecto (se reemplazan por los valores que haya en el archivo)

int DIAS_DE_AVISO_EVENTO = 0;


bool Config::leerConfig(string rutaConfig)
{
    Archivo<Config> configFile(rutaConfig);
    Mensajero m;

    vector<Config> configuraciones;
    if(!configFile.leerRegistros(configuraciones))
        {
            m.mensajeAdvertencia("No se pudo leer el archivo de configuracion.");
            return false;
        }

    for (Config c : configuraciones)
        {
            if (c.getClave()=="DIAS_DE_AVISO_EVENTO")
                {
                    try
                    {
                    DIAS_DE_AVISO_EVENTO = stoi(c.getValor());
                    }
                    catch (...)
                    {
                        m.mensajeError("Error al leer el dato " + c.getClave());
                    }
                }
            // Acá se agregarían nuevas variables posibles

        }

    cout << "CONFIG LEIDO - "<< configuraciones.size() << " VALOR/ES" <<endl;
    return true;
}

bool Config::agregarConfig(string rutaConfig, string clave, string valor, TipoConfig t)
{
    Archivo<Config> configFile(rutaConfig);
    Config c;
    c.setClave(clave);
    c.setValor(valor);
    c.setTipoConfig(t);
    return configFile.agregarRegistro(c);
}

bool Config::crearConfig(string rutaConfig)
{
    if (agregarConfig(rutaConfig, "DIAS_DE_AVISO_EVENTO", "7", ENTERO))
        return true;
    else return false;
}

