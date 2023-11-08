#ifndef GESTORMATERIAS_H
#define GESTORMATERIAS_H

#include "Materia.h"
#include "Archivo.h"
#include "Mensajero.h"

class GestorMaterias {

private:

    Archivo<Materia> archivoMaterias;
    std::vector<Materia> registros;
    Mensajero msj ;

public:

    GestorMaterias(std::string nombre);
    void iniciarGestorMaterias();
    void CargarMaterias();
    void modificarMaterias();
    void mostrarMaterias();

    bool cargaCsv();
    void mostrarNombresMaterias();
    bool guardarIDsMatRequeridas(int cant, Materia& datosMateria);
    bool AgregarUnaMateria();
    std::string buscarIDMateria();
    bool buscarMateria(std::string& IDmateria, Materia& datosMateria, int& pos) ;
    bool modificarUnaMateria();

    /// Devuelve idMateria luego de permitir seleccionar de forma interactiva (para uso por otros gestores)
    string seleccionarIdMateria();

};

#endif // GESTORMATERIAS_H
