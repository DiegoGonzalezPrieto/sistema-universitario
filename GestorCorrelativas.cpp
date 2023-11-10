#include <iostream>
using namespace std;
#include <vector>
#include "GestorCorrelativas.h"
#include "Mensajero.h"


bool GestorCorrelativas::validarSisepuedeCursar(std::string idMateria)
{
    Mensajero m;
    int nregistros = archivoMaterias.contarRegistros();

    Materia datosMateria;

    for (int x = 0; x < nregistros; x++)
    {
        archivoMaterias.leerRegistro(x, datosMateria);

        if (datosMateria.getIdMateria() == idMateria)
        {

            break;
        }
    }

    vector<string> materiasRequeridas;

    for (int i = 0; i < 10; i++)
    {
        if (datosMateria.getIdMateriasRequeridas(i) != "")
        {
            materiasRequeridas.push_back(datosMateria.getIdMateriasRequeridas(i));
        }
    }

    if (materiasRequeridas.empty())
    {

        return true;
    }
    nregistros = archivoCursadaMateria.contarRegistros();
    CursadaMateria datosCursadaMateria;
    int materiasRequeridasAprobadas = materiasRequeridas.size();
    int cantidadMateriasAprobadas = 0;

    for (int x = 0; x < nregistros; x++)
    {
        archivoCursadaMateria.leerRegistro(x, datosCursadaMateria);

        for (int i = 0; i < materiasRequeridas.size(); i++)
        {
            if (datosCursadaMateria.getIdMateria() == materiasRequeridas[i] && datosCursadaMateria.getEstado() == MAT_APROBADA)
            {
                cantidadMateriasAprobadas++;
            }
        }
    }

    if (materiasRequeridasAprobadas == cantidadMateriasAprobadas)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> GestorCorrelativas::getNoAprobadas(std::string idMateria)
{
    Mensajero m;
    int nregistros = archivoMaterias.contarRegistros();

    Materia datosMateria;

    for (int x = 0; x < nregistros; x++)
    {
        archivoMaterias.leerRegistro(x, datosMateria);

        if (datosMateria.getIdMateria() == idMateria)
        {
            break;
        }
    }

    std::vector<std::string> materiasRequeridasNoAprobadas;

    for (int i = 0; i < 10; i++)
    {
        if (datosMateria.getIdMateriasRequeridas(i) != "")
        {
            bool materiaAprobada = false;

            int nCursadas = archivoCursadaMateria.contarRegistros();
            CursadaMateria datosCursadaMateria;

            for (int j = 0; j < nCursadas; j++)
            {
                archivoCursadaMateria.leerRegistro(j, datosCursadaMateria);

                if (datosCursadaMateria.getIdMateria() == datosMateria.getIdMateriasRequeridas(i) &&
                    datosCursadaMateria.getEstado() == MAT_APROBADA)
                {
                    materiaAprobada = true;
                    break;
                }
            }

            if (!materiaAprobada)
            {
                materiasRequeridasNoAprobadas.push_back(datosMateria.getIdMateriasRequeridas(i));
            }
        }
    }

    return materiasRequeridasNoAprobadas;
}

void GestorCorrelativas::mostrarCorrelativas(std::string idMateria)
{
    int registros = archivoMaterias.contarRegistros();
    Materia datosMateria;
    bool hayCorrelativas = false;
    const int CANTMATERIASCO = 10;
    std::vector<std::string> materias;
    int cantreg = archivoMaterias.contarRegistros();


    for (int x = 0; x < cantreg; x++)
    {
        archivoMaterias.leerRegistro(x, datosMateria);

        if (datosMateria.getIdMateria() == idMateria)
        {
            for (int i = 0; i < CANTMATERIASCO; i++)
            {
                if (datosMateria.getIdMateriasRequeridas(i) != "N/A" && datosMateria.getIdMateriasRequeridas(i) != "")
                {
                    materias.push_back(datosMateria.getIdMateriasRequeridas(i));
                }
            }
            break;
        }
    }

    if (!materias.empty())
    {
        std::cout << "La materia: " << idMateria << " Posee las siguientes Correlativas: \n\n";

        for (const std::string &correlativa : materias)
        {
            int reg = archivoMaterias.contarRegistros();

            for (int x = 0; x < reg; x++)
            {
                archivoMaterias.leerRegistro(x, datosMateria);

                if (datosMateria.getIdMateria() == correlativa)
                {
                    std::cout << datosMateria.getIdMateria() << " " << datosMateria.getNombreMateria() << std::endl;
                    break;
                }
            }
        }
    }
    else
    {
        std::cout << "No tiene correlativas" << std::endl;
    }
}
