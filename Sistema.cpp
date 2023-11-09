#include "Sistema.h"
#include <filesystem>
#include <iostream>
#include <vector>
using namespace std;
#include "Menu.h"
#include "func_utiles.h"
#include "func_archivos.h"


//EN TEORIA FUNCIONA EL MENU PRINCIPAL CON UN CONTADOR QUE TIENE COMO OBJETIVO CONSGUIR LA INFORMACION NECESARIA
//PARA PODER ACCEDER AL SIGUIENTE MENU,
// APLICAR PRUEBAS Y VERIFICACIONES LO MAYOR POSIBLE.
//HAY QUE VALIDAR QUE UNA VEZ QUE SE IMPORTARON LAS MATERIAS POR CSV NO SE PERMITA AGREGAR DE FORMA MANUAL EN EL MENU INICIAL " ANALIZAR SI NOS PERJUDICA O NO
// ANALIZAR LAS VALIDACIONES QUE REALICE EN EL CASE 3 Y EL CASE 1 DEL MENU INICIAL.
//ANALIZAR SI HACE FALTA ALGUNA PARA EL CASE 2.
//AGREUE LA FUNCION LIMPIAR PANTALLA AL LA CLASE MANU
//MODIFICAMOS VARIAS CLASES Y GESTORES EN FUNCION DEL MENU INICIAL
// LA CLASE CARGA INICIAL CONTIENE VALORES ENTEROS
// FUNUCIONES ANTERIORES DE CARGA INICIAL LAS DEJE COMENTADAS
//DIEGO FIJATE SI TE ANDA EL LIMPIAR PANTALA / SINO TE ENCARGO QUE LA ADAPTES A TU GUSTO.
//LES PIDO PORFA REVISEN ESXAUSTIVAMENTE LAS LLAVES DE TODA LA FUNCION INICIAR DEL SISTEMA, MAREA UN POCO, NO VAYA A SER QUE SE ME HAYA PASADO ALGUNA LLAVE.
//PARA SALIR DEL MENU INICIAL TENES QUE INGRESAR LOS DATOS DE LA CARRERA Y LOS DATOS DE LAS MATERIAS
//TENEMOS QUE HACER MENSAJES QUE ACLAREN LOS REQUISITOS PARA SALIR DEL MENU INICIAL Y LOS REQUISITOS DE LAS CARGAS MANUALES DE LAS MATERIAS
//POR EJEMPLO TIENEN QUE IR POR ORDEN DE CORRELATIVIDAD , NO PODES INGRESAR UNA MATERIA DE 5TO AÑO ANTES QUE UNA DE PRIMER CUATRIMESTRE.
//ANALIZAR LA RUTA DE LOS ARCHIVOS Y ESTABLECER LA QUE MEJOR LES PAREZCA
//CUIDADO DE SOBREESCRIBIR EL ARCHIVO EXCEL QUE PERDEMOS LOS DATOS DE LAS CORRELATIVIDADES.
// UN BESO.

bool crearDirectorios(string ruta)
{
    return filesystem::create_directories(ruta);
}

Sistema::Sistema() :
    _gestorCarrera("Archivos/datos/carrera.dat","carga_inicial.dat"), _gestorEventos("Archivos/datos/eventos.dat"), _gestorMaterias("Archivos/datos/materias.dat"),
    _gestorNotasFinales("Archivos/datos/notas_finales.dat"), _cargaInicial("carga_inicial.dat"),
    _gestorCsv("archivoImportacion.csv", "Archivos/datos/materias.dat", "carga_inicial.dat")
{
    //ctor
}

