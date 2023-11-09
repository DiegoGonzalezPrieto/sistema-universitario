#ifndef CARGAINICIAL_H
#define CARGAINICIAL_H


class CargaInicial
{
    public:
        CargaInicial();

        void disminuirDatosCargados();
        void aumentarcontadorDatosCargados();
        int getdatoscargados();

    private:
        int  _contador;


};

#endif // CARGAINICIAL_H
