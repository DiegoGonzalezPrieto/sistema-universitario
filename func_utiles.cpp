#include <iostream>

#include "func_utiles.h"

bool cargarCadenaConString(std::string input, char* output, size_t tamanioOutput)
{
    int largoInput = input.size();

    std::strncpy(output, input.c_str(), tamanioOutput - 1);
    output[tamanioOutput-1] = '\0';  // Asegurar la terminación nula

    return (largoInput < (int)tamanioOutput);
}
