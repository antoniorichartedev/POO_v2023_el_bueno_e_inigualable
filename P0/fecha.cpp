//
// Created by Anton on 10/03/2023.
//
#include "fecha.hpp"
#include <cstdio>
#include <cstring>

// constructor.
Fecha::Fecha(int d, int m, int a):
    dia_{d},
    mes_{m},
    anno_{a}
{
    ArreglarFecha(d,m,a);
    ComprobarFecha();
}

// Función Privada ArreglarFecha(int d, int m, int a)
void Fecha::ArreglarFecha(int d, int m, int a) {

    // Creamos un objeto r de la clase Reloj.
    reloj r;

    if (d == 0){
        dia_ = r.diaact();
    }

    if (m == 0){
        mes_ = r.mesact();
    }

    if (a == 0){
        anno_ = r.annoact();
    }
}

// Función Privada Bisiesto(int a): Nos dice si un año es bisiesto o no.
bool bisiesto(int a){
    return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

// Función Privada ComprobarFecha()
void Fecha::ComprobarFecha() {
    if(dia_ < 1 or dia_ > DiasqueTieneunMes[mes_ - 1]){
        throw Invalida("Día no válido.");
    }

    if(mes_ < 0 or mes_ > 12){
        throw Invalida("Mes no válido.");
    }

    if(anno_ > AnnoMaximo or anno_ < AnnoMinimo){
        throw Invalida("Año no válido.");
    }

    if(mes_ == 2 and dia_ == 29 and !bisiesto(anno_)){
        throw Invalida("Año no bisiesto");
    }
}

Fecha &Fecha::operator++() {
    *this += 1;
    ComprobarFecha();
    return *this;
}

Fecha Fecha::operator++(int) {
    Fecha f = *this;
    *this += 1;
    ComprobarFecha();
    return f;
}

Fecha &Fecha::operator--() {
    *this += -1;
    ComprobarFecha();
    return *this;
}

Fecha Fecha::operator--(int) {
    Fecha f = *this;
    *this += -1;
    ComprobarFecha();
    return f;
}

Fecha &Fecha::operator+=(int n) {
    if (n != 0){
        tm faux = {};
        faux.tm_mday = dia_ + n;
        faux.tm_mon = mes_ - 1;
        faux.tm_year = anno_ - 1900;
        mktime(&faux);
        dia_ = faux.tm_mday;
        mes_ = faux.tm_mon + 1;
        anno_ = faux.tm_year + 1900;
    }
    ComprobarFecha();
    return *this;
}

Fecha &Fecha::operator-=(int n) {
    *this += -n;
    ComprobarFecha();
    return *this;
}

Fecha Fecha::operator+(int n) const {
    Fecha f = *this;
    f += n;
    f.ComprobarFecha();
    return f;
}

Fecha Fecha::operator-(int n) const {
    Fecha f = *this;
    f += -n;
    f.ComprobarFecha();
    return f;
}

bool operator == (const Fecha& f1, const Fecha& f2){
    return (f1.anno() == f2.anno() and f1.mes() == f2.mes() and f1.dia() == f2.dia());
}

bool operator != (const Fecha& f1, const Fecha& f2){
    return !(f1 == f2);
}

bool operator > (const Fecha& f1, const Fecha& f2){
    return (f2 < f1);
}

bool operator <= (const Fecha& f1, const Fecha& f2){
    return !(f2 < f1);
}

bool operator >= (const Fecha& f1, const Fecha& f2){
    return !(f1 < f2);
}

bool operator < (const Fecha& f1, const Fecha& f2){


    if (f1.anno() < f2.anno()){
        return true;
    }else if (f1.anno() == f2.anno()){
        if(f1.mes() < f2.mes()){
            return true;
        }else if (f1.mes() == f2.mes() and f1.dia() < f2.dia()){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }

}

// Fecha a partir de una cadena de bajo nivel. (Usamos sscanf)
Fecha::Fecha(const char *f) {
    if (sscanf(f, "%d/%d/%d", &dia_, &mes_, &anno_) != 3){
        throw Invalida("Formato incorrecto");
    }

    ArreglarFecha(dia_, mes_, anno_);
    ComprobarFecha();
}

const char *Fecha::obtenercadenita() const {
    char *res = new char[50], *aux = new char[50];
    std::tm* fec = new tm;

    memset(fec, 0, sizeof(*fec));
    fec->tm_mday = dia_;
    fec->tm_mon = mes_ - 1;
    fec->tm_year = anno_ - 1900;

    mktime(fec);

    switch(fec->tm_wday){
        case 0: strcpy(res, "domingo "); break;
        case 1: strcpy(res, "lunes "); break;
        case 2: strcpy(res, "martes "); break;
        case 3: strcpy(res, "miércoles "); break;
        case 4: strcpy(res, "jueves "); break;
        case 5: strcpy(res, "viernes "); break;
        case 6: strcpy(res, "sábado "); break;
    }

    sprintf(aux, "%d", dia_);
    strcat(res, aux);
    strcat(res, " de ");

    switch(mes_){
        case 1: strcat(res, "enero de "); break;
        case 2: strcat(res, "febrero de "); break;
        case 3: strcat(res, "marzo de "); break;
        case 4: strcat(res, "abril de "); break;
        case 5: strcat(res, "mayo de "); break;
        case 6: strcat(res, "junio de "); break;
        case 7: strcat(res, "julio de "); break;
        case 8: strcat(res, "agosto de "); break;
        case 9: strcat(res, "septiembre de "); break;
        case 10: strcat(res, "octubre de "); break;
        case 11: strcat(res, "noviembre de "); break;
        case 12: strcat(res, "diciembre de "); break;
    }

    sprintf(aux, "%d", anno_);
    strcat(res, aux);

    delete[] aux;
    delete fec;

    return res;
}