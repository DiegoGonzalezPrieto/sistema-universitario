#ifndef FUNC_CSV_H_INCLUDED
#define FUNC_CSV_H_INCLUDED

#include <string>
#include <vector>
#include "Materia.h"

bool validarColumnas(std::string lineaColumnas, std::vector <std::string>& errores);
bool validarCamposObligatoriosVacios(std::string campo, int nroFila, int nroColumna, std::vector <std::string>& errores);
bool validarCuatrimestreSugerido(std::string campo, int nroFila, int nroColumna, std::vector <std::string>& errores);
bool validarDuracionCuatrimestre(std::string campo, int nroFila, int nroColumna, std::vector <std::string>& errores);
void mostrarErrores(const std::vector <std::string>& errores);



#endif // FUNC_CSV_H_INCLUDED
