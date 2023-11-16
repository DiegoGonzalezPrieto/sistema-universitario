#include "Sistema.h"
#include <filesystem>
#include <iostream>
#include <vector>
using namespace std;
#include "Menu.h"
#include "func_utiles.h"
#include "func_archivos.h"
#include "rutas.h"

bool crearDirectorios(string ruta)
{
    return filesystem::create_directories(ruta);
}

Sistema::Sistema() :
    _gestorCarrera(Rutas::carrera,Rutas::cargaInicial ),
    _gestorEventos(Rutas::eventos, Rutas::materias, Rutas::cursadas ),
    _gestorMaterias(Rutas::materias),
    _gestorCorrelativas(Rutas::materias, Rutas::cursadas),
    _gestorNotasFinales(Rutas::notas, Rutas::materias, Rutas::cursadas),
    _cargaInicial(Rutas::cargaInicial ),
    _gestorCuatrimestre(Rutas::cuatrimestres, Rutas::cursadas, Rutas::materias, Rutas::notas),
    _gestorCsv(Rutas::archivoCsv, Rutas::materias, Rutas::cargaInicial ),
    _gestorConfig(Rutas::config),
    _gestorCursadaMaterias(Rutas::cursadas, Rutas::materias),
    _gestorRespaldos()

{
    //ctor
}

void Sistema::preInicio()
{
    crearDirectoriosEsenciales();
    if (!Config::leerConfig(Rutas::config))
        {
            _mensajero.mensajeAdvertencia("No se encuentra el archivo de configuración, se creará uno nuevo y se usarán valores por defecto.");
            Config::crearConfig(Rutas::config);
        }

    // Crea el archivo de eventos, ya que lo revisa para instanciar el menú inicial
    if (!_gestorEventos.getArchivo().archivoExiste())
        {
            _mensajero.mensajeAdvertencia("No se encuentra el archivo de eventos, se creará uno nuevo sin registros.");
            _gestorEventos.getArchivo().crearArchivo();
        }
}

void Sistema::iniciar()
{
    preInicio();

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


    string mensaje = "Datos necesarios para el funcionamiento del sistema:\n";
    mensaje += carreraCargada ? "Carrera : OK" : "Carrera : Falta";
    mensaje += "\n";
    mensaje += materiaCargada ? "Materias : OK" : "Materias : Falta";
    mensaje += "\n";


    ///Si falta 1 o  los 2 datos entra el bucle de carga inicial
    if(!materiaCargada || !carreraCargada)
        {
            menuCargaInicial();
        }

    CargaInicial cargaInicial;
    _cargaInicial.leerRegistro(0,cargaInicial);


    if (!cargaInicial.getMateriasCargadas() || !cargaInicial.getCarreraCargada())
        {
            _mensajero.mensajeAdvertencia("No se puede continuar hasta no finalizar la carga inicial de datos. Reiniciar el programa.");
            return;
        }

    // Chequeo eventos próximos
    string alertaEvento = "";
    if (_gestorEventos.hayEventoEnLosProximosDias(DIAS_DE_AVISO_EVENTO))
        {
            alertaEvento = " (!)";
        }

    vector <string> opcMenu = {"Materias",
                               "Cuatrimestres cursados",
                               "Eventos" + alertaEvento,
                               "Notas finales",
                               "Carrera",
                               "Configuracion",
                               "Backups",
                               "Créditos"
                              };

    Archivo<Carrera> ac(Rutas::carrera);
    Carrera c;
    ac.leerRegistro(0, c);
    string nombreUniversidad = c.getNombreUniversidad();
    string nombreCarrera = c.getNombreCarrera();

    limpiarPantallaSinPausa();
    cout << "\n\tBienvenido/a " + c.getNombreEstudiante() + "!" << endl;
    cout << "\n\tEstás cursando la carrera " << nombreCarrera << " en " << nombreUniversidad << "." << endl;
    cout << "\n\tTu número de legajo es " << c.getLegajo() << "." << endl;
    cout << endl;
    limpiarPantalla();

    Menu menu(opcMenu, "Gestion de Carrera " + nombreCarrera + " en " + nombreUniversidad);
    int opc;

    /// Una vez finalizada la carga inicial
    while(true)
        {
            opc = menu.mostrar();
            switch(opc)
                {


                case 0:
                    return;
                case 1:
                {
                    _gestorMaterias.menuCortoGMaterias();
                }
                break;
                case 2:
                {
                    _gestorCuatrimestre.iniciarGestorCuatrimestre();
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
                    _gestorConfig.iniciar();
                }
                break;
                case 7:
                {
                    _gestorRespaldos.iniciar();
                }
                break;
                case 8:
                    limpiarPantallaSinPausa();
                    cout << "*******************************************************************" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*                           Créditos                              *" << endl;
                    cout << "*                           ^^^^^^^^                              *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*  Librerías de terceros:                                         *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*     * rlutil                                                    *" << endl;
                    cout << "*       - Licencia DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE    *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*  Desarrolladores:                                               *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*      * José Arias                                               *" << endl;
                    cout << "*      * Franco Formía                                            *" << endl;
                    cout << "*      * Diego G. Prieto                                          *" << endl;
                    cout << "*      * Lucho Santostefano                                       *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*                                                                 *" << endl;
                    cout << "*******************************************************************" << endl;
                    break;
                default:
                    break;
                }



        }
}
void Sistema::crearDirectoriosEsenciales()
{
    GestorDirectorios gd;

    gd.crearDirectorios(Rutas::raizSistema);
    gd.crearDirectorios(Rutas::raizCursada);
    gd.crearDirectorios(Rutas::raizDatos);
    gd.crearDirectorios(Rutas::raizConfig);

    return;
}

void Sistema::menuCargaInicial()
{
    CargaInicial datos;
    _cargaInicial.leerRegistro(0,datos);

    bool materiaCargada = datos.getMateriasCargadas();
    bool carreraCargada = datos.getCarreraCargada();

    string mensaje = "Datos necesarios para el funcionamiento del sistema:\n";
    mensaje += carreraCargada ? "Carrera : OK" : "Carrera : Falta";
    mensaje += "\n";
    mensaje += materiaCargada ? "Materias : OK" : "Materias : Falta";
    mensaje += "\n";

    _mensajero.mensajeInformacion(mensaje);


    _mensajero.mensajeInformacion("Como primer paso, se debe cargar la información de la carrera y de todas las materias de la misma.");

    vector <string> opcMenuInicial = {"> Cargar datos de la carrera ","> Cargar de forma manual las materias", "> Cargar las materias mediante archivo csv","> Gestionar copias de seguridad"};
    Menu menuInicial(opcMenuInicial, "MENU DE CARGA INICIAL");

    bool salir=false;

    while(!materiaCargada || !carreraCargada )
        {
            if (salir) break;

            int opc = menuInicial.mostrar();
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
                            _mensajero.mensajeInformacion("Se ha guardado información parcial de las materias.\nAún pueden agregarse más materias.");
                        }

                    break;
                }


                case 3:
                {
                    Archivo<Materia> Materias(Rutas::materias);
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
                case 4:
                    {
                        _gestorRespaldos.PrimerInicio();
                        break;
                    }
                break;
                }
        }
}

