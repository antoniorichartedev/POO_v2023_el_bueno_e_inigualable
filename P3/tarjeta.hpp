//
// Created by Anton on 23/04/2023.
//

#ifndef P2_TARJETA_HPP
#define P2_TARJETA_HPP
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include <set>
using namespace std;

// Declaración adelantada.
class Usuario;

// clases de objetos función
struct EsBlanco: public std::unary_function<char,bool>{
    bool operator () (char c) const { return isspace(c); };
};

struct EsDigito: public std::unary_function<char,bool>{
    bool operator () (char c) const { return isdigit(c); };
};


class Numero{
public:
    typedef enum{LONGITUD, DIGITOS, NO_VALIDO}Razon;
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


// *************************************************************************
// ************************    CLASE TARJETA    ****************************
// *************************************************************************



class Tarjeta{
public:
    friend class Usuario;
    typedef enum{
        Otro,
        VISA,
        Mastercard,
        Maestro,
        JCB,
        AmericanExpress
    }Tipo;

    // Ctor.
    Tarjeta(const Numero& num, Usuario& user, const Fecha& fecha_cad);

    // Ctor de copia y op. de asignación, eliminados.
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator =(const Tarjeta&) = delete;

    // Clase de excepción Tarjeta::Caducada.
    class Caducada{
    public:
        Caducada(const Fecha& fecha): caducada_(fecha) {}
        Fecha cuando() const noexcept { return caducada_; };
    private:
        Fecha caducada_;
    };

    // Clase de excepción Tarjeta::num_duplicado.
    class Num_duplicado{
    public:
        Num_duplicado(const Numero& num): n_{num} {}
        const Numero& que() const noexcept { return n_; };
    private:
        Numero n_;
    };

    // Clase de excepción Tarjeta::Desactivada, pero vacía.
    class Desactivada {};

    // Métodos Observadores.
    inline const Numero& numero() const noexcept { return numTarj_; };
    inline const Usuario* titular() const noexcept { return titular_; };
    inline const Fecha& caducidad() const noexcept { return fecha_caducidad_; };
    inline bool activa() const noexcept { return activa_; };
    Tipo tipo() const noexcept;

    // Método modificador activa(bool estado).
    bool activa(bool estado);

    // Destructor
    ~Tarjeta();

private:
    const Numero numTarj_;
    const Usuario* titular_;
    const Fecha fecha_caducidad_;
    bool activa_;

    void anula_titular();
    static std::set<Numero> tarjetasactivas;
};

// Operador de inserción de flujo de salida para un tipo X de una tarjeta.
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tip);

// Operador de inserción de flujo de salida.
std::ostream& operator <<(std::ostream& os, const Tarjeta& tarjeta);

// Operador menor-que para comparar dos tarjetas.
bool operator <(const Tarjeta& tarj1, const Tarjeta& tarj2);
#endif //P2_TARJETA_HPP
