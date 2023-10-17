#include <iostream>
#include <sys/stat.h> ///Necesario para poder utilizar la función mkdir
#include <errno.h> /// Útil para analizar lo que ocurre con mkdir

#include <string>

#ifdef _WIN32
#define SISTEMA "Windows"
#elif __linux__
#define SISTEMA "Linux"
#endif


using namespace std;


int main(){

    int cantUnidades = 5;

    string materia = "Ecuaciones diferenciales II";

    /// Si el resultado es -1 es porque hubo un error al crear la carpeta
    if(mkdir(materia.c_str()) == -1){

        /// perror nos da una  descripción más detallada del tipo de error
        /// ya sea que la carpeta existe, si la ruta es incorrecta, etc
        perror("Error");
    }

    for (int i = 0; i < cantUnidades; i++){

        string unidad = "Unidad " + to_string(i+1);

        /// Aquí podríamos establecer un códio por defecto para Windows, y otro para Linux
        /// Tal que las // o .. se adapten según el SO en donde se compila
        #ifdef _WIN32

            string ruta = materia + "//" + unidad;

        #elif __linux__

            ///string ruta /// Definimos ruta para que funcione en Linux

        #endif


        if(mkdir(ruta.c_str()) == -1){

            perror("Error");

        }

        unidad = "";
        ruta = "";
    }


    return 0;
}
