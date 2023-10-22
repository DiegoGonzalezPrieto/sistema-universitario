#include <iostream>
#include "Carrera.h"
#include <cstring>


Carrera::Carrera()
{
     for (int i = 0; i < 50; ++i){

        for (int j = 0; j < 10; ++j){
            _idMaterias[i][j] = '\0';

            }
     }
}
std::string Carrera::getNombreUniversidad() const
{
    return _nombreUniversidad;
}

std::string Carrera::getNombreCarrera() const
{
    return _nombreCarrera;
}

std::string Carrera::getIdMateria(int index) const
{
    return _idMaterias[index];
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

void Carrera::setIdMateria(const std::string& nuevoIdMateria)
{
    // Buscar el primer espacio disponible
    int index = -1;
    for (int i = 0; i < 50; ++i)
    {
        if (_idMaterias[i][0] == '\0')
        {
            index = i;
            break;
        }
    }

    // Verificar si se encontró un espacio disponible
    if (index != -1)
    {
        std::strncpy(_idMaterias[index], nuevoIdMateria.c_str(), sizeof(_idMaterias[index]) - 1);
        _idMaterias[index][sizeof(_idMaterias[index]) - 1] = '\0';
    }

}

//SOBRECARGA PARA ENVIARLE UNA MATRIZ DE TIPO VECTOR Y ASINGAR TODOS LOS ID DE MATERIAS.

void Carrera::setIdMaterias(const std::vector<std::string>& nuevosIdMaterias)
{
    // Buscar el primer espacio disponible
    int index = -1;
    for (const auto& nuevoIdMateria : nuevosIdMaterias)
    {
        for (int i = 0; i < 50; ++i)
        {
            if (_idMaterias[i][0] == '\0')
            {
                index = i;
                break;
            }
        }

        // Verificar si se encontró un espacio disponible
        if (index != -1)
        {
            std::strncpy(_idMaterias[index], nuevoIdMateria.c_str(), sizeof(_idMaterias[index]) - 1);
            _idMaterias[index][sizeof(_idMaterias[index]) - 1] = '\0';
        }
    }
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







