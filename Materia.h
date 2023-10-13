#ifndef MATERIA_H
#define MATERIA_H

const int CANTMATERIAS = 10;
const int LONGMAX = 30;

class Materia
{
    public:
        Materia();

        void setNombreMateria(const char* nombre);
        void setIdMateria(const char* idMateria);
        void setIdMateriasRequeridas(int pos, const char* idMateriaRequerida);
        void setCuatrimestreSugerido(int cuatrimestreSugerido);
        void setCuatrimestreDeDuracion(int cuatrimestreDeDuracion);

        const char* getNombreMateria() const;
        const char* getIdMateria() const;
        const char* getIdMateriasRequeridas(int pos) const;
        int getCuatrimestreSugerido() const;
        int getCuatrimestreDeDuracion() const;

    private:

        char _nombre[30];
        char _idMateria[LONGMAX];
        char _idMateriasRequeridas[CANTMATERIAS][LONGMAX];
        int _cuatrimestreSugerido;
        int _cuatrimestresDeDuracion;
};

#endif // MATERIA_H
