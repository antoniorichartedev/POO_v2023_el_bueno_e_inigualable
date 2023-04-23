//
// Created by Anton on 23/04/2023.
//
#include "tarjeta.hpp"
#include <cstring>

// Añadimos la función luhn.
bool luhn(const Cadena&);

Numero::Numero(const Cadena &numtarj) {
    unsigned int tamaux = 0;

    // creamos una cadena auxiliar con el tamaño de la cadena que recibe
    // el constructor por parámetro.
    Cadena aux(numtarj.length());

    for(unsigned int i = 0; i < numtarj.length(); i++){
        // Si no es un espacio, seguimos.
        if(!isspace((unsigned char)numtarj[i])){

            // Si el caracter sobre el que estamos no es ni un dígito
            // ni un espacio, se lanza la excepción Incorrecto.
            if(!isdigit((unsigned char) numtarj[i])){
                throw Incorrecto{DIGITOS};
            }

            // Le asignamos el caracter actual a aux.
            aux[tamaux++] = numtarj[i];
        }
    }

    if(tamaux != numtarj.length()){
        // Utilizamos la función substr de Cadena para obtener el tamaño justo y necesario.
        aux = aux.substr(0, tamaux);
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