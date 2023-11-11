#ifndef CURSADAMATERIA_H
#define CURSADAMATERIA_H

#include <vector>
#include <string>

using namespace std;

#include "Materia.h"
#include "DatosCursada.h"
#include "Unidad.h"

enum EstadoMateria
{
    MAT_EN_CURSO = 0,
    MAT_REGULARIZADA = 1,
    MAT_APROBADA = 2,
    MAT_ANULADA = 3
};

class CursadaMateria: public Materia
{
public:
    CursadaMateria();
    CursadaMateria(Materia);

    const int getMaxUnidades();
    const int getMaxDatosCursada();
    string getIdCuatrimestreInicio();
    void setIdCuatrimestreInicio(string);
    string getEstadoToString();
    EstadoMateria getEstado();
    void setEstado(EstadoMateria);
    string getDatosCursadaToString();
    vector<DatosCursada> getDatosCursada();
    void setDatosCursada(vector<DatosCursada>);
    vector<Unidad> getUnidades();
    void setUnidades(vector<Unidad>);

    void agregarDatoCursada(DatosCursada);
    void agregarUnidad(Unidad);


    string getIdCursadaMateria();
    string toString();
    string toFullString();

protected:

private:
    const static int MAX_UNIDADES = 14;
    const static int MAX_DATOS_CURSADA = 4;
    char _idCuatrimestreInicio[7];
    EstadoMateria _estado;
    DatosCursada _datosCursada[MAX_DATOS_CURSADA];
    Unidad _unidades[MAX_UNIDADES];


};

#endif // CURSADAMATERIA_H
