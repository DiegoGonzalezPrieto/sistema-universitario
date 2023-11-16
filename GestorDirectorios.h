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

        std::string validarCaracteresEspeciales(std::string nombreMateria);
        bool validarNombresReservados(std::string nombreMateria);

        int contarElementosEnDirectorio(std::string ruta);
        float calcularProgresoUnidad(std::string rutaUnidad);
        void calcularProgresoMateria(CursadaMateria materia, std::string idCuatrimestre);
        void mostrarPorcentajeMateria();

        void almacenarExtensionesDetectadas(std::vector <std::string>& extensiones, std::vector <int>& contadorDeExtensiones, std::string ruta);
        bool extensionYaDetectada(std::vector <std::string>& extensiones, std::string tipoArchivo);
        int buscarPosicionExtension(std::vector <std::string>& extensiones, std::string tipoArchivo);
        void mostrarExtensionesArchivos();

        int contarTotalElementosCompletados(std::string ruta);
        int contarTotalElementosPendientes(std::string ruta);
        int contarTotalElementos(std::string ruta);


    private:

};

#endif // GESTORDIRECTORIOS_H
