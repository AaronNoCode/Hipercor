#ifndef FECHA_HPP
#define FECHA_HPP
/*
 * '[[nodiscard]]' es un atributo que protege que la función
 * sea usada sin que almacene el dato que ésta retorna
 *
 * 'const' usado en las funciones para asegurarse de que éstas
 * no cambian los atributos (elementos dentro de private) de la clase
*/

#include <iostream>
#include <fstream>
using namespace std;

class Fecha{
private:
    short dia;
    short mes;
    short anio;
public:
    Fecha(){
        this->dia = 0;
        this->mes = 0;
        this->anio = 0;
    }
    Fecha(short dia, short mes, short anio){
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
    }
    void setDia(short num){
        this->dia = num;
    }
    void setMes(short num){
        this->mes = num;
    }
    void setAnio(short num){
        this->anio = num;
    }

    [[nodiscard]] short getDia() const{
        return this->dia;
    }
    [[nodiscard]] short getMes() const{
        return this->mes;
    }
    [[nodiscard]] short getAnio() const{
        return this->anio;
    }

    string toString() const{
        return to_string(getDia()) + '/' + to_string(getMes()) + '/' + to_string(getAnio());
    }

    friend ofstream &operator << (ofstream &ofs, Fecha &f){
        ofs << f.toString();
        return ofs;
    }
    friend ifstream operator >> (ifstream ifs, Fecha &f){
        string dia1, mes1, anio1;
        getline(ifs, dia1, '/');
        f.dia = stoi(dia1);

        getline(ifs, mes1, '/');
        f.mes = stoi(mes1);

        getline(ifs, anio1, '/');
        f.anio = stoi(anio1);

        return ifs;
    }

    friend class Empleado;
};
#endif //FECHA_HPP