#include <iostream>
#include "GestorCuatrimestre.h"
#include "CursadaMateria.h"
#include "Menu.h"
#include "func_utiles.h"

GestorCuatrimestre::GestorCuatrimestre(std::string archivoCuatrimestre, std::string archivoCursadas, std::string archivoMaterias, std::string archivoNotas) :
    archivoCuatrimestres(archivoCuatrimestre),
    gcm(archivoCursadas, archivoMaterias),
    gnf(archivoNotas, archivoMaterias, archivoCursadas)
{}

void GestorCuatrimestre::actualizarMateriasEnCursoEnCuatrimestre()
{
    Cuatrimestre actualizarcuatrimestre;
    Fecha hoy;
    int ultpos=archivoCuatrimestres.contarRegistros();
    int periodo = hoy.getMes() > 6 ? 2 : 1;
    int anio=hoy.getAnio();
    actualizarcuatrimestre.setAnio(anio);
    actualizarcuatrimestre.setPeriodo(periodo);

    Archivo<CursadaMateria> archivoCursada("Archivos/datos/cursada_materias.dat");
    int cantRegCursada = archivoCursada.contarRegistros();
    for (int j = 0; j < cantRegCursada; ++j)
        {
            CursadaMateria cursada;
            archivoCursada.leerRegistro(j, cursada);


            if (cursada.getEstado() == MAT_EN_CURSO)
                {
                    actualizarcuatrimestre.setIdCursadaMateria(cursada.getIdMateria());
                }

        }
    actualizarcuatrimestre.setFinalizado(false);


    if (archivoCuatrimestres.modificarRegistro(ultpos-1,actualizarcuatrimestre))
        {
            std::cout << "Datos Actualizados Correctamente" << std::endl;
        }

}


void GestorCuatrimestre::iniciarGestorCuatrimestre()
{
    std::vector<std::string> opciones =
    {
        "Iniciar cuatrimestre",
        "Cerrar cuatrimestre",
        "Informacion del Actual Cuatrimestre",
        "Informacion de Todos los Cuatrimestres Cursados",
        "Gestion de Cursada de Materias",

    };

    Menu menuPrincipal(opciones, "------ GESTION CUATRIMESTRE ------");

    int op;
    do
        {
            op = menuPrincipal.mostrar();
            switch (op)
                {
                case 0:
                    break;
                case 1:
                    iniciarCuatrimestre();
                    break;
                case 2:
//                    cerrarCuatrimestre();
                    cerrarCuatrimestreYCursadas();
                    break;
                case 3:
                    mostrarInformacionCuatrimestreActual();
                    break;
                case 4:
                    mostrarTodosCuatrimestresCursados();
                    break;
                case 5:
                    modificarCuatrimestreActual();
                    break;
                }
            std::cout << std::endl;
        }
    while (op != 0);
}

