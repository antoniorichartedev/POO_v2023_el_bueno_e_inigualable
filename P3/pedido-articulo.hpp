//
// Created by antonio on 28/04/23.
//

#ifndef P3_PEDIDO_ARTICULO_HPP
#define P3_PEDIDO_ARTICULO_HPP
#include <iostream>
#include "articulo.hpp"
#include "pedido.hpp"
#include <map>

// Declaración adelantada.
class Pedido;
class Articulo;

// usamos espacio de nombres std.
using namespace std;

class LineaPedido{
public:
    // Ctor.
    explicit LineaPedido(double precioventa, unsigned int cant = 1);

    // Métodos observadores.
    inline double precio_venta() const noexcept { return p_venta_; };
    inline unsigned int cantidad() const noexcept { return cantidad_; };

private:
    double p_venta_;
    unsigned int cantidad_;
};

// Operador de inserción en flujo de salida.
ostream& operator << (ostream& os, const LineaPedido& lp);


// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

// Clase de objetos función OrdenaPedidos.
struct OrdenaPedidos{
    bool operator() (const Pedido* p1, const Pedido* p2) const;
};

// Clase de objetos función OrdenaArticulos.
struct OrdenaArticulos{
    bool operator() (const Articulo* a1, const Articulo* a2) const {
        return a1->referencia() < a2->referencia();
    }
};

class Pedido_Articulo{
public:
    // Asociaciones.
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    void pedir(Pedido& ped, Articulo& art, double precio, unsigned int cant = 1);
    void pedir(Articulo& art, Pedido& ped, double precio, unsigned int cant = 1);

    // Métodos observadores.
    ItemsPedido detalle(Pedido& ped) const;
    Pedidos ventas(Articulo& art) const;

    // Funciones para mostrar el detalle de un pedido y las ventas de los artículos.
    void mostrarDetallePedidos(std::ostream& os) const;
    void mostrarVentasArticulos(std::ostream& os) const;

private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> ped_art;
    std::map<Articulo*, Pedidos, OrdenaArticulos> art_ped;
};

// Operadores de inserción en flujo de salida.
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& itsped);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& peds);


#endif //P3_PEDIDO_ARTICULO_HPP
