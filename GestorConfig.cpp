#include <iostream>
using namespace std;
#include "GestorConfig.h"
#include "Menu.h"
#include "func_utiles.h"

GestorConfig::GestorConfig(string rutaConfig) : _archivo(rutaConfig)
{
    //ctor
}

void GestorConfig::iniciar()
{

    string tituloMenu = "** Configuración **";
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
    cout << endl;
}


void GestorConfig::editarValoresDeConfig()
{
    cout << endl;
    cout << "****************************************" << endl;
    cout << "*** Editar valores de Configuración  ***" << endl;
    cout << "****************************************" << endl;
    cout << endl;

    vector<Config> configuraciones;
    if(!_archivo.leerRegistros(configuraciones))
        {
            _m.mensajeError("No se pudo leer el archivo de configuración.");
            return;
        }

    for (int i =0; i<configuraciones.size(); i++)
        {
            cout << "(" << i+1<<") " <<configuraciones[i].getClave() << " : " << configuraciones[i].getValor()<< endl;
        }
    cout << endl;

    cout << "Seleccionar valor a modificar (0 para volver): ";
    int selec, cantConfig = configuraciones.size();

    while (true)
        {
            selec = validar<int>();
            if (selec == 0) return;
            if (selec < 1 || selec > cantConfig)
                {
                    _m.mensajeError("Seleccionar un valor entre 1 y " + to_string(cantConfig));
                }
            else
                {
                    break;
                }
        }
    int posicion = selec-1;
    Config c = configuraciones[posicion];
    cout << "Ingresar nuevo valor para " << c.getClave() << "." << endl;
    cout << "Debe ser de tipo ";
    TipoConfig t = c.getTipoConfig();
    switch (t)
        {
        case TEXTO:
        {
            cout << "TEXTO: ";
            string valor;
            getline(cin>>ws, valor);
            c.setValor(valor);
            break;
        }
        case ENTERO:
        {
            cout << "NUMERO ENTERO: ";
            int valor = validar<int>();
            c.setValor(to_string(valor));
            break;
        }
        case DECIMAL:
        {
            cout << "NUMERO DECIMAL: ";
            float valor = validar<float>();
            c.setValor(to_string(valor));
            break;
        }
        }

    if (_archivo.modificarRegistro(posicion, c))
    {
        _m.mensajeInformacion("Configuración modificada correctamente.");
    }
    else
    {
        _m.mensajeError("No se pudo modificar la configuración.");
        return;
    }
    if (Config::leerConfig(_archivo.getNombre()))
    {
        _m.mensajeInformacion("Configuración del programa actualizada.");
    }
    else
    {
        _m.mensajeError("No se pudo actualizar la configuración, reiniciar el programa para que los cambios tengan efecto.");
        return;
    }


}
