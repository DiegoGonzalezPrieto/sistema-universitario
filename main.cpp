#include <iostream>

using namespace std;
#include "FechaHorario.h"

int main()
{

    FechaHorario aux(15,2,2018,0,0,12);

    cout << aux.toString() << endl;

    cout << aux.getFecha().getNombreDia(aux.getFecha());
    return 0;
}
