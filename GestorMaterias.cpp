#include <iostream>
#include <vector>
using namespace std;

#include "GestorMaterias.h"
#include "Materia.h"
#include "Menu.h"
#include "GestorCsv.h"
#include "func_utiles.h"


GestorMaterias::GestorMaterias(std::string nombreArchivo) : archivoMaterias(nombreArchivo) {}


void GestorMaterias::iniciarGestorMaterias()
{
    std::vector<string> opciones =
    {
        "Cargar materias",
        "Modificar una materia",
        "Mostrar materias"
    };
    string tituloMenu = "** Materias **";

    Menu menuPrincipal(opciones,tituloMenu) ;

    int op;
    do
    {
        op = menuPrincipal.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            limpiarPantalla();
            CargarMaterias();
            limpiarPantalla();
            break;
        case 2:
            limpiarPantalla();
            modificarMaterias();
            limpiarPantalla();
            break;
        case 3:
            limpiarPantalla();
            mostrarMaterias();
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


void GestorMaterias::menuCortoGMaterias()
{
    std::vector<string> opciones =
    {
        "Modificar una materia",
        "Mostrar materias",
    };
    string tituloMenu = "** Materias **";

    Menu menuPrincipal(opciones,tituloMenu) ;

    int op;
    do
    {
        op = menuPrincipal.mostrar();
        switch(op)
        {
        case 0:
            break;
        case 1:
            limpiarPantalla();
            modificarMaterias();
            limpiarPantalla();
            break;
        case 2:
            limpiarPantalla();
            mostrarMaterias();
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


void GestorMaterias::CargarMaterias()
{
    while(true)
    {
        if (AgregarUnaMateria())
        {
            cout << "Materia agregada correctamente" << endl ;
            char op ;
            cout << "Desea agregar otra materia? (S/N)" << endl ;
            op=validar<char>();
            if (op == 'N' || op == 'n')
            {
                break ;
            }
        }

        else
        {
            msj.mensajeError("No se pudo agregar la materia");
            break ;
        }
    }
}

void GestorMaterias::modificarMaterias()
{
    while (true)
    {
        if (modificarUnaMateria())
        {
            char op ;
            cout << "Desea modificar otra materia? (S/N)" << endl ;
            op=validar<char>();
            if (op == 'N' || op == 'n')
            {
                break ;
            }
        }
        else
        {
            msj.mensajeError("No se logro modificar la materia") ;
            break ;
        }
    }
}


void GestorMaterias::mostrarMaterias()
{
    Materia datosMateria;
    if (archivoMaterias.leerRegistros(materias))
    {
        if (materias.empty())
        {
            msj.mensajeError("No hay materias para mostrar.") ;
        }
        else
        {
            int cantMat = archivoMaterias.contarRegistros() ;
            for (int i=0; i<cantMat; i++)
            {

                if (archivoMaterias.leerRegistro(i,datosMateria))
                {
                    cout << endl << datosMateria.toString() ;
                    cout  << endl << "----------------------------------" ;

                }

                else
                {
                    msj.mensajeError("No se pudo leer el registro") ;
                }
            }
        }
    }

    else
    {
        cout << "Error al leer los registros del archivo." << endl;
    }
}


bool GestorMaterias::AgregarUnaMateria()
{
    if (!archivoMaterias.archivoExiste())
    {
        if (!archivoMaterias.crearArchivo())
        {
            msj.mensajeError("El archivo no existe y no puede ser creado ") ;
            return false ;
        }
    }

    Materia datosMateria;
    string datoString;
    int datoInt ;
    bool grabo ;

    do
    {
        cout << "Ingrese el nombre de la Materia: ";
        getline(cin >> ws, datoString);
        if (!nombreExiste(datoString))
        {
            datosMateria.setNombreMateria(datoString);
            grabo = true;
        }
        else
        {
            msj.mensajeError("Ese nombre de materia ya existe. Intente nuevamente");
            grabo = false;
        }
    }
    while(!grabo);

    do
    {
        cout << "Ingrese el ID de la Materia: ";
        getline(cin >> ws, datoString);

        if(!IDExiste(datoString))
        {
            datosMateria.setIdMateria(datoString);
            grabo = true;
        }
        else
        {
            msj.mensajeError("Ese ID de materia ya existe. Intente nuevamente");
            grabo = false;
        }

    }
    while (!grabo);

    string IDPropio = datoString;

    if(archivoMaterias.contarRegistros()>0)
    {
        bool valorValido;
        do
        {
            cout << "Ingrese la cantidad de materias requeridas: ";
            datoInt=validar<int>();
            ///LA CANTIDAD DE MATERIAS REQUERIDAS NO PUEDE SER MAYOR A LA CANTIDAD DE MATERIAS CARGADAS
            if (datoInt>0 && datoInt<=archivoMaterias.contarRegistros())
            {
                mostrarNombresMaterias();
                if (!guardarIDsMatRequeridas(datoInt,IDPropio, datosMateria))
                {
                    msj.mensajeError("No se pudieron guardar las correlativas");
                }
                valorValido = true;
            }
            else if(datoInt==0)
            {
                datosMateria.setIdMateriasRequeridas(0,"N/A");
                valorValido = true;
            }
            else
            {
                msj.mensajeError("Numero ingresado no valido. Intente de nuevo");
                valorValido = false;
            }
        }
        while(!valorValido);

    }
    else if (archivoMaterias.contarRegistros()==0)
    {

        datosMateria.setIdMateriasRequeridas(0,"N/A");
    }

    do
    {
        cout << "Ingrese el cuatrimestre sugerido: ";
        datoInt=validar<int>();

        if(datoInt>0 && datoInt<=12)
        {
            datosMateria.setCuatrimestreSugerido(datoInt) ;
            grabo = true;
        }
        else
        {
            msj.mensajeError("Ingrese un numero de cuatrimestre valido. Intente nuevamente");
            grabo = false;
        }
    }
    while(!grabo);

    do
    {
        cout << "Ingrese la cantidad de cuatrimestres de duracion:(1 o 2) " ;
        datoInt=validar<int>();

        if(datoInt>0 && datoInt<=2)
        {
            datosMateria.setCuatrimestreDeDuracion(datoInt) ;
            grabo=true;
        }
        else
        {
            msj.mensajeError("Ingrese una duracion de materia valida. Intente nuevamente");
            grabo = false;
        }
    }
    while(!grabo);

    if (archivoMaterias.agregarRegistro(datosMateria))
    {
        return true ;
    }
    else
    {
        msj.mensajeError("Error al agregar el registro en el archivo.") ;
        return false ;
    }

};


bool GestorMaterias::modificarUnaMateria()
{
    if(archivoMaterias.contarRegistros()>0)
    {
        Materia datosMateria;
        string IDmateria;

        msj.mensajeInformacion("Tanto los IDs de las materias cargadas como su duración ya no se pueden modificar.");
        mostrarNombresMaterias();
        IDmateria = buscarIDMateria();

        cout << endl << IDmateria << endl ;
        system("pause");
        int pos ;

        if (!buscarMateria(IDmateria, datosMateria, pos))
        {
            msj.mensajeError("No se encontró la materia con el ID proporcionado.");
            return false;
        }

        std::vector<std::string> opciones =
        {
            "Nombre de la materia",
            "IDs de las materias requeridas",
            "Cuatrimestre sugerido"
        };

        Menu MenuMod(opciones,"Seleccione qué dato desea modificar: ");

        while (true)
        {
            cout << endl ;
            switch (MenuMod.mostrar())
            {
            case 0:
            {
                break ;
            }
            case 1:
            {
                string nuevoNombreMateria;
                cout << "Ingrese el nuevo nombre de la Materia: ";
                getline(cin >> ws, nuevoNombreMateria);
                datosMateria.setNombreMateria(nuevoNombreMateria);
                break ;
            }
            case 2:
            {

                limpiarCorrelativas(pos,datosMateria);
                int cant;
                cout << "Ingrese la cantidad de IDs de materias requeridas: ";
                cant=validar<int>();
                if (cant>0)
                {
                    mostrarNombresMaterias();
                    guardarIDsMatRequeridas(cant,IDmateria, datosMateria) ;
                }
                break ;
            }
            break;
            case 3:
            {
                int nuevoCuatrimestreSugerido;
                cout << "Ingrese el nuevo cuatrimestre sugerido: ";
                nuevoCuatrimestreSugerido=validar<int>();
                datosMateria.setCuatrimestreSugerido(nuevoCuatrimestreSugerido);
                break ;
            }
            default:
            break;
            }

            char op ;
            cout << "Desea modificar otro dato de esta materia? (S/N): " ;
            op=validar<char>();
            if (op == 'N' || op == 'n')
            {
                break ;
            }
        }

        if (archivoMaterias.modificarRegistro(pos, datosMateria))
        {
            cout << "Materia modificada correctamente" << endl << endl ;
            return true;
        }
        else
        {
            cout << "Error al modificar el registro en el archivo." << endl;
            return false;
        }

    }
    else
    {
        msj.mensajeError(" No se han ingresado materias ");
        return false;
    }
}


void GestorMaterias::mostrarNombresMaterias()
{


    Materia datosMateria;
    int cantMat = archivoMaterias.contarRegistros() ;
    if (archivoMaterias.leerRegistros(materias))
    {
        cout << endl << "--- MATERIAS CARGADAS ---" << endl ;
        for (int i=0; i<cantMat; i++)
        {
            if (archivoMaterias.leerRegistro(i,datosMateria))
            {
                cout << i+1 << ": " << datosMateria.getNombreMateria() << endl ;
            }
            else
            {
                msj.mensajeError("No se pudo mostrar las materias") ;
                break;
            }
        }

    }
    else
    {
        msj.mensajeError ("No se pudo mostrar las materias");
    }
}

bool GestorMaterias::guardarIDsMatRequeridas(int cant, string _IDpropio, Materia& datosMateria)
{
    vector<string> vMat(cant, "");
    string nuevoID;
    Materia dataMateria;
    int op;

    cout << "Seleccione las materias requeridas" << endl;
    for (int i = 0; i < cant; i++)
    {
        bool IDvalido;
        do
        {
            op = validar<int>();

            if (op >= 1 && op <= archivoMaterias.contarRegistros())
            {
                if (archivoMaterias.leerRegistro(op - 1, dataMateria))
                {
                    nuevoID = dataMateria.getIdMateria();

                    bool repetido = false;
                    for (string& ID : vMat)
                    {
                        if (ID == nuevoID)
                        {
                            repetido = true;
                            break;
                        }
                    }

                    if (nuevoID != _IDpropio)
                    {
                        if (!repetido)
                        {
                            datosMateria.setIdMateriasRequeridas(i, nuevoID);
                            IDvalido = true;
                            vMat[i] = nuevoID;
                        }
                        else
                        {
                            msj.mensajeError("Esa materia ya fue agregada, vuelva a intentarlo");
                            IDvalido = false;
                        }
                    }
                    else
                    {
                        msj.mensajeError("La materia no puede ser correlativa de sí misma, vuelva a intentarlo");
                        IDvalido = false;
                    }
                }
            }
            else
            {
                msj.mensajeError("Ingreso no válido. Por favor, ingrese un número válido.");
                IDvalido = false;
            }
        } while (!IDvalido);
    }

    return true;
}

string GestorMaterias::buscarIDMateria()
{
    int op ;
    Materia datosMateria;
    while (true)
    {

        cout << endl << "Seleccione la materia que desea modificar: " ;

        /// PIDO INGRESAR LOS NUMEROS QUE CORRESPONDEN A LAS MATERIAS REQUERIDAS
        op=validar<int>();
        if (op >= 1 && op <= archivoMaterias.contarRegistros()) ///VALIDO EL NUMERO
        {
            if (archivoMaterias.leerRegistro(op-1,datosMateria)) ///ABRO EL REGISTRO DE LA MATERIA QUE EL USUARIO SELECCIONO
            {
                return datosMateria.getIdMateria() ; ///COPIO EL ID DE ESA MATERIA SELECCIONADA
            }
        }
        else
        {
            msj.mensajeError("Ingreso no valido. Por favor, ingrese un numero valido.");
        }
    }
}


string GestorMaterias::mostrarNombrePorID(string IDMateria)
{
    Materia datosMateria;
    int cantMat = archivoMaterias.contarRegistros() ;
    if (archivoMaterias.leerRegistros(materias))
    {
        for (int i=0; i<cantMat; i++)
        {
            archivoMaterias.leerRegistro(i,datosMateria);
            if (datosMateria.getIdMateria()==IDMateria)
            {
                return datosMateria.getNombreMateria();
            }


        }

    }
    return "";
}

bool GestorMaterias::buscarMateria(std::string& IDmateria, Materia& datosMateria, int &pos)
{
    Materia mat;
    int tam = archivoMaterias.contarRegistros() ;
    for (int i=0;i<tam;i++)
    {
        archivoMaterias.leerRegistro(i,mat);
        if (mat.getIdMateria() == IDmateria)
        {
            datosMateria = mat;
            pos = i ;
            return true;
        }
    }
    return false;

}

std::string GestorMaterias::seleccionarIdMateria()
{
    // Adaptado de listarMaterias para presentar las materias en columnas
    int opc=0;
    Materia datosMateria;
    int cantMat = archivoMaterias.contarRegistros();
    if (cantMat<=0)
    {
        msj.mensajeAdvertencia("No hay materias guardadas en el sistema.");
        return "";
    }

    const int CANT_COLUMNAS = 2, ANCHO_COLUMNAS = 35;
    int cantFilas = cantMat % CANT_COLUMNAS == 0 ? cantMat / CANT_COLUMNAS : cantMat / CANT_COLUMNAS + 1;
    std::string * filas = new std::string[cantFilas] {};
    if (filas==NULL)
    {
        msj.mensajeError("No se pudo listar las materias.");
        return "";
    }

    bool inicioFila=true;
    int espaciosHastaSiguienteColumna = 0;
    Materia aux;
    std::string espacioBlanco ="";
    int e;
    if (archivoMaterias.leerRegistros(materias))
    {
        for (int i=0; i<cantMat; i++)
        {
            if (archivoMaterias.leerRegistro(i,datosMateria))
            {
                if (i>=cantFilas) inicioFila=false;

                archivoMaterias.leerRegistro(i-cantFilas,aux);
                espaciosHastaSiguienteColumna = ANCHO_COLUMNAS - aux.getNombreMateria().size();
                e=0;
                espacioBlanco="";
                while (e<espaciosHastaSiguienteColumna)
                {
                    espacioBlanco += " ";
                    e++;
                }

                filas[i%cantFilas] += inicioFila ? "" : espacioBlanco;
                filas[i%cantFilas] += "\t" + std::to_string(i+1) + ": " + datosMateria.getNombreMateria();

            }
            else
            {
                msj.mensajeError("No se pudo mostrar las materias") ;
                return "";
            }
        }

        for (int i=0; i<cantFilas; i++)
        {
            std::cout << filas[i]<< endl;
        }

        while (true)
        {
            std::cout << std::endl << "Ingresar número de la materia deseada: ";
            opc = validar<int>();
            if (opc > 0 && opc <= cantMat) break;
            msj.mensajeError("Opción inexistente.");
        }
        if (archivoMaterias.leerRegistro(opc-1,datosMateria)) return datosMateria.getIdMateria();
        else
        {

            msj.mensajeError("No se pudo mostrar las materias") ;
            return "";
        }
    }
    else
    {
        msj.mensajeError ("No se pudo mostrar las materias");
    }

    delete[] filas;
}

bool GestorMaterias::nombreExiste(string _nombre)
{
    ///Chequear si el nombre existe
    archivoMaterias.leerRegistros(materias);
    int tam = archivoMaterias.contarRegistros() ;

    for (int i = 0; i < tam; i++)
    {
        if (materias[i].getNombreMateria() == _nombre)
        {
            return true;
        }
    }

    return false;

}

bool GestorMaterias::IDExiste(string _ID)
{

    ///Chequear si el ID existe
    archivoMaterias.leerRegistros(materias);
    int tam = archivoMaterias.contarRegistros() ;

    for (int i = 0; i < tam; i++)
    {
        if (materias[i].getIdMateria() == _ID)
        {
            return true;
        }
    }

    return false;


}

void GestorMaterias::limpiarCorrelativas(int pos,Materia& datosMateria)
{
    archivoMaterias.leerRegistro(pos,datosMateria);
    for(int i = 0; i < CANTMATERIAS; i++)
    {
        datosMateria.setIdMateriasRequeridas(i,"N/A");
    }
}

Archivo<Materia> GestorMaterias::getArchivoMaterias()
{
    return archivoMaterias;

}
