#include <sys/stat.h> /// Necesario para crear el struct stat dst
#include <dirent.h> /// Nos permite abrir, leer y cerrar directorios (carpetas) con el struct dirent
#include <iostream>
#include <string>


#ifdef _WIN32
#define SISTEMA "Windows"
#elif __linux__
#define SISTEMA "Linux"
#endif



using namespace std;

int main(){


    /// Mientras vayamos leyendo cada elemento en el directorio, *entrada ser� un puntero de struct que contiene m�todos
    /// as� podemos determinar el nombre de cada elemento le�do
    struct dirent *entrada;

    /// Este struct nos ser� de utilidad para determinar el tipo de elemnto le�do en entrada
    /// (Si es un archivo regular o una carpeta)
    struct stat info;

    /// Es una variable tipo DIR, nos permitir� abrir un directorio, leer los archivos y subdirectorios
    /// en ese directorio, y cerrar el drectorio una vez terminado de usar
    DIR *directorio;

    /// Asignamos una ruta para trabajar, en este caso coloqu� en donde se ejecuta el programa
    /// Deber�a adaptarse seg�n si se compila desde Windows o Linux
     #ifdef _WIN32

        string path = ".\\";

    #elif __linux__

        string path = ".";

    #endif // __linux__


    /// Abrimos el directorio a trabajar en la ruta deseada
    directorio = opendir(path.c_str());


    /// Preguntamos si se pudo abrir el directorio
    if(directorio == nullptr){

        cout << "ERROR AL ABRIR LA CARPETA";
        return -1;
    }

    int cantArchivos = 0;
    int cantCarpetas = 0;

    /// Vamos leyendo la siguiente entrada en el directorio, en caso de haber elementos
    /// Lo almacenamos en *entrada, que representar� la "entrada" le�da en el directorio
    while((entrada = readdir(directorio)) != nullptr){

        /// La funci�n stat toma el nombre del elemento como primer par�metro, y un puntero
        /// al struct stat donde se almacenar� la informaci�n como segundo par�metro.
        /// Devuelve 0 si se ejecuta correctamente, y -1 en caso de error.

        if(stat(entrada->d_name, &info) == 0){

            /// Preguntamos si el tipo de elemento le�do es un archivo regular con el struct stat
            if(info.st_mode & S_IFREG){

                /// Mostramos por pantalla el nombre del archivo almacenado en entrada con d_name
                cout << "Archivo: " << entrada->d_name << endl;

                cantArchivos++;
            }

            /// Preguntamos si el tipo de elemento le�do es un directorio (carpeta) con el struct stat
            else if (info.st_mode & S_IFDIR){

                /// Mostramos por pantalla el nombre de la carpeta almacenado en entrada con d_name
                cout << "Carpeta: " << entrada->d_name << endl;

                cantCarpetas++;

            }

        }

    }

    /// Cuando mostramos por pantalla, veremos:
    /// . que representa el directorio de trabajo actual
    /// .. representan al directorio padre
    /// El resto de los elementos en este caso son archivos, deber�an listarse con sus nombres

    cout << "En la carpeta se detectaron: " << cantArchivos << " archivos y " << cantCarpetas << " carpetas" << endl;



    /// Preguntamos si se pudo cerrar el directorio satisfactoriamente
    if(closedir(directorio) == -1){

        cout << "ERROR AL CERRAR LA CARPETA";
        return -1;
    }


    return 0;
}
