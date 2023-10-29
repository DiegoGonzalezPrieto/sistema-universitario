#ifndef GESTORVALIDACION_H_INCLUDED
#define GESTORVALIDACION_H_INCLUDED
#include <iostream>
#include <limits>

class ValidadorEntrada {
public:
    template<typename T>
    static T validar() {
        T entrada;
        while (true) {
            std::cout << "Ingrese un valor: ";
            std::cin >> entrada;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada no v�lida. Intente de nuevo." << std::endl;
            } else {
                // Verificar si hay caracteres no v�lidos en el b�fer
                char c;
                std::cin.get(c);
                if (c != '\n' && !std::isdigit(c)) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entrada no v�lida. Intente de nuevo." << std::endl;
                } else {
                    break;
                }
            }
        }

        return entrada;
    }
};


#endif // GESTORVALIDACION_H_INCLUDED
