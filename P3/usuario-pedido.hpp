//
// Created by antonio on 28/04/23.
//

#ifndef P3_USUARIO_PEDIDO_HPP
#define P3_USUARIO_PEDIDO_HPP
#include "usuario.hpp"
#include "pedido.hpp"
#include <iostream>
#include <map>
#include <set>

class Usuario;
class Pedido;

class Usuario_Pedido{
public:
    // Asociaciones.
    typedef std::set<Pedido*> Pedidos;
    void asocia(Usuario& usu, Pedido& ped);
    void asocia(Pedido& ped, Usuario& usu);

    // Métodos observadores.
    Pedidos pedidos(Usuario& usu) const;
    Usuario* cliente(Pedido& ped) const;

private:
    std::map<Usuario*, Pedidos> usu_ped;
    std::map<Pedido*, Usuario*> ped_usu;
};
#endif //P3_USUARIO_PEDIDO_HPP
