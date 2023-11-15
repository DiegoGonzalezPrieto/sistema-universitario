#include <iostream>
#include <cstring>
using namespace std;

#include "gestorRespaldos.h"
#include "Menu.h"
#include "Mensajero.h"
#include "func_utiles.h"
#include "rutas.h"

GestorRespaldos::GestorRespaldos() :
    respaldoNotaFinal(Rutas::notas),
    respaldoCargaInicial(Rutas::cargaInicial),
    respaldoCarrera(Rutas::carrera),
    respaldoCuatrimestre(Rutas::cuatrimestres),
    respaldoEventos(Rutas::eventos),
    respaldoMaterias(Rutas::materias),
    respaldoConfiguracion(Rutas::config)

{}

void GestorRespaldos::iniciar()
{

    std::vector<std::string> opciones =
    {
        "Crear copia de seguridad de un archivo",
        "Crear copia de seguridad de todos los archivos",
        "Reestablecer un archivo",
        "Reestablecer todos los archivos",
        "Borrar datos de un archivo",
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
        case 1:
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
        case 2:
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
        case 3:
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
        case 4:
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
        case 5:
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
            break;
        case 6:
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
        case 7:
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
    if(respaldoNotaFinal.crearBackup())
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
    cout << "Materias: " ;
    if(respaldoMaterias.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo realizar la copia de seguridad");
    }
    cout << "Configuracion: " ;
    if(respaldoConfiguracion.crearBackup())
    {
        msj.mensajeInformacion("La copia de seguridad se realizo correctamente");
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
        case 5:
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
        case 6:
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
        case 7:
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
    if(respaldoNotaFinal.restoreDesdeBup())
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
    cout << "Materias: " ;
    if(respaldoMaterias.restoreDesdeBup())
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Configuracion: " ;
    if(Config::crearConfig(Rutas::config))
    {
        msj.mensajeInformacion("Archivo restaurado correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    limpiarPantalla();
}

void GestorRespaldos::menuPorDefecto()
{
    std::vector<std::string> opciones =
    {
        "Notas finales",
        "Cuatrimestre",
        "Eventos",
        "Configuracion"

    };

    string tituloMenu = "---Seleccione el archivo que quiera vaciar---";
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
        case 2:
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
        case 3:
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
        case 4:
            limpiarPantallaSinPausa();
            if(Config::crearConfig(Rutas::config))
            {
                msj.mensajeAdvertencia("Registros borrados correctamente");
            }
            else
            {
                msj.mensajeError("No se pudieron borrar los registros del archivo");
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


///BORRAR PROGRAMA
void GestorRespaldos::porDefectoTotal()
{

    limpiarPantallaSinPausa();
    cout << "Nota final: " ;
    if(respaldoNotaFinal.borrarRegistros())
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
    cout << "Materias: " ;
    if(respaldoMaterias.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    cout << "Configuracion: " ;
    if(respaldoConfiguracion.borrarRegistros())
    {
        msj.mensajeAdvertencia("Registros borrados correctamente");
    }
    else
    {
        msj.mensajeError("No se pudo restaurar el archivo");
    }
    limpiarPantalla();

}
