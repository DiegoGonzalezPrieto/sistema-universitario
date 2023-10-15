#ifndef MATERIA_H
#define MATERIA_H

#include <string>

const int CANTMATERIAS = 10;
const int LONGMAX = 30;

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

        char _nombre[30];
        char _idMateria[LONGMAX];
        char _idMateriasRequeridas[CANTMATERIAS][LONGMAX];
        int _cuatrimestreSugerido;
        int _cuatrimestresDeDuracion;
};

#endif // MATERIA_H
