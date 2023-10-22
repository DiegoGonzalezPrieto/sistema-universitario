#include "GESTORCARRERA.h"

bool GESTORCARRERA::agregarTodoslosDatosdeLaCarreraEnCurso(CLASECARRERA& carrera) {
    return archivoCarreraEnCurso.agregarRegistro(carrera);
}

void GESTORCARRERA::mostrarCarreraEnCurso() {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    std::cout << "Nombre de la Carrera en Curso: " << carrera.getNombreCarrera() << std::endl;
}

void GESTORCARRERA::modificarNombreCarreraEnCurso(std::string& nuevoNombre) {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    carrera.setNombreCarrera(nuevoNombre);
    archivoCarreraEnCurso.modificarRegistro(0, carrera);
}

void GESTORCARRERA::modificarNombreUniversidad( std::string& nuevoNombre) {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    carrera.setNombreUniversidad(nuevoNombre);
    archivoCarreraEnCurso.modificarRegistro(0, carrera);
}

void GESTORCARRERA::modificarIdMaterias(std::vector<std::string>& nuevosIds) {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    carrera.setIdMaterias(nuevosIds);
    archivoCarreraEnCurso.modificarRegistro(0, carrera);
}

void GESTORCARRERA::mostrarNombreUniversidad() {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    std::cout << "Nombre de la Universidad en Curso: " << carrera.getNombreUniversidad() << std::endl;
}

void GESTORCARRERA::mostrarIdMaterias() {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    std::cout << "IDs de las Materias en Curso:" << std::endl;
    for (int i = 0; i < 50 && !carrera.getIdMateria(i).empty(); ++i) {
        std::cout << " - " << carrera.getIdMateria(i) << std::endl;
    }
}

void GESTORCARRERA::modificarNombreEstudiante(std::string& nuevoNombre) {
    // Leer la información actual desde el archivo
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);

    // Modificar el nombre del estudiante
    carrera.setNombreEstudiante(nuevoNombre);

    // Escribir la información modificada de nuevo al archivo
    archivoCarreraEnCurso.modificarRegistro(0, carrera);
}

void GESTORCARRERA::modificarLegajo(std::string& nuevoLegajo) {
    // Leer la información actual desde el archivo
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);

    // Modificar el legajo
    carrera.setLegajo(nuevoLegajo);

    // Escribir la información modificada de nuevo al archivo
    archivoCarreraEnCurso.modificarRegistro(0, carrera);
}

void GESTORCARRERA::mostrarNombreEstudiante() {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    std::cout << "Nombre del Estudiante: " << carrera.getNombreEstudiante() << std::endl;
}

void GESTORCARRERA::mostrarLegajo() {
    CLASECARRERA carrera;
    archivoCarreraEnCurso.leerRegistro(0, carrera);
    std::cout << "Legajo del Estudiante: " << carrera.getLegajo() << std::endl;
};

string GESTORCARRERA::tostring() {
    CLASECARRERA carrera;
    if (archivoCarreraEnCurso.leerRegistro(0,carrera)) {
        std::cout << "Información de la Carrera en Curso:" << std::endl;
        std::cout << "Nombre de la Universidad: " << carrera.getNombreUniversidad() << std::endl;
        std::cout << "Nombre de la Carrera: " << carrera.getNombreCarrera() << std::endl;
        std::cout << "Legajo: " << carrera.getLegajo() << std::endl;
        std::cout << "Nombre del Estudiante: " << carrera.getNombreEstudiante() << std::endl;
        mostrarIdMaterias();
    } else {
        std::cout << "Error al leer la carrera del archivo." << std::endl;
    }

}
