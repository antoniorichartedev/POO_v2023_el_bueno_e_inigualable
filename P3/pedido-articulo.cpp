//
// Created by antonio on 28/04/23.
//
#include "pedido-articulo.hpp"
#include <iomanip>

ostream& operator << (ostream& os, const LineaPedido& lp){
    os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €";
    os << "\t" << lp.cantidad() << endl;

    return os;
}

LineaPedido::LineaPedido(double precioventa, unsigned int cant):
    p_venta_{precioventa}, cantidad_{cant}
{}

// -------------------------------------------------
// -------------------------------------------------
// -------------------------------------------------

void Pedido_Articulo::pedir(Pedido &ped, Articulo &art, double precio, unsigned int cant) {
    ped_art[&ped].insert(std::make_pair(&art, LineaPedido(precio, cant)));
    art_ped[&art].insert(std::make_pair(&ped, LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(Articulo &art, Pedido &ped, double precio, unsigned int cant) {
    pedir(ped, art, precio, cant);
}

Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& ped) const {
    auto it = ped_art.find(&ped);

    if(it != ped_art.end()){
        return it->second;
    }else{
        return ItemsPedido{};
    }
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo &art) const {
    auto it = art_ped.find(&art);

    if(it != art_ped.end()){
        return it->second;
    }else{
        return Pedidos{};
    }
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& itsped){
    os << "  PVP\t" << "Cantidad\t" << "Artículo" << endl;
    os << "==================================================================" << endl;

    // Creamos esta variable para poder mostrar el importe total del pedido.
    double importetotal = 0;

    for(auto i = itsped.begin(); i != itsped.end(); i++){
        os << fixed << setprecision(2) << i->second.precio_venta() << " € " << left << setw(16) <<
        i->second.cantidad() << "[" << i->first->referencia() << "] " << "\"" << i->first->titulo() << "\"" << endl;

        importetotal += i->second.precio_venta() * i->second.cantidad();
    }
    os << "==================================================================" << endl;
    os << left << setw(8) << "Total" << fixed << setprecision(2) << importetotal << " €" << endl;

    return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& ps){
    os << "[Pedidos: ]" << ps.size() << "]" << endl;
    os << "==================================================================" << endl;
    os << "  PVP\t" << "Cantidad\t" << "Fecha de venta" << endl;
    os << "==================================================================" << endl;

    // Creamos esta variable para poder mostrar el importe total del pedido.
    double importetotal = 0;

    for(auto i = ps.begin(); i != ps.end(); i++){
        os << fixed << setprecision(2) << i->second.precio_venta() << " € " << left << setw(16) <<
           i->second.cantidad() << i->first->fecha() << endl;

        importetotal += i->second.precio_venta() * i->second.cantidad() ;
    }

    os << "==================================================================" << endl;
    os << fixed << setprecision(2) << importetotal << " €\t" << ps.size() << endl;

    return os;
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream &os) const {
    double importetotal = 0;
    for(auto it = ped_art.begin(); it != ped_art.end(); it++){
        os << "Pedido núm. " << it->first->numero() << endl;
        os << "Cliente: " << it->first->tarjeta()->titular() << "\t" << "Fecha: " << it->first->fecha() << endl;
        os << detalle(*(it->first)) << endl;

        importetotal += it->first->total();
    }
    os << "TOTAL VENTAS\t\t" << fixed << setprecision(2) << importetotal << " € " << endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream &os) const {
    for(auto it = art_ped.begin(); it != art_ped.end(); it++){
        os << "Ventas de [" << it->first->referencia() << "] \"" << it->first->titulo() << "\"" << endl;
        os << ventas(*(it->first)) << endl;
    }
}

bool OrdenaPedidos::operator()(const Pedido *p1, const Pedido *p2) const {
    return p1->numero() < p2->numero();
}