//
// Created by Anton on 23/04/2023.
//
#include "tarjeta.hpp"
#include <cstring>
#include <functional>

// Añadimos la función luhn.
bool luhn(const Cadena&);

Numero::Numero(const Cadena &numtarj) {

    // creamos una cadena auxiliar con el tamaño de la cadena que recibe
    // el constructor por parámetro.
    Cadena aux{numtarj};

    // Utilizamos remove_if poniéndole el predicado EsBlanco{}, es decir, vamos a mirar desde el principio de la cadena
    // hasta el final de la misma y, a su paso, vamos borrando cada espacio en blanco que encontremos.
    auto eliminarespacios = remove_if(aux.begin(), aux.end(), EsBlanco());

    if(eliminarespacios != aux.end()){
        *eliminarespacios = '\0';
        Cadena aux2 (aux.c_str());
        aux = aux2;
    }

    // Utilizamos find_if para ver si en la Cadena tenemos algún carácter que no sea un dígito.
    // En dicho caso, devolveremos la excepción Incorrecto{DIGITOS}.
    if(std::find_if(aux.begin(), aux.end(), not1(EsDigito{})) != aux.end()){
        throw Incorrecto{DIGITOS};
    }

    // Si la longitud de la tarjeta se pasa del rango, lanzamos la excepción correspondiente.
    if(aux.length() < 13 or aux.length() > 19){
        throw Incorrecto{LONGITUD};
    }

    // Si el algoritmo de luhn nos devuelve false, quiere decir que el número de la tarjeta
    // no es válido, por lo tanto, lanzamos la excepción correspondiente.
    if(!luhn(aux)){
        throw Incorrecto{NO_VALIDO};
    }

    // Si todo está correcto, guardamos el número.
    num_ = aux;
}

bool operator < (const Numero& n1, const Numero& n2){
    return strcmp(n1, n2) < 0;
}

// *************************************************************************
// ************************    CLASE TARJETA    ****************************
// *************************************************************************

std::set<Numero> Tarjeta::tarjetasactivas{};

Tarjeta::Tarjeta(const Numero &num, Usuario &user, const Fecha &fecha_cad):
    numTarj_{num},
    titular_{&user},
    fecha_caducidad_(fecha_cad),
    activa_(true)
{
    if(fecha_caducidad_ < Fecha()){
        throw Tarjeta::Caducada(fecha_caducidad_);
    }

    // Asignamos esta tarjeta a su usuario.
    user.es_titular_de(*this);

    if(!tarjetasactivas.insert(num).second){
        throw Num_duplicado{num};
    }
}

Tarjeta::Tipo Tarjeta::tipo() const noexcept {

    if(numTarj_[0] == '3'){
        if(numTarj_[1] == '4' or numTarj_[1] == '7'){
            return Tarjeta::Tipo{AmericanExpress};
        }else{
            return Tarjeta::Tipo{JCB};
        }
    }else if(numTarj_[0] == '4'){
        return Tarjeta::Tipo{VISA};
    }else if(numTarj_[0] == '5'){
        return Tarjeta::Tipo{Mastercard};
    }else if (numTarj_[0] == '6'){
        return Tarjeta::Tipo{Maestro};
    }else{
        return Tarjeta::Tipo{Otro};
    }

}

void Tarjeta::anula_titular() {
    titular_ = nullptr;
    activa_ = false;
}

bool Tarjeta::activa(bool estado) {
    activa_ = estado;
    return activa_;
}

Tarjeta::~Tarjeta() {
    if(titular_ != nullptr){
        const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
    }

    tarjetasactivas.erase(this->numTarj_);
}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tip){
    static Cadena cadenas[] {"Otro", "VISA", "Mastercard", "Maestro", "JCB", "American Express"};

    return os << cadenas[tip];
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& tarjeta){
    os << tarjeta.tipo() << std::endl;
    os << tarjeta.numero() << std::endl;

    Cadena nombre{tarjeta.titular()->nombre().c_str()}, apellidos{tarjeta.titular()->apellidos().c_str()};  //Guardamos las cadenas en cuestion
    for(auto i = nombre.begin(); i != nombre.end(); i++)
        *i = toupper((unsigned char) *i);
    for(auto i = apellidos.begin(); i != apellidos.end(); i++)
        *i = toupper((unsigned char) *i);

    os << nombre << " " << apellidos << std::endl;

    os << "Caduca: ";
    if(tarjeta.caducidad().mes() < 10)
        os << "0" << tarjeta.caducidad().mes();
    else
        os << tarjeta.caducidad().mes();
    if(tarjeta.caducidad().anno() % 1000 < 10)
        os << "/0" << tarjeta.caducidad().anno() % 1000 << std::endl;
    else
        os << "/" << tarjeta.caducidad().anno() % 1000 << std::endl;

    return os;
}

bool operator <(const Tarjeta& tarj1, const Tarjeta& tarj2){
    return tarj1.numero() < tarj2.numero();
}