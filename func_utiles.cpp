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
void limpiarPantalla()
{
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
void limpiarPantallaSinPausa()
{
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

std::string limpiarCaracteresNoAscii(std::string nombreMateria)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::wstring wideString = converter.from_bytes(nombreMateria);

    std::wstring resultado;

    for (wchar_t wc : wideString)
        {
            if (wc>127)
                {
                    switch (wc)
                        {
                        case L'á':
                            resultado += L'a';
                            break;
                        case L'Á':
                            resultado += L'A';
                            break;
                        case L'ó':
                            resultado += L'o';
                            break;
                        case L'Ó':
                            resultado += L'O';
                            break;
                        case L'é':
                            resultado += L'e';
                            break;
                        case L'É':
                            resultado += L'E';
                            break;
                        case L'í':
                            resultado += L'i';
                            break;
                        case L'Í':
                            resultado += L'I';
                            break;
                        case L'ú':
                            resultado += L'u';
                            break;
                        case L'Ú':
                            resultado += L'U';
                            break;
                        case L'ñ':
                            resultado += L'n';
                            break;
                        case L'Ñ':
                            resultado += L'N';
                            break;
                        }
                }
            else
                {
                    resultado += wc;
                }
        }

    return converter.to_bytes(resultado);
}

