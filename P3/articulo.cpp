//
// Created by Anton on 21/04/2023.
//
#include "articulo.hpp"

using namespace std;

Articulo::Articulo(const Cadena codref, const Cadena tit, const Fecha fpubli, double precio, size_t existencias):
    cod_referencia_(codref),
    titulo_(tit),
    f_de_publi_(fpubli),
    precio_(precio),
    num_ejemplares_(existencias)
{}

ostream& operator << (ostream& os, const Articulo& art){
    os << "[" << art.referencia() << " \"" << art.titulo() << "\", " << art.f_publi().anno() << ". " << art.precio() << " €";

    return os;
}

