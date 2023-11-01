/*ESTRUCTURAS DE DATOS II
  SECCION D03
  GRACIELA LARA LOPEZ
  217782851 Ernesto Ariel Garcia Serna
  218169878 Omar Alejandro Quiroz Trujillo
  219550494 Cesar Aaron Perez Ramirez */

#ifndef EMPLEADO_HPP
#define EMPLEADO_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <map>
#include <random>
#include "fecha.hpp"
using namespace std;
class Empleado{
private:
    string dni;
    string nombre;
    string cargo;
    short edad;
    float sueldo;
    // Fecha es una clase aparte ya que necesita su propio formateo
    Fecha fechaDeContratacion;
    // Mapa para el cálculo de la letra del DNI
    map<int,char> diccionarioLetrasDNI;
public:
    Empleado(string nombre, string cargo, short edad, float sueldo,Fecha fechaDeContratacion){
        generarDni();
        this->nombre = nombre;
        this->cargo = cargo;
        this->edad = edad;
        this->sueldo = sueldo;
        this->fechaDeContratacion = fechaDeContratacion;
        this->diccionarioLetrasDNI = {
                {0,'T'},
                {1,'R'},
                {2,'W'},
                {3,'A'},
                {4,'G'},
                {5,'M'},
                {6,'Y'},
                {7,'F'},
                {8,'P'},
                {9,'D'},
                {10,'X'},
                {11,'B'},
                {12,'N'},
                {13,'J'},
                {14,'Z'},
                {15,'S'},
                {16,'Q'},
                {17,'V'},
                {18,'H'},
                {19,'L'},
                {20,'C'},
                {21,'K'},
                {22,'E'}
        };
    }
    // Se inicializan todas las variables por buena praxis
    Empleado(){
        this->dni = "";
        this->nombre = "";
        this->cargo = "";
        this->edad = 0;
        this->sueldo = 0;
        this->fechaDeContratacion = Fecha();
        this->diccionarioLetrasDNI = {
                {0,'T'},
                {1,'R'},
                {2,'W'},
                {3,'A'},
                {4,'G'},
                {5,'M'},
                {6,'Y'},
                {7,'F'},
                {8,'P'},
                {9,'D'},
                {10,'X'},
                {11,'B'},
                {12,'N'},
                {13,'J'},
                {14,'Z'},
                {15,'S'},
                {16,'Q'},
                {17,'V'},
                {18,'H'},
                {19,'L'},
                {20,'C'},
                {21,'K'},
                {22,'E'}
        };
    }
    // Getters para cada atributo
    string getDni() const {
        return this->dni;
    }
    string getNombre() const {
        return this->nombre;
    }
    string getCargo() const {
        return this->cargo;
    }
    short getEdad() const {
        return this->edad;
    }
    float getSueldo() const {
        return this->sueldo;
    }
    string getFechaDeContratacionString() const {
        return this->fechaDeContratacion.toString();
    }
    // Setters para cada atributo
    void generarDni() {
        // String auxiliar para ir guardando los números cuando se generen
        int dniNumero;
        // Obtiene un número aleatorio del hardware
        random_device rd;
        // Semilla para el generador Marsenne Twister generado con el número aleatorio del hardware
        mt19937 eng(rd());
        // Define el rango del número deseado en la distribución
        uniform_int_distribution<>distr(10000000,99999999);
        // Se asigna el número aleatorio usando la distribución y como argumento el número aleatorio
        dniNumero = distr(eng);
        /* Acorde al proceso canónico de generar el DNI, se concatena el número aleatorio generado
           convertido a string con la letra asociada en el diccionario obtenida de el número aleatorio módulo 23
           y se asigna al atributo de DNI del empleado */
        this->dni = to_string(dniNumero) + diccionarioLetrasDNI[dniNumero % 23];
    }
    void setDNI(const string &dni){
        this->dni = dni;
    }
    void setNombre(const string &nombre) {
        this->nombre = nombre;
    }
    void setCargo(const string &cargo) {
        this->cargo = cargo;
    }
    void setEdad(short edad) {
        this->edad = edad;
    }
    void setSueldo(float sueldo) {
        this->sueldo = sueldo;
    }
    // Se separan las funciones para el setter de la fecha para seguir con el esquema de getters y setters
    void setFechaDeContratacionDia(short dia) {
        this->fechaDeContratacion.setDia(dia);
    }
    void setFechaDeContratacionMes(short mes) {
        this->fechaDeContratacion.setMes(mes);
    }
    void setFechaDeContratacionAnio(int anio) {
        this->fechaDeContratacion.setAnio(anio);
    }
    string toString(){
        string totalNombre, totalCargo, totalSueldo;
        totalNombre = toMayusName();
        for(auto i = 0;i < 25-toMayusName().length();i++)
            totalNombre += " ";
        totalCargo = toMayusCharge();
        for(auto i = 0;i < 10-toMayusCharge().length();i++)
            totalCargo += " ";
        totalSueldo = exitFormatSueldo();
        for(auto i = 0;i < 10-exitFormatSueldo().length();i++)
            totalSueldo += " ";
        cout<<getDni() + "|" + totalNombre + "|" + totalCargo + "|" + "$" + totalSueldo + "|" + getFechaDeContratacionString();
        return getDni() + "|" + totalNombre + "|" + totalCargo + "|" + "$" + totalSueldo + "|" + getFechaDeContratacionString();
    }
    // Función para darle formato de salida al nombre
    string toMayusName() const{
        string uppercase = getNombre();
        for(char &c : uppercase)
            c = toupper(c);
        return uppercase;
    }
    // Función para darle formato de salida al cargo
    string toMayusCharge() const{
        string uppercase = getCargo();
        for(char &c : uppercase)
            c = toupper(c);
        return uppercase;
    }
    // Función para saber si el sueldo tiene decimales
    bool tieneDecimales() const{
        return this->getSueldo() != static_cast<int>(this->getSueldo());
    }
    // Función para darle formato de salida al sueldo
    string putCommas(string numero) const{
        string decimales;
        // Se separan los decimales del número volteando la cadena y tomando los primeros dos caracteres (los decimales)
        reverse(numero.begin(), numero.end());
        // Se guardan los decimales en una variable aparte
        decimales = numero.substr(0,2);
        // Se vuelve a voltear la cadena de decimales para que quede en el orden correcto
        reverse(decimales.begin(),decimales.end());
        // Se eliminan los decimales del número
        numero = numero.substr(3);
        // Se insertan comas cada 3 caracteres empezando desde el final
        for(auto i = 3; i < numero.length(); i+=4)
            numero.insert(i,",");
        // Se vuelve a voltear el número para que quede en el orden correcto
        reverse(numero.begin(),numero.end());
        // Se retorna el número completo con enteros y decimales
        return numero + '.' + decimales;
    }
    // Función para darle formato de salida al sueldo incluyendo el signo de pesos
    string exitFormatSueldo() const{
        /* Hacemos uso de un stringstream para poder formatear los datos de una forma
           más específica que sólo convirtiendo el número a string con to_string */
        stringstream ss;
        /* Si el sueldo tiene punto decimal no hay necesidad de ponerle ".00" después
           del número, por eso se hace esa validación, ya que cada caso necesita un formateo distinto */
        if(tieneDecimales()) {
            /* De include <cmath>
               Ya que al imprimir un float definiendo un número específico de números después del punto
               éstos se redondean, es necesario truncar los decimales para evitar este redondeo indeseado
               Este método funciona ya que al multiplicar por 100 los dos decimales que queremos se pasan a
               la izquierda del punto y al dividir entre 100 los decimales que no queremos se eliminan al
               recorrer el punto decimal dos lugares a la derecha */
            double sueldoTruncadoDeDecimales = trunc(this->getSueldo() * 100) / 100;
            /* De include <iomanip>
               Fixed: para controlar la presición del float, ya que C++ por defecto decide
               si se usa notación fija (mostrar cierta cantidad de números después del punto) o
               notación científica (4.000000e+03). Al usar fixed se especifica que se quiere usar
               siempre notación fija.
               Setprecision: para controlar cuántos números se deben considerar después del punto (en este
               caso SOLAMENTE 2).
               Para finalizar, se ingresa el sueldo ya con formato especificado dentro de el stringstream */
            ss << fixed << setprecision(2) << sueldoTruncadoDeDecimales;
            string final, preeliminar;
            preeliminar = ss.str();
            final = putCommas(preeliminar);
            return final;
        }else {
            /*En caso de que no haya números después del punto decimal, solamente se mete el sueldo crudo y
              la terminación ".00" al stringstream */
            ss << this->getSueldo() << ".00";
            string preeliminar, final;
            preeliminar = ss.str();
            final = putCommas(preeliminar);
            return final;
        }
        // Retorna el sueldo ya formateado para salida a archivo
        return "nothing";
    }
    // Sobrecarga de operadores para poder comparar empleados por DNI (pensando en escalabilidad del programa)
    bool operator==(const Empleado &empl) const {
        return dni == empl.dni;
    }
    bool operator!=(const Empleado &empl) const {
        return !(empl == *this);
    }
    bool operator < (Empleado &empl) const {
        return dni < empl.dni;
    }
    bool operator > (Empleado &empl) const {
        return dni > empl.dni;
    }
    bool operator<=(const Empleado &empl) const {
        return dni <= empl.dni;
    }
    bool operator >= (Empleado &empl) const {
        return dni >= empl.dni;
    }
    // Sobrecarga de operador de salida para formatear cómo se muestran en el archivo con sus separaciones
    friend ofstream &operator << (ofstream &ofs, Empleado &empl) {
        // Todos los atributos salen con su formato correspondiente
        ofs << empl.getDni() + "|" + empl.toMayusName() + "|" + empl.toMayusCharge() + "|" + "$" + empl.exitFormatSueldo() + "|" + empl.getFechaDeContratacionString();
        return ofs;
    }
    // Operador de entrada para leer cada atributo del empleado y asignarlo
    friend istream &operator >> (istream &ifs, Empleado &empl){
        string dni, nombre, cargo, sueldo, diaStr, mesStr, anioStr;
        // Se usa getline para poder leer hasta el delimitador del DNI
        getline(ifs, dni,'|');
        // DNI se pobla con el dni leído en la lína anterior
        empl.setDNI(dni);
        // Getline para leer el campo de nombre y
        getline(ifs, nombre, '|');
        empl.setNombre(nombre);
        getline(ifs, cargo, '|');
        empl.setCargo(cargo);
        getline(ifs,sueldo,'|');
        //Le quitamos el $ a sueldo
        sueldo = sueldo.substr(1);
        empl.setSueldo(stof(sueldo));
        getline(ifs, diaStr, '/');
        /* Como no hay función para convertir directamente un string a short
           usamos primero stoi para convertir a int y luego static_cast para
           convertir a short */
        empl.setFechaDeContratacionDia(static_cast<short>(stoi(diaStr)));
        getline(ifs, mesStr, '/');
        /* Como no hay función para convertir directamente un string a short
           usamos primero stoi para convertir a int y luego static_cast para
           convertir a short */
        empl.setFechaDeContratacionMes(static_cast<short>(stoi(mesStr)));
        getline(ifs, anioStr, '\n');
        empl.setFechaDeContratacionAnio(stoi(anioStr));
        return ifs;
    }

    friend class EmpleadosFile;
    friend class MenuPrincipal;
};
#endif