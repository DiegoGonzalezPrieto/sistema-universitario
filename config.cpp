#include <iostream>
#include <vector>
#include "config.h"
#include "Archivo.h"
#include "Mensajero.h"
using namespace std;


/// Aquí van las variables con sus valores por defecto (si están en config.dat se usaran esos valores)

int DIAS_DE_AVISO_EVENTO = 8;


bool Config::leerConfig(string rutaConfig)
{
    Archivo<Config> configFile(rutaConfig);
    Mensajero m;

    vector<Config> configuraciones;
    if(!configFile.leerRegistros(configuraciones))
        {
            m.mensajeError("No se pudo leer el archivo de configuración.");
            return false;
        }

    for (Config c : configuraciones)
        {
            if (c.getClave()=="DIAS_DE_AVISO_EVENTO")
            {
                DIAS_DE_AVISO_EVENTO = stoi(c.getValor());
            }
            // Acá se agregarían nuevas variables posibles

        }

    cout << "CONFIG LEIDO - "<< configuraciones.size() << " VALORES" <<endl;
    return true;
}

