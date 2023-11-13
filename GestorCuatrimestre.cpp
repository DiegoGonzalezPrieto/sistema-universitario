#include <iostream>
#include "GestorCuatrimestre.h"
#include "CursadaMateria.h"
#include "Menu.h"
#include "func_utiles.h"

GestorCuatrimestre::GestorCuatrimestre(std::string nombre) : archivoCuatrimestres(nombre) {}

void GestorCuatrimestre::actualizarMateriasEnCursoEnCuatrimestre()
{
    Cuatrimestre actualizarcuatrimestre;
    Fecha hoy;
    int ultpos=archivoCuatrimestres.contarRegistros();
    int periodo = hoy.getMes() > 6 ? 2 : 1;
    int anio=hoy.getAnio();
    actualizarcuatrimestre.setAnio(anio);
    actualizarcuatrimestre.setPeriodo(periodo);

    Archivo<CursadaMateria> archivoCursada("Archivos/datos/cursadamateria.dat");
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

    Menu menuPrincipal(opciones, "** Cursadas de Cuatrimestre ** ");

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
            cerrarCuatrimestre();
            break;
        case 3:
            mostrarInformacionCuatrimestreActual();
            break;
        case 4:
            mostrarTodosCuatrimestresCursados();
            break;
        case 5:
            modificarCuatrimestreActual();
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

        Archivo<CursadaMateria> archivoCursada("Archivos/datos/cursadamateria.dat");
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

    Archivo<CursadaMateria> archivoCursada("Archivos/datos/cursadamateria.dat");
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
    {   std::cout<<endl;
        msj.mensajeAdvertencia("Para cerrar un cuatrimestre no debe tener materias en curso \n Si la materia tiene una duraccion mayor a un cuatrimestre \n Se le dejara cerrar el cuatrimestre y la informacion pasara al siguiente cuatrimestre ");

        int cantregistros=archivoCursada.contarRegistros();

        for(int x=0 ; x<cantregistros; x++)
        {

            archivoCursada.leerRegistro(x,cursada);
            if(cursada.getEstado()==MAT_EN_CURSO )
            {
                std::string aux= "> " + cursada.getIdMateria() + cursada.getNombreMateria();
                std::cout<<aux<<endl;
            }

        }
    }
}

void GestorCuatrimestre::modificarCuatrimestreActual()
{

    GestorCursadaMateria cursadaM("Archivos/datos/cursadamateria.dat","Archivos/datos/materias.dat");
    cursadaM.iniciar();



}

void GestorCuatrimestre::mostrarInformacionCuatrimestreActual()
{
    limpiarPantallaSinPausa();
    if (!archivoCuatrimestres.archivoExiste())
    {
        cout << "No hay informacion de cuatrimestres disponible." << endl;
        return;
    }

    int cantregistros = archivoCuatrimestres.contarRegistros();

    if (cantregistros == 0)
    {
        cout << "No hay cuatrimestres registrados." << endl;
        return;
    }

    cout << "Informacion del ultimo cuatrimestre:" << endl;

    Cuatrimestre ultimoCuatrimestre;
    archivoCuatrimestres.leerRegistro(cantregistros - 1, ultimoCuatrimestre);

    cout << "Anio: " << ultimoCuatrimestre.getAnio() << endl;
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
        cout << "No hay materias registradas en este cuatrimestre." << endl;
    }
    else
    {
        // Iterar sobre los ids y obtener la información de la materia
        Archivo<Materia> archivoMaterias("Archivos/datos/materias.dat");
        int regMaterias = archivoMaterias.contarRegistros();
        Materia materia;
        cout<<" Materias Registradas en el Cuatrimestre : "<<endl;

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
    cout << "Fin de la informacion de este cuatrimestre." << endl<<endl;
}
void GestorCuatrimestre::mostrarTodosCuatrimestresCursados()
{
    limpiarPantallaSinPausa();
    if (!archivoCuatrimestres.archivoExiste())
    {
        cout << "No hay informacion de cuatrimestres disponible." << endl;
        return;
    }

    int cantregistros = archivoCuatrimestres.contarRegistros();

    if (cantregistros == 0)
    {
        cout << "No hay cuatrimestres registrados." << endl;
        return;
    }

    cout << "Informacion de todos los cuatrimestres cursados:" << endl;

    for (int i = 0; i < cantregistros; ++i)
    {

        Cuatrimestre ultimoCuatrimestre;
        archivoCuatrimestres.leerRegistro(i, ultimoCuatrimestre);

        cout << "Anio: " << ultimoCuatrimestre.getAnio() << endl;
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
            cout << "No hay materias registradas en este cuatrimestre." << endl;
        }
        else
        {
            // Iterar sobre los ids y obtener la información de la materia
            Archivo<Materia> archivoMaterias("Archivos/datos/materias.dat");
            int regMaterias = archivoMaterias.contarRegistros();
            Materia materia;
            cout<<" Materias Registradas en el Cuatrimestre : "<<endl;

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
        cout << "Fin de la informacion de este cuatrimestre." << endl<<endl;



    }
}

