//
// Created by Anton on 23/04/2023.
//

#ifndef P2_TARJETA_HPP
#define P2_TARJETA_HPP
#include "../P1/cadena.hpp"

class Numero{
public:
    typedef enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
    Numero(const Cadena& numtarj);

    // Operador de conversión
    operator const char*() const {return num_.c_str();};

    class Incorrecto{
    public:
        Incorrecto(const Razon raz): razon_{raz} {}
        Razon razon() const noexcept { return razon_; };
    private:
        Razon razon_;
    };


private:
    Cadena num_;
};

// Operador para comparar dos objetos Numero.
bool operator < (const Numero& n1, const Numero& n2);





class Tarjeta{
    
};
#endif //P2_TARJETA_HPP
