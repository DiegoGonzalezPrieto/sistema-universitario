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
            "Ver cursadas de materias según su estado (incluye anuladas).",
            "Ver todas las cursadas de materias.",
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
                    altaCursadaMateriaPorConsola();
                    break;
                case 2:
                {
                    EstadoMateria estado;
                    Menu m({"En curso", "Regularizadas", "Aprobadas", "Anuladas"}, "Seleccionar estado de las materias a visualizar");
                    int e = m.mostrar();
                    if (e==0) break;
                    if (e==1) estado = MAT_EN_CURSO;
                    if (e==2) estado = MAT_REGULARIZADA;
                    if (e==3) estado = MAT_APROBADA;
                    if (e==4) estado = MAT_ANULADA;

                    mostrarCursadasMateriaPorEstado(estado);
                    break;
                }
                case 3:
                    mostrarTodasCursadaMateria();
                    break;
                case 4:
                    buscarCursadaMateria();
                    break;
                case 5:
                    modificarCursadaMateria();
                    break;
                case 6:
                    eliminarCursadaMateria();
                    break;
                }
        }
}

void GestorCursadaMateria::altaCursadaMateriaPorConsola()
{
    cout << endl;
    cout << "***********************" << endl;
    cout << "***  Nueva Cursada  ***" << endl;
    cout << "***********************" << endl;
    cout << endl;


    cout << "Qué materia se va a cursar?" << endl<< endl;

    string idMateria = gm.seleccionarIdMateria();
    Fecha hoy;
    int periodo = hoy.getMes() > 6 ? 2 : 1;
    string idCuatrimestre = to_string(hoy.getAnio()) + "0" + to_string(periodo);
    string futuroIdCursadaMateria = idMateria + idCuatrimestre;
    string erroresValidacion = "";
    if (!sePuedeCursar(futuroIdCursadaMateria, erroresValidacion))
        {
            cout << endl;
            _mensajero.mensajeError("La materia seleccionada no se puede cursar.");
            cout << erroresValidacion << endl;
            return;
        }

    if (!gc.validarSisepuedeCursar(idMateria))
        {
            _mensajero.mensajeAdvertencia("La materia seleccionada tiene correlativas sin aprobar");
            gc.mostrarCorrelativas(idMateria);
            Menu mCor({"Continuar de todos modos."}, "Desea continuar registrando la cursada de esta materia?");
            int seguir = mCor.mostrar();
            if (seguir==0) return;
        }
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


    // Carga de datos específicos de CM //

    CursadaMateria cursadaMateria(aux);

    // ESTADO
    EstadoMateria estado = MAT_EN_CURSO;
    cursadaMateria.setEstado(estado);

    // DATOS:CURSADA
    int maxDatosCursada = cursadaMateria.getMaxDatosCursada(); // para validar
    vector<DatosCursada> datosCursada;
    if (!cargarDatosCursada(datosCursada, maxDatosCursada)) return;
    cursadaMateria.setDatosCursada(datosCursada);

    // UNIDADES
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

    // ID_CUATRIMESTRE (generado al inicio)
    cursadaMateria.setIdCuatrimestreInicio(idCuatrimestre);

    _mensajero.mensajeInformacion("Guardando cursada...");
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
    limpiarPantallaSinPausa();
    cout << endl;
    cout << "****************************" << endl;
    cout << "***  Todas las Cursadas  ***" << endl;
    cout << "****************************" << endl;
    cout << endl;
    vector<CursadaMateria> vec;
    if (!_archivo.leerRegistros(vec))
        {
            _mensajero.mensajeError("No se pudo leer el archivo de datos.");
            return;
        }

    for (CursadaMateria cm : vec)
        {
            if (cm.getEstado() != MAT_ANULADA)
                {
                    cout << cm.toString();
                    cout << "-------------------------------------" << endl;
                }
        }
}

