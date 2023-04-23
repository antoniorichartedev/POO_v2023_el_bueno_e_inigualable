//
// Created by Anton on 10/03/2023.
//

#ifndef P0_FECHA_HPP
#define P0_FECHA_HPP
#include <ctime>

bool Bisiesto (int anno);

class Fecha{
public:

    // constructores.
    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const char* f);

    // funciones observadoras.
    inline int dia() const noexcept{ return dia_; };
    inline int mes() const noexcept{ return mes_; };
    inline int anno() const noexcept{ return anno_; };

    // excepciones.
    class Invalida{
    public:
        Invalida(const char* inv): fallo(inv) {}
        const char* por_que() const { return fallo; };
    private:
        const char* fallo;
    };

    // constantes a definir.
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    // Operadores para incrementar o decrementar una fecha
    Fecha& operator ++();                   // Preincrementa
    Fecha operator ++(int);                 // Postincrementa
    Fecha& operator --();                   // Predecrementa
    Fecha operator --(int);                 // Postdecrementa
    Fecha operator +(int n) const;
    Fecha operator -(int n) const;
    Fecha& operator +=(int n);
    Fecha& operator -=(int n);

    // Esta clase reloj nos sirve para poder dar la fecha del sistema.
    class reloj {
    public:
        static int diaact() {
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mday;
        }

        static int mesact() {
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mon + 1;
        }

        static int annoact() {
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_year + 1900;
        }
    };

    //operator const char*() { return obtenercadenita(); };
    operator const char*() const{ return obtenercadenita(); };


private:
    int dia_, mes_, anno_;

    // función auxiliar que nos permite arreglar la fecha en el caso de que el dia, mes o el año sea 0.
    void ArreglarFecha(int d, int m, int a);

    // función auxiliar que nos permite comprobar que la fecha introducida es correcta. En el caso de que falle algo,
    // con throw lanzaremos la excepción adecuada con su respectivo mensaje de error.
    void ComprobarFecha();

    // vector de enteros que almacena los días que tiene cada mes del año.
    int DiasqueTieneunMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Esta función nos permite hacer la conversión de la fecha en números a una cadena con palabras.
    const char* obtenercadenita() const;
};

// Operadores para comparar dos fechas.
bool operator == (const Fecha& f1, const Fecha& f2);
bool operator != (const Fecha& f1, const Fecha& f2);
bool operator > (const Fecha& f1, const Fecha& f2);
bool operator < (const Fecha& f1, const Fecha& f2);
bool operator >= (const Fecha& f1, const Fecha& f2);
bool operator <= (const Fecha& f1, const Fecha& f2);

#endif //P0_FECHA_HPP
