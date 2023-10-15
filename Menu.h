#ifndef MENU_H
#define MENU_H

class Menu
{
private:

int numero[5] ;

public:
    Menu(){}
    void mostrar();
    void ejecutar();
    void ejecutarOpcion(int numero) ;
    void mostrarSubMenu(int numero);
    void ejecutarSubMenu(int numero);
    void ejecutarOpcionSubMenu (int numero) ;
};

#endif // MENU_H