void GestorCuatrimestre::iniciarCuatrimestre()
{
    Cuatrimestre datosCuatrimestre;
    datosCuatrimestre.setFinalizado(true);
    GestorCursadaMateria cursadaM("Archivos/datos/cursada_materias.dat","Archivos/datos/materias.dat");
    if(archivoCuatrimestres.archivoExiste())
        {
            int cantregistros=archivoCuatrimestres.contarRegistros();
            archivoCuatrimestres.leerRegistro(cantregistros-1,datosCuatrimestre);
        }

    if(datosCuatrimestre.getFinalizado())
        {
            Fecha hoy;
            Cuatrimestre nuevocuatrimestre;
            int periodo = hoy.getMes() > 6 ? 2 : 1;
            int anio=hoy.getAnio();
            nuevocuatrimestre.setAnio(anio);
            nuevocuatrimestre.setPeriodo(periodo);
            bool termino=false;
            do
                {
                    limpiarPantallaSinPausa();
                    cursadaM.altaCursadaMateriaPorConsola();
                    limpiarPantalla();
                    cout << " >> Desea agregar otra materia al cuatrimestre ? (S/N)" << endl;

                    char resp = validar<char>();

                    while (resp != 'S' && resp != 's' && resp != 'N' && resp != 'n')
                        {
                            cout << "Respuesta no válida. Por favor, ingrese 'S' o 'N'." << endl;
                            resp = validar<char>();
                        }

                    if (resp == 'N' || resp == 'n')
                        {
                            termino = true; // Terminar el bucle si la respuesta es 'N' o 'n'
                        }

                }
            while (!termino);

            Archivo<CursadaMateria> archivoCursada("Archivos/datos/cursada_materias.dat");
            int cantRegCursada = archivoCursada.contarRegistros();
            for (int j = 0; j < cantRegCursada; ++j)
                {
                    CursadaMateria cursada;
                    archivoCursada.leerRegistro(j, cursada);


                    if (cursada.getEstado() == MAT_EN_CURSO)
                        {
                            nuevocuatrimestre.setIdCursadaMateria(cursada.getIdMateria());
                        }

                }
            nuevocuatrimestre.setFinalizado(false);

            if (archivoCuatrimestres.agregarRegistro(nuevocuatrimestre))
                {
                    msj.mensajeInformacion("Cuatrimestre iniciado correctamente.");
                }
            else
                {
                    msj.mensajeError("Error al iniciar el cuatrimestre. Inténtelo nuevamente.");
                }
        }
    else
        {

            msj.mensajeInformacion("SOLO PODRA CREAR UN NUEVO CUATRIMESTRE SI CIERRA/ TERMINA EL ANTERIOR");

        }

}

void GestorCuatrimestre::cerrarCuatrimestre()
{
    Cuatrimestre datosCuatrimestre;
    datosCuatrimestre.setFinalizado(true);
    CursadaMateria cursada;

    if (!archivoCuatrimestres.archivoExiste())
        {
            msj.mensajeError(">> No posee cuatrimestres Activos para cerrar.");
            return;
        }

    int cantRegCuatrimestres = archivoCuatrimestres.contarRegistros();
    archivoCuatrimestres.leerRegistro(cantRegCuatrimestres - 1, datosCuatrimestre);

    if (datosCuatrimestre.getFinalizado())
        {
            msj.mensajeError(">> El cuatrimestre ya se encuentra cerrado.");
            return;
        }

    Archivo<CursadaMateria> archivoCursada("Archivos/datos/cursada_materias.dat");
    int cantRegCursada = archivoCursada.contarRegistros();
    bool seEstaCursando = false;

    for (int x = 0; x < cantRegCursada; x++)
        {
            archivoCursada.leerRegistro(x, cursada);
            if (cursada.getEstado() == MAT_EN_CURSO && cursada.getCuatrimestreDeDuracion() > 1 && cursada.getIdCuatrimestreInicio() < datosCuatrimestre.getIdCuatrimestre())
                {
                    seEstaCursando = true;
                    break;
                }
        }

    for (int x = 0; x < cantRegCursada; x++)
        {
            archivoCursada.leerRegistro(x, cursada);
            if (cursada.getEstado() == MAT_EN_CURSO && cursada.getCuatrimestreDeDuracion()==1)
                {
                    seEstaCursando = true;
                    break;
                }
        }



    if (!seEstaCursando)
        {
            datosCuatrimestre.setFinalizado(true);
            archivoCuatrimestres.modificarRegistro(cantRegCuatrimestres - 1, datosCuatrimestre);
            msj.mensajeInformacion(">> Cuatrimestre cerrado correctamente.");
        }


    if(seEstaCursando==true)
        {
            std::cout<<endl;
            msj.mensajeAdvertencia("Para cerrar un cuatrimestre no debe tener materias en curso \n Si la materia tiene una duraccion mayor a un cuatrimestre \n Se le dejara cerrar el cuatrimestre y la informacion pasara al siguiente cuatrimestre ");

            int cantregistros=archivoCursada.contarRegistros();

            for(int x=0 ; x<cantregistros; x++)
                {

                    archivoCursada.leerRegistro(x,cursada);
                    if(cursada.getEstado()==MAT_EN_CURSO )
                        {
                            std::string aux= "> " + cursada.getIdMateria() + " " + cursada.getNombreMateria();
                            std::cout<<aux<<endl;
                        }

                }
        }
}

