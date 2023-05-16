//
// Created by antonio on 28/04/23.
//
#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario &usu, Pedido &ped) {
    usu_ped[&usu].insert(&ped);
    ped_usu[&ped] = &usu;
}

void Usuario_Pedido::asocia(Pedido &ped, Usuario &usu) {
    asocia(usu, ped);
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario &usu) const {
    // Buscamos al usuario que nos pasan por parámetro.
    auto it = usu_ped.find(&usu);

    // Si lo encontramos, pasamos los pedidos que tenga.
    // En caso contrario, devolvemos un map de pedidos vacío.
    if(it != usu_ped.end()){
        return it->second;
    }else{
        return Pedidos {};
    }
}

Usuario *Usuario_Pedido::cliente(Pedido &ped) const {
    // Buscamos el pedido que nos llega por parámetro.
    auto it = ped_usu.find(&ped);

    // Una vez encontrado el pedido, devolvemos el cliente que ha realizado dicho pedido.
    // Si no lo encontramos, devolvemos un puntero nulo.
    if(it != ped_usu.end()){
        return it->second;
    }else{
        return nullptr;
    }
}

