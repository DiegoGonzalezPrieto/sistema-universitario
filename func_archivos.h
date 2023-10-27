#ifndef FUNC_ARCHIVOS_H_INCLUDED
#define FUNC_ARCHIVOS_H_INCLUDED

#include <string>

/// Cuenta la cantidad de archivos en esa ruta (no es recursivo).
int contarArchivos(std::string ruta);
/// Crea todos los directorios que no existen y son parte de la ruta ingresada.
bool crearDirectorios(std::string ruta);


#endif // FUNC_ARCHIVOS_H_INCLUDED
