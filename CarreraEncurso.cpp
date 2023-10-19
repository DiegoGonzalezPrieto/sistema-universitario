#include "CARRERAENCURSO.h"
#include <iostream>
#include <cstring>
#include <vector>

//CONSTRUCTOR

CARRERAENCURSO::CARRERAENCURSO()
{
    // Inicializar los arreglos con valores por defecto si es necesario
    legajo[0] = '\0';
    _nombreestudiante[0] = '\0';
    _idCuatrimestre[0] = '\0';
    for (int i = 0; i < 50; ++i)
    {
        _idMateriasCursadas[i][0] = '\0';
    }
}


//METODOS GET

std::string CARRERAENCURSO::getLegajo() const
{
    return std::string(legajo);
}

std::string CARRERAENCURSO::getNombreEstudiante() const
{
    return std::string(_nombreestudiante);
}

std::string CARRERAENCURSO::getIdCuatrimestre() const
{
    return std::string(_idCuatrimestre);
}

std::string CARRERAENCURSO::getIdMateriaCursada(int index) const
{
    return _idMateriasCursadas[index];
}

//METODOS SET

void CARRERAENCURSO::setLegajo(const std::string& nuevoLegajo)
{
    strncpy(legajo, nuevoLegajo.c_str(), sizeof(legajo) - 1);
    legajo[sizeof(legajo) - 1] = '\0';
}

void CARRERAENCURSO::setNombreEstudiante(const std::string& nuevoNombre)
{
    strncpy(_nombreestudiante, nuevoNombre.c_str(), sizeof(_nombreestudiante) - 1);
    _nombreestudiante[sizeof(_nombreestudiante) - 1] = '\0';
}

void CARRERAENCURSO::setIdCuatrimestre(const std::string& nuevoIdCuatrimestre)
{
    strncpy(_idCuatrimestre, nuevoIdCuatrimestre.c_str(), sizeof(_idCuatrimestre) - 1);
    _idCuatrimestre[sizeof(_idCuatrimestre) - 1] = '\0';
}

// Sett una Materia Cursada / toma una cadena de caracteres.

void CARRERAENCURSO::setIdMateriaCursada(const std::string& nuevoIdMateria)
{
    // Buscar el primer espacio disponible
    int index = -1;
    for (int i = 0; i < 50; ++i)
    {
        if (_idMateriasCursadas[i][0] == '\0')
        {
            index = i;
            break;
        }
    }

    // Verificar si se encontró un espacio disponible
    if (index != -1)
    {
        strncpy(_idMateriasCursadas[index], nuevoIdMateria.c_str(), sizeof(_idMateriasCursadas[index]) - 1);
        _idMateriasCursadas[index][sizeof(_idMateriasCursadas[index]) - 1] = '\0';
        std::cout<<"MATERIA AGREGADA CORRECTAMENTE "<<nuevoIdMateria<<std::endl;
    }
    else
    {
        // Manejar el caso cuando no hay espacio disponible
        std::cout << "Error: No hay espacio disponible para agregar más materias" << std::endl;
    }
}

//ESTA SOBRECARGA PERMITE MANDAR UN VECTOR STRING Y ASIGNAR LOS ID DE LAS MATERIAS CURSADAS

void CARRERAENCURSO::setIdMateriaCursada(const std::vector<std::string>& nuevoIdMaterias)
{
    // Recorrer la matriz de nuevos ID de materias
    for (const auto& n: nuevoIdMaterias)
    {
        // Buscar el primer espacio disponible
        int index = -1;
        for (int i = 0; i < 50; ++i)
        {
            if (_idMateriasCursadas[i][0] == '\0')
            {
                index = i;
                break;
            }
        }

        // Verificar si se encontró un espacio disponible
        if (index != -1)
        {
            strncpy(_idMateriasCursadas[index], n.c_str(), sizeof(_idMateriasCursadas[index]) - 1);
            _idMateriasCursadas[index][sizeof(_idMateriasCursadas[index]) - 1] = '\0';
            std::cout << "MATERIA AGREGADA CORRECTAMENTE: " << n << std::endl;
        }
        else
        {
            // Manejar el caso cuando no hay espacio disponible
            std::cout << "Error: No hay espacio disponible para agregar más materias" << std::endl;
            break;  // Salir del bucle, ya que no hay más espacio
        }
    }
}
void CARRERAENCURSO::mostrarIdMateriasCursadas() const
{
    std::cout << "ID de Materias Cursadas:" << std::endl;
    for (int i = 0; i < 50 && _idMateriasCursadas[i][0] != '\0'; ++i)
    {
        std::cout << " - " << _idMateriasCursadas[i] << std::endl;
    }
}
