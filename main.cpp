#include <iostream>

using namespace std;
#include "Fecha.h"
#include "Materia.h"

int main()
{

    Materia aux;
    Materia prueba1, prueba2;

    prueba1.setIdMateria("P512");
    prueba2.setIdMateria("J444");

    cout << prueba1.getIdMateria() << endl;
    cout << prueba2.getIdMateria() << endl;

    cout << "---------------" << endl;

    aux.setIdMateriasRequeridas(0, prueba1.getIdMateria());
    aux.setIdMateriasRequeridas(1, prueba2.getIdMateria());

    cout << aux.getIdMateriasRequeridas(0) << endl;
    cout << aux.getIdMateriasRequeridas(1) << endl;

    return 0;
}