void GestorCuatrimestre::cerrarCuatrimestreYCursadas()
{
    if (!archivoCuatrimestres.archivoExiste() || archivoCuatrimestres.contarRegistros() == 0)
        {
            msj.mensajeError(">> No posee cuatrimestres Activos para cerrar.");
            return;
        }


    /// 1. Obtener el cuatrimestre activo

    Cuatrimestre c;
    int pos;
    bool hayCuatrimestreActivo = false;
    int cantRegCuatrimestres = archivoCuatrimestres.contarRegistros();
    for (int i=0; i<cantRegCuatrimestres; i++)
        {
            if(!archivoCuatrimestres.leerRegistro(i,c))
                {
                    msj.mensajeError("Error al leer el archivo de cuatrimestres.");
                    return;
                }

            if (!c.getFinalizado())
                {
                    hayCuatrimestreActivo=true;
                    pos = i;
                    break;
                }
        }
    if (!hayCuatrimestreActivo)
        {
            msj.mensajeError(">> No posee cuatrimestres Activos para cerrar.");
            return;
        }

    /// 2. Chequear si hay materias EN_CURSO y ofrecer cerrarlas
    vector<CursadaMateria> cursadasDelCuatrimestre = gcm.buscarCursadasDeMateriaPorCuatrimestre(c.getIdCuatrimestre());
    bool hayMateriasEnCurso = false;
    for (CursadaMateria cm : cursadasDelCuatrimestre)
        {
            if (cm.getEstado()==MAT_EN_CURSO)
                {
                    hayMateriasEnCurso = true;
                    break;
                }
        }

    if (!hayMateriasEnCurso)
        {
            c.setFinalizado(true);
            archivoCuatrimestres.modificarRegistro(pos, c);
            msj.mensajeInformacion(">> Cuatrimestre cerrado correctamente.");
            return;
        }

    msj.mensajeAdvertencia(">> Hay materias en curso en este cuatrimestre. \n\tDeben marcarse como Aprobadas/Regularizadas/Anuladas para poder cerrar el cuatrimestre.");
    cout << "Desea actualizar el estado de las cursadas y cerrar el cuatrimestre? (S/n): ";
    char rta = validar<char>();

    if (rta == 'n' || rta == 'N')
        {
            msj.mensajeInformacion("El cuatrimestre permanecerá sin finalizar.");
            return;
        }

    /// 3. Modificar estado y nota final de cada cursada

    EstadoMateria e;
    NotaFinal nf;

    for (CursadaMateria cm : cursadasDelCuatrimestre)
        {
            bool cargaNotaFinal = true;

            msj.mensajeInformacion("A continuación, seleccionar el estado en que quedará la cursada de: " + cm.getNombreMateria());
            // 3. A - Estado
            while (true)
                {
                    if (!gcm.seleccionarEstadoCursadaMateria(e, cm.getNombreMateria())) return;
                    if (e!=MAT_EN_CURSO)
                        {
                            cm.setEstado(e);
                            break;

                        }
                    else
                        {
                            if (sePuedeSeguirCursando(cm, c))
                                {
                                    msj.mensajeInformacion("La materia " + cm.getNombreMateria() + " permanece en curso. Por su duración, puede seguir cursándose el cuatrimestre que viene.");
                                    cm.setEstado(e);
                                    cargaNotaFinal = false;
                                    break;
                                }
                            msj.mensajeAdvertencia("La materia " + cm.getNombreMateria() + " no puede permanecer en curso.\n\tSu duracion y cuatrimestre de inicio no lo permiten.");
                        }

                }
                if (!cargaNotaFinal) continue;
            // 3. B - Nota (ya se guarda)
            msj.mensajeInformacion("A continuación, puede seleccionar la nota final de la cursada de: " + cm.getNombreMateria());
            cout << "Desea guardar una nota final para la materia " << cm.getNombreMateria() << "? (S/n) ";
            char rta = validar<char>();
            if (rta != 'n'&& rta != 'N')
                {
                    if(gnf.crearNotaFinal(cm.getIdCursadaMateria()))
                        {
                            msj.mensajeInformacion("Nota guardada correctamente.");
                        }
                    else
                        {
                            msj.mensajeError("No se pudo guardar la nota.");
                        }

                }



            // 3. C - Guardar Cursada
            gcm.guardarCursadaMateriaModificada(cm);
            msj.mensajeInformacion(">> Cambio de estado en cursada de " + cm.getNombreMateria() + " guardado correctamente.");
        }


    c.setFinalizado(true);
    archivoCuatrimestres.modificarRegistro(pos, c);
    msj.mensajeInformacion(">> Cuatrimestre cerrado correctamente.");
    return;

}

