//
// Created by Anton on 15/05/2023.
//
#include <iomanip>
#include "pedido.hpp"

// Primer pedido.
int Pedido::pedidoshechos_{1};

Pedido::Pedido(Usuario_Pedido &usped, Pedido_Articulo &pedart, Usuario &user, const Tarjeta &tarjeta, const Fecha &fped):
    numped_{pedidoshechos_++},
    tarj_{&tarjeta},
    fechapedido_{fped},
    importetotal_{0}
{
    // Si el carrito está vacío...
    if(user.compra().empty()){
        // Como está vacío, decremento la variable pedidoshechos_, puesto que este pedido no es válido.
        pedidoshechos_--;

        // Lanzamos la excepción.
        throw Vacio(const_cast<Usuario&>(user));
    }

    // Si el que hace el pedido NO es el titular de la tarjeta...
    if(&user != tarjeta.titular()){
        // Como no es el titular de la tarjeta, decremento la variable pedidoshechos_, puesto que este pedido no es válido.
        pedidoshechos_--;

        // Lanzamos excepción.
        throw Impostor{user};
    }

    // Si la tarjeta está caducada...
    if(tarjeta.caducidad() < fped){
        // Como no se puede pagar con esta tarjeta, decremento la variable pedidoshechos_, puesto que este pedido no es válido.
        pedidoshechos_--;

        // Lanzamos la excepción.
        throw Tarjeta::Caducada{tarjeta.caducidad()};
    }

    // Si la tarjeta está desactivada...
    if(!tarjeta.activa()){
        // Como no se puede pagar con esta tarjeta, puesto que está desactivada,
        // decremento la variable pedidoshechos_, ya que este pedido no es válido.
        pedidoshechos_--;

        // Lanzamos la excepción.
        throw Tarjeta::Desactivada{};
    }

    // Si queremos una cantidad de un artículo más grande que la cantidad disponible en stock...
    for(auto it = user.compra().begin(); it != user.compra().end(); it++){

        // en el caso de que sea verdad que queremos más cantidad de ese artículo de la que hay disponible...
        if(it->first->stock() < it->second){

            // Como no hay suficiente stock para satisfacer la demanda, decremento la variable pedidoshechos_, puesto que este pedido no se puede hacer.
            pedidoshechos_--;

            // Luego, vaciamos el carrito.
            auto art = it->first;
            const_cast<Usuario::Articulos&>(user.compra()).clear();
            throw SinStock{*art};
        }
    }

    // Hacemos la asociación Usuario-Pedido que nos piden.
    usped.asocia(*this, user);

    // Ahora, vamos a ir disminuyendo el stock según la cantidad demandada por el cliente.
    for(auto it = user.compra().begin(); it != user.compra().end(); it++){
        it->first->stock() -= it->second;

        // Asociamos el pedido con el artículo.
        pedart.pedir(*(it->first), *this, it->first->precio(), it->second);

        // Al importe total, le sumamos el precio por la cantidad demandada del artículo sobre
        // el que estamos iterando.
        importetotal_ += it->first->precio() * it->second;
    }

    // Luego de hacer el pedido, vaciamos el carrito.
    const_cast<Usuario::Articulos&>(user.compra()).clear();
}

std::ostream& operator <<(std::ostream& os, const Pedido& pedido){
    os << "Núm. pedido: " << pedido.numero() << endl;
    os << left << setw(13) << "Fecha: " << pedido.fecha() << endl;
    os << left << setw(13) << "Pagado con: ";
    if(pedido.tarjeta()->tipo() == Tarjeta::Otro){
        os << "Tipo indeterminado";
    }else{
        os << pedido.tarjeta()->tipo();
    }
    os << " n.º: " << pedido.tarjeta()->numero() << endl;
    os << left << setw(13) << "Importe:" << fixed << setprecision(2) << pedido.total() << " €" << endl;

    return os;
}