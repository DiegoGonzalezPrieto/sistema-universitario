#ifndef GESTORMATERIAS_H
#define GESTORMATERIAS_H

#include "Materia.h"
#include "Archivo.h"
#include "Mensajero.h"

class GestorMaterias {

private:

    Archivo<Materia> archivoMaterias;
    std::vector<Materia> materias;
    Mensajero msj;

public:

    GestorMaterias(std::string nombre);
    void iniciarGestorMaterias();
    void menuCortoGMaterias();
    void CargarMaterias();
    void modificarMaterias();
    void mostrarMaterias();
    void borrarMaterias();

    bool cargaCsv();
    void mostrarNombresMaterias();
    bool guardarIDsMatRequeridas(int cant,std::string IDpropio, Materia& datosMateria);
    bool AgregarUnaMateria();
    std::string buscarIDMateria();
    std::string mostrarNombrePorID(std::string IDMateria);
    bool buscarMateria(std::string& IDmateria, Materia& datosMateria, int& pos) ;
    bool modificarUnaMateria();
    bool nombreExiste(std::string _nombre);
    bool IDExiste(std::string _ID);
    void limpiarCorrelativas(int pos,Materia& datosMateria);

    /// Devuelve idMateria luego de permitir seleccionar de forma interactiva (para uso por otros gestores)
    std::string seleccionarIdMateria();

    Archivo<Materia> getArchivoMaterias();

};

#endif // GESTORMATERIAS_H
