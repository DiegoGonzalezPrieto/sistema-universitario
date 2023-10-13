#include <iostream>
#include "claseCarrera.h"
#include <cstring>
claseCarrera::claseCarrera() {
}

// Implementación de los métodos get
const char* claseCarrera::getNombreUniversidad() const {
    return _nombreUniversidad;
}

const char* claseCarrera::getNombre() const {
    return _nombre;
}

const char* claseCarrera::getIdMateria(int index) const {
    return _idMaterias[index];
}

// Implementación de los métodos set

void claseCarrera::setNombreUniversidad(const char* nombreUniversidad) {
    std::strncpy(_nombreUniversidad, nombreUniversidad, sizeof(_nombreUniversidad) - 1);
    _nombreUniversidad[sizeof(_nombreUniversidad) - 1] = '\0';  // Asegurar la terminación nula
}

void claseCarrera::setNombre(const char* nombre) {
    std::strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';  // Asegurar la terminación nula
}

void claseCarrera::setIdMateria(int index, const char* idMateria) {
    std::strncpy(_idMaterias[index], idMateria, sizeof(_idMaterias[index]) - 1);
    _idMaterias[index][sizeof(_idMaterias[index]) - 1] = '\0';  // Asegurar la terminación nula
}
