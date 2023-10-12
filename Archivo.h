#ifndef ARCHIVO_H
#define ARCHIVO_H



class Archivo
{
public:
    Archivo();
    Archivo(string nombre);
    std::string getNombre();
    void setNombre(string n);


    bool crearArchivo();
    bool archivoExiste();

    int contarRegistros();

    template <typename T>
    T leerRegistro(int pos);

//    <T>[] leerRegistros();
//    bool escribirRegistro(<T>);
    bool borrarRegistro(int pos);
//    bool modificarRegistro(int pos, <T>);
    bool crearBackup();


protected:

private:
    char _nombre[30];

};

#endif // ARCHIVO_H
