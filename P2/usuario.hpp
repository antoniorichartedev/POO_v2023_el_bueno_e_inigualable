//
// Created by Anton on 23/04/2023.
//

#ifndef P2_USUARIO_HPP
#define P2_USUARIO_HPP
#include <iostream>
#include "../P1/cadena.hpp"

class Clave{
public:

    // Ctor. de clave
    explicit Clave(const char* claro);

    // Enumeración para la clase Incorrecta.
    enum Razon{CORTA, ERROR_CRYPT};

    // Clase de excepción Clave::Incorrecta.
    class Incorrecta{
    public:
        Incorrecta(const Razon raz): razon_(raz) {}
        Razon razon() const noexcept { return razon_; };
    private:
        Razon razon_;
    };

    // Métodos observadores.
    inline Cadena clave() const noexcept { return password_; };

    // Método verifica que nos dice si una contraseña, en claro, coincide con la almacenada.
    bool verifica(const char* passcad);
private:
    Cadena password_;
};

class Usuario{

};
#endif //P2_USUARIO_HPP
