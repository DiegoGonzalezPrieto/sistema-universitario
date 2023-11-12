#include <iostream>

#include "func_utiles.h"

#include "rlutil.h"

bool cargarCadenaConString(std::string input, char* output, size_t tamanioOutput)
{
    int largoInput = input.size();

    std::strncpy(output, input.c_str(), tamanioOutput - 1);
    output[tamanioOutput-1] = '\0';  // Asegurar la terminación nula

    return (largoInput < (int)tamanioOutput);
}


int obtenerNumeroEntero(std::string mensajeError)
{
    while (true)
        {
            std::string input = "";
            getline(std::cin, input);
            int resultado;
            bool salir=true;

            try
                {
                    resultado = stoi(input);
                }
            catch (...)
                {
                    std::cout << mensajeError;
                    salir = false;
                }

            if (salir) return resultado;
        }
}

float obtenerNumeroDecimal(std::string mensajeError)
{
    while (true)
        {
            std::string input = "";
            getline(std::cin, input);
            float resultado;
            bool salir=true;

            try
                {
                    resultado = stof(input);
                }
            catch (...)
                {
                    std::cout << mensajeError;
                    salir = false;
                }

            if (salir) return resultado;
        }
}
void limpiarPantalla(){
    rlutil::saveDefaultColor();
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::LIGHTMAGENTA);
    std::cout<<"Presione una tecla para continuar . . . ";
    rlutil::resetColor();
    std::cin.get();

#ifdef _WIN32
#define SISTEMA "Windows"
#elif __linux__
#define SISTEMA "Linux"
#endif
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

}
void limpiarPantallaSinPausa(){
#ifdef _WIN32
#define SISTEMA "Windows"
#elif __linux__
#define SISTEMA "Linux"
#endif
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

}


