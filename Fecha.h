#ifndef FECHA_H
#define FECHA_H
#include <cstring>
#include <string>
#include <time.h>

class Fecha
{
public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    virtual ~Fecha();
    int getDia();
    int getMes();
    int getAnio();
    void setDia(int);
    void setMes(int);
    void setAnio(int);
    std::string toString();
    static bool esAnioBisiesto(int anio);
    bool esAnioBisiesto();
    static bool esFechaValida(int dia, int mes, int anio);
    bool esFechaValida();
    void agregarDias(int dias);
    std::string getNombreDia();

    bool operator <(Fecha & f)
    {
        if (_anio < f.getAnio()) return true;
        if (_anio > f.getAnio()) return false;
        if (_mes < f.getMes()) return true;
        if (_mes > f.getMes()) return false;
        if (_dia < f.getDia()) return true;
        return false;
    }
    bool operator >(Fecha & f)
    {
        if (_anio > f.getAnio()) return true;
        if (_anio < f.getAnio()) return false;
        if (_mes > f.getMes()) return true;
        if (_mes < f.getMes()) return false;
        if (_dia > f.getDia()) return true;
        return false;
    }
    bool operator ==(Fecha & f)
    {
        if (_anio != f.getAnio() || _mes != f.getMes() || _dia != f.getDia())
            {
                return false;
            }
        return true;
    }
    bool operator !=(Fecha & f)
    {
        if (_anio != f.getAnio() || _mes != f.getMes() || _dia != f.getDia())
            {
                return true;
            }
        return false;
    }


protected:

private:
    int _dia;
    int _mes;
    int _anio;
    void agregarDia();
    void restarDia();
};

#endif // FECHA_H
