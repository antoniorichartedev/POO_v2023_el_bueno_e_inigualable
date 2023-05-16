//
// Created by Anton on 21/04/2023.
//

#ifndef P2_ARTICULO_HPP
#define P2_ARTICULO_HPP
#include <iostream>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

using namespace std;

class Articulo{
public:
    // Ctor. de Artículo
    explicit Articulo(const Cadena codref, const Cadena tit, const Fecha fpubli, double precio, size_t existencias = 0);

    // Métodos observadores.
    inline const Cadena referencia() const noexcept { return cod_referencia_; };
    inline const Cadena titulo() const noexcept { return titulo_; };
    inline const Fecha f_publi() const noexcept { return f_de_publi_; };
    inline double precio() const noexcept { return precio_; };
    inline double& precio() noexcept { return precio_; };
    inline size_t stock() const noexcept { return num_ejemplares_; };
    inline size_t& stock() noexcept { return num_ejemplares_; };

private:
    const Cadena cod_referencia_;
    const Cadena titulo_;
    const Fecha f_de_publi_;
    double precio_;
    size_t num_ejemplares_;
};

// Operador de inserción en flujo de salida.
ostream& operator <<(ostream& os, const Articulo& art);

#endif //P2_ARTICULO_HPP
