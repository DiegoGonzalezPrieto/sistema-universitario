#ifndef CLASECARRERA_H
#define CLASECARRERA_H
class claseCarrera {
public:
    // Constructor
    claseCarrera();

    // Métodos get
    const char* getNombreUniversidad() const;
    const char* getNombre() const;
    const char* getIdMateria(int index) const;

    // Métodos set
    void setNombreUniversidad(const char* nombreUniversidad);
    void setNombre(const char* nombre);
    //El primer dato es un entero que indica la posicion, el segundo dato entre comillas el codigo de la materia.
    void setIdMateria(int index, const char* idMateria);

private:
    char _nombreUniversidad[30];
    char _nombre[30];
    char _idMaterias[50][50];
};

#endif // CLASECARRERA_H
