//
// Created by Anton on 19/03/2023.
//

#ifndef P0_CADENA_HPP
#define P0_CADENA_HPP
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <iterator>
using namespace std;

class Cadena{
public:

    // Constructores.
    explicit Cadena(unsigned t = 0, char s = ' ');

    // Constructor de copia.
    Cadena(const Cadena& c);

    // Constructor de conversión.
    Cadena(const char* cad);

    // Ctor. de movimiento.
    Cadena(Cadena&& c);

    // conversores.
    explicit operator const char*() const {return s_;}
    inline const char* c_str() const {return s_;}

    // Operador de asignación.
    Cadena& operator =(const Cadena& c2);
    Cadena& operator =(const char* cad);
    Cadena& operator =(Cadena&& c);

    // Funciones observadoras.
    inline unsigned length() const noexcept { return tam_; }

    // Operador de suma con asignación para la concatenación de dos cadenas.
    Cadena& operator +=(const Cadena& c2);

    // Operador suma para la concatenación de dos cadenas.
    Cadena operator +(const Cadena& c2) const;

    // Operador de índice.
    char& operator [](unsigned i) { return s_[i]; };
    char operator [] (unsigned i) const { return s_[i]; };

    // Función at, hace lo mismo que el op. de índice, pero comprueba que el índice esté dentro del rango de la cadena.
    char at(unsigned i) const;
    char& at(unsigned i);

    // Función substr.
    Cadena substr(unsigned i, unsigned tam) const;

    // Iteradores.
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // Funciones de los iteradores.
    iterator begin() noexcept{return s_;}
    const_iterator begin() const noexcept{ return const_iterator(s_);}
    iterator end() noexcept{return s_ + tam_;}
    const_iterator end() const noexcept{return const_iterator(s_ + tam_);}
    const_iterator cbegin() const noexcept{return const_iterator(s_);}
    const_iterator cend() const noexcept{return const_iterator(s_ + tam_);}
    reverse_iterator rbegin() noexcept{return reverse_iterator(end());}
    const_reverse_iterator rbegin() const noexcept{return const_reverse_iterator(end());}
    reverse_iterator rend() noexcept{return reverse_iterator(begin());}
    const_reverse_iterator rend() const noexcept{return const_reverse_iterator(begin());}
    const_reverse_iterator crbegin() const noexcept{return const_reverse_iterator(end());}
    const_reverse_iterator crend() const noexcept{return const_reverse_iterator(begin());}


    // Destructor.
    ~Cadena() { delete[] s_; };
private:
    char* s_;
    unsigned tam_;
};

// Operadores lógicos para comparar cadenas
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator <(const Cadena& c1, const Cadena& c2);

// Operadores de insercción y de extracción.
ostream& operator <<(ostream& os, const Cadena& c1);
istream& operator >>(istream& is, Cadena& c1);

// Para P2 y ss.
// Especialización de la plantilla std::hash<Key> para definir la función hash a usar
// en contenedores desordenados de Cadena, unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std.
    template <> // Es una especialización de una plantilla para Cadena.
    struct hash<Cadena> { // Es una clase con solo un operador público.
        size_t operator() (const Cadena& cad) const // El operador función.
        {
            hash<string> hs; // Creamos un objeto hash de string.
            auto p{(const char*)(cad)}; // Convertimos Cadena a cadena de bajo nivel.
            string s{p}; // Creamos un string desde la cadena de b. nivel.
            size_t res{hs(s)}; // El hash del string . Como hs.operator()(s);
            return res; // Devolvemos el hash del string.
// En forma abreviada:
// return hash<string>{}((const char*)(cad));
        }
    };
}
#endif //P0_CADENA_HPP
