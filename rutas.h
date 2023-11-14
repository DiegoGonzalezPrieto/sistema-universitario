#ifndef RUTAS_H_INCLUDED
#define RUTAS_H_INCLUDED

namespace Rutas
{
    /// Raíces y archivo caga CSV
const std::string raizSistema = "sistema";
const std::string raizCursada = "cursada";
const std::string raizDatos = raizSistema + "/datos";
const std::string raizConfig = raizSistema + "/configuracion";

const std::string archivoCsv = "archivoImportacion.csv";

    /// Config y carga inicial
const std::string config = raizConfig + "/config.dat";
const std::string cargaInicial = raizSistema + "/carga_inicial.dat";

    /// Datos
const std::string carrera = raizDatos+ "/carrera.dat";
const std::string cuatrimestres = raizDatos + "/cuatrimestres.dat";
const std::string cursadas = raizDatos + "/cursadas.dat";
const std::string eventos = raizDatos + "/eventos.dat";
const std::string materias = raizDatos + "/materias.dat";
const std::string notas = raizDatos + "/notas.dat";
}



#endif // RUTAS_H_INCLUDED
