#ifndef FUNC_ARCHIVOS_H_INCLUDED
#define FUNC_ARCHIVOS_H_INCLUDED

#include <cstring>

/// Devuelve true si el input cabe en el output. Trunca el input si es necesario. Agrega terminación nula al final.
bool cargarCadenaConString(std::string input, char* output, size_t tamanioOutput);


#endif // FUNC_ARCHIVOS_H_INCLUDED
