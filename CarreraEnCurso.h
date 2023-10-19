#ifndef CARRERAENCURSO_H_INCLUDED
#define CARRERAENCURSO_H_INCLUDED
#include "CLASECARRERA.h"
#include <string>
#include <vector>

class CARRERAENCURSO : public CLASECARRERA
{
public:
    CARRERAENCURSO();  // Constructor

    // Métodos getter
    std::string getLegajo() const;
    std::string getNombreEstudiante() const;
    std::string getIdCuatrimestre() const;
    std::string getIdMateriaCursada(int index) const;
    void mostrarIdMateriasCursadas() const;

    // Métodos setter

    void setLegajo(const std::string& nuevoLegajo);
    void setNombreEstudiante(const std::string& nuevoNombre);
    void setIdCuatrimestre(const std::string& nuevoIdCuatrimestre);
    void setIdMateriaCursada(const std::string& nuevoIdMateria);
    void setIdMateriaCursada(const std::vector<std::string>& nuevoIdMaterias);

private:
    char legajo[15];
    char _nombreestudiante[30];
    char _idMateriasCursadas[50][50];
    char _idCuatrimestre[20];
};

#endif // CARRERAENCURSO_H_INCLUDED
