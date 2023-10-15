#ifndef CARRERAENCURSO_H_INCLUDED
#define CARRERAENCURSO_H_INCLUDED
#include "claseCarrera.h"

class CarreraEnCurso : public claseCarrera {
public:
    CarreraEnCurso();  // Constructor

    // Métodos getter
    const char* getLegajo() const;
    const char* getNombreEstudiante() const;
    const char* getIdCuatrimestre() const;
    const char* getIdMateriaCursada(int index) const;

    // Métodos setter
    void setLegajo(const char* nuevoLegajo);
    void setNombreEstudiante(const char* nuevoNombre);
    void setIdCuatrimestre(const char* nuevoIdCuatrimestre);
   void setIdMateriaCursada(const char* nuevoIdMateria);
    int buscarIndiceMateria(const char* idMateria);
    void mostrarIdMateriasCursadas() const;
private:
    char legajo[15];
    char _nombreestudiante[30];
    char _idMateriasCursadas[50][50];
    char _idCuatrimestre[20];
};

#endif // CARRERAENCURSO_H_INCLUDED
