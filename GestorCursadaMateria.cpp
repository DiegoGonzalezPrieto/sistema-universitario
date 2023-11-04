#include <iostream>
using namespace std;

#include "Menu.h"
#include "GestorCursadaMateria.h"

GestorCursadaMateria::GestorCursadaMateria(string rutaArchivo): _archivo(rutaArchivo)
{
}

GestorCursadaMateria::~GestorCursadaMateria()
{
    //dtor
}

Archivo<CursadaMateria> GestorCursadaMateria::getArchivo()
{
    return _archivo;
}
void GestorCursadaMateria::setArchivo(string ruta)
{
    Archivo<CursadaMateria> acm(ruta);
    _archivo = acm;
}

void GestorCursadaMateria::iniciar()
{
    // 0. Chequear o crear archivo.
    if (!getArchivo().archivoExiste())
        {
            getArchivo().crearArchivo();
        }

    // 1. Loop principal
    string tituloMenu = "\n========================\n** Gestión de Cursadas de Materias **\n========================";
    Menu m({"Ingresar nueva cursada de materia.",
            "Ver todas las cursadas de materias.",
            "Ver cursadas de materias en curso.",
            "Buscar cursada de materia.",
            "Modificar cursada de materia.",
            "Eliminar cursada de materia."},
           tituloMenu);

    int opc= 1;
    while (opc != 0)
        {
            opc = m.mostrar();
            switch (opc)
                {
                case 0:
                    break;
                // ABM
                case 1:
                    void altaCursadaMateriaPorConsola(); // TODO
                    break;
                case 2:
                    void mostrarTodasCursadaMateria(); // TODO
                    break;
                case 3:
                    void mostrarCursadasMateriaEnCurso(); // TODO
                    break;
                case 4:
                    void buscarCursadaMateria(); // TODO
                    break;
                case 5:
                    void modificarCursadaMateria(); // TODO
                    break;
                case 6:
                    void eliminarCursadaMateria(); // TODO
                    break;
                }
        }
}

void altaCursadaMateriaPorConsola() // WIP
{
    cout << endl;
    cout << "***********************" << endl;
    cout << "***  Nueva Cursada  ***" << endl;
    cout << "***********************" << endl;
    cout << endl;

    CursadaMateria cursadaMateria;

 // 1. Pedir  validar datos para construir el objeto

    // 1.a Ofrecer materias para que elija qué materia va a cursar. Buscarla con GestorMaterias y setear las propiedades.

    // 1.b Pedir y validar datos de CursadaMateria, setearlos

    EstadoMateria _estado;
    DatosCursada _datosCursada[MAX_DATOS_CURSADA];

    // en qué Cuatrimestre inició? AÑO: 2023 - NRO: 2
    char _idCuatrimestreInicio[7];

        // cantidad de unidades. el resto quedan vacías
    Unidad _unidades[MAX_UNIDADES];

    // 1.c Generar datos automáticos

    char _idCuatrimestreActual[7];




 // 2. Guardar y revisar resultado de guardarNuevaCursadaMateria(CursadaMateria cm)

}

void mostrarTodasCursadaMateria() // TODO
{

}
void mostrarCursadasMateriaEnCurso() // TODO
{

}
void buscarCursadaMateria() // TODO
{

}
void modificarCursadaMateria() // TODO
{

}
void eliminarCursadaMateria()// TODO
{

}

// ---------------- Métodos de Apoyo ----------------------- //

bool GestorCursadaMateria::guardarNuevaCursadaMateria(CursadaMateria cm)
{
    // 1. Chequear o crear archivo.
    Archivo<CursadaMateria> ac = getArchivo();
    if (!ac.archivoExiste())
    {
        if(!ac.crearArchivo())
        {
            _mensajero.mensajeError("No se pudo crear el archivo para guardar Cursadas de Materias");
            return false;
        }
    }
    // 2. Agregar registro
    return ac.agregarRegistro(cm);

}
