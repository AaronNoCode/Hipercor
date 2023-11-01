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
// Ya que no se usa otro namespace, se usa std para no tener que escribir std::stoi, etc.
using namespace std;
// Clase que se encarga de manejar la fecha
class Fecha{
    // Atributos privados de la clase
private:
    // Se usan short para que no se puedan ingresar números negativos e int para que no se desborde ningún número
    short dia;
    short mes;
    int anio;
    // Métodos públicos de la clase
public:
    // Constructor por defecto inicializando los atributos en 0 para evitar errores
    Fecha(){
        this->dia = 0;
        this->mes = 0;
        this->anio = 0;
    }
    // Constructor con parámetros para inicializar los atributos con los valores dados
    Fecha(short dia, short mes, int anio){
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
    }
    // Setter de día
    void setDia(short num){
        // Asigna el valor dado como parámetro al atributo
        this->dia = num;
    }
    // Setter de mes
    void setMes(short num){
        // Asigna el valor dado como parámetro al atributo
        this->mes = num;
    }
    // Setter de año
    void setAnio(int num){
        // Asigna el valor dado como parámetro al atributo
        this->anio = num;
    }

    // Nodiscard es para que el compilador nos avise si no usamos el valor de retorno
    // Getter de día
    [[nodiscard]] short getDia() const{
        return this->dia;
    }
    // Getter de mes
    [[nodiscard]] short getMes() const{
        return this->mes;
    }
    // Getter de año
    [[nodiscard]] int getAnio() const{
        return this->anio;
    }
    /* Método para darle formato de salida a la fecha
      (pensando en que los días o meses que tengan sólo un dígito se les agregue un 0) */
    string toString() const{
        // Se crean dos strings para guardar el día y el mes en caso de que sean de un sólo dígito y poder agregarles un cero
        string diaFinal, mesFinal;
        // Se verifica si el día es de un dígito (1-9)
        if(getDia() < 10)
            // Si es de un dígito, se convierte a string y se le agrega un 0 al inicio
            diaFinal = "0" + to_string(getDia());
        else
            // Si no es de un dígito, se convierte a string y se guarda en diaFinal
            diaFinal = to_string(getDia());
        // Se verifica si el mes es de un dígito (1-9)
        if(getMes() < 10)
            // Si es de un dígito, se convierte a string y se le agrega un 0 al inicio
            mesFinal = "0" + to_string(getMes());
        else
            // Si no es de un dígito, se convierte a string y se guarda en mesFinal
            mesFinal = to_string(getMes());
        // Se retorna la fecha con el formato dd/mm/aaaa (con los ceros agregados y el año convertido a string)
        return diaFinal + "/" + mesFinal + "/" + to_string(getAnio());
    }
    // Sobrecarga de operador de salida a archivos
    friend ofstream &operator << (ofstream &ofs, Fecha &f){
        // Usando el método toString(), se escribe la fecha en el archivo con el formato requerido
        ofs << f.toString();
        return ofs;
    }
    // Sobrecarga de operador de entrada de archivos
    friend ifstream operator >> (ifstream ifs, Fecha &f){
        // Se crean tres strings para guardar el día, mes y año
        string dia1, mes1, anio1;
        // Se lee el archivo hasta encontrar un '/' y se guarda en dia1
        getline(ifs, dia1, '/');
        /* Se convierte a int y se guarda en el atributo dia (por defecto se angosta el valor para caber en short)
          NOTA: no existe un método para convertir directamente en short*/
        f.dia = stoi(dia1);

        // Se lee el archivo hasta encontrar un '/' y se guarda en mes1
        getline(ifs, mes1, '/');
        /* Se convierte a int y se guarda en el atributo mes (por defecto se angosta el valor para caber en short)
          NOTA: no existe un método para convertir directamente en short*/
        f.mes = stoi(mes1);

        // Se lee el archivo hasta encontrar un '\n' que es el fin del registro y se guarda en anio1
        getline(ifs, anio1, '/');
        // Se convierte a int y se guarda en el atributo anio
        f.anio = stoi(anio1);

        return ifs;
    }
    // Declaración de amistad para indicar relaciones entre clases que usan los atributos privados de la clase actual
    friend class Empleado;
};
#endif //FECHA_HPP