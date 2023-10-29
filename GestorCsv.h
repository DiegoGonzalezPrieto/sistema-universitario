#ifndef GESTORCSV_H
#define GESTORCSV_H

#include <string>
#include <vector>

#include "Materia.h"

class GestorCsv
{
    public:
        GestorCsv();
        virtual ~GestorCsv();

        void iniciar();

    private:
        void mostrarInstrucciones();
        bool generarArchivoModelo(const std::string& nombreArchivo);
        bool importarArchivoCsv(const std::string& nombreArchivo, std::vector <Materia>& datos);
        bool mostrarMaterias(const std::vector <Materia>& datos);
        bool grabarDatosImportados(const std::vector <Materia>& datos);

};

#endif // GESTORCSV_H
