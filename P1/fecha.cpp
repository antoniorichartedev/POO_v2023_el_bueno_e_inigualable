//
// Created by Anton on 10/03/2023.
//
#include "fecha.hpp"
#include <cstdio>
#include <cstring>

const int Fecha::DiasqueTieneunMes[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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

const char *Fecha::obtenercadenita() const noexcept{
    static char res[36];

    std::locale::global(std::locale("es_ES.utf8"));
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* fec = std::localtime(&tiempo_calendario);

    fec->tm_mday = dia_;
    fec->tm_mon = mes_ - 1;
    fec->tm_year = anno_ - 1900;

    mktime(fec);
    strftime(res, 36, "%A %e de %B de %Y", fec);
    return res;
}

ostream& operator << (ostream& os, const Fecha& f){
    os << f.cadena();
    return os;
}

istream& operator >> (istream& is, Fecha& f){
    /*// creamos una cadena de tamaño 11 para almacenar la fecha.
    char* formato = new char[11];

    // pasamos la fecha introducida a la variable formato.
    is >> formato;

    try{
        f = Fecha(formato);
    }catch(Fecha::Invalida& e){

        // ponemos el bit de estado en fail.
        is.setstate(ios_base::failbit);
        f = Fecha();
        throw;
    }

    // Si el formato está correcto, pasamos a comprobar la fecha.
    unsigned i = 0, cont = 0;

    while(cont < 2 and formato[i] == '0'){
        cont++;
        i++;
    }
    if(cont == 2 and formato[i] != '/'){
        is.setstate(ios_base::failbit);
        f = Fecha();
        throw Fecha::Invalida("Te has pasado de los 2 dígitos.");
    }else{
        while(formato[i] == '/')
            i++;
        // 22/02/2002
        cont = 0;
        while(cont < 2 and formato[i] == '0'){
            cont++;
            i++;
        }
        if(cont == 2 and formato[i] != '/'){
            is.setstate(ios_base::failbit);
            f = Fecha();
            throw Fecha::Invalida("Te has pasado de los 2 dígitos.");
        }
        delete[] formato;
    }
    return is;*/

    // creamos una cadena de tamaño 11 para almacenar la fecha.
    char c[11] {};

    // con getline, cogemos toda la línea del flujo de entrada.
    is.getline(c,11);

    // comprobamos que la fecha es correcta.
    try{
        f = Fecha(c);
    }catch(Fecha::Invalida& e){
        // ponemos el bit de estado en fail, ya que la fecha no es correcta.
        is.setstate(ios_base::failbit);
        f = Fecha();
        throw;
    }


    return is;
}

