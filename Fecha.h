#ifndef FECHA_H
#define FECHA_H
#include <cstring>

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
    std::string getNombreDia(const Fecha& fecha);

protected:

private:
    int _dia;
    int _mes;
    int _anio;
    void agregarDia();
    void restarDia();
};

#endif // FECHA_H
