#include <iostream>
#include <cstring>
using namespace std;

#include "gestorRespaldos.h"
#include "Menu.h"
#include "Mensajero.h"
#include "func_utiles.h"

GestorRespaldos::GestorRespaldos() :
    respaldoNotaFinal("Archivos/datos/notas.dat"),
    respaldoCargaInicial("carga_inicial.dat"),
    respaldoCarrera("Archivos/datos/carrera.dat"),
    respaldoCuatrimestre("Archivos/backup/cuatrimestre.dat"),
    respaldoEventos("Archivos/datos/eventos.dat"),
    respaldoMaterias("Archivos/datos/materias.dat"),
    respaldoConfiguracion("Archivos/configuracion/config.dat")

{}

void GestorRespaldos::iniciar()
{

    std::vector<std::string> opciones =
    {
        "Crear copia de seguridad de un archivo",
        "Crear copia de seguridad de todos los archivos",
        "Reestablecer un archivo",
        "Reestablecer todos los archivos",
        "Reestablecer valores por defecto de un archivo",
        "Reestablecer valores por defecto de todos los archivos"

    };

    string tituloMenu = "\n=====================================\n    ** Gestión de copias de seguridad **\n=====================================";
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
            limpiarPantallaSinPausa();
            porDefectoTotal();
            limpiarPantallaSinPausa();
            break;
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida" << endl;
            break;
        }

        cout << endl ;
    }
    while (op != 0);
}

///OPCIONES DEL MENU
void GestorRespaldos::menuBackups()
{
    std::vector<std::string> opciones =
    {
        "Notas finales",
        "Carga Inicial",
        "Carrera",
        "Cuatrimestre",
        "Eventos",
        "Materias",
        "Configuracion"

    };

    string tituloMenu = "\n---Seleccione el archivo del que quiere crear una copia de seguridad---\n";
    Menu MBackups(opciones,tituloMenu);

    int op;
    do
    {
        op = MBackups.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            limpiarPantallaSinPausa();

            if(backupNotaFinal())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
        case 2:
            limpiarPantallaSinPausa();
            if(backupCargaInicial())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
        case 3:
            limpiarPantallaSinPausa();
            if(backupCarrera())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
        case 4:
            limpiarPantallaSinPausa();
            if(backupCuatrimestre())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
        case 5:
            limpiarPantallaSinPausa();
            if(backupEventos())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
        case 6:
            limpiarPantallaSinPausa();
            if(backupMaterias())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
            }
            limpiarPantalla();
            break;
        case 7:
            limpiarPantallaSinPausa();
            if(backupConfiguracion())
            {
                msj.mensajeInformacion("Copia de seguridad realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo realizar la copia de seguridad");
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

void GestorRespaldos::backupTotal()
{

    limpiarPantallaSinPausa();
    cout << "Nota final: " ;
    if(backupNotaFinal())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Carga Inicial: " ;
    if(backupCargaInicial())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Carrera: " ;
    if(backupCarrera())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Cuatrimestre: " ;
    if(backupCuatrimestre())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Eventos: " ;
    if(backupEventos())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Materias: " ;
    if(backupMaterias())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Configuracion: " ;
    if(!backupConfiguracion())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    limpiarPantalla();

}

void GestorRespaldos::menuRestores()
{
    std::vector<std::string> opciones =
    {
        "Notas finales",
        "Carga Inicial",
        "Carrera",
        "Cuatrimestre",
        "Eventos",
        "Materias",
        "Configuracion"

    };

    string tituloMenu = "\n---Seleccione el archivo que quiere restaurar desde una copia de seguridad---\n";
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

            if(restoreNotaFinal())
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
            if(restoreCargaInicial())
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
            if(restoreCarrera())
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
            if(restoreCuatrimestre())
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
            if(restoreEventos())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");;
            }
            limpiarPantalla();
            break;
        case 6:
            limpiarPantallaSinPausa();
            if(restoreMaterias())
            {
                msj.mensajeInformacion("Restauracion realizada correctamente");;
            }
            else
            {
                msj.mensajeError("No se pudo restaurar el archivo");
            }
            limpiarPantalla();
            break;
        case 7:
            limpiarPantallaSinPausa();
            if(restoreConfiguracion())
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

void GestorRespaldos::restoreTotal()
{

    limpiarPantallaSinPausa();
    cout << "Nota final: " ;
    if(backupNotaFinal())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carga Inicial: " ;
    if(backupCargaInicial())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Carrera: " ;
    if(backupCarrera())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Cuatrimestre: " ;
    if(backupCuatrimestre())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Eventos: " ;
    if(backupEventos())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Materias: " ;
    if(backupMaterias())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Configuracion: " ;
    if(!backupConfiguracion())
    {
        msj.mensajeInformacion("OK");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    limpiarPantalla();
}

void GestorRespaldos::menuPorDefecto()
{
///FALTA IMPLEMENTAR
}

void GestorRespaldos::porDefectoTotal()
{
///FALTA IMPLEMENTAR
}

/// BACKUPS POR ARCHIVOS
bool GestorRespaldos::backupNotaFinal()
{
    if(respaldoNotaFinal.crearBackup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::backupCargaInicial()
{
    if(respaldoCargaInicial.crearBackup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::backupCarrera()
{
    if(respaldoCarrera.crearBackup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::backupCuatrimestre()
{
    if(respaldoCuatrimestre.crearBackup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::backupEventos()
{
    if(respaldoMaterias.crearBackup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::backupMaterias()
{
    if(respaldoMaterias.crearBackup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::backupConfiguracion()
{
    if(respaldoConfiguracion.crearBackup())
    {
        return true;
    }
    return false;
}


///RESTORES POR ARCHIVOS
bool GestorRespaldos::restoreNotaFinal()
{
    if(respaldoNotaFinal.restoreDesdeBup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::restoreCargaInicial()
{
    if(respaldoCargaInicial.restoreDesdeBup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::restoreCarrera()
{
    if(respaldoCarrera.restoreDesdeBup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::restoreCuatrimestre()
{
    if(respaldoCuatrimestre.restoreDesdeBup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::restoreEventos()
{
    if(respaldoMaterias.restoreDesdeBup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::restoreMaterias()
{
    if(respaldoMaterias.restoreDesdeBup())
    {
        return true;
    }
    return false;
}

bool GestorRespaldos::restoreConfiguracion()
{
    if(respaldoConfiguracion.restoreDesdeBup())
    {
        return true;
    }
    return false;
}

///RESTORES POR DEFECTO

///FALTA IMPLEMENTAR
