//
// Created by Anton on 19/03/2023.
//
#include "cadena.hpp"
#include <cstring>
using namespace std;


Cadena::Cadena(unsigned t, char s):
    s_{new char[t + 1]},
    tam_{t}
{
    for(unsigned i = 0; i < tam_; i++){
        s_[i] = s;
    }
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena &c):
    s_{new char[c.tam_ + 1]},
    tam_{c.tam_}
{
    for(unsigned i = 0; i < tam_; i++){
        s_[i] = c.s_[i];
    }
    s_[tam_] = '\0';
}

Cadena::Cadena(const char *cad):
    s_{new char [(unsigned) strlen(cad) + 1]},
    tam_{(unsigned) strlen(cad)}
{
    for(unsigned i = 0; i < tam_; i++){
        s_[i] = cad[i];
    }
    s_[tam_] = '\0';
}

Cadena &Cadena::operator=(const Cadena &c2) {

    // evitamos autoasignación.
    if(this != &c2){
        if(tam_ != c2.tam_){
            delete[] s_;
            tam_ = c2.tam_;
            s_ = new char[tam_ + 1];
        }

        for (unsigned i = 0; i < tam_; i++){
            s_[i] = c2.s_[i];
        }
        s_[tam_] = '\0';
    }

    return *this;
}

Cadena &Cadena::operator=(const char *cad) {

    // Creamos una cadena con la cadena de bajo nivel.

    if(tam_ != strlen(cad)){
        delete[] s_;
        tam_ = strlen(cad);
        s_ = new char[tam_ + 1];
    }

    for (unsigned i = 0; i < tam_; i++){
        s_[i] = cad[i];
    }
    s_[tam_] = '\0';
    return *this;
}

Cadena &Cadena::operator+=(const Cadena &c2) {
    char* cadaux = new char[tam_ + c2.tam_ + 1];

    // copiamos la primera cadena en la cadena que hemos creado antes.
    for(unsigned i = 0; i < tam_; i++){
        cadaux[i] = s_[i];
    }

    // ahora, copiamos la otra cadena justo después del último caracter introducido en la cadena ppal.
    for(unsigned i = tam_; i < tam_ + c2.tam_; i++){
        cadaux[i] = c2.s_[i - tam_];    // i - tam_ porque i = tam_.
                                        // por ej. tam_ = 5 i = tam_, pues si empezamos a copiar, 5 - 5 = 0, 5 - 4 = 1
                                        // y así sucesivamente hasta llegar al final de la segunda cadena.
    }

    // una vez que hayamos copiado la cadena, introducimos el carácter terminador.
    cadaux[tam_ + c2.tam_] = '\0';

    // ahora tenemos la cadena lista, pero no nos han dicho que tengamos que crear una cadena nueva, por lo tanto
    // tenemos que copiar cadaux en this.
    // borramos el antiguo contenido
    delete[] s_;

    // definimos el nuevo tamaño.
    tam_ = tam_ + c2.tam_;

    // reservamos memoria para albergar la nueva cadena.
    s_ = new char[tam_ + 1];

    // copiamos la cadena nueva a this.
    for (unsigned i = 0; i < tam_ + 1; i++){
        s_[i] = cadaux[i];
    }
    delete[] cadaux;
    // devolvemos this.
    return *this;
}

Cadena Cadena::operator+(const Cadena &c2) const {
    char* cadaux = new char[tam_ + c2.tam_ + 1];

    // copiamos la primera cadena en la cadena que hemos creado antes.
    for(unsigned i = 0; i < tam_; i++){
        cadaux[i] = s_[i];
    }

    // ahora, copiamos la otra cadena justo después del último caracter introducido en la cadena ppal.
    for(unsigned i = tam_; i < tam_ + c2.tam_; i++){
        cadaux[i] = c2.s_[i - tam_];    // i - tam_ porque i = tam_.
        // por ej. tam_ = 5 i = tam_, pues si empezamos a copiar, 5 - 5 = 0, 5 - 4 = 1
        // y así sucesivamente hasta llegar al final de la segunda cadena.
    }

    // una vez que hayamos copiado la cadena, introducimos el carácter terminador.
    cadaux[tam_ + c2.tam_] = '\0';

    // ahora tenemos la cadena lista, devolvemos esa cadena, pero hemos creado un char*, simplemente
    // creamos un objeto Cadena pasándole como parámetro cadaux.
    Cadena cad(cadaux);
    delete[] cadaux;
    // devolvemos la cadena.
    return cad;
}

// ahora, vamos a hacer cada uno de los operadores de comparación de la clase cadena.
bool operator ==(const Cadena& c1, const Cadena& c2){
    return (std::strcmp((const char *)(c1.c_str()), (const char *)(c2.c_str())) == 0);
}

bool operator !=(const Cadena& c1, const Cadena& c2){
    return !(c1 == c2);
}

bool operator >=(const Cadena& c1, const Cadena& c2){
    return (std::strcmp((const char *)(c1.c_str()), (const char *)(c2.c_str())) >= 0);
}

bool operator <=(const Cadena& c1, const Cadena& c2){
    return (std::strcmp((const char *)(c1.c_str()), (const char *)(c2.c_str())) <= 0);
}

bool operator >(const Cadena& c1, const Cadena& c2){
    return (std::strcmp((const char *)(c1.c_str()), (const char *)(c2.c_str())) > 0);
}

bool operator <(const Cadena& c1, const Cadena& c2){
    return (std::strcmp((const char *)(c1.c_str()), (const char *)(c2.c_str())) < 0);
}

char &Cadena::at(unsigned i) {
    if((int)i < 0 or i >= tam_){
        throw std::out_of_range("Límites de rango excedidos.");
    }

    return s_[i];
}

char Cadena::at(unsigned i) const {
    if((int)i < 0 or i >= tam_){
        throw std::out_of_range("Límites de rango excedidos.");
    }

    return s_[i];
}

Cadena Cadena::substr(unsigned i, unsigned tam) const {
    if((int)i < 0 or (int)tam < 0 or i + tam >= tam_){
        throw std::out_of_range("Límites de rangos excedidos.");
    }

    Cadena cad{tam};

    size_t cont = 0;

    while(cont < tam){
        cad.s_[cont] = s_[cont + i];
        cont++;
    }

    return cad;

}

ostream& operator <<(ostream& os, const Cadena& c1){
    os << c1.c_str();

    return os;
}

istream& operator >>(istream& is, Cadena& c1){
    // creamos una cadena aux para poder albergar la cadena.
    char cad[33] {};

    // ahora, le decimos a is que tiene que leer 33 caracteres.
    is.width(33);
    is >> cad;

    // sobreescribimos la Cadena c1 con la cadena que hemos creado anteriormente.
    c1 = cad;

    // devolvemos el flujo de entrada.
    return is;
}

Cadena::Cadena(Cadena &&c):
    s_{c.s_},
    tam_{c.tam_}
{
    // una vez que hayamos movido la cadena, quedará vacía. Por lo tanto, como nos dicen que la tenemos que dejar en un
    // estado válido, la dejamos vacía.
    c.s_ = new char[1];
    c.s_[0] = '\0';
    c.tam_ = 0;

}

Cadena &Cadena::operator=(Cadena &&c) {
    if(this != &c){
        delete[] s_;
        s_ = c.s_;
        tam_ = c.tam_;

        // una vez que hayamos movido la cadena, quedará vacía. Por lo tanto, como nos dicen que la tenemos que dejar en un
        // estado válido, la dejamos vacía.
        c.s_ = new char[1];
        c.s_[0] = '\0';
        c.tam_ = 0;

    }
    return *this;
}