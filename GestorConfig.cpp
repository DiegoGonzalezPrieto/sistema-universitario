#include <iostream>
using namespace std;
#include "GestorConfig.h"
#include "Menu.h"

GestorConfig::GestorConfig(string rutaConfig) : _archivo(rutaConfig)
{
    //ctor
}

void GestorConfig::iniciar()
{

    string tituloMenu = "\n===============================\n** Gestión de Configuración **\n===============================";
    Menu m({"Ver valores de configuración",
            "Editar configuración"},
           tituloMenu);

    int opc= 1;
    while (opc != 0)
        {
            opc = m.mostrar();
            switch (opc)
                {
                case 0:
                    return;
                case 1:
                    mostrarValoresDeConfig(); // TODO
                    break;
                case 2:
                    editarValoresDeConfig(); // TODO
                    break;


                }
        }
}

void GestorConfig::mostrarValoresDeConfig()
{
    cout << endl;
    cout << "**********************************" << endl;
    cout << "***  Valores de Configuración  ***" << endl;
    cout << "**********************************" << endl;
    cout << endl;

    vector<Config> configuraciones;
    if(!_archivo.leerRegistros(configuraciones))
        {
            _m.mensajeError("No se pudo leer el archivo de configuración.");
            return;
        }

    for (Config c : configuraciones)
        {
            cout << c.getClave() << " : " << c.getValor()<< endl;
        }
}


void GestorConfig::editarValoresDeConfig()
{

}
