#ifndef MENU_HPP
#define MENU_HPP
#include <map>
#include <iostream>
#include <algorithm>
#include "../headers/empleado.hpp"
#include "../headers/empleadosFile.hpp"
#include "../headers/disponiblesFile.hpp"
using namespace std;

/* Estas dos funcione son estáticas porque no necesitan acceder a ningún atributo de la clase
  y las dos funciones que las utilizan precisan que sean estáticas */
static bool isNumericOrPointChar(char c){
    return isalpha(c) || c=='.';
}
static bool isAlphabethicCharacterOrSpace(char c){
    return isalpha(c) || isspace(c);
}

class MenuPrincipal{
private:
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
                // Se limpia la consola cada vuelta
                system("cls");
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
                int diaAux,mesAux,anioAux;
                // Bool exclusivo para checar año bisiesto y días de cada mes (que la fecha sea válida conforme al calendario)
                bool valid = false;
                // Switch para cada opción
                switch(opcion){
                    case 1: // + Agregar
                        // Captura de DNI
                        cout << "Ingrese DNI de ocho dígitos" << '\n' << "->";
                        do {
                            // Se captura el DNI en el string auxiliar
                            cin >> strAux;
                            if (strAux.length() != 8)
                                cout << "Longitud inválida, intente de nuevo" <<'\n'<<"->";
                            else if (!isNumeric(strAux))
                                cout << "Debe contener solamente caracteres numéricos, intente de nuevo"<<'\n'<<"->";
                        }while(strAux.length() != 8 || !isNumeric(strAux));
                        emp.setDni(strAux);

                        //Captura de nombre
                        cout << "Ingrese nombre incluyendo nombres y apellidos" << '\n' << "->";
                        do{
                            cin >> strAux;
                            if (!isAlphabeticOrSpace(strAux))
                                cout<<"No se permiten caracteres numéricos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el nombre en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(!isAlphabeticOrSpace(strAux) || strAux.empty());
                        emp.setNombre(strAux);
                        nombreEmpleadoAlta = strAux;

                        //Captura de cargo
                        cout << "Ingrese el cargo de " << nombreEmpleadoAlta << '\n' << "->";
                        do{
                            cin >> strAux;
                            if (!isAlphabeticOrSpace(strAux))
                                cout<<"No se permiten caracteres numéricos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el nombre en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(!isAlphabeticOrSpace(strAux) || strAux.empty());
                        emp.setCargo(strAux);

                        //Captura de edad
                        cout << "Ingrese el la edad de "<< nombreEmpleadoAlta << '\n' << "->";
                        do{
                            cin >> strAux;
                            if (!isNumeric(strAux))
                                cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar la edad en blanco, intente de nuevo"<<'\n'<<"->";
                        }while(!isNumeric(strAux) || strAux.empty());
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
                                    cout << "El número de día seleccionado es mayor al número de días totales del mes seleccionado, intente de nuevo"<<'\n';
                                }else{
                                    // En caso de que el valor del mapa no sea mayor, entonces la fecha es válida y se hace verdadera la bandera
                                    valid = true;
                                }
                            }
                        }while(valid);
                        emp.setFechaDeContratacionDia(diaAux);
                        emp.setFechaDeContratacionMes(mesAux);
                        emp.setFechaDeContratacionAnio(anioAux);
                        // Se agrega el empleado al archivo
                        empleadosFile.addData(emp);
                        break;
                    case 2: // Eliminar
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
                        empleadosFile.delData(strAux);
                        break;
                    case 3: // Buscar por DNI
                        break;
                    case 4: // Generar lista de disponibles
                        break;
                    case 5: // Salir
                        break;
                    default:
                        cout<<"Opción inválida\n";
                }
            }while(opcion != 5);
        }
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


