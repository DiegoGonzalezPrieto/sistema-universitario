#include "Evento.h"

Evento::Evento(): _id(0)
{

}

void Evento::setId(int id)
{
    _id = id;
}
int Evento::getId()
{
    return _id;
}

void Evento::setFecha(const Fecha& fecha){

    _fecha = fecha;
}

void Evento::setDescripcion(const std::string& descripcion){

    cargarCadenaConString(descripcion, _descripcion, LONGMAXDESCRIPCION);
}

void Evento::setInformacion(const std::string& informacion){

    cargarCadenaConString(informacion, _informacion, LONGMAXINFORMACION);
}

void Evento::setIdCursadaMateria(const std::string& idCursadaMateria){

    cargarCadenaConString(idCursadaMateria, _idCursadaMateria, LONGMAXIDMATERIA);
}

void Evento::setTipoEvento(char tipoEvento){

   switch(tipoEvento){

        case 'e':
            _tipoEvento = tipoEvento;
            break;
        case 'E':
            _tipoEvento = 'e';
            break;
        case 'o':
            _tipoEvento = tipoEvento;
            break;
        case 'O':
            _tipoEvento = 'o';
            break;
        default:
            _tipoEvento = 'o';
            break;
    }


}


void Evento::setEstado(bool estado){

    _estado = estado;
}

Fecha Evento::getFecha() const{

    return _fecha;
}

std::string Evento::getDescripcion() const{

    return _descripcion;
}

std::string Evento::getInformacion() const{

    return _informacion;
}

std::string Evento::getIdCursadaMateria() const{

    return _idCursadaMateria;
}

char Evento::getTipoEvento() const{

    return _tipoEvento;
}

bool Evento::getEstado() const{

    return _estado;
}

std::string Evento::getCategoriaDeEvento() const{

    std::string categoriaDeEvento;

    switch(_tipoEvento){

        case 'e':
            categoriaDeEvento = "Examen";
            break;
        case 'o':
            categoriaDeEvento = "Otro";
            break;
        default:
            categoriaDeEvento = "Otro";
            break;
    }

    return categoriaDeEvento;
}


std::string Evento::toString() const{

    std::string aux = "";

    aux = "Fecha: ";

    Fecha auxFecha = _fecha;

    aux += auxFecha.toString();

    aux += ", Categoria del evento: " + getCategoriaDeEvento();

    aux += "\nDescripcion: " + getDescripcion();

    aux += "\nInformacion: " + getInformacion();

    return aux;

}
