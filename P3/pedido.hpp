//
// Created by Anton on 15/05/2023.
//

#ifndef P3_PEDIDO_HPP
#define P3_PEDIDO_HPP
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iostream>

// Declaración adelantada.
class Usuario_Pedido;
class Pedido_Articulo;

using namespace std;

class Pedido{
public:
    // Ctor. de Pedido.
    Pedido(Usuario_Pedido& usped, Pedido_Articulo& pedart, Usuario& user, const Tarjeta& tarjeta, const Fecha& fped = Fecha());

    // Excepciones necesarias.
    // Pedido::Vacio
    class Vacio{
    public:
        Vacio(Usuario& us): usuarioquehaceelpedido_{&us} {}
        Usuario& usuario() const noexcept { return *usuarioquehaceelpedido_; };
    private:
        Usuario* usuarioquehaceelpedido_;
    };

    // Pedido::Impostor.
    class Impostor{
    public:
        Impostor(Usuario& us): usuarioimpostor_{&us} {}
        Usuario& usuario() const noexcept { return *usuarioimpostor_; };
    private:
        Usuario* usuarioimpostor_;
    };

    // Pedido::SinStock
    class SinStock{
    public:
        SinStock(Articulo& art): artsinstock_{&art} {}
        Articulo& articulo() const noexcept { return *artsinstock_; };
    private:
        Articulo* artsinstock_;
    };

    // Métodos observadores.
    inline int numero() const noexcept { return numped_; };
    inline const Tarjeta* tarjeta() const noexcept { return tarj_; };
    inline const Fecha& fecha() const noexcept { return fechapedido_; };
    inline double total() const noexcept { return importetotal_; };
    inline static int n_total_pedidos() noexcept { return pedidoshechos_; };


private:
    int numped_;
    const Tarjeta* tarj_;
    Fecha fechapedido_;
    double importetotal_;

    // Número del último pedido hecho o la cantidad total de pedidos hechos.
    static int pedidoshechos_;
};

// Operador de inserción en flujo de salida.
std::ostream& operator <<(std::ostream& os, const Pedido& ped);
#endif //P3_PEDIDO_HPP
