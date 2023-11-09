#ifndef FUNC_ARCHIVOS_H_INCLUDED
#define FUNC_ARCHIVOS_H_INCLUDED
#include <iostream>
#include <limits>
#include <cstring>
#include <string>

/// Devuelve true si el input cabe en el output. Trunca el input si es necesario. Agrega terminación nula al final.
bool cargarCadenaConString(std::string input, char* output, size_t tamanioOutput);

/// Obtiene un entero con getline, dejando vacío el buffer de cin
int obtenerNumeroEntero(std::string mensajeError="Valor incorrecto. Ingrese un número entero: ");

/// Obtiene un decimal con getline, dejando vacío el buffer de cin
float obtenerNumeroDecimal(std::string mensajeError="Valor incorrecto. Ingrese un número decimal: ");

/// Valida datos de tipo int y float
template<typename T>
T validar(std::string mensaje)
{
    T entrada;
    while (true)
        {
            std::cin >> entrada;

            if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << mensaje;
                }
            else
                {
                    // Verificar si hay caracteres no válidos en el búfer
                    char c;
                    std::cin.get(c);
                    if (c != '\n' && !std::isdigit(c))
                        {
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << mensaje<< std::endl;
                        }
                    else
                        {
                            break;
                        }
                }
        }

    return entrada;
}

template<typename T>
T validar()
{
    T entrada;
    while (true)
        {
            std::cin >> entrada;

            if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entrada no válida. Intente de nuevo." << std::endl;
                }
            else
                {
                    // Verificar si hay caracteres no válidos en el búfer
                    char c;
                    std::cin.get(c);
                    if (c != '\n' && !std::isdigit(c))
                        {
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Entrada no válida. Intente de nuevo." << std::endl;
                        }
                    else
                        {
                            break;
                        }
                }
        }

    return entrada;
}
void limpiarPantalla();

#endif // FUNC_ARCHIVOS_H_INCLUDED
