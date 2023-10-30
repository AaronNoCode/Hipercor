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
#include "fecha.hpp"
using namespace std;
//if(m.find(s1)!=m.end()){
//      if the element is found before the end of the map
//      cout<<" : found : Value : "<<m[s1]<<endl;
class Empleado{
private:
    string dni;
    string nombre;
    string cargo;
    short edad;
    float sueldo;
    Fecha fechaDeContratacion;
    map<short,char> dniCanon;
public:
    Empleado(string dni, string nombre, string cargo, short edad, float sueldo,Fecha fechaDeContratacion){
        this->dni = formaCanonDni(dni);
        this->nombre = nombre;
        this->cargo = cargo;
        this->edad = edad;
        this->sueldo = sueldo;
        this->fechaDeContratacion = fechaDeContratacion;
        this->dniCanon = {
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
    Empleado(){
        this->dni = "";
        this->nombre = "";
        this->cargo = "";
        this->edad = 0;
        this->sueldo = 0;
        this->fechaDeContratacion = Fecha();
        this->dniCanon = {
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
    
    void setDni(const string &dni) {
        this->dni = formaCanonDni(dni);
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
    // TODO DELETE THIS
    void setFechaDeContratacion(const Fecha &fechaDeContratacion) {
        this->fechaDeContratacion = fechaDeContratacion;
    }
    void setFechaDeContratacionDia(short dia) {
        this->fechaDeContratacion.setDia(dia);
    }
    void setFechaDeContratacionMes(short mes) {
        this->fechaDeContratacion.setMes(mes);
    }
    void setFechaDeContratacionAnio(int anio) {
        this->fechaDeContratacion.setAnio(anio);
    }

    string formaCanonDni(const string &dniCrudo){
        return dniCrudo + (dniCanon[stoi(dniCrudo) % 23]);
    }
    void popBackDni(){
        if(this->dni.length() != 9)
            this->dni.pop_back();
    }
    string toMayusName() const{
        string uppercase = getNombre();
        for(char &c : uppercase)
            c = toupper(c);
        return uppercase;
    }

    string toMayusCharge() const{
        string uppercase = getCargo();
        for(char &c : uppercase)
            c = toupper(c);
        return uppercase;
    }
    bool tieneDecimales() const{
        return this->getSueldo() != static_cast<int>(this->getSueldo());
    }
    string putCommas(string numero) const{
        string decimales;
        reverse(numero.begin(), numero.end());
        decimales = numero.substr(0,2);
        reverse(decimales.begin(),decimales.end());
        numero = numero.substr(3);
        for(auto i = 3; i < numero.length(); i+=4)
            numero.insert(i,",");
        reverse(numero.begin(),numero.end());
        return numero + '.' + decimales;
    }
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

    }

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

    friend ofstream &operator << (ofstream &ofs, Empleado &empl) {
        ofs << empl.dni << '|' << empl.toMayusName() << '|' << empl.toMayusCharge() << '|' << '$' << empl.exitFormatSueldo() << '|' << empl.getFechaDeContratacionString();
        return ofs;
    }
    friend istream &operator >> (istream &ifs, Empleado &empl){
        string dni, nombre, cargo, sueldo, diaStr, mesStr, anioStr;

        getline(ifs, dni,'|');
        empl.setDni(dni);
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