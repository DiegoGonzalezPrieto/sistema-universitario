#ifndef CURSADAMATERIA_H
#define CURSADAMATERIA_H

#include <vector>
#include <string>

using namespace std;

//#include "Materia.h"
//#include "DatosCursada.h"
//#include "Unidad.h"

enum EstadoMateria {
    EN_CURSO = 0,
    REGULARIZADA = 1,
    APROBADA = 2,
    ANULADA = 3
};

class CursadaMateria//: public Materia
{
    public:
        CursadaMateria();
        CursadaMateria(string cuatrimestreActual); // TODO

        string getIdCuatrimestreInicio();
        void setIdCuatrimestreInicio(string);
        string getIdCuatrimestreActual();
        void setIdCuatrimestreActual(string);
        string getEstadoToString();
        EstadoMateria getEstado();
        void setEstado(EstadoMateria);
//        string getDatosCursadaToString();
//        vector<DatosCursada> getDatosCursada();
//        void setDatosCursada(vector<DatosCursada>, int);
//        vector<Unidad> getUnidades();
//        void setUnidades(vector<Unidad>);


        string getIdCursadaMateria();
        string toString();

    protected:

    private:
        char _idCuatrimestreInicio[7];
        char _idCuatrimestreActual[7];
        EstadoMateria _estado;
//        DatosCursada _datosCursada[4];
//        Unidad _unidades[14];


};

#endif // CURSADAMATERIA_H
