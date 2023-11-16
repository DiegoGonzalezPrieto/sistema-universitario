#include <iostream>
#include <cstring>
using namespace std;

#include "GestorRespaldos.h"
#include "Menu.h"
#include "Mensajero.h"
#include "func_utiles.h"
#include "rutas.h"

GestorRespaldos::GestorRespaldos() :
    respaldoConfiguracion(Rutas::config),
    respaldoCargaInicial(Rutas::cargaInicial),
    respaldoCarrera(Rutas::carrera),
    respaldoMaterias(Rutas::materias),
    respaldoCursadaMateria(Rutas::cursadas),
    respaldoCuatrimestre(Rutas::cuatrimestres),
    respaldoEventos(Rutas::eventos),
    respaldoNotaFinal(Rutas::notas)

{}

///MENU PRINCIPAL
void GestorRespaldos::iniciar()
{

    std::vector<std::string> opciones =
    {
        "Crear copia de seguridad de un solo archivo",
        "Crear copia de seguridad de todos los archivos",
        "Reestablecer un archivo desde el backup",
        "Reestablecer todos los archivos desde backup",
        "Borrar datos de un solo archivo",
        "Borrar todos los datos de archivos (restaurar programa a estado de fabrica)"

    };

    string tituloMenu = "** Gestion de copias de seguridad **";
    Menu MenuPrincipal(opciones,tituloMenu);


    int op;
    do
    {
        op = MenuPrincipal.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            limpiarPantallaSinPausa();
            menuBackups();
            limpiarPantallaSinPausa();
            break;
        case 2:
            limpiarPantallaSinPausa();
            backupTotal();
            limpiarPantallaSinPausa();
            break;
        case 3:
            limpiarPantallaSinPausa();
            menuRestores();
            limpiarPantallaSinPausa();
            break;
        case 4:
            limpiarPantallaSinPausa();
            restoreTotal();
            limpiarPantallaSinPausa();
            break;
        case 5:
            limpiarPantallaSinPausa();
            menuPorDefecto();
            limpiarPantallaSinPausa();
            break;
        case 6:
            {
            limpiarPantallaSinPausa();
            Menu m({"Si","No"},"Esta seguro que desea eliminar todos los datos?");
            int opc = m.mostrar();
            if(opc==1)
            {
            porDefectoTotal();
            limpiarPantallaSinPausa();
            }
            limpiarPantallaSinPausa();
            break;
            }
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///MENU PARA SELECCIONAR UN ARCHIVO PARA HACERLE .BUP
void GestorRespaldos::menuBackups()
{
    std::vector<std::string> opciones =
    {
        "Configuracion",
        "Carga Inicial",
        "Carrera",
        "Materias",
        "Cursada Materias",
        "Cuatrimestre",
        "Eventos",
        "Notas finales"

    };

    string tituloMenu = "---Seleccione el archivo del que quiere crear una copia de seguridad---";
    Menu MBackups(opciones,tituloMenu);

    int op;
    do
    {
        op = MBackups.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1: ///CONFIG 1
            {

            limpiarPantallaSinPausa();
            if(respaldoConfiguracion.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 2: ///NOTA FINAL 2
            {

            limpiarPantallaSinPausa();
            if(respaldoCargaInicial.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 3: ///CARRERA 3
            {

            limpiarPantallaSinPausa();
            if(respaldoCarrera.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 4: ///MATERIAS 4
            {
            limpiarPantallaSinPausa();
            if(respaldoMaterias.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 5: ///CURSADA MATERIAS 5
            {
            limpiarPantallaSinPausa();
            if(respaldoCursadaMateria.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 6: ///CUATRIMESTRE 6
            {
            limpiarPantallaSinPausa();
            if(respaldoCuatrimestre.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 7: ///EVENTOS 7
            {
            limpiarPantallaSinPausa();
            if(respaldoEventos.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            }
            break;
        case 8: /// NOTA FINAL 8
            {
            limpiarPantallaSinPausa();
            if(respaldoNotaFinal.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///CREA .BUP DE TODOS LOS ARCHIVOS CON DATOS
void GestorRespaldos::backupTotal()
{

    limpiarPantallaSinPausa();
    cout << "Configuracion: " ;
    if(respaldoConfiguracion.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }

    cout << "Carga Inicial: " ;
    if(respaldoCargaInicial.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Carrera: " ;
    if(respaldoCarrera.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Materias: " ;
    if(respaldoMaterias.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Cursada materias: " ;
    if(respaldoCursadaMateria.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Cuatrimestre: " ;
    if(respaldoCuatrimestre.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Eventos: " ;
    if(respaldoEventos.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Nota final: " ;
    if(respaldoNotaFinal.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    limpiarPantalla();

}

///MENU PARA SELECCIONAR QUE ARCHIVO RESTAURAR DESDE .BUP
void GestorRespaldos::menuRestores()
{
    std::vector<std::string> opciones =
    {
        "Configuracion",
        "Carga Inicial",
        "Carrera",
        "Materias",
        "Cursada Materias",
        "Cuatrimestre",
        "Eventos",
        "Notas finales"

    };

    string tituloMenu = "---Seleccione el archivo que quiere restaurar desde una copia de seguridad---";
    Menu MRestores(opciones,tituloMenu);

    int op;
    do
    {
        op = MRestores.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            limpiarPantallaSinPausa();
            if(respaldoConfiguracion.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;

        case 2:
            limpiarPantallaSinPausa();
            if(respaldoCargaInicial.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 3:
            limpiarPantallaSinPausa();
            if(respaldoCarrera.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 4:
            limpiarPantallaSinPausa();
            if(respaldoMaterias.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 5:
            limpiarPantallaSinPausa();
            if(respaldoCursadaMateria.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 6:
            limpiarPantallaSinPausa();
            if(respaldoCuatrimestre.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 7:
            limpiarPantallaSinPausa();
            if(respaldoEventos.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");;
            }
            limpiarPantalla();
            break;
        case 8:
            limpiarPantallaSinPausa();

            if(respaldoNotaFinal.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///RESTAURA TODOS LOS ARCHIVOS DESDE LOS .BUP
void GestorRespaldos::restoreTotal()
{

    limpiarPantallaSinPausa();
    cout << "Configuracion: " ;
    if(  Config::crearConfig(Rutas::config))
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carga Inicial: " ;
    if(respaldoCargaInicial.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carrera: " ;
    if(respaldoCarrera.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Materias: " ;
    if(respaldoMaterias.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Cursada materias: " ;
    if(respaldoCursadaMateria.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Cuatrimestre: " ;
    if(respaldoCuatrimestre.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Eventos: " ;
    if(respaldoEventos.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Nota final: " ;
    if(respaldoNotaFinal.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    limpiarPantalla();
}

///MENU PARA SELECCIONAR UN ARCHIVO Y BORRAR SUS DATOS
void GestorRespaldos::menuPorDefecto()
{
    std::vector<std::string> opciones =
    {
        "Configuracion",
        "Cursada materias",
        "Cuatrimestre",
        "Eventos",
        "Notas finales"

    };

    string tituloMenu = "---Seleccione el archivo que quiera vaciar---";
    Menu MRestores(opciones,tituloMenu);
    msj.mensajeInformacion("Al borrar los datos de un archivo se creara una copia de seguridad automaticamente");
    int op;
    do
    {
        op = MRestores.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            {
            limpiarPantallaSinPausa();

            if(respaldoConfiguracion.borrarRegistros() && Config::crearConfig(Rutas::config))
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }
        case 2:
            {
            limpiarPantallaSinPausa();

            if(respaldoCursadaMateria.borrarRegistros())
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }
        case 3:
            {

            limpiarPantallaSinPausa();
            if(respaldoCuatrimestre.borrarRegistros())
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }
        case 4:
            {

            limpiarPantallaSinPausa();
            if(respaldoEventos.borrarRegistros())
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }

        case 5:
            {

            limpiarPantallaSinPausa();

            if(respaldoNotaFinal.borrarRegistros())
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///BORRA TODOS LOS DATOS DE TODOS LOS ARCHIVOS EXISTENTES
void GestorRespaldos::porDefectoTotal()
{
    msj.mensajeInformacion("Al borrar los datos de un archivo se creara una copia de seguridad automaticamente");
    limpiarPantallaSinPausa();
    cout << "Configuracion: " ;
    if(respaldoConfiguracion.borrarRegistros() && Config::crearConfig(Rutas::config))
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }

    cout << "Carga Inicial: " ;
    if(respaldoCargaInicial.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carrera: " ;
    if(respaldoCarrera.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Materias: " ;
    if(respaldoMaterias.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Cursada materias: " ;
    if(respaldoCursadaMateria.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Cuatrimestre: " ;
    if(respaldoCuatrimestre.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Eventos: " ;
    if(respaldoEventos.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Nota final: " ;
    if(respaldoNotaFinal.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    limpiarPantalla();

}

/// ------------------------------------------- ///

///MENU PRIMER INICIO
void GestorRespaldos::PrimerInicio()
{

    std::vector<std::string> opciones =
    {
        "Crear copia de seguridad de un solo archivo",
        "Crear copia de seguridad de todos los archivos",
        "Reestablecer un archivo desde el backup",
        "Reestablecer todos los archivos desde backup",
        "Borrar datos de un solo archivo",
        "Borrar todos los datos de archivos"

    };

    string tituloMenu = "** Gestion de copias de seguridad **";
    Menu MenuPrincipal(opciones,tituloMenu);


    int op;
    do
    {
        op = MenuPrincipal.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            limpiarPantallaSinPausa();
            primerInicioMenuBackups();
            limpiarPantallaSinPausa();
            break;
        case 2:
            limpiarPantallaSinPausa();
            primerInicioBackupTotal();
            limpiarPantallaSinPausa();
            break;
        case 3:
            limpiarPantallaSinPausa();
            primerInicioMenuRestores();
            limpiarPantallaSinPausa();
            break;
        case 4:
            limpiarPantallaSinPausa();
            primerInicioRestoreTotal();
            limpiarPantallaSinPausa();
            break;
        case 5:
            limpiarPantallaSinPausa();
            primerInicioMenuPorDefecto();
            limpiarPantallaSinPausa();
            break;
        case 6:
            {
            limpiarPantallaSinPausa();
            Menu m({"Si","No"},"Esta seguro que desea eliminar todos los datos?");
            int opc = m.mostrar();
            if(opc==1)
            {
            primerInicioPorDefectoTotal();
            }
            limpiarPantallaSinPausa();
            break;
            }
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///MENU PARA SELECCIONAR UN ARCHIVO PARA HACERLE .BUP
void GestorRespaldos::primerInicioMenuBackups()
{
    std::vector<std::string> opciones =
    {
        "Configuracion",
        "Carga Inicial",
        "Carrera",
        "Materias"

    };

    string tituloMenu = "---Seleccione el archivo del que quiere crear una copia de seguridad---";
    Menu MBackups(opciones,tituloMenu);

    int op;
    do
    {
        op = MBackups.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1: ///CONFIG 1
            {

            limpiarPantallaSinPausa();
            if(respaldoConfiguracion.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 2: ///NOTA FINAL 2
            {

            limpiarPantallaSinPausa();
            if(respaldoCargaInicial.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 3: ///CARRERA 3
            {

            limpiarPantallaSinPausa();
            if(respaldoCarrera.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        case 4: ///MATERIAS 4
            {
            limpiarPantallaSinPausa();
            if(respaldoMaterias.crearBackup())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
            }
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///CREA .BUP DE TODOS LOS ARCHIVOS CON DATOS
void GestorRespaldos::primerInicioBackupTotal()
{

    limpiarPantallaSinPausa();
    cout << "Configuracion: " ;
    if(respaldoConfiguracion.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }

    cout << "Carga Inicial: " ;
    if(respaldoCargaInicial.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Carrera: " ;
    if(respaldoCarrera.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Materias: " ;
    if(respaldoMaterias.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    limpiarPantalla();

}

///MENU PARA SELECCIONAR QUE ARCHIVO RESTAURAR DESDE .BUP
void GestorRespaldos::primerInicioMenuRestores()
{
    std::vector<std::string> opciones =
    {
        "Configuracion",
        "Carga Inicial",
        "Carrera",
        "Materias"

    };

    string tituloMenu = "---Seleccione el archivo que quiere restaurar desde una copia de seguridad---";
    Menu MRestores(opciones,tituloMenu);

    int op;
    do
    {
        op = MRestores.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            limpiarPantallaSinPausa();
            if(respaldoConfiguracion.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;

        case 2:
            limpiarPantallaSinPausa();
            if(respaldoCargaInicial.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 3:
            limpiarPantallaSinPausa();
            if(respaldoCarrera.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 4:
            limpiarPantallaSinPausa();
            if(respaldoMaterias.restoreDesdeBup())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///RESTAURA TODOS LOS ARCHIVOS DESDE LOS .BUP
void GestorRespaldos::primerInicioRestoreTotal()
{

    limpiarPantallaSinPausa();
    cout << "Configuracion: " ;
    if(respaldoConfiguracion.borrarRegistros() && Config::crearConfig(Rutas::config))
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carga Inicial: " ;
    if(respaldoCargaInicial.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carrera: " ;
    if(respaldoCarrera.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Materias: " ;
    if(respaldoMaterias.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    limpiarPantallaSinPausa();
msj.mensajeInformacion("Reinicie el programa para que sus cambios se vean reflejados");
    limpiarPantalla();
}

///MENU PARA SELECCIONAR UN ARCHIVO Y BORRAR SUS DATOS
void GestorRespaldos::primerInicioMenuPorDefecto()
{
    std::vector<std::string> opciones =
    {
        "Carga Inicial",
        "Carrera",
        "Materias"

    };
    string tituloMenu = "---Seleccione el archivo que quiera vaciar---";
    Menu MRestores(opciones,tituloMenu);

    msj.mensajeInformacion("Al borrar los datos de un archivo se creara una copia de seguridad automaticamente");
    int op;
    do
    {
        op = MRestores.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            {
            limpiarPantallaSinPausa();

            if(respaldoCargaInicial.borrarRegistros())
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }
            case 2:
            {
            limpiarPantallaSinPausa();

            if(respaldoCarrera.borrarRegistros())
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }
        case 3:
            {
            limpiarPantallaSinPausa();

            if(respaldoMaterias.borrarRegistros())
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
            }
            limpiarPantalla();
            break;
            }
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///BORRA TODOS LOS DATOS DE TODOS LOS ARCHIVOS EXISTENTES
void GestorRespaldos::primerInicioPorDefectoTotal()
{
    msj.mensajeInformacion("Al borrar los datos de un archivo se creara una copia de seguridad automaticamente");
    limpiarPantallaSinPausa();
    cout << "Configuracion: " ;
    if(respaldoConfiguracion.borrarRegistros() && Config::crearConfig(Rutas::config))
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carga Inicial: " ;
    if(respaldoCargaInicial.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carrera: " ;
    if(respaldoCarrera.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Materias: " ;
    if(respaldoMaterias.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    limpiarPantalla();

}
