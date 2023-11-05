#ifndef GESTORCSV_H
#define GESTORCSV_H

#include <string>
#include <vector>

#include "Materia.h"
#include "Archivo.h"

class GestorCsv
{
    public:
        GestorCsv(std::string archivoImportacion, std::string archivoMateria);
        virtual ~GestorCsv();

        void iniciar();

    private:

        Archivo <Materia> _auxArchivo;
        std::string _nombreArchivo;

        void mostrarInstrucciones();
        bool generarArchivoModelo();
        bool importarArchivoCsv(std::vector <Materia>& datos);
        bool mostrarMaterias(const std::vector <Materia>& datos);
        bool grabarDatosImportados(const std::vector <Materia>& datos);

};

#endif // GESTORCSV_H
