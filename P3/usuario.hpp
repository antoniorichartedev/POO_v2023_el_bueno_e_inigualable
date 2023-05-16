//
// Created by Anton on 23/04/2023.
//

#ifndef P2_USUARIO_HPP
#define P2_USUARIO_HPP
#include <iostream>
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "articulo.hpp"

class Numero;
class Tarjeta;

class Clave{
public:

    // Ctor. de clave
    Clave(const char* claro);

    // Enumeración para la clase Incorrecta.
    typedef enum{CORTA, ERROR_CRYPT} Razon;

    // Clase de excepción Clave::Incorrecta.
    class Incorrecta{
    public:
        Incorrecta(Razon raz): razon_(raz) {}
        Razon razon() const noexcept { return razon_; };
    private:
        Razon razon_;
    };

    // Métodos observadores.
    inline Cadena clave() const noexcept { return password_; };

    // Método verifica que nos dice si una contraseña, en claro, coincide con la almacenada.
    bool verifica(const char* passcad) const;
private:
    Cadena password_;
};



class Usuario{
public:
    // Asociaciones.
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    void es_titular_de(const Tarjeta& tarjeta);
    void no_es_titular_de(Tarjeta& tarjeta);
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    // Ctor.
    Usuario(const Cadena& id, const Cadena& nom, const Cadena& ape, const Cadena& dir, const Clave& pass);

    // Ctor. de copia y operador de asig.
    Usuario(const Usuario& u) = delete;
    Usuario& operator =(const Usuario& u) = delete;

    // Excepciones.
    class Id_duplicado{
    public:
        Id_duplicado(const Cadena& ident): id_{ident} {}
        const Cadena& idd() const noexcept { return id_; };
    private:
        Cadena id_;
    };

    // Métodos observadores.
    inline const Cadena& id() const noexcept { return identificador_; };
    inline const Cadena& nombre() const noexcept { return nombre_; };
    inline const Cadena& apellidos() const noexcept { return apellidos_; };
    inline const Cadena& direccion() const noexcept { return direccion_; };
    inline const Tarjetas& tarjetas() const noexcept { return tarjetas_; };
    inline const Articulos& compra() const noexcept { return articulos_; };
    unsigned int n_articulos() const noexcept { return articulos_.size(); };

    // Asociación con Articulo.
    void compra(Articulo& articulo, unsigned int cant = 1);

    // Destructor.
    ~Usuario();

    // Operador de inserción en flujo de salida.
    friend std::ostream& operator << (std::ostream& os, const Usuario& us);

    // Vacíar carrito.
    void vaciar_carro();
private:
    const Cadena identificador_;
    const Cadena nombre_;
    const Cadena apellidos_;
    const Cadena direccion_;
    Clave password_;
    Tarjetas tarjetas_;
    Articulos articulos_;

    // Usuarios registrados en el sistema.
    static std::unordered_set<Cadena> registrados;


};

// El carrito de la compra.
void mostrar_carro(std::ostream& os, const Usuario& us);
#endif //P2_USUARIO_HPP
