/*ESTRUCTURAS DE DATOS II
  SECCION D03
  GRACIELA LARA LOPEZ
  217782851 Ernesto Ariel Garcia Serna
  218169878 Omar Alejandro Quiroz Trujillo
  219550494 Cesar Aaron Perez Ramirez */

#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>
#include <fstream>
using namespace std;

class Fecha{
private:
    short dia;
    short mes;
    int anio;
public:
    Fecha(){
        this->dia = 0;
        this->mes = 0;
        this->anio = 0;
    }
    Fecha(short dia, short mes, int anio){
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
    }
    // Setters
    void setDia(short num){
        this->dia = num;
    }
    void setMes(short num){
        this->mes = num;
    }
    void setAnio(int num){
        this->anio = num;
    }
    // Getters
    // Nodiscard es para que el compilador nos avise si no usamos el valor de retorno
    [[nodiscard]] short getDia() const{
        return this->dia;
    }
    [[nodiscard]] short getMes() const{
        return this->mes;
    }
    [[nodiscard]] int getAnio() const{
        return this->anio;
    }
    /* Método para darle formato de salida a la fecha
      (pensando en que los días o meses que tengan sólo un dígito se les agregue un 0) */
    string toString() const{
        string diaFinal, mesFinal;
        if(getDia() < 10)
            diaFinal = "0" + to_string(getDia());
        else
            diaFinal = to_string(getDia());
        if(getMes() < 10)
            mesFinal = "0" + to_string(getMes());
        else
            mesFinal = to_string(getMes());
        return diaFinal + "/" + mesFinal + "/" + to_string(getAnio());
    }
    // Sobrecarga de operadores de entrada y salida de archivos
    friend ofstream &operator << (ofstream &ofs, Fecha &f){
        ofs << f.toString();
        return ofs;
    }
    // Se usa stoi() para convertir de string a int, ya que se usa getline
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
    // Declaración de amistad para indicar relaciones entre clases
    friend class Empleado;
};
#endif //FECHA_HPP