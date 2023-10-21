#include <iostream>
#include <filesystem>

using namespace std;

int contarArchivos(string ruta)
{
    int archivos = 0;
    try
        {
            const filesystem::path path{ruta};
            for (auto const& item : filesystem::directory_iterator{path})
                {
                    if (item.is_regular_file())
                        {
                            archivos++;
                        }
                }
        }
    catch (...)
        {
            return -1;
        }
    return archivos;
}

bool crearDirectorios(string ruta)
{
    return filesystem::create_directories(ruta);
}
