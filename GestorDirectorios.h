#ifndef GESTORDIRECTORIOS_H
#define GESTORDIRECTORIOS_H
#include <filesystem>
#include <string>
#include <vector>

#include "CursadaMateria.h"

class GestorDirectorios
{
    public:

        GestorDirectorios();
        bool crearDirectorios(std::string ruta);
        bool crearDirectoriosCuatrimestre(std::vector<CursadaMateria> materiasEnCurso, std::string idCuatrimestre);
        bool directoriosMateriasAnualesYaCreados(std::string idCuatrimestreInicio, std::string idCuatrimestreActual);

        int contarElementosEnDirectorio(std::string ruta);
        float calcularProgresoUnidad(std::string rutaUnidad);
        void calcularProgresoMateria(CursadaMateria materia, std::string idCuatrimestre);


    private:

};

#endif // GESTORDIRECTORIOS_H
