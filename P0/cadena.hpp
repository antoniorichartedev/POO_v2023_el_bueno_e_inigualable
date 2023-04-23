//
// Created by Anton on 19/03/2023.
//

#ifndef P0_CADENA_HPP
#define P0_CADENA_HPP
#include <cstdlib>
#include <stdexcept>
class Cadena{
public:

    // Constructores.
    explicit Cadena(size_t t = 0, char s = ' ');

    // Constructor de copia.
    Cadena(const Cadena& c);

    // Constructor de conversión.
    Cadena(const char* cad);

    // conversores.
    explicit operator const char*() const {return s_;}

    // Operador de asignación.
    Cadena& operator =(const Cadena& c2);
    Cadena& operator =(const char* cad);

    // Funciones observadoras.
    inline size_t length() const noexcept { return tam_; }

    // Operador de suma con asignación para la concatenación de dos cadenas.
    Cadena& operator +=(const Cadena& c2);

    // Operador suma para la concatenación de dos cadenas.
    Cadena operator +(const Cadena& c2) const;

    // Operador de índice.
    char& operator [](size_t i) { return s_[i]; };
    char operator [] (size_t i) const { return s_[i]; };

    // Función at, hace lo mismo que el op. de índice, pero comprueba que el índice esté dentro del rango de la cadena.
    char at(size_t i) const;
    char& at(size_t i);

    // Función substr.
    Cadena substr(size_t i, size_t tam) const;

    // Destructor.
    ~Cadena() { delete[] s_; };
private:
    char* s_;
    size_t tam_;
};

// Operadores lógicos para comparar cadenas
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator <(const Cadena& c1, const Cadena& c2);
#endif //P0_CADENA_HPP
