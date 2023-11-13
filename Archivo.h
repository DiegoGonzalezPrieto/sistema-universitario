#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <cstring>
#include <vector>
#include <cstring>

template<typename T>
class Archivo
{
public:
    Archivo(std::string nombre)
    {
        setNombre(nombre);
    }
    std::string getNombre()
    {
        return _nombre;
    }
    void setNombre(std::string n)
    {
        _nombre = n;
    }

    std::string getNombreBackup()
    {
        return quitarExtension(getNombre()) + ".bup";
    }

    bool crearArchivo()
    {
        if (FILE* p = fopen(_nombre.c_str(), "wb"))
        {
            fclose(p);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool archivoExiste()
    {
        if (FILE* p = fopen(_nombre.c_str(), "rb"))
        {
            fclose(p);
            return true;
        }
        else
        {
            return false;
        }
    }


    bool leerRegistro(int pos, T& registro)
    {
        if (FILE* p = fopen(_nombre.c_str(), "rb"))
        {
            fseek(p, sizeof(T) * pos, SEEK_SET);
            fread(&registro, sizeof(T), 1, p);
            fclose(p);
            return true;
        }
        else
        {
            return false;
        }
    }

    int contarRegistros()
    {
        int tamanio;
        if (FILE* p = fopen(_nombre.c_str(), "rb"))
        {
            fseek(p, 0, SEEK_END);
            tamanio = ftell(p);
            fclose(p);
            return tamanio / sizeof(T);
        }
        else
        {
            return -1;
        }
    }


    bool leerRegistros(std::vector<T>& registros)
    {
        T aux;
        int cant = contarRegistros();
        if (FILE* p = fopen(_nombre.c_str(), "rb"))
        {
            for (int i=0; i< cant; i++)
            {
                fread(&aux, sizeof(T), 1, p);
                registros.push_back(aux);
            }
            fclose(p);
            return true;
        }
        else
        {
            return false;
        }
    }


    bool agregarRegistro(T registro)
    {
        if (FILE* p = fopen(_nombre.c_str(), "ab"))
        {
            fwrite(&registro, sizeof(T), 1, p);
            fclose(p);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool borrarRegistro(int pos)
    {
        if (! Archivo::crearBackup()) return false;
        T aux;
        int cantReg = contarRegistros();
        if (cantReg < 1) return false;
        std::string nombreBup = getNombreBackup();
        FILE* pi = fopen(nombreBup.c_str(), "rb");
        FILE* po = fopen(_nombre.c_str(), "wb");
        if (pi == NULL || po == NULL) return false;
        for (int i=0; i<cantReg; i++)
        {
            fread(&aux, sizeof(T), 1, pi);
            if (i == pos) continue;
            fwrite(&aux, sizeof(T), 1, po);
        }
        fclose(po);
        fclose(pi);
        return true;
    }

    bool modificarRegistro(int pos, T registro)
    {
        if (FILE* p = fopen(_nombre.c_str(), "rb+"))
        {
            fseek(p, sizeof(T) * pos, SEEK_SET);
            fwrite(&registro, sizeof(T), 1, p);
            fclose(p);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool crearBackup() {
        T aux;
        int cantReg = contarRegistros();
        if (cantReg < 1) return false;

        std::string nombreBup = getNombreBackup();
        FILE* pi = fopen(_nombre.c_str(), "rb");
        FILE* po = fopen(nombreBup.c_str(), "wb");

        if (pi == NULL || po == NULL) {
            std::cout << "Error abriendo archivos de entrada/salida." << std::endl;
            return false;
        }

        for (int i = 0; i < cantReg; i++) {
            fread(&aux, sizeof(T), 1, pi);
            fwrite(&aux, sizeof(T), 1, po);
        }

        fclose(po);
        fclose(pi);
        return true;
    }

    bool restoreDesdeBup() {
    T aux;
    int cantReg = contarRegistros();
    if (cantReg < 1) return false;

    std::string nombreBup = getNombreBackup();
    FILE* pi = fopen(nombreBup.c_str(), "rb");
    FILE* po = fopen(_nombre.c_str(), "wb");

    if (pi == NULL || po == NULL) {
        std::cout << "Error abriendo archivos de entrada/salida." << std::endl;
        return false;
    }

    for (int i = 0; i < cantReg; i++) {
        fread(&aux, sizeof(T), 1, pi);
        fwrite(&aux, sizeof(T), 1, po);
    }

    fclose(po);
    fclose(pi);
    return true;
}

std::string quitarExtension(const std::string& nombreArchivo) {
    size_t posUltimoPunto = nombreArchivo.rfind('.');
    if (posUltimoPunto != std::string::npos) {
        return nombreArchivo.substr(0, posUltimoPunto);
    } else {
        return nombreArchivo;
    }
}


protected:

private:
    std::string _nombre;

};



#endif // ARCHIVO_H
