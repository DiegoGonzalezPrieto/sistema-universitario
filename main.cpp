#include <iostream>

using namespace std;
#include "Fecha.h"
#include "NotaFinal.h"

int main()
{

    NotaFinal aux;

    aux.setIdMateria("P512");
    aux.setFecha(Fecha(15,10,2023));
    aux.setNota(8);

    cout << "ID Materia: " << aux.getIdMateria() << endl;
    cout << "Fecha: " << aux.getFecha().toString() << endl;
    cout << "Dia de la semana: " << aux.getFecha().getNombreDia(aux.getFecha()) << endl;
    cout << "Nota final: " << aux.getNota() << endl;

    return 0;
}
