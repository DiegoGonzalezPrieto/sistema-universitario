#include <iostream>
using namespace std;

#include "Menu.h"
#include "GestorCursadaMateria.h"


GestorCursadaMateria::GestorCursadaMateria(string rutaArchivo, string rutaMaterias):
    _archivo(rutaArchivo),
    gm(rutaMaterias)
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
    string tituloMenu = "\n=====================================\n** Gestión de Cursadas de Materias **\n=====================================";
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
                    altaCursadaMateriaPorConsola(); // TODO
                    break;
                case 2:
                    mostrarTodasCursadaMateria(); // TODO
                    break;
                case 3:
                    mostrarCursadasMateriaEnCurso(); // TODO
                    break;
                case 4:
                    buscarCursadaMateria(); // TODO
                    break;
                case 5:
                    modificarCursadaMateria(); // TODO
                    break;
                case 6:
                    eliminarCursadaMateria(); // TODO
                    break;
                }
        }
}

void GestorCursadaMateria::altaCursadaMateriaPorConsola() // WIP
{
    cout << endl;
    cout << "***********************" << endl;
    cout << "***  Nueva Cursada  ***" << endl;
    cout << "***********************" << endl;
    cout << endl;


// 1. Pedir y validar datos para construir el objeto

    cout << "Qué materia se va a cursar?" << endl<< endl;

    string idMateria = gm.seleccionarIdMateria();
    Archivo<Materia> archiMat = gm.getArchivoMaterias();
    int cantMat = archiMat.contarRegistros();

    if (cantMat<=0)
        {
            _mensajero.mensajeError("No hay información de materias almacenada en el sistema.");
            return;
        }
    Materia aux;
    for (int i=0; i<cantMat; i++)
        {
            if (!archiMat.leerRegistro(i,aux))
                {
                    _mensajero.mensajeError("No se pudo leer correctamente el archivo de materias.");
                    return;
                }
            if (aux.getIdMateria()==idMateria)
            {
                cout << "\n* Selección:\n\n" << aux.toString() <<endl<<endl;
                break;
            }
        }

    // leerMateria
    CursadaMateria cursadaMateria(aux);

    // 1.b Pedir y validar datos de CursadaMateria, setearlos

    EstadoMateria estado;
    if (!seleccionarEstadoCursadaMateria(estado)) return;
    cursadaMateria.setEstado(estado);

    // WIP: datosCursada
    int maxDatosCursada = cursadaMateria.getMaxDatosCursada(); // para validar
    DatosCursada _datosCursada[1];

    // en qué Cuatrimestre inició? AÑO: 2023 - NRO: 2
    char _idCuatrimestreInicio[7];

    // cantidad de unidades. el resto quedan vacías - puede ingresar 0
    int maxUnidades = cursadaMateria.getMaxUnidades(); // para validar
    Unidad _unidades[1];

    // 1.c Generar datos automáticos

    char _idCuatrimestreActual[7];




// 2. Guardar y revisar resultado de guardarNuevaCursadaMateria(CursadaMateria cm)

}

void GestorCursadaMateria::mostrarTodasCursadaMateria() // TODO
{
    // Evitar anuladas:
    MAT_ANULADA;
}
void GestorCursadaMateria::mostrarCursadasMateriaEnCurso() // TODO
{

}
void GestorCursadaMateria::buscarCursadaMateria() // TODO
{

}
void GestorCursadaMateria::modificarCursadaMateria() // TODO
{
    /*
        IMPORTANTE

        No se debe poder modificar idCuatrimestreDeInicio ni idMateria
        ya que en base a estos atributos se arma el id de CursadaMateria.

    */
}
void GestorCursadaMateria::eliminarCursadaMateria()// TODO
{
//    anularRegistroCursadaMateria();
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



bool GestorCursadaMateria::anularRegistroCursadaMateria()
{
    // PASA A estado 3
    MAT_ANULADA;
}

bool GestorCursadaMateria::seleccionarEstadoCursadaMateria(EstadoMateria &estado)
{
    Menu m({"En curso", "Regularizada", "Aprobada", "Anulada"}, "Seleccionar estado de la cursada.");
    int seleccion = m.mostrar();
    if (seleccion==0) return false;
    switch (seleccion)
    {
    case 1:
    estado = MAT_EN_CURSO;
        break;
    case 2:
    estado = MAT_REGULARIZADA;
        break;
    case 3:
    estado = MAT_APROBADA;
        break;
    case 4:
    estado = MAT_ANULADA;
        break;
    }
    return true;
}