void GestorCuatrimestre::modificarCuatrimestreActual()
{

    GestorCursadaMateria cursadaM("Archivos/datos/cursada_materias.dat","Archivos/datos/materias.dat");
    cursadaM.iniciar();



}

void GestorCuatrimestre::mostrarInformacionCuatrimestreActual()
{
    limpiarPantallaSinPausa();
    if (!archivoCuatrimestres.archivoExiste())
        {
            msj.mensajeAdvertencia("No hay informacion de cuatrimestres disponible.");
            return;
        }

    int cantregistros = archivoCuatrimestres.contarRegistros();

    if (cantregistros == 0)
        {
            msj.mensajeAdvertencia("No hay cuatrimestres registrados.");
            return;
        }

    cout << "Informacion del ultimo cuatrimestre:" << endl;

    Cuatrimestre ultimoCuatrimestre;
    archivoCuatrimestres.leerRegistro(cantregistros - 1, ultimoCuatrimestre);

    cout << "Año: " << ultimoCuatrimestre.getAnio() << endl;
    cout << "Periodo: " << ultimoCuatrimestre.getPeriodo() << endl;
    cout << "Finalizado: " << (ultimoCuatrimestre.getFinalizado() ? "Si" : "No") << endl;

    // Obtener la lista de ids de materias asociadas al cuatrimestre
    std::vector<std::string> idsMaterias;
    for (int i = 0; i < CANTMATERIASC; ++i)
        {
            std::string idMateria = ultimoCuatrimestre.getIdsCursadaMateria(i);
            if (!idMateria.empty())
                {
                    idsMaterias.push_back(idMateria);
                }
        }

    if (idsMaterias.empty())
        {
            msj.mensajeInformacion("No hay materias registradas en este cuatrimestre.");
        }
    else
        {
            // Iterar sobre los ids y obtener la información de la materia
            Archivo<Materia> archivoMaterias("Archivos/datos/materias.dat");
            int regMaterias = archivoMaterias.contarRegistros();
            Materia materia;
            cout<<"Materias Registradas en el Cuatrimestre : "<<endl;

            for (const auto &idMateria : idsMaterias)
                {
                    for (int i = 0; i < regMaterias; i++)
                        {
                            archivoMaterias.leerRegistro(i, materia);
                            if (materia.getIdMateria() == idMateria)
                                {
                                    std::string infoMateria = "> " + materia.getIdMateria() + " - " + materia.getNombreMateria();
                                    std::cout << infoMateria << endl;
                                    break;
                                }
                        }
                }
        }

    cout << "ID del Cuatrimestre: " << ultimoCuatrimestre.getIdCuatrimestre() << endl;
    cout << endl;
    msj.mensajeInformacion("Fin de la informacion de este cuatrimestre.");
}
void GestorCuatrimestre::mostrarTodosCuatrimestresCursados()
{
    limpiarPantallaSinPausa();
    if (!archivoCuatrimestres.archivoExiste())
        {
            msj.mensajeAdvertencia("No hay informacion de cuatrimestres disponible.");
            return;
        }

    int cantregistros = archivoCuatrimestres.contarRegistros();

    if (cantregistros == 0)
        {
            msj.mensajeAdvertencia("No hay cuatrimestres registrados.");
            return;
        }

    cout << "Informacion de todos los cuatrimestres cursados:" << endl;

    for (int i = 0; i < cantregistros; ++i)
        {

            Cuatrimestre ultimoCuatrimestre;
            archivoCuatrimestres.leerRegistro(i, ultimoCuatrimestre);

            cout << "Año: " << ultimoCuatrimestre.getAnio() << endl;
            cout << "Periodo: " << ultimoCuatrimestre.getPeriodo() << endl;
            cout << "Finalizado: " << (ultimoCuatrimestre.getFinalizado() ? "Si" : "No") << endl;

            // Obtener la lista de ids de materias asociadas al cuatrimestre
            std::vector<std::string> idsMaterias;
            for (int i = 0; i < CANTMATERIASC; ++i)
                {
                    std::string idMateria = ultimoCuatrimestre.getIdsCursadaMateria(i);
                    if (!idMateria.empty())
                        {
                            idsMaterias.push_back(idMateria);
                        }
                }

            if (idsMaterias.empty())
                {
                    msj.mensajeAdvertencia("No hay materias registradas en este cuatrimestre.");
                }
            else
                {
                    // Iterar sobre los ids y obtener la información de la materia
                    Archivo<Materia> archivoMaterias("Archivos/datos/materias.dat");
                    int regMaterias = archivoMaterias.contarRegistros();
                    Materia materia;
                    cout << "Materias Registradas en el Cuatrimestre : "<<endl;

                    for (const auto &idMateria : idsMaterias)
                        {
                            for (int i = 0; i < regMaterias; i++)
                                {
                                    archivoMaterias.leerRegistro(i, materia);
                                    if (materia.getIdMateria() == idMateria)
                                        {
                                            std::string infoMateria = "> " + materia.getIdMateria() + " - " + materia.getNombreMateria();
                                            std::cout << infoMateria << endl;
                                            break;
                                        }
                                }
                        }
                }

            cout << "ID del Cuatrimestre: " << ultimoCuatrimestre.getIdCuatrimestre() << endl;
            cout << endl;
            msj.mensajeInformacion("Fin de la informacion de este cuatrimestre.");



        }
}

bool GestorCuatrimestre::sePuedeSeguirCursando(CursadaMateria cursada, Cuatrimestre cuatriCierre)
{
    int duracion = cursada.getCuatrimestreDeDuracion();
    if (duracion<=1) return false;

    string cuatriInicio = cursada.getIdCuatrimestreInicio();

    int  anioInicio = stoi(cuatriInicio.substr(0,4));
    int  anioCierre = cuatriCierre.getAnio();
    int periodoInicio = stoi(cuatriInicio.substr(5,6));
    int periodoCierre = cuatriCierre.getPeriodo();

    if (cuatriInicio==cuatriCierre.getIdCuatrimestre())
        {
            return true;
        }

    // Cálculo de cuatrimestres de diferencia

    int cuatrisDeDiferencia = (anioCierre-anioInicio) * 2 + (periodoCierre-periodoInicio);

    // Se suma uno ya que la diferenica entre 2023-1 y 2023-2 es 1. Pero son 2 cuatrimestres ya cursados.
    return cuatrisDeDiferencia+1 >= duracion;
}

