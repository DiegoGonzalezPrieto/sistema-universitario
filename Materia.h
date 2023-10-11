#ifndef MATERIA_H
#define MATERIA_H


class Materia
{
    public:
        Materia();

        void setNombreMateria(const char* nombre);
        void setIdMateria(int idMateria);
        void setIdMateriasRequeridas(int* idMateriasRequeridas, int cantMateriasRequeridas);
        void setIdMateriasRequeridas(int pos, int idMateriaRequerida);
        void setCuatrimestreSugerido(int cuatrimestreSugerido);
        void setCuatrimestreDeDuracion(int cuatrimestreDeDuracion);

        const char* getNombreMateria() const;
        int getIdMateria() const;
        int* getMateriasRequeridas();
        int getMateriasRequeridas(int pos) const;
        int getCuatrimestreSugerido() const;
        int getCuatrimestreDeDuracion() const;

    private:

        char _nombre[30];
        int _idMateria;
        int _idMateriasRequeridas[10];
        int _cuatrimestreSugerido;
        int _cuatrimestresDeDuracion;
};

#endif // MATERIA_H
