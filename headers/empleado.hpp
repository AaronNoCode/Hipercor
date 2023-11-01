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
// Include de la clase Fecha para poder usarla en el empleado (fecha de contratación)
#include "fecha.hpp"
// Ya que no se usa otro namespace, se usa std para no tener que escribir std::string, std::map, etc.
using namespace std;
// Clase que se encarga de manejar los empleados
class Empleado{
    // Atributos privados de la clase
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
    // Métodos públicos de la clase
public:
    Empleado(string nombre, string cargo, short edad, float sueldo,Fecha fechaDeContratacion){
        // Ya que el DNI no es un campo que se ingrese, se genera automáticamente
        generarDni();
        // Se asignan los demás atributos acorde a los argumentos del constructor
        this->nombre = nombre;
        this->cargo = cargo;
        this->edad = edad;
        this->sueldo = sueldo;
        this->fechaDeContratacion = fechaDeContratacion;
        // Se inicializa el diccionario de letras del DNI
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
        // En caso de que no se ingrese un argumento para construir un empleado, todas las variables se inicializan en cero o cadena vacía por buena praxis
        this->dni = "";
        this->nombre = "";
        this->cargo = "";
        this->edad = 0;
        this->sueldo = 0;
        // El constructor de fecha por defecto ya inicializa la fecha en cero
        this->fechaDeContratacion = Fecha();
        // Se inicializa el diccionario de letras del DNI
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
    // Getter para DNI
    string getDni() const {
        return this->dni;
    }
    // Getter para nombre
    string getNombre() const {
        return this->nombre;
    }
    // Getter para cargo
    string getCargo() const {
        return this->cargo;
    }
    // Getter para edad
    short getEdad() const {
        return this->edad;
    }
    // Getter para sueldo
    float getSueldo() const {
        return this->sueldo;
    }
    // Getter para fecha de contratación
    string getFechaDeContratacionString() const {
        return this->fechaDeContratacion.toString();
    }
    // Esta función se encarga de la forma canónica del DNI
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
    // Setter de DNI
    void setDNI(const string &dni){
        this->dni = dni;
    }
    // Setter de nombre
    void setNombre(const string &nombre) {
        this->nombre = nombre;
    }
    // Setter de cargo
    void setCargo(const string &cargo) {
        this->cargo = cargo;
    }
    // Setter de edad
    void setEdad(short edad) {
        this->edad = edad;
    }
    // Setter de sueldo
    void setSueldo(float sueldo) {
        this->sueldo = sueldo;
    }
    // Se separan las funciones de los setters de la fecha para seguir con el esquema de getters y setters
    // Setter de dia de contratación
    void setFechaDeContratacionDia(short dia) {
        this->fechaDeContratacion.setDia(dia);
    }
    // Setter de mes de contratación
    void setFechaDeContratacionMes(short mes) {
        this->fechaDeContratacion.setMes(mes);
    }
    // Setter de año de contratación
    void setFechaDeContratacionAnio(int anio) {
        this->fechaDeContratacion.setAnio(anio);
    }
    // Función para darle formato de salida al empleado al archivo (rellenar los campos con espacios)
    string toString(){
        // Strings auxiliares para ir guardando los datos con su formato correspondiente
        string totalNombre, totalCargo, totalSueldo;
        // Se pobla primero la cadena de nombre con el valor de nombre del empleado
        totalNombre = toMayusName();
        // Mediante un ciclo for se rellena la cadena agregando los espacios faltantes para completar los 25 caracteres
        for(auto i = 0;i < 25-toMayusName().length();i++)
            // Se agregan espacios al final de la cadena con el método append (+=)
            totalNombre += " ";
        // Se hace lo mismo con el cargo para que tenga 10 caracteres
        totalCargo = toMayusCharge();
        for(auto i = 0;i < 10-toMayusCharge().length();i++)
            totalCargo += " ";
        // Se hace lo mismo con el sueldo para que tenga 10 caracteres
        totalSueldo = exitFormatSueldo();
        for(auto i = 0;i < 10-exitFormatSueldo().length();i++)
            totalSueldo += " ";
        // Se retorna el empleado con su formato correspondiente (ni el DNI ni la fecha necesitan formateo ya que el DNI tiene un tamaño fijo y la hora tiene justo después el salto de línea)
        return getDni() + "|" + totalNombre + "|" + totalCargo + "|" + "$" + totalSueldo + "|" + getFechaDeContratacionString();
    }
    // Función para darle formato de salida al nombre (mayúsculas)
    string toMayusName() const{
        // Se crea una copia del nombre para no modificar el original
        string uppercase = getNombre();
        // Se recorre la cadena y se convierten todos los caracteres a mayúsculas
        for(char &c : uppercase)
            // Se usa toupper para convertir a mayúsculas
            c = toupper(c);
        // Se retorna el nombre ya en mayúsculas
        return uppercase;
    }
    // Función para darle formato de salida al cargo (mayúsculas)
    string toMayusCharge() const{
        // Se crea una copia del cargo para no modificar el original
        string uppercase = getCargo();
        // Se recorre la cadena y se convierten todos los caracteres a mayúsculas
        for(char &c : uppercase)
            // Se usa toupper para convertir a mayúsculas
            c = toupper(c);
        // Se retorna el cargo ya en mayúsculas
        return uppercase;
    }
    // Función para saber si el sueldo tiene decimales
    bool tieneDecimales() const{
        // Se usa static_cast para convertir el sueldo a int y compararlo con el sueldo original
        return this->getSueldo() != static_cast<int>(this->getSueldo());
    }
    // Función para darle formato de salida al sueldo
    string putCommas(string numero) const{
        // String auxiliar para guardar los decimales
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
            // Se declaran dos cadenas auxiliares para guardar los datos del stringstream y poder formatearlos
            string final, preeliminar;
            // Se guardan los datos del stringstream en un string auxiliar
            preeliminar = ss.str();
            // Se llama a la función putCommas para darle formato al sueldo separando los cientos, los miles, los millones, etc.
            final = putCommas(preeliminar);
            // Se retorna el sueldo ya formateado para salida a archivo
            return final;
        }else {
            /*En caso de que no haya números después del punto decimal, solamente se mete el sueldo crudo y
              la terminación ".00" al stringstream */
            ss << this->getSueldo() << ".00";
            // Se declaran dos cadenas auxiliares para guardar los datos del stringstream y poder formatearlos
            string preeliminar, final;
            // Se guardan los datos del stringstream en un string auxiliar
            preeliminar = ss.str();
            // Se llama a la función putCommas para darle formato al sueldo separando los cientos, los miles, los millones, etc.
            final = putCommas(preeliminar);
            // Se retorna el sueldo ya formateado para salida a archivo
            return final;
        }
    }
    // Sobrecarga de operadores para poder comparar empleados por DNI (pensando en escalabilidad del programa) y para poder ordenarlos
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
        // Getline para leer el campo de nombre hasta el delimitador
        getline(ifs, nombre, '|');
        // Nombre se pobla con el nombre leído en la línea anterior
        empl.setNombre(nombre);
        // Getline para leer el campo de cargo hasta el delimitador
        getline(ifs, cargo, '|');
        // Cargo se pobla con el cargo leído en la línea anterior
        empl.setCargo(cargo);
        // Getline para leer el campo de sueldo hasta el delimitador
        getline(ifs,sueldo,'|');
        //Le quitamos el $ a sueldo
        sueldo = sueldo.substr(1);
        // Sueldo se pobla con el sueldo leído y tratado (quitarle el $) en la línea anterior
        empl.setSueldo(stof(sueldo));
        // Getline para leer el campo de dia de contratación hasta el delimitador (/)
        getline(ifs, diaStr, '/');
        /* Como no hay función para convertir directamente un string a short
           usamos primero stoi para convertir a int y luego static_cast para
           convertir a short y luego asignarlo al dia de contratación */
        empl.setFechaDeContratacionDia(static_cast<short>(stoi(diaStr)));
        getline(ifs, mesStr, '/');
        /* Como no hay función para convertir directamente un string a short
           usamos primero stoi para convertir a int y luego static_cast para
           convertir a short y luego asignarlo al mes de contratación */
        empl.setFechaDeContratacionMes(static_cast<short>(stoi(mesStr)));
        // Getline para leer el campo de año de contratación hasta el delimitador final (\n)
        getline(ifs, anioStr, '\n');
        // Usamos stoi para convertir el string a int y luego asignarlo al año de contratación
        empl.setFechaDeContratacionAnio(stoi(anioStr));
        return ifs;
    }
    // Declaraciones de clases amigas para indicar relaciones entre clases (hacen uso de los atributos privados de la clase Empleado)
    friend class EmpleadosFile;
    friend class MenuPrincipal;
};
#endif