#include "Evento.h"

Evento::Evento()
{
    //ctor
}

void Evento::setFecha(const Fecha& fecha){

    _fecha = fecha;
}

void Evento::setDescripcion(const std::string& descripcion){

    strcpy(_descripcion, descripcion.c_str());
}

void Evento::setInformacion(const std::string& informacion){

    strcpy(_informacion, informacion.c_str());
}

void Evento::setIdCursadaMateria(const std::string& idCursadaMateria){

    strcpy(_idCursadaMateria, idCursadaMateria.c_str());
}

void Evento::setTipoEvento(char tipoEvento){

    if(tipoEvento == 'e' || tipoEvento == 'E' || tipoEvento == 'o' || tipoEvento == 'O'){

        if(tipoEvento == 'E'){

            _tipoEvento = 'e';
        }
        else if (tipoEvento == 'O'){

            _tipoEvento = 'o';
        }
        else{

            _tipoEvento = tipoEvento;
        }


    }
    else{

        _tipoEvento = 'o';
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

    if(_tipoEvento == 'e'){

        categoriaDeEvento = "Examen";
    }
    else if (_tipoEvento == 'o'){

        categoriaDeEvento = "Otro";
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