void GestorCursadaMateria::mostrarCursadasMateriaPorEstado(EstadoMateria e) // TODO
{
    string estado = "*Sin Definir*";
    switch (e)
        {
        case MAT_EN_CURSO:
            estado = "*En Curso*";
            break;
        case MAT_REGULARIZADA:
            estado = "*Regularizada*";
            break;
        case MAT_APROBADA:
            estado = "*Aprobada*";
            break;
        case MAT_ANULADA:
            estado = "*Anulada*";
            break;

        }
    cout << endl;
    cout << "****************************************" << endl;
    cout << "***  Cursadas en estado " + estado +" ***" << endl;
    cout << "****************************************" << endl;
    cout << endl;

    vector<CursadaMateria> vec;
    if (!_archivo.leerRegistros(vec))
        {
            _mensajero.mensajeError("No se pudo leer el archivo de datos.");
            return;
        }


    for (CursadaMateria cm : vec)
        {
            if (cm.getEstado() == e)
                {
                    cout << cm.toString();
                    cout << "-------------------------------------" << endl;
                }
        }
}
CursadaMateria GestorCursadaMateria::buscarCursadaMateria()
{
    cout << endl;
    cout << "***********************************"<< endl;
    cout << "***  Buscar cursada de materia  ***" << endl;
    cout << "***********************************" << endl;
    cout << endl;

    CursadaMateria cursadaElegida;
    cursadaElegida.setIdMateria("");

    string cuatrimestre;
    if (!seleccionarCuatrimestre(cuatrimestre))
        return cursadaElegida;

    vector<CursadaMateria> cursadas = buscarCursadasDeMateriaPorCuatrimestre(cuatrimestre);

    if (cursadas.size()==0)
        {
            _mensajero.mensajeInformacion("No hay registros de cursadas en el cuatrimestre seleccionado");
            return cursadaElegida;
        }

    cout << "Materias del cuatrimestre " << cuatrimestre << ":"<<endl;
    for (int i=0; i<cursadas.size(); i++)
        {
            cout <<"\t" << i+1 << ". " << cursadas[i].getNombreMateria()<< endl;
        }
    cout << endl << "Seleccionar número de cursada a revisar: ";
    int seleccion;
    while (true)
        {
            seleccion = validar<int>();
            if (seleccion > 0 && seleccion <= cursadas.size())
                break;
            cout << "Seleccionar un número entre 1 y " << cursadas.size() << endl;
        }
    cursadaElegida = cursadas[seleccion -1];
    cout << endl;
    cout << "\tCursada seleccionada:" << endl;
    cout << cursadaElegida.toFullString() << endl;
    return cursadaElegida;
}

bool GestorCursadaMateria::sePuedeCursar(string idCursadaMateria, string &mensajeError)
{
    bool cursable = true;
    CursadaMateria cm;
    if (buscarCursadaMateriaPorId(idCursadaMateria,cm))
        {   limpiarPantallaSinPausa();
            cursable = false;
            mensajeError += "\n- Ya hay una cursada de de esta materia en este cuatrimestre:\n";
            mensajeError += cm.toString();
        }

    // Otras validaciones posibles

    return cursable;
}

