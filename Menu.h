#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

class Menu
{
private:
    vector<string> _opciones;
public:
    Menu(const vector<string> &opciones);
    int mostrar();
};

#endif // MENU_H
