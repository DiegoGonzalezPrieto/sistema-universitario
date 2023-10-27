#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <vector>
#include <cstring>

template<typename T>
class Archivo
{
public:
    Archivo(string nombre)
    {
        setNombre(nombre);
    }
    std::string getNombre()
    {
        string nombre(_nombre);
        return string(nombre);
    }
    void setNombre(string n)
    {
        strcpy(_nombre, n.c_str());
    }

    std::string getNombreBackup()
    {
        return getNombre() + ".bup";
    }

    bool crearArchivo()
    {
        if (FILE* p = fopen(_nombre, "wb"))
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
        if (FILE* p = fopen(_nombre, "rb"))
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
        if (FILE* p = fopen(_nombre, "rb"))
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
        if (FILE* p = fopen(_nombre, "rb"))
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


    bool leerRegistros(vector<T>& registros)
    {
        T aux;
        int cant = contarRegistros();
        if (FILE* p = fopen(_nombre, "rb"))
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
        if (FILE* p = fopen(_nombre, "ab"))
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
        char nombreBup[35];
        string snom = getNombreBackup();
        strcpy(nombreBup, snom.c_str());
        FILE* pi = fopen(nombreBup, "rb");
        FILE* po = fopen(_nombre, "wb");
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
        if (FILE* p = fopen(_nombre, "rb+"))
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

    bool crearBackup()
    {
        T aux;
        int cantReg = contarRegistros();
        if (cantReg < 1) return false;
        char nombreBup[35];
        string snom = getNombreBackup();
        strcpy(nombreBup, snom.c_str());
        FILE* pi = fopen(_nombre, "rb");
        FILE* po = fopen(nombreBup, "wb");
        if (pi == NULL || po == NULL) return false;
        for (int i=0; i<cantReg; i++)
            {
                fread(&aux, sizeof(T), 1, pi);
                fwrite(&aux, sizeof(T), 1, po);
            }
        fclose(po);
        fclose(pi);
        return true;
    }



protected:

private:
    char _nombre[30];

};

#endif // ARCHIVO_H
