#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

class Menu
{
private:
    std::vector<std::string> _opciones;
    std::string _titulo;
public:
    Menu(const std::vector<std::string> &opciones, std::string titulo="Menu:");
    int mostrar();
};

#endif // MENU_H