void Sistema::iniciar()
{
//    system("color B1");
    crearDirectoriosEsenciales();


    vector <string> opcMenu = {"Materias", "Cuatrimestres cursados", "Eventos", "Notas finales", "Carrera", "Configuracion"};

    Menu menu(opcMenu, "Sistema de Gestion de Carrera Universitaria");
    int opc;
    int datosAgregadoss=0;
    bool materiaCargada = false, carreraCargada =false;

    if(_cargaInicial.archivoExiste())
        {
            CargaInicial datos;
            _cargaInicial.leerRegistro(0,datos);

            datosAgregadoss=datos.getdatoscargados();
            materiaCargada = datos.getMateriasCargadas();
            carreraCargada = datos.getCarreraCargada();

        }

    else
        {
            _cargaInicial.crearArchivo();
        }

    ///Si falta 1 o 2 datos entra el primer while

    string mensaje = "Datos necesarios para el funcionamiento del sistema:\n";
    mensaje += carreraCargada ? "Carrera : OK" : "Carrera : Falta";
    mensaje += "\n";
    mensaje += materiaCargada ? "Materias : OK" : "Materias : Falta";
    mensaje += "\n";


    if(!materiaCargada || !carreraCargada)
        {
            _mensajero.mensajeInformacion(mensaje);


            _mensajero.mensajeInformacion("Como primer paso, se debe cargar la información de la carrera y de todas las materias de la misma.");
            vector <string> opcMenuInicial = {"> Cargar datos de la carrera ","> Cargar de forma manual las materias", "> Cargar las materias mediante archivo csv "};

            Menu menuInicial(opcMenuInicial, "MENU DE CARGA INICIAL");

            bool salir=false;

            while(!materiaCargada || !carreraCargada )
                {
                    if (salir) break;

                    opc = menuInicial.mostrar();
                    limpiarPantalla();
                    switch(opc)
                        {

                        case 0:
                            salir = true;
                            break;
                        case 1:
                        {
                            if(!carreraCargada)
                                {
                                    _gestorCarrera.cargarManual();
                                    CargaInicial datos;
                                    _cargaInicial.leerRegistro(0,datos);
                                    datos.aumentarcontadorDatosCargados();
                                    datos.setCarreraCargada(true);
                                    _cargaInicial.modificarRegistro(0,datos);
                                }
                            else
                                {
                                    _mensajero.mensajeInformacion("La carrera ya fue cargada correctamente. Ingresar datos de la carrera.");
                                    CargaInicial datos;
                                    _cargaInicial.leerRegistro(0,datos);
                                    datos.setCarreraCargada(true);
                                    _cargaInicial.modificarRegistro(0,datos);
                                }
                            //limpiarPantalla();
                            break;
                        }
                        case 2:
                        {
                            if (materiaCargada)
                                {
                                    _mensajero.mensajeInformacion("Las materias ya fueron cargadas correctamente. Ingresar datos de la carrera.");
                                    break;
                                }

                            _gestorMaterias.iniciarGestorMaterias();
                            std::cout << "Luego de confirmar la carga actual, no podrán agregarse nuevas materias." << std::endl;
                            std::cout << "Si selecciona 'N', se guardará información parcial de las materias, permitiendo continuar luego." << std::endl;
                            std::cout << "Desea dar por finalizada la carga de todas materias? (S/N) " << std::endl;
                            std::cin.clear();
                            char respuesta;
                            respuesta = validar<char>();
                            if(respuesta=='S' || respuesta=='s')
                                {
                                    _mensajero.mensajeInformacion("Se ha guardado la información total de las materias.\nPara el correcto funcionamiento del sistema, no pueden agregarse más materias.");
                                    CargaInicial datos;
                                    _cargaInicial.leerRegistro(0,datos);
                                    datos.aumentarcontadorDatosCargados();
                                    datos.setMateriasCargadas(true);
                                    _cargaInicial.modificarRegistro(0,datos);
                                    break;
                                }
                            else
                                {
                                    _mensajero.mensajeInformacion("Se ha guardado la información total de las materias.\nPara el correcto funcionamiento del sistema, no pueden agregarse más materias.");
                                }

                            break;
                        }


                        case 3:
                        {
                            Archivo<Materia> Materias("Archivos/datos/materias.dat");
                            if(Materias.archivoExiste())
                                {
                                    std::cout<<" Hemos detectado que ya realizo ingresos manuales de materias"<<std::endl;
                                    std::cout<<" en caso de querer ingresar las materias a travez de la carga"<<std::endl;
                                    std::cout<<" por archivo, se eliminara toda la informacion anteriormente ingresada "<<std::endl;
                                    std::cout<<" para evitar errores"<<std::endl;
                                    std::cout<<" Desea Continuar? (S/N) "<<std::endl;
                                    char res = validar<char>();

                                    if(res =='s' || res =='S' )
                                        {
                                            CargaInicial datos;
                                            _cargaInicial.leerRegistro(0,datos);
                                            datos.disminuirDatosCargados();
                                            datos.setMateriasCargadas(false);
                                            _cargaInicial.modificarRegistro(0,datos);
                                            Materias.crearArchivo();
                                            _gestorCsv.iniciar();

                                        }
                                }

                            else
                                {
                                    _gestorCsv.iniciar();
                                }


                            break;
                        }

                        default:
                            break;
                        }
                    CargaInicial datos;
                    _cargaInicial.leerRegistro(0,datos);
                    datosAgregadoss=datos.getdatoscargados();

                }
        }

    CargaInicial cargaInicial;
    _cargaInicial.leerRegistro(0,cargaInicial);


    if (!cargaInicial.getMateriasCargadas()|| !cargaInicial.getCarreraCargada())
        {
            _mensajero.mensajeAdvertencia("No se puede continuar hasta no finalizar la carga inicial de datos. Reiniciar el programa.");
            return;
        }

    /// Una vez finalizada la carga inicial
    while(true)
        {


            opc = menu.mostrar();

            switch(opc)
                {

                case 0:
                    return;
                    break;
                case 1:
                {
                    _gestorMaterias.iniciarGestorMaterias();
                }
                case 2:
                {
                    cout<<" En desarrollo "<<endl;
                }
                break;
                case 3:
                    _gestorEventos.iniciar();
                    break;
                case 4:
                    _gestorNotasFinales.iniciar();
                    break;
                case 5:
                    _gestorCarrera.iniciar();
                    break;
                case 6:
                {
                    cout<<" En desarrollo "<<endl;
                }
                break;
                default:
                    break;
                }
        }

}

///Si no existe el archivo cargaInicial lo creamos (y suponemos que estamos en esta instancia del programa)
///Si el archivo existe, pero su estado es true, significa que aun faltan cargar materias
///Si devuelve false, el usuario confirmo que finalizo la carga de todas las materias
/*bool Sistema::cargaInicial()
{
  bool Baux;
    CargaInicial aux;
    CargaInicial auxCarrera;

    if(_cargaInicial.archivoExiste() == false)
    {

        aux.setEstadoMateria(true);
        auxCarrera.setEstadoCarrera(true);

        _cargaInicial.agregarRegistro(aux);
        _cargaInicial.agregarRegistro(auxCarrera);
        Baux= true;
    }

    else
    {

        _cargaInicial.leerRegistro(0, aux);
        _cargaInicial.leerRegistro(1,auxCarrera);

       if(aux.getEstadoMateria()==true)
       {
           Baux= true;
       }
        if(aux.getEstadoCarrera()==true)
       {
           Baux= true;
       }
       else if (!aux.getEstadoMateria() && !auxCarrera.getEstadoCarrera())  {

        Baux= false;
       }

    }
return Baux;

}*/

void Sistema::crearDirectoriosEsenciales()
{

    crearDirectorios("Archivos/datos");
    crearDirectorios("Archivos/configuracion");
    crearDirectorios("Archivos/cursada");

    return;
}