void GestorCursadaMateria::modificarCursadaMateria() // TODO
{
    /*
        IMPORTANTE

        No se debe poder modificar idCuatrimestreDeInicio ni idMateria
        ya que en base a estos atributos se arma el id de CursadaMateria.

    */

    cout << endl;
    cout << "******************************************" << endl;
    cout << "***  Modificar información de Cursada  ***" << endl;
    cout << "******************************************" << endl;
    cout << endl;
    cout << "1) Seleccionar la materia a modificar" << endl;
    cout << "..................................." << endl;

    CursadaMateria cm = buscarCursadaMateria();
    if (cm.getIdMateria()=="") return;

    cout << "2) Seleccionar el campo a a modificar" << endl;
    cout << "....................................." << endl;

    Menu m({"Estado de la cursada",
            "Reemplazar datos de cursada (horario - aula)",
            "Agregar dato de cursada (horario - aula)",
            "Guardar cambios"
           }, "Campo a modificar:");
    int opc;
    bool guardar = false;
    while (!guardar)
        {
            opc = m.mostrar();
            if (opc==0) return;
            switch (opc)
                {
                case 1:
                {
                    EstadoMateria e;
                    if(!seleccionarEstadoCursadaMateria(e)) break;
                    cm.setEstado(e);
                    _mensajero.mensajeInformacion("Estado actualizado: " + cm.getEstadoToString() + "\n");
                    break;
                }
                case 2:
                {
                    _mensajero.mensajeAdvertencia("Si se continúa, los datos de cursada serán reemplazados, perdiendo los datos previos.");
                    cout << "Continuar (s/N)" << endl;
                    string respuesta;
                    getline(cin>>ws, respuesta);
                    if (respuesta !="S" && respuesta != "s") break;

                    vector<DatosCursada> aux;
                    int maxDC = cm.getMaxDatosCursada();
                    cargarDatosCursada(aux, maxDC);
                    cm.setDatosCursada(aux);
                    break;
                }
                case 3:
                {
                    vector<DatosCursada> aux, datosCursadaActuales = cm.getDatosCursada();
                    cout << "\n\tDatos de cursada actualmente registrados:\n";
                    cout << cm.getDatosCursadaToString();

                    int maxDC = cm.getMaxDatosCursada() - datosCursadaActuales.size();
                    cargarDatosCursada(aux, maxDC);
                    datosCursadaActuales.insert(datosCursadaActuales.end(), aux.begin(), aux.end());
                    cm.setDatosCursada(datosCursadaActuales);
                    break;
                }
                case 4:
                    guardar = true;
                    break;
                }
        }

    if(guardarCursadaMateriaModificada(cm))
        {
            _mensajero.mensajeInformacion("Cursada editada correctamente.");
        }
    else
        {
            _mensajero.mensajeError("No se pudo guardar la cursada editada.");
        }
}

