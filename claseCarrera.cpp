#include <iostream>
#include "CLASECARRERA.h"
#include <cstring>
#include <vector>

CLASECARRERA::CLASECARRERA()
{

    // Inicializar la matriz con caracteres nulos
    for (int i = 0; i < 50; ++i)
    {
        std::memset(_idMaterias[i], '\0', sizeof(_idMaterias[i]));
    }
}

CLASECARRERA::CLASECARRERA(const std::string& nombreUniversidad, const std::string& nombrecarrera)
{
    setNombreUniversidad(nombreUniversidad);
    setNombreCarrera(nombrecarrera);
    for (int i = 0; i < 50; ++i)
    {
        std::memset(_idMaterias[i], '\0', sizeof(_idMaterias[i]));
    }
}

// Implementación de los métodos get

std::string CLASECARRERA::getNombreUniversidad() const
{
    return _nombreUniversidad;
}

std::string CLASECARRERA::getNombreCarrera() const
{
    return _nombreCarrera;
}

std::string CLASECARRERA::getIdMateria(int index) const
{
    return _idMaterias[index];
}

// Implementación de los métodos set

void CLASECARRERA::setNombreUniversidad(const std::string& nombreUniversidad)
{
    std::strncpy(_nombreUniversidad, nombreUniversidad.c_str(), sizeof(_nombreUniversidad) - 1);
    _nombreUniversidad[sizeof(_nombreUniversidad) - 1] = '\0';  // Asegurar la terminación nula
}

void CLASECARRERA::setNombreCarrera(const std::string& nombre)
{
    std::strncpy(_nombreCarrera, nombre.c_str(), sizeof(_nombreCarrera) - 1);
    _nombreCarrera[sizeof(_nombreCarrera) - 1] = '\0';  // Asegurar la terminación nula
}

//ASIGNAR UN ID DE MATERIA

void CLASECARRERA::setIdMateria(const std::string& nuevoIdMateria)
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
        std::cout << "MATERIA AGREGADA CORRECTAMENTE" << std::endl;
    }
    else
    {
        // Manejar el caso cuando no hay espacio disponible
        std::cout << "Error: No hay espacio disponible para agregar más materias" << std::endl;
    }
}

//SOBRECARGA PARA ENVIARLE UNA MATRIZ DE TIPO VECTOR Y ASINGAR TODOS LOS ID DE MATERIAS.

void CLASECARRERA::setIdMaterias(const std::vector<std::string>& nuevosIdMaterias)
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
            std::cout << "MATERIA AGREGADA CORRECTAMENTE: " << nuevoIdMateria << std::endl;
        }
        else
        {
            // Manejar el caso cuando no hay espacio disponible
            std::cout << "Error: No hay espacio disponible para agregar más materias" << std::endl;
            break;
        }
    }
}







