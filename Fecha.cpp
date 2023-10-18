#include <iostream>
#include <cmath>
using namespace std;

#include "Fecha.h"

Fecha::Fecha()
{
    ///Creamos una variable del tipo time_T
    ///Le asignamos nuestros datos del sistema con localtime
    ///Creamos un struct tm para acceder a todas las funciones de <time.h>

    time_t t = time(NULL);
    localtime(&t);
    struct tm date = *localtime(&t);

    setDia(date.tm_mday);
    setMes(date.tm_mon + 1); ///Los meses van de 0 a 11, como un array
    setAnio(date.tm_year + 1900); ///Le sumamos 1900 para ubicarnos en el año actual
}

Fecha::Fecha(int dia, int mes, int anio)
{
    if (!Fecha::esFechaValida(dia, mes, anio))
        {
            Fecha();
            return;
        }
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

Fecha::~Fecha()
{
    //dtor
}

int Fecha::getDia()
{
    return _dia;
}
int Fecha::getMes()
{
    return _mes;
}
int Fecha::getAnio()
{
    return _anio;
}

void Fecha::setDia(int d)
{
    _dia = d;
}
void Fecha::setMes(int m)
{
    _mes = m;
}
void Fecha::setAnio(int a)
{
    _anio = a;
}

string Fecha::toString()
{
    string d = getDia() >=10 ? to_string(getDia()) : "0" + to_string(getDia());
    string m = getMes() >=10 ? to_string(getMes()) : "0" + to_string(getMes());
    string a;
    int anio = getAnio();
    if (anio >= 1000)
        {
            a = to_string(getAnio());
        }
    else if (anio < 100)
    {
        a = "00" + to_string(getAnio());
    }
else if (anio < 10)
    {
        a = "000" + to_string(getAnio());
    }
else
    {
        a = "0" + to_string(getAnio());
    }

return d + "/" + m + "/" + a;
}

bool Fecha::esAnioBisiesto(int anio)
{
    if (anio % 4 != 0) return false;
    if (anio % 100 == 0 && anio % 400 != 0) return false;
    return true;
}

bool Fecha::esAnioBisiesto()
{
    return esAnioBisiesto(getAnio());
}

bool Fecha::esFechaValida(int dia, int mes, int anio)
{
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1 || anio > 9999) return false;
    bool bisiesto = esAnioBisiesto(anio);

    switch (mes)
        {
        case 2:
            if (bisiesto && dia <= 29) return true;
            return dia <= 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            return dia <= 30;
            break;
        default:
            return true;
        }
}
bool Fecha::esFechaValida()
{
    return esFechaValida(getDia(), getMes(), getAnio());
}

void Fecha::agregarDia()
{
    setDia(getDia()+1);
    if (esFechaValida()) return;
    setDia(1);
    setMes(getMes()+1);
    if (esFechaValida()) return;
    setMes(1);
    setAnio(getAnio()+1);
}
void Fecha::restarDia()
{
    if (getDia() != 1)
        {
            setDia(getDia()-1);
            return;
        }
    if (getMes() == 1)
        {
            setAnio(getAnio()-1);
            setMes(12);
            setDia(31);
            return;
        }
    setMes(getMes()-1);
    setDia(31);
    while (!esFechaValida()) setDia(getDia()-1);
}


void Fecha::agregarDias(int dias)
{
    if (dias == 0) return;
    bool agregar = dias > 0;
    int cant = abs(dias);
    {
        for (int i=0; i< cant; i++)
            {
                if (agregar)
                    {
                        agregarDia();
                        continue;
                    }
                restarDia();
            }
    }
}

std::string Fecha::getNombreDia(){

    ///Este array sirve porque es el orden que maneja <ctime>
    ///date.tm_wday devuelve un numero de 0 a 6 que representa cada dia de la semana
    std::string vDiasSemana[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};


    time_t t = time(NULL);
    localtime(&t);
    struct tm date = *localtime(&t);

    std::string aux = vDiasSemana[date.tm_wday];

    return aux;
}
