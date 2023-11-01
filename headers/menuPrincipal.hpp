/*ESTRUCTURAS DE DATOS II
  SECCION D03
  GRACIELA LARA LOPEZ
  217782851 Ernesto Ariel Garcia Serna
  218169878 Omar Alejandro Quiroz Trujillo
  219550494 Cesar Aaron Perez Ramirez */

#ifndef MENU_HPP
#define MENU_HPP

#include <map>
#include <iostream>
#include <algorithm>
#include "empleado.hpp"
#include "empleadosFile.hpp"
#include "disponiblesFile.hpp"
using namespace std;

/* Estas dos funcione son estáticas porque no necesitan acceder a ningún atributo de la clase
  y las dos funciones que las utilizan precisan que sean estáticas */
static bool isNumericOrPointChar(char c){
    return isdigit(c) || c=='.';
}
static bool isAlphabethicCharacterOrSpace(char c){
    return isalpha(c) || isspace(c);
}

class MenuPrincipal{
private:
    // Al ser la clase principal, es la que contiene a las dos clases más como variables
    DisponiblesFile disponiblesFile;
    EmpleadosFile empleadosFile;
    // Opción del menú
    int opcion;
    // Exclusivo para checar año bisiesto y días de cada mes
    map<int,int> meses{
            {1,31},
            {2,28},
            {3,31},
            {4,30},
            {5,31},
            {6,30},
            {7,31},
            {8,31},
            {9,30},
            {10,31},
            {11,30},
            {12,31}
    };
public:
    MenuPrincipal(){
        // Se inicializa a cero por buena praxis (no es bueno tener variables sin inicializar)
          opcion = 0;
            do{
                // Display de opciones
                cout << "\t.:Menu principal:.\n1.-Agregar\n2.-Eliminar\n3.-Buscar por DNI\n4.-Generar lista de disponibles\n5.-Salir\n->";
                // Leer opción desde consola
                cin >> opcion;
                // Empleado para guardar la información capturada
                Empleado emp;
                /* String auxiliar para guardar cada entrada, hacer pruebas y luego asignarla al empleado, y string
                  para guardar el nombre del empleado y hacerlo más estético a la hora de capturar */
                string strAux, nombreEmpleadoAlta;
                // Auxiliares para capturar la fecha de contratación y hacer comprobaciones
                int diaAux,mesAux,anioAux,numAux;
                // Bool exclusivo para checar año bisiesto y días de cada mes (que la fecha sea válida conforme al calendario)
                bool valid = false;
                // Switch para cada opción
                switch(opcion){
                    case 1: // + Agregar
                        // Captura de DNI, el método está contenid en la función
                        emp.generarDni();
                        //Captura de nombre
                        cout << "Ingrese nombre incluyendo nombres y apellidos" << '\n' << "->";
                        do{
                            cin.ignore();
                            getline(cin,strAux,'\n');
                            if (!isAlphabeticOrSpace(strAux))
                                cout<<"No se permiten caracteres numéricos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el nombre en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(!isAlphabeticOrSpace(strAux) || strAux.empty());
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setNombre(strAux);
                        nombreEmpleadoAlta = strAux;

                        //Captura de cargo
                        cout << "Ingrese el cargo de " << nombreEmpleadoAlta << '\n' << "->";
                        do{
                            getline(cin,strAux,'\n');
                            if (!isAlphabeticOrSpace(strAux))
                                cout<<"No se permiten caracteres numéricos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el cargo en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(!isAlphabeticOrSpace(strAux) || strAux.empty());
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setCargo(strAux);

                        //Captura de edad
                        cout << "Ingrese la edad de "<< nombreEmpleadoAlta << '\n' << "->";
                        do{
                            cin >> strAux;
                            numAux = stoi(strAux);
                            if (!isNumeric(strAux))
                                cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                            else if (numAux < 16)
                                cout << "No se permiten edades menores a 16, intente de nuevo" << '\n' << "->";
                            else if (strAux.empty())
                                cout<<"No puede dejar la edad en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(!isNumeric(strAux) || strAux.empty() || numAux < 16);
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setEdad(stoi(strAux));

                        //Captura de sueldo
                        cout << "Ingrese el sueldo de "<< nombreEmpleadoAlta << '\n' << "->";
                        do{
                            cin >> strAux;
                            if (!isNumericOrPoint(strAux))
                                cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el nombre en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(!isNumericOrPoint(strAux) || strAux.empty());
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setSueldo(stof(strAux));

                        //Captura de fecha de contratación
                        do{
                            // Captura de día
                            cout << "Ingrese el día de contratación de "<< nombreEmpleadoAlta << '\n' << "->";
                            do{
                                cin >> strAux;
                                diaAux = stoi(strAux);
                                if (!isNumeric(strAux))
                                    cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                                else if (diaAux > 31)
                                    cout<<"No se permiten números mayores a 31, intente de nuevo"<<'\n'<<"->";
                                else if (diaAux < 1)
                                    cout<<"No se permiten números menores a 1, intente de nuevo"<<'\n'<<"->";
                                else if (strAux.empty())
                                    cout<<"No puede dejar el día en blanco, intente de nuevo"<<'\n'<<"->";
                            }while(!isNumeric(strAux) || strAux.empty() || diaAux > 31 || diaAux < 1);

                            // Captura de mes
                            cout << "Ingrese el mes de contratación de "<< nombreEmpleadoAlta << '\n' << "->";
                            do{
                                cin >> strAux;
                                mesAux = stoi(strAux);
                                if (!isNumeric(strAux))
                                    cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                                else if (mesAux > 12)
                                    cout<<"No se permiten números mayores a 12, intente de nuevo"<<'\n'<<"->";
                                else if (mesAux < 1)
                                    cout<<"No se permiten números menores a 1, intente de nuevo"<<'\n'<<"->";
                                else if (strAux.empty())
                                    cout<<"No puede dejar el mes en blanco, intente de nuevo"<<'\n'<<"->";
                            }while(!isNumeric(strAux) || strAux.empty() || mesAux > 12 || mesAux < 1);

                            // Captura de año
                            cout << "Ingrese el año de contratación de "<< nombreEmpleadoAlta << '\n' << "->";
                            do{
                                cin >> strAux;
                                anioAux = stoi(strAux);
                                if (!isNumeric(strAux))
                                    cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                                else if (anioAux < 1)
                                    cout<<"No se permiten números menores a 1, intente de nuevo"<<'\n'<<"->";
                                else if (strAux.empty())
                                    cout<<"No puede dejar el año en blanco, intente de nuevo"<<'\n'<<"->";
                            }while(!isNumeric(strAux) || strAux.empty() || anioAux < 1);

                            // Checa año bisiesto en caso de que se haya seleccionado el 29 como dia y el 2 como mes
                            if(diaAux == 29 && mesAux == 2) {
                                /* La comprobación es checar si el día es divisible entre 4 sin dejar residuo, si sí, el año fue bisiesto
                                   y ese febrero sí tuvo 29 días */
                                if (anioAux % 4 == 0)
                                    valid = true;
                                else {
                                    cout << "El febrero del año seleccionado no tuvo 29 días, intente de nuevo" << '\n';
                                }
                            }else{
                                // Iterador para encontrar el número de días correspondiente al mes seleccionado y comprobar excepciones
                                auto it = meses.find(mesAux);
                                /* Si el día seleccionado es mayor al valor correspondiente del mes seleccionado, la bandera de fecha válida
                                  no se hace verdadera y la fecha de contratación debe capturarse de nuevo */
                                if(it->second < diaAux){
                                    cout<<it->second<<'\n';
                                    cout<<diaAux<<'\n';
                                    cout << "El número de día seleccionado es mayor al número de días totales del mes seleccionado, intente de nuevo"<<'\n';
                                }else{
                                    // En caso de que el valor del mapa no sea mayor, entonces la fecha es válida y se hace verdadera la bandera
                                    valid = true;
                                }
                            }
                        }while(!valid);
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setFechaDeContratacionDia(diaAux);
                        emp.setFechaDeContratacionMes(mesAux);
                        emp.setFechaDeContratacionAnio(anioAux);
                        cout<<"Empleado dado de alta con DNI: "<<emp.getDni()<<'\n';
                        // Se agrega el empleado al archivo ya que tiene todos sus campos completos
                        empleadosFile.addData(emp);
                        break;
                    case 2: // Eliminar
                        // Captura de DNI
                        cout << "Ingrese DNI de nueve dígitos" << '\n' << "->";
                        do {
                            // Limpia el buffer
                            cin.ignore();
                            // Se captura el DNI en el string auxiliar
                            getline(cin,strAux,'\n');
                            if (strAux.length() != 9)
                                cout << "Longitud inválida, intente de nuevo" << '\n' << "->";
                            else if (!isAlphanumeric(strAux))
                                cout << "Debe contener solamente caracteres numéricos, intente de nuevo" << '\n'<< "->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el DNI en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(strAux.length() != 9 || !isAlphanumeric(strAux) || strAux.empty());
                        // Checa si existe el registro en la lista de empleados
                        if(!empleadosFile.checkForExistance(strAux)){
                            cout<<"No existe un empleado con ese DNI"<<'\n';
                            break;
                        }else{
                            // Si el empleado existe
                            empleadosFile.delData(strAux);
                            // Se agrega el índice del empleado eliminado a la lista de disponibles
                            disponiblesFile.pushDisp(empleadosFile.getIndex());
                            disponiblesFile.listToFile();
                        }
                        break;
                    case 3: // Buscar por DNI
                        // Captura de DNI
                        // Captura de DNI
                        cout << "Ingrese DNI de nueve dígitos" << '\n' << "->";
                        do {
                            // Se captura el DNI en el string auxiliar
                            cin >> strAux;
                            if (strAux.length() != 9)
                                cout << "Longitud inválida, intente de nuevo" << '\n' << "->";
                            else if (!isAlphanumeric(strAux))
                                cout << "Debe contener solamente caracteres numéricos, intente de nuevo" << '\n'
                                     << "->";
                        }while(strAux.length() != 9 || !isAlphanumeric(strAux));
                        if(!empleadosFile.checkForExistance(strAux)) {
                            cout << "No existe un empleado con ese DNI" << '\n';
                            break;
                        }else{
                            // Se imprime el empleado encontrado
                            empleadosFile.findDataByDni(strAux);
                        }
                        break;
                    case 4: // Generar lista de disponibles
                        // Se imprime la lista de disponibles
                        disponiblesFile.printList();
                        break;
                    case 5: // Salir
                        break;
                    default:
                        cout<<"Opción inválida, intente de nuevo\n->";
                }
            }while(opcion != 5);
        }
    /* Funciones para comprobar si una cadena es numérica, alfabética, alfanumérica, etc.
       Nótese que se usan las funciones estáticas en el principio de este código */
    /* Se usa all_of para checar si todos los caracteres de la cadena son numéricos
       y el tercer argumento de dicha función es un protocolo personalizado para hacer la comprobación*/
    bool isNumericOrPoint(const string &str){
        return all_of(str.begin(),str.end(),isNumericOrPointChar);
    }
    bool isNumeric(const string &str){
        return all_of(str.begin(),str.end(),::isdigit);
    }
    bool isAlphabeticOrSpace(const string &str) {
        return all_of(str.begin(), str.end(), isAlphabethicCharacterOrSpace);
    }
    bool isAlphanumeric(const std::string& str) {
        return std::all_of(str.begin(), str.end(), ::isalnum);
    }
};


#endif //MENU_HPP


