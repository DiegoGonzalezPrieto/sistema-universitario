#ifndef CARGAINICIAL_H
#define CARGAINICIAL_H


class CargaInicial
{
    public:
        CargaInicial();

        void disminuirDatosCargados();
        void aumentarcontadorDatosCargados();
        int getdatoscargados();

        bool getCarreraCargada();
        bool getMateriasCargadas();

        void setCarreraCargada(bool);
        void setMateriasCargadas(bool);

    private:
        int  _contador;
        bool carreraCargada;
        bool materiasCargadas;


};

#endif // CARGAINICIAL_H
