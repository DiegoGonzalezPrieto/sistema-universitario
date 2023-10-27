#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

class Menu
{
private:
    std::vector<std::string> _opciones;
public:
    Menu(const std::vector<std::string> &opciones);
    int mostrar();
};

#endif // MENU_H
