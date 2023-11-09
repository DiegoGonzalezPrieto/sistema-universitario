#include <iostream>
using namespace std;

#include "Menu.h"
#include "GestorCursadaMateria.h"
#include "Fecha.h"
#include "func_utiles.h"

GestorCursadaMateria::GestorCursadaMateria(string rutaArchivo, string rutaMaterias):
    _archivo(rutaArchivo),
    gm(rutaMaterias),
    gc(rutaMaterias, rutaArchivo)
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
        cout << "\nLas materias correlativas de " << aux.getNombreMateria() << "son: " << endl;
        gc.mostrarCorrelativas(aux.getIdMateria());


    // leerMateria
    CursadaMateria cursadaMateria(aux);

    // 1.b Pedir y validar datos de CursadaMateria, setearlos

    // En el alta siempre están en estado: EN_CURSO
    EstadoMateria estado = MAT_EN_CURSO;
//    if (!seleccionarEstadoCursadaMateria(estado)) return;
    cursadaMateria.setEstado(estado);

    int maxDatosCursada = cursadaMateria.getMaxDatosCursada(); // para validar
    vector<DatosCursada> datosCursada;
    if (!cargarDatosCursada(datosCursada, maxDatosCursada)) return;
    cursadaMateria.setDatosCursada(datosCursada);


    char _idCuatrimestreInicio[7];

    int maxUnidades = cursadaMateria.getMaxUnidades(); // para validar
    cout << "Cantidad de unidades que posee la materia (0 para ignorar): ";
    int cantUnidades = validar<int>();
    if (cantUnidades> maxUnidades)
        {
            _mensajero.mensajeAdvertencia("El máximo de unidades por materia es " + to_string(maxUnidades));
            cantUnidades = maxUnidades;
        }
    vector<Unidad> vUnidad;
    for (int i=0; i<cantUnidades; i++)
        {
            string nombre = "Unidad " + to_string(i+1);
            Unidad u(nombre);
            vUnidad.push_back(u);
        }

    cursadaMateria.setUnidades(vUnidad);

    // 1.c Generar datos automáticos
    Fecha hoy;
    int periodo = hoy.getMes() > 6 ? 1 : 2;
    string idCuatrimestre = to_string(hoy.getAnio()) + "0" + to_string(periodo);
    cursadaMateria.setIdCuatrimestreInicio(idCuatrimestre);

    cout << "*** Guardando cursada...****"<< endl;
    cout <<cursadaMateria.toString() << endl;

    if (!guardarNuevaCursadaMateria(cursadaMateria))
        {
            _mensajero.mensajeError("No se pudo guardar la cursada ingresada.");
        }
        else
            {
            _mensajero.mensajeInformacion("Cursada guardada correctamente.");
        }
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

bool GestorCursadaMateria::cargarDatosCursada(vector<DatosCursada> &vec, int cantMax)
{
    DatosCursada aux;
    Menu mDias({"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"}, "Seleccionar día de cursada:");

    int cantCargada = 0;
    while (cantCargada<cantMax)
        {
            int diaCursada = mDias.mostrar();
            if (diaCursada==0) return false;
            aux.setDiaSemana(diaCursada+1);
            while (true)
                {
                    cout << "Ingresar horario de la cursada:" << endl<< endl;
                    cout << "Hora: ";
                    int horas = validar<int>();
                    cout << "Minutos: ";
                    int minutos = validar<int>();
                    if (Horario::validarHorario(0, minutos, horas))
                        {
                            Horario h(0,minutos,horas);
                            aux.setHorario(h);
                            break;
                        }
                    else
                        {
                            _mensajero.mensajeError("El horario ingresado no es válido, vuelva a intentar.");
                            cout  << endl;
                        }
                }

            cout << endl << "Ingresar datos del aula/lugar de cursada:" << endl<< endl;
            string aula;
            getline(cin>>ws, aula);
            aux.setAula(aula);

            cout << endl << "***Dato de cursada***" << endl;
            cout << endl << aux.toString() << endl;
            cout << endl << "*********************" << endl;
            cout << endl;
            cout << "Confirmar si los datos son correctos (S/n): ";
            string respuesta;
            getline(cin>>ws, respuesta);

            if (respuesta != "n" && respuesta != "N")
                {
                    vec.push_back(aux);
                    Menu m({"Cargar otro horario de cursada", "Continuar"});
                    int op = m.mostrar();
                    if (op != 1) break;
                    cantCargada++;
                }
            else
                {
                    _mensajero.mensajeAdvertencia("Datos descartados, intentar nuevamente.");
                }
        }

    cout << "Datos de cursada confirmados:"<< endl<< endl;
    for (int i=0; i<vec.size(); i++)
        {
            cout << vec[i].toString()<< endl;
            cout << endl << "*********************" << endl;
        }

    return true;
}

bool GestorCursadaMateria::seleccionarCuatrimestre(string &cuatrimestre)
{
    int anio=0;
    while (true)
        {
            cout << "Año del cuatrimestre: ";
            anio = validar<int>();
            Fecha hoy;
            if (anio > hoy.getAnio())
                {
                    _mensajero.mensajeError("No se puede seleccionar un año a futuro.");
                }
            else
                {
                    break;
                }

        }
    Menu m({"Primer Cuatrimestre", "Segundo Cuatrimestre"});
    int periodo = m.mostrar();
    if (periodo==0) return false;
    cuatrimestre = std::to_string(anio) + "0"+ to_string(periodo);

    return true;
}