void GestorCursadaMateria::eliminarCursadaMateria()// TODO
{
    cout << endl;
    cout << "*************************************" << endl;
    cout << "***  Eliminar Cursada de Materia  ***" << endl;
    cout << "*************************************" << endl;
    cout << endl;
    _mensajero.mensajeAdvertencia("La cursada seleccionada será marcada como Anulada y no podrá recuperarse.\n\tSolo podrá visualizarse en la búsqueda por estados.");

    CursadaMateria cm = buscarCursadaMateria();
    if (anularRegistroCursadaMateria(cm.getIdCursadaMateria()))
        {

            _mensajero.mensajeInformacion("Cursada eliminada correctamente.");
        }
    else
        {
            _mensajero.mensajeError("La cursada no pudo ser eliminada.");
        }
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

bool GestorCursadaMateria::buscarCursadaMateriaPorId(string idCursadaMateria, CursadaMateria& cm)
{
    bool encontrada = false;
    vector<CursadaMateria> cursadas;
    if(!_archivo.leerRegistros(cursadas))
        {
            _mensajero.mensajeError("No se pudo leer el archivo de cursadas.");
            return false;
        }

    for (CursadaMateria cursada : cursadas)
        {
            if (cursada.getIdCursadaMateria()==idCursadaMateria && cursada.getEstado() != MAT_ANULADA)
                {
                    cm = cursada;
                    encontrada = true;
                }
        }
    return encontrada;
}

vector<CursadaMateria> GestorCursadaMateria::buscarCursadasDeMateriaPorCuatrimestre(string idCuatrimestreInicio)
{
    vector<CursadaMateria> vec;
    vector<CursadaMateria> aux;
    if(!_archivo.leerRegistros(vec))
        {
            _mensajero.mensajeError("No se pudo leer el archivo de cursadas.");
            return vec;
        }

    for (CursadaMateria cm : vec)
        {
            if (cm.getIdCuatrimestreInicio()==idCuatrimestreInicio && cm.getEstado()!= MAT_ANULADA)
                {
                    aux.push_back(cm);
                }
        }

    return aux;

}


bool GestorCursadaMateria::anularRegistroCursadaMateria(string idCursadaMateria)
{
    int pos = buscarPosicionEnArchivoPorId(idCursadaMateria);
    if (pos<0) return false;

    CursadaMateria aux;
    if (!_archivo.leerRegistro(pos, aux)) return false;

    aux.setEstado(MAT_ANULADA);

    return _archivo.modificarRegistro(pos, aux);
}

int GestorCursadaMateria::buscarPosicionEnArchivoPorId(string idCursadaMateria)
{
    vector<CursadaMateria> aux;
    if(!_archivo.leerRegistros(aux))
        {
            return -1;
        }

    for (int i=0; i<aux.size(); i++)
        {
            if (idCursadaMateria== aux[i].getIdCursadaMateria())
                return i;
        }
    return -1;
}

bool GestorCursadaMateria::guardarCursadaMateriaModificada(CursadaMateria cm)
{
    int pos = buscarPosicionEnArchivoPorId(cm.getIdCursadaMateria());

    if (pos<0) return false;

    return _archivo.modificarRegistro(pos, cm);

}

bool GestorCursadaMateria::seleccionarEstadoCursadaMateria(EstadoMateria &estado)
{
    Menu m({"En curso", "Regularizada", "Aprobada", "Anulada - Eliminada"}, "Seleccionar estado de la cursada.");
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
    vector<DatosCursada> vecAux;
    Menu mDias({"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"}, "Seleccionar día de cursada:");

    int cantCargada = 0;
    while (cantCargada<cantMax)
        {
            int diaCursada = mDias.mostrar();
            if (diaCursada==0) return false;
            aux.setDiaSemana(diaCursada);
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
                    vecAux.push_back(aux);
                    aux.setAula("");
                    Menu m({"Cargar otro horario de cursada", "Continuar"}, "Carga de Horarios de Cursada");
                    int op = m.mostrar();
                    if (op != 1) break;
                    cantCargada++;
                }
            else
                {
                    _mensajero.mensajeAdvertencia("Datos descartados, intentar nuevamente.");
                }
            if (cantCargada >= cantMax)
                {
                    _mensajero.mensajeInformacion("Se alcanzó la cantidad máxima de datos de cursada.");
                }
        }

    cout << "Datos de cursada confirmados:"<< endl<< endl;
    for (int i=0; i<vecAux.size(); i++)
        {
            cout << vecAux[i].toString()<< endl;
            cout << endl << "*********************" << endl;
        }

    vec = vecAux;
    return true;
}

bool GestorCursadaMateria::seleccionarCuatrimestre(string &cuatrimestre)
{
    int anio=0;
    bool actual = false;
    Fecha hoy;
    while (true)
        {
            cout << "Año del cuatrimestre (0 para cuatrimestre actual): ";
            anio = validar<int>();
            if (anio == 0)
                {
                    anio = hoy.getAnio();
                    actual = true;
                    break;
                }
            else if (anio > hoy.getAnio() || anio < 1900)
                {
                    _mensajero.mensajeError("No se puede seleccionar un año a futuro ni anterior a 1900.");
                }
            else
                {
                    break;
                }

        }
    if (actual)
        {
            int periodo = hoy.getMes() > 6 ? 2 : 1;
            cuatrimestre = std::to_string(anio) + "0"+ to_string(periodo);
            return true;
        }
    Menu m({"Primer Cuatrimestre", "Segundo Cuatrimestre"});
    int periodo = m.mostrar();
    if (periodo==0) return false;
    cuatrimestre = std::to_string(anio) + "0"+ to_string(periodo);

    return true;
}
