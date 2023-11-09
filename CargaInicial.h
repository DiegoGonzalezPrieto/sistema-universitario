#ifndef CARGAINICIAL_H
#define CARGAINICIAL_H


class CargaInicial
{
    public:
        CargaInicial();

        void setEstado(bool estado);
        bool getEstado() const;

    private:
        bool _estado;
};

#endif // CARGAINICIAL_H
