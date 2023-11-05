#include <iostream>
using namespace std;
#include <vector>
#include "GestorCorrelativas.h"
#include "Mensajero.h"

/// Retorna 0 Si no se cumple con las correlativas, Retorna 1 Si se cumple con las coorrelativas, Retorna 2 si hubo error al abrir archivos.
int GestorCorrelativas::validarSisepuedeCursar(std::string idMateria)
{
    Mensajero m;
    int nregistros = archivoMaterias.contarRegistros();
    Materia datosMateria;
    if(!archivoMaterias.archivoExiste()){
        return 2;
    }
    for(int x=0; x<nregistros; x++)
    {
        archivoMaterias.leerRegistro(x,datosMateria);

        if(datosMateria.getIdMateria()==idMateria)
        {
            break;
        }
    }
    vector<string> materiasRequeridas;

    for(int i = 0; i< 10; i++)
    {
        materiasRequeridas.push_back(datosMateria.getIdMateriasRequeridas(i));
    }
    if(materiasRequeridas[0]=="")
    {

        return 1;
    }

    /*else
    {
        cout<<"el vector no esta vacio"<<endl;
        for(int x =0; x<materiasRequeridas.size(); x++)
        {
            cout<<materiasRequeridas[x];
        }
        cout<<endl;
    }*/

    if(!archivoCursadaMateria.archivoExiste()){
        return 2;
    }
    nregistros = archivoCursadaMateria.contarRegistros();
    CursadaMateria datosCursadaMateria;
    int materiasRequeridasAprobadas=materiasRequeridas.size();
    int cantidadMateriasAprobadas=0;
    for(int x=0; x<nregistros; x++)
    {
        archivoCursadaMateria.leerRegistro(x,datosCursadaMateria);

        for(int i = 0; i< 10; i++)
        {
            if(datosCursadaMateria.getIdMateria()==materiasRequeridas[i] && datosCursadaMateria.getEstado()==MAT_APROBADA)
            {

                cantidadMateriasAprobadas++;
            }

        }
    }

    if(materiasRequeridasAprobadas==cantidadMateriasAprobadas)
    {

        return 1;
    }
    else
    {

        return 0;
    }
}

void GestorCorrelativas::mostrarCorrelativas(std::string idMateria)
{
    int registros = archivoMaterias.contarRegistros();
    Materia datosMateria;
    for(int x=0; x<registros; x++)
    {
        if (!archivoMaterias.leerRegistro(x,datosMateria))
        {
            Mensajero m;
            m.mensajeError("No se pudo leer el archivo materias.dat");
            return;
        }
        if(datosMateria.getIdMateria()==idMateria)
        {
            cout<<datosMateria.toString();
        }
    }
}
