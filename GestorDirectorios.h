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
        bool crearDirectoriosCuatrimestre(CursadaMateria materiaEnCurso, std::string idCuatrimestre);
        bool directoriosMateriasAnualesYaCreados(std::string idCuatrimestreInicio, std::string idCuatrimestreActual);

        string validarCaracteresEspeciales(std::string nombreMateria);

        int contarElementosEnDirectorio(std::string ruta);
        float calcularProgresoUnidad(std::string rutaUnidad);
        void calcularProgresoMateria(CursadaMateria materia, std::string idCuatrimestre);

        void almacenarExtensionesDetectadas(vector <string>& extensiones, vector <int>& contadorDeExtensiones, string ruta);
        bool extensionYaDetectada(vector <string>& extensiones, string tipoArchivo);
        int buscarPosicionExtension(vector <string>& extensiones, string tipoArchivo);

        int contarTotalElementosCompletados(string ruta);
        int contarTotalElementosPendientes(string ruta);
        int contarTotalElementos(string ruta);


    private:

};

#endif // GESTORDIRECTORIOS_H
