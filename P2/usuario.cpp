//
// Created by Anton on 23/04/2023.
//
#include "usuario.hpp"
#include <unistd.h>
#include <random>
#include <cstring>

using namespace std;

Clave::Clave(const char *claro)
{
    // Caso 1: La contraseña tiene menos de 5 caracteres.
    if(password_.length() < 5){
        throw Incorrecta(CORTA);
    }

    // Caso 2: La contraseña no ha podido cifrarse correctamente.
    static const char* caracteres = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    random_device r;
    auto tamcaracteres = strlen(caracteres);
    uniform_int_distribution<int> distribucion(0, tamcaracteres);
    char sal[2] = {caracteres[distribucion(r)], caracteres[distribucion(r)]};

    if(crypt(claro, sal)){
        throw Incorrecta(ERROR_CRYPT);
    }else{
        password_ = crypt(claro, sal);
    }
}

bool Clave::verifica(const char *passcad) {
    return strcmp(password_.c_str(), crypt(passcad, password_.c_str())) == 0;
}