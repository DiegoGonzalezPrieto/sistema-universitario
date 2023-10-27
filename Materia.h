#ifndef MATERIA_H
#define MATERIA_H

#include <string>
#include "func_utiles.h"

const int CANTMATERIAS = 10;
const int LONGMAXID = 10;
const int LONGMAXNOMBRE = 60;

class Materia
{
    public:
        Materia();

        void setNombreMateria(const std::string& nombre);
        void setIdMateria(const std::string& idMateria);
        void setIdMateriasRequeridas(int pos, const std::string& idMateriaRequerida);
        void setCuatrimestreSugerido(int cuatrimestreSugerido);
        void setCuatrimestreDeDuracion(int cuatrimestreDeDuracion);

        std::string getNombreMateria() const;
        std::string getIdMateria() const;
        std::string getIdMateriasRequeridas(int pos) const;
        int getCuatrimestreSugerido() const;
        int getCuatrimestreDeDuracion() const;

        std::string toString() const;

    private:

        char _nombre[LONGMAXNOMBRE];
        char _idMateria[LONGMAXID];
        char _idMateriasRequeridas[CANTMATERIAS][LONGMAXID];
        int _cuatrimestreSugerido;
        int _cuatrimestresDeDuracion;
};

#endif // MATERIA_H
