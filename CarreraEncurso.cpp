#include "CarreraEnCurso.h"
#include <iostream>
#include <cstring>

CarreraEnCurso::CarreraEnCurso() {
    // Inicializar los arreglos con valores por defecto si es necesario
    legajo[0] = '\0';
    _nombreestudiante[0] = '\0';
    _idCuatrimestre[0] = '\0';
    for (int i = 0; i < 50; ++i) {
        _idMateriasCursadas[i][0] = '\0';
    }
}

const char* CarreraEnCurso::getLegajo() const {
    return legajo;
}

const char* CarreraEnCurso::getNombreEstudiante() const {
    return _nombreestudiante;
}

const char* CarreraEnCurso::getIdCuatrimestre() const {
    return _idCuatrimestre;
}

void CarreraEnCurso::setLegajo(const char* nuevoLegajo) {
    strncpy(legajo, nuevoLegajo, sizeof(legajo) - 1);
    legajo[sizeof(legajo) - 1] = '\0';
}

void CarreraEnCurso::setNombreEstudiante(const char* nuevoNombre) {
    strncpy(_nombreestudiante, nuevoNombre, sizeof(_nombreestudiante) - 1);
    _nombreestudiante[sizeof(_nombreestudiante) - 1] = '\0';
}

void CarreraEnCurso::setIdCuatrimestre(const char* nuevoIdCuatrimestre) {
    strncpy(_idCuatrimestre, nuevoIdCuatrimestre, sizeof(_idCuatrimestre) - 1);
    _idCuatrimestre[sizeof(_idCuatrimestre) - 1] = '\0';
}

//Retorna el Id de una materia Guardada en el indice.

const char* CarreraEnCurso::getIdMateriaCursada(int index) const {
    // Verificar que el índice esté dentro del rango
    if (index >= 0 && index < 50) {
        return _idMateriasCursadas[index];
    } else {
        // Devolver un valor por defecto o manejar el error según sea necesario
        return "Índice fuera de rango";
    }
}
// Sett una Materia Cursada

void CarreraEnCurso::setIdMateriaCursada(const char* nuevoIdMateria) {
    // Buscar el primer espacio disponible
    int index = -1;
    for (int i = 0; i < 50; ++i) {
        if (_idMateriasCursadas[i][0] == '\0') {
            index = i;
            break;
        }
    }
    // Verificar si se encontró un espacio disponible
    if (index != -1) {
        strncpy(_idMateriasCursadas[index], nuevoIdMateria, sizeof(_idMateriasCursadas[index]) - 1);
        _idMateriasCursadas[index][sizeof(_idMateriasCursadas[index]) - 1] = '\0';
        std::cout<<"MATERIA AGREGADA CORRECTAMENTE"<<std::endl;

    } else {
        // Manejar el caso cuando no hay espacio disponible
        std::cout << "Error: No hay espacio disponible para agregar más materias" << std::endl;
    }
}

int CarreraEnCurso::buscarIndiceMateria(const char* idMateria) {
    for (int i = 0; i < 50; ++i) {
        if (strcmp(_idMateriasCursadas[i], idMateria) == 0) {
            return i;  // La materia fue encontrada, devolver el índice
        }
    }
    // Si no se encuentra, devuelve -1
    return -1;
}

void CarreraEnCurso::mostrarIdMateriasCursadas() const {
    std::cout << "ID de Materias Cursadas:" << std::endl;
    for (int i = 0; i < 50 && _idMateriasCursadas[i][0] != '\0'; ++i) {
        std::cout << " - " << _idMateriasCursadas[i] << std::endl;
    }
}
