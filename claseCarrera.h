#ifndef CLASECARRERA_H
#define CLASECARRERA_H
#include <iostream>
#include <cstring>
#include <vector>

class CLASECARRERA
{
public:
    // Constructor
    CLASECARRERA();
    CLASECARRERA(const std::string& nombreUniversidad, const std::string& nombreCarrera);
    // Métodos get
    std::string getNombreUniversidad() const;
    std::string getNombreCarrera() const;
    std::string getIdMateria(int index) const;
    std::string getLegajo() const;
    std::string getNombreEstudiante() const;

    void setLegajo(const std::string& nuevoLegajo);
    void setNombreEstudiante(const std::string& nuevoNombre);
    void setNombreUniversidad(const std::string& nombreUniversidad);
    void setNombreCarrera(const std::string& nombre);
    void setIdMateria(const std::string& idMateria);
    void setIdMaterias(const std::vector<std::string>& nuevosIdMaterias);

private:
    char _nombreUniversidad[30];
    char _nombreCarrera[30];
    char _idMaterias[50][50];
    char _legajo[15];
    char _nombreEstudiante[30];

};

#endif // CLASECARRERA_H
