#ifndef FUNC_CSV_H_INCLUDED
#define FUNC_CSV_H_INCLUDED

#include <string>
#include <vector>
#include "Materia.h"

bool validarColumnas(std::string lineaColumnas, std::vector <std::string>& errores);
bool validarCamposObligatoriosVacios(std::string campo, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <Materia>& datos);
bool validarCuatrimestreSugerido(std::string campo, int nroFila, int nroColumna, std::vector <std::string>& errores);
bool validarDuracionCuatrimestre(std::string campo, int nroFila, int nroColumna, std::vector <std::string>& errores);
void mostrarErrores(const std::vector <std::string>& errores);
bool validarNombreUnico(const std::string nombreMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <Materia>& datos);
bool validarIdMateriaUnico(const std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <Materia>& datos);
bool validarSiYaSeCargaronIdMateriasRequeridas(const std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <Materia>& datos);
bool validarDatosFueraDeLasColumnas(std::string linea, std::vector <std::string>& errores);
bool validarIdMateriasRequeridasNoRepetidas(std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <std::string>& auxCorrelativas);
bool validarIdMateriasRequeridasNoSeanIdMateriaPropia(std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores, std::vector <std::string>& auxCorrelativas);
bool validarEspaciosEnBlanco(std::string idMateria, int nroFila, int nroColumna, std::vector <std::string>& errores);

#endif // FUNC_CSV_H_INCLUDED
