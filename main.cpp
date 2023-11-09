#include <iostream>
using namespace std;
#include "GestorEventos.h"
#include "Menu.h"
#include "GestorMaterias.h"
#include "GestorCursadaMateria.h"

int main()
{
    GestorCursadaMateria g("sistema/datos/cursada_materias.dat", "sistema/datos/materias.dat");
    g.iniciar();



//cout << vec[1].toString()<< endl;

//EstadoMateria e;
//cout << (int)g.seleccionarEstadoCursadaMateria(e);
//cout<< endl<< "seleccion: "<< e;

//    Menu m({"Uno", "Dos", "Tres"});

//    cout << "Resultado : "<< m.mostrar();
//
//float a = obtenerNumeroDecimal();
//string b;
//cout << "VALOR: " << a<< endl;
//cin >> b;
//cout << "RESIDUO: "<< b;
    return 0;
}
