#include <iostream>
#include <vector>
using namespace std;

#include "GestorMaterias.h"
#include "Materia.h"
#include "Menu.h"
#include "GestorCsv.h"
#include "func_utiles.h"


GestorMaterias::GestorMaterias(std::string nombre) : archivoMaterias(nombre) {}

void GestorMaterias::iniciarGestorMaterias()
{
    std::vector<string> opciones =
    {
        "Cargar materias",
        "Modificar una materia",
        "Mostrar materias"
    };

    Menu menuPrincipal(opciones,"------ MATERIAS ------") ;

    int op;

    do
        {
            op = menuPrincipal.mostrar();
            switch(op)
                {
                case 0:
                    break;
                case 1:
                    CargarMaterias();
                    break;
                case 2:
                    modificarMaterias();
                    break;
                case 3:
                    mostrarMaterias();
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
    int opCarga ;
    cout << "Como desea realizar la carga de materias?" << endl;
    cout << "1 - Manual" << endl;
    cout << "2 - Mediante un archivo" << endl;
    cout << endl << "Ingrese una opcion: ";
    cin >> opCarga ;
    cin.ignore();

    switch(opCarga)
        {
        case 1:

            while (true)
                {
                    if (AgregarUnaMateria())
                        {
                            cout << "Materia agregada correctamente" << endl ;

                            char op ;
                            cout << "Desea agregar otra materia? (S/N)" << endl ;
                            cin >> op ;
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
            break ;
        case 2:
        {
            GestorCsv csv("","","");
            csv.iniciar();
            break;
        }
        default:
            cout << "Opcion ingresada no valida. Por favor, ingrese 1 o 2" << endl ;
            break ;
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
                    cin >> op ;
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
    if (archivoMaterias.leerRegistros(registros))
        {
            if (registros.empty())
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

    cout << "Ingrese el nombre de la Materia: ";
    getline(cin >> ws, datoString);
    datosMateria.setNombreMateria(datoString);

    cout << "Ingrese el ID de la Materia: ";
    getline(cin >> ws, datoString);
    datosMateria.setIdMateria(datoString);

    cout << "Ingrese la cantidad de materias requeridas: ";
    cin >> datoInt;
    cin.ignore();
    if (datoInt>0)
        {
            mostrarNombresMaterias();
            if (!guardarIDsMatRequeridas(datoInt, datosMateria))
                {
                    msj.mensajeError("No se pudieron guardar las correlativas");
                }
        }

    cout << "Ingrese el cuatrimestre sugerido: ";
    cin >> datoInt ;
    cin.ignore();
    datosMateria.setCuatrimestreSugerido(datoInt) ;

    cout << "Ingrese la cantidad de cuatrimestres de duracion: " ;
    cin >> datoInt ;
    cin.ignore();
    datosMateria.setCuatrimestreDeDuracion(datoInt) ;


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

    Materia datosMateria;
    string IDmateria;

    mostrarNombresMaterias();
    IDmateria = buscarIDMateria();
    int pos ;

    if (!buscarMateria(IDmateria, datosMateria, pos))
        {
            msj.mensajeError("No se encontró la materia con el ID proporcionado.");
            return false;
        }

    std::vector<std::string> opciones =
    {
        "Nombre de la materia",
        "ID de la materia",
        "IDs de las materias requeridas",
        "Cuatrimestre sugerido",
        "Duracion de la materia"
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
                }
                break;
                case 2:
                {
                    string nuevoIDmateria;
                    cout << "Ingrese el nuevo ID de la materia: ";
                    getline(cin >> ws, nuevoIDmateria);
                    datosMateria.setIdMateria(nuevoIDmateria);
                }
                break;
                case 3:
                {
                    int cant;
                    cout << "Ingrese la cantidad de IDs de materias requeridas: ";
                    cin >> cant;
                    cin.ignore();
                    if (cant>0)
                        {
                            mostrarNombresMaterias();
                            guardarIDsMatRequeridas(cant, datosMateria) ;
                        }

                }
                break;
                case 4:
                {
                    int nuevoCuatrimestreSugerido;
                    cout << "Ingrese el nuevo cuatrimestre sugerido: ";
                    cin >> nuevoCuatrimestreSugerido;
                    cin.ignore();
                    datosMateria.setCuatrimestreSugerido(nuevoCuatrimestreSugerido);
                }
                case 5:
                {
                    int nuevoCuatrimestresDuracion;
                    cout << "Ingrese la cantidad de cuatrimestres de duracion: ";
                    cin >> nuevoCuatrimestresDuracion;
                    cin.ignore();
                    datosMateria.setCuatrimestreDeDuracion(nuevoCuatrimestresDuracion);
                }
                }
            char op ;
            cin.ignore();
            cout << "Desea modificar otro dato de esta materia? (S/N): " ;
            cin >> op ;
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


void GestorMaterias::mostrarNombresMaterias()
{


    Materia datosMateria;
    int cantMat = archivoMaterias.contarRegistros() ;
    if (archivoMaterias.leerRegistros(registros))
        {
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

bool GestorMaterias::guardarIDsMatRequeridas(int cant, Materia& datosMateria)
{

    string nuevoID;
    Materia dataMateria;
    int op ;
    cout << "Seleccione las materias requeridas" << endl ;
    for (int i=0; i<cant; i++) ///ITERO POR LA CANTIDAD DE MATERIAS REQUERIDAS QUE EL USUARIO HABIA INGRESADO PREVIAMENTE
        {
            /// PIDO INGRESAR LOS NUMEROS QUE CORRESPONDEN A LAS MATERIAS REQUERIDAS
            cin >> op ;
            cin.ignore();
            if (op >= 1 && op <= archivoMaterias.contarRegistros()) ///VALIDO EL NUMERO
                {

                    if (archivoMaterias.leerRegistro(op-1,dataMateria)) ///ABRO EL REGISTRO DE LA MATERIA QUE EL USUARIO SELECCIONO
                        {
                            nuevoID = dataMateria.getIdMateria() ; ///COPIO EL ID DE ESA MATERIA SELECCIONADA
                            datosMateria.setIdMateriasRequeridas(i, nuevoID); ///SETEO EL ID COMO ID DE MATERIA REQUERIDA
                        }
                }
            else
                {
                    msj.mensajeError("Ingreso no valido. Por favor, ingrese un numero valido.");
                    return false ;
                }



        }
    return true ;
}


string GestorMaterias::buscarIDMateria()
{
    int op ;
    Materia datosMateria;
    while (true)
        {

            cout << endl << "Seleccione la materia que desea modificar: " ;

            /// PIDO INGRESAR LOS NUMEROS QUE CORRESPONDEN A LAS MATERIAS REQUERIDAS
            cin >> op ;
            cin.ignore();
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
    if (archivoMaterias.leerRegistros(registros))
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
    archivoMaterias.leerRegistros(registros);
    int tam = archivoMaterias.contarRegistros() ;

    for (int i = 0; i < tam; i++)
        {
            if (registros[i].getIdMateria() == IDmateria)
                {

                    datosMateria = registros[i];
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
    if (archivoMaterias.leerRegistros(registros))
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

