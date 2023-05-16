//
// Created by Anton on 23/04/2023.
//
#include "usuario.hpp"
#include <unistd.h>
#include <random>
#include <cstring>
#include <iomanip>

using namespace std;

Clave::Clave(const char *claro)
{
    // Caso 1: La contraseña tiene menos de 5 caracteres.
    if(strlen(claro) < 5){
        throw Incorrecta{CORTA};
    }

    // Caso 2: La contraseña no ha podido cifrarse correctamente.
    static const char* caracteres = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    random_device r;

    uniform_int_distribution<int> distribucion(0, strlen(caracteres));
    char sal[2] = {caracteres[distribucion(r)], caracteres[distribucion(r)]};

    if(crypt(claro, sal) == nullptr){
        throw Incorrecta{ERROR_CRYPT};
    }else{
        password_ = crypt(claro, sal);
    }
}

bool Clave::verifica(const char *passcad) const {
    return strcmp(password_.c_str(), crypt(passcad, password_.c_str())) == 0;
}

// *************************************************************************
// ************************    CLASE USUARIO    ****************************
// *************************************************************************

std::unordered_set<Cadena> Usuario::registrados;

Usuario::Usuario(const Cadena &id, const Cadena &nom, const Cadena &ape, const Cadena &dir, const Clave &pass):
    identificador_{id},
    nombre_{nom},
    apellidos_{ape},
    direccion_{dir},
    password_{pass}
{
    // En el caso de que esté registrado dicho usuario, lanzamos excepción.
    if(!registrados.insert(id).second){
        throw Id_duplicado{id};
    }
}

void Usuario::es_titular_de(const Tarjeta &tarjeta) {
    if(tarjeta.titular() == this){
        tarjetas_[tarjeta.numero()] = const_cast<Tarjeta*>(&tarjeta);
    }
}

void Usuario::no_es_titular_de(Tarjeta &tarjeta) {
    tarjetas_.erase(tarjeta.numero());
    tarjeta.anula_titular();
}

Usuario::~Usuario() {
    for(auto it = tarjetas_.begin(); it != tarjetas_.end(); it++){
        if((*it).second->titular_->nombre_ == this->nombre_){
            (*it).second->anula_titular();
        }
    }

    // Hay que borrar el usuario registrado.
    registrados.erase(this->identificador_);
}

void Usuario::compra(Articulo &articulo, unsigned int cant) {
    if(cant == 0){
        articulos_.erase(&articulo);
    }else{
        articulos_[&articulo] = cant;
    }
}

void Usuario::vaciar_carro() {
    articulos_.clear();
}

std::ostream& operator << (std::ostream& os, const Usuario& us){
    os << us.identificador_ << " [" << us.password_.clave() << "] " << us.nombre_ << " " << us.apellidos_ << endl;
    os << us.direccion_ << endl;
    os << "Tarjetas:" << endl;
    for(auto it = us.tarjetas_.begin(); it != us.tarjetas_.end(); it++){
        os << *it->second << endl;
    }

    return os;
}

void mostrar_carro(std::ostream& os, const Usuario& us){
    Usuario::Articulos carro = us.compra();

    os << "Carrito de compra de " << us.id() << " [Artículos: " << us.n_articulos() << "]" << std::endl;
    os << " Cant. Artículo" << std::endl;
    os << "===========================================================" << std::endl;

    for(auto i = carro.begin(); i != carro.end(); i++){
        os << "    " << i->second << "    " << " [" << (*i->first).referencia() << "] " << "\"" << (*i->first).titulo()
        << "\", " << (*i->first).f_publi().anno() << ". " << std::fixed << std::setprecision(2) << (*i->first).precio()
        << " €" << std::endl;
    }
}