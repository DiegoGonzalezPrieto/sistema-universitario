#ifndef EVENTO_H
#define EVENTO_H

#include <string>
#include "FechaHorario.h"
#include "func_utiles.h"

const int LONGMAXIDMATERIA = 10;
const int LONGMAXDESCRIPCION = 50;
const int LONGMAXINFORMACION = 250;

class Evento
{
    public:
        Evento();

        void setId(int);
        void setFechaHorario(const FechaHorario& fechaHorario);
        void setDescripcion(const std::string& descripcion);
        void setInformacion(const std::string& informacion);
        void setIdCursadaMateria(const std::string& idCursadaMateria);
        void setTipoEvento(char tipoEvento);
        void setEstado(bool estado);

        int getId();
        FechaHorario getFechaHorario() const;
        std::string getDescripcion() const;
        std::string getInformacion() const;
        std::string getIdCursadaMateria() const;
        char getTipoEvento() const;
        bool getEstado() const;

        std::string getCategoriaDeEvento() const;
        std::string toString() const;

    private:
        int _id;
        FechaHorario _fechaHorario;
        char _descripcion[LONGMAXDESCRIPCION];
        char _informacion[LONGMAXINFORMACION];
        char _idCursadaMateria[LONGMAXIDMATERIA];
        char _tipoEvento;
        bool _estado;

};

#endif // EVENTO_H
