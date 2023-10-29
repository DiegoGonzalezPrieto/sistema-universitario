#ifndef FUNC_ARCHIVOS_H_INCLUDED
#define FUNC_ARCHIVOS_H_INCLUDED

/// Cuenta la cantidad de archivos en esa ruta (no es recursivo).
int contarArchivos(string ruta);
/// Crea todos los directorios que no existen y son parte de la ruta ingresada.
bool crearDirectorios(string ruta);


#endif // FUNC_ARCHIVOS_H_INCLUDED
