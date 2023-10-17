#include <iostream>

/// Macros que indican el sistema operativo
/// La detecci�n se realiza en tiempo de compilaci�n
#ifdef _WIN32
#define SISTEMA "Windows"
#elif __linux__
#define SISTEMA "Linux"
#endif

using namespace std;

int main() {

    /// Mostramos por pantalla el SO
    cout << "Sistema operativo detectado: " << SISTEMA << endl;

#ifdef _WIN32
    /// Este bloque de c�digo se ejecutar� unicamente si estamos en el SO Windows
    cout << "El programa funciona en Windows" << endl;
#elif __linux__
    /// Este bloque de c�digo se ejecutar� unicamente si estamos en el SO Linux
    cout << "El programa funciona en Linux" << endl;
#endif

    return 0;
}
