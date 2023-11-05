#include <iostream>
#include "Carrera.h"
#include <cstring>


Carrera::Carrera()
{
}
std::string Carrera::getNombreUniversidad() const
{
    return _nombreUniversidad;
}

std::string Carrera::getNombreCarrera() const
{
    return _nombreCarrera;
}

std::string Carrera::getLegajo() const
{
    return std::string(_legajo);
}

std::string Carrera::getNombreEstudiante() const
{
    return std::string(_nombreEstudiante);
}

void Carrera::setNombreUniversidad(const std::string& nombreUniversidad)
{
    std::strncpy(_nombreUniversidad, nombreUniversidad.c_str(), sizeof(_nombreUniversidad) - 1);
    _nombreUniversidad[sizeof(_nombreUniversidad) - 1] = '\0';  // Asegurar la terminación nula
}

void Carrera::setNombreCarrera(const std::string& nombre)
{
    std::strncpy(_nombreCarrera, nombre.c_str(), sizeof(_nombreCarrera) - 1);
    _nombreCarrera[sizeof(_nombreCarrera) - 1] = '\0';  // Asegurar la terminación nula
}

void Carrera::setLegajo(const std::string& nuevoLegajo)
{
    strncpy(_legajo, nuevoLegajo.c_str(), sizeof(_legajo) - 1);
    _legajo[sizeof(_legajo) - 1] = '\0';
}

void Carrera::setNombreEstudiante(const std::string& nuevoNombre)
{
    strncpy(_nombreEstudiante, nuevoNombre.c_str(), sizeof(_nombreEstudiante) - 1);
    _nombreEstudiante[sizeof(_nombreEstudiante) - 1] = '\0';
}

 std::string Carrera::toString() const
    {
        std::string Aux;
        Aux += "Nombre Universidad: " + getNombreUniversidad() + "\n";
        Aux += "Nombre Carrera: " + getNombreCarrera() + "\n";
        Aux += "Legajo: " + getLegajo() + "\n";
        Aux += "Nombre Estudiante: " + getNombreEstudiante() + "\n";
        return Aux;
    }






