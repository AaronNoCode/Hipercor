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
// Regresa un booleando y recibe un caracter como argumento
static bool isNumericOrPointChar(char c){
    // Regresa verdadero si el caracter es numérico o un punto
    return isdigit(c) || c=='.';
}
// Regresa un booleando y recibe un caracter como argumento
static bool isAlphabethicCharacterOrSpace(char c){
    // Regresa verdadero si el caracter es alfabético o un espacio
    return isalpha(c) || isspace(c);
}
// Clase principal para operar el programa
class MenuPrincipal{
    // Atributos privados de la clase
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
                            // Limpia el buffer
                            cin.ignore();
                            // Se captura el nombre en el string auxiliar
                            getline(cin,strAux,'\n');
                            // Hace una comprobación para verificar que el dato ingresado sea válido (alfabético o espacio o que no se haya dejado la línea vacía)
                            if (!isAlphabeticOrSpace(strAux))
                                cout<<"No se permiten caracteres numéricos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el nombre en blanco, intente de nuevo"<<'\n'<<"->";
                        // Se repite hasta que se ingresa un dato válido
                        }while(!isAlphabeticOrSpace(strAux) || strAux.empty());
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setNombre(strAux);
                        // Se guarda el nombre para imprimirlo en los mensajes de captura siguientes
                        nombreEmpleadoAlta = strAux;

                        //Captura de cargo
                        cout << "Ingrese el cargo de " << nombreEmpleadoAlta << '\n' << "->";
                        do{
                            // Lee el cargo en el string auxiliar
                            getline(cin,strAux,'\n');
                            // Hace una comprobación para verificar que el dato ingresado sea válido (alfabético o espacio o que no se haya dejado la línea vacía)
                            if (!isAlphabeticOrSpace(strAux))
                                cout<<"No se permiten caracteres numéricos, intente de nuevo"<<'\n'<<"->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el cargo en blanco, intente de nuevo"<<'\n'<<"->";
                        // Se repite hasta que se ingresa un dato válido
                        }while(!isAlphabeticOrSpace(strAux) || strAux.empty());
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setCargo(strAux);

                        //Captura de edad
                        cout << "Ingrese la edad de "<< nombreEmpleadoAlta << '\n' << "->";
                        do{
                            // Lee la edad en el string auxiliar
                            cin >> strAux;
                            // Convierte el string a int para hacer las comprobaciones
                            numAux = stoi(strAux);
                            // Hace una comprobación para verificar que el dato ingresado sea válido (numérico, que la edad no sea menor a 16 años o que no se haya dejado la línea vacía)
                            if (!isNumeric(strAux))
                                cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                            else if (numAux < 16)
                                cout << "No se permiten edades menores a 16, intente de nuevo" << '\n' << "->";
                            else if (strAux.empty())
                                cout<<"No puede dejar la edad en blanco, intente de nuevo"<<'\n'<<"->";
                        // Se repite hasta que se ingresa un dato válido
                        }while(!isNumeric(strAux) || strAux.empty() || numAux < 16);
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado
                        emp.setEdad(stoi(strAux));

                        //Captura de sueldo
                        cout << "Ingrese el sueldo de "<< nombreEmpleadoAlta << '\n' << "->";
                        do{
                            // Lee el sueldo en el string auxiliar
                            cin >> strAux;
                            // Hace una compronación para verificar que el dato ingresado sea válido (numérico o punto o que no se haya dejado la línea vacía)
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
                                // Lee el día en el string auxiliar
                                cin >> strAux;
                                // Convierte el string a int con stoi() para hacer las comprobaciones
                                diaAux = stoi(strAux);
                                /* Hace una comprobación para verificar que el dato ingresado sea válido (numérico, que el día no sea mayor a 31 (por los días del mes),
                                  que el día no sea menor a 1 (no hay días negativos ni existe el día cero o que no se haya dejado la línea vacía) */
                                if (!isNumeric(strAux))
                                    cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                                else if (diaAux > 31)
                                    cout<<"No se permiten números mayores a 31, intente de nuevo"<<'\n'<<"->";
                                else if (diaAux < 1)
                                    cout<<"No se permiten números menores a 1, intente de nuevo"<<'\n'<<"->";
                                else if (strAux.empty())
                                    cout<<"No puede dejar el día en blanco, intente de nuevo"<<'\n'<<"->";
                            // Se repite hasta que se ingresa un dato válido
                            }while(!isNumeric(strAux) || strAux.empty() || diaAux > 31 || diaAux < 1);

                            // Captura de mes
                            cout << "Ingrese el mes de contratación de "<< nombreEmpleadoAlta << '\n' << "->";
                            do{
                                // Lee el mes en el string auxiliar
                                cin >> strAux;
                                // Convierte el string a int con stoi() para hacer las comprobaciones
                                mesAux = stoi(strAux);
                                /* Hace una comprobación para verificar que el dato ingresado sea válido (numérico, que el mes no sea mayor a 12 (por los meses del año),
                                  que no sea menor a 1 (no existe el mes 0) y tampoco haya dejado la línea vacía) */
                                if (!isNumeric(strAux))
                                    cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                                else if (mesAux > 12)
                                    cout<<"No se permiten números mayores a 12, intente de nuevo"<<'\n'<<"->";
                                else if (mesAux < 1)
                                    cout<<"No se permiten números menores a 1, intente de nuevo"<<'\n'<<"->";
                                else if (strAux.empty())
                                    cout<<"No puede dejar el mes en blanco, intente de nuevo"<<'\n'<<"->";
                            // Se repite hasta que se ingresa un dato válido
                            }while(!isNumeric(strAux) || strAux.empty() || mesAux > 12 || mesAux < 1);

                            // Captura de año
                            cout << "Ingrese el año de contratación de "<< nombreEmpleadoAlta << '\n' << "->";
                            do{
                                // Lee el año en el string auxiliar
                                cin >> strAux;
                                // Convierte el string a int con stoi() para hacer las comprobaciones
                                anioAux = stoi(strAux);
                                /* Hace una comprobación para verificar que el dato ingresado sea válido (numérico, que no sea menor a 1700
                                  (pensando en que ninguna empresa vigente es tan antigua) y que no haya dejado la línea vacía) */
                                if (!isNumeric(strAux))
                                    cout<<"No se permiten caracteres alfabéticos, intente de nuevo"<<'\n'<<"->";
                                else if (anioAux < 1700)
                                    cout<<"No se permiten números menores a 1, intente de nuevo"<<'\n'<<"->";
                                else if (strAux.empty())
                                    cout<<"No puede dejar el año en blanco, intente de nuevo"<<'\n'<<"->";
                            // Se repite hasta que se ingresa un dato válido
                            }while(!isNumeric(strAux) || strAux.empty() || anioAux < 1700);

                            // Checa año bisiesto en caso de que se haya seleccionado el 29 como dia y el 2 como mes
                            if(diaAux == 29 && mesAux == 2) {
                                /* La comprobación es checar si el día es divisible entre 4 sin dejar residuo, si sí, el año fue bisiesto
                                   y ese febrero sí tuvo 29 días */
                                if (anioAux % 4 == 0)
                                    // Se hace verdadera la bandera de fecha válida en caso de que se cumpla la condición
                                    valid = true;
                                else {
                                    // Imprime un error en caso de que el año no sea bisiesto y el día sea 29
                                    cout << "El febrero del año seleccionado no tuvo 29 días, intente de nuevo" << '\n';
                                }
                            // Si no se seleccionó el 29 como día y el 2 como mes, entonces se hace otro tipo de comprobación con el mapa de meses declarado al principio de la clase
                            }else{
                                // Iterador para encontrar el número de días correspondiente al mes seleccionado y comprobar excepciones
                                auto it = meses.find(mesAux);
                                /* Si el día seleccionado es mayor al valor correspondiente del mes seleccionado, la bandera de fecha válida
                                  no se hace verdadera y la fecha de contratación debe capturarse de nuevo */
                                if(it->second < diaAux){
                                    cout << "El número de día seleccionado es mayor al número de días totales del mes seleccionado, intente de nuevo"<<'\n';
                                }else{
                                    // En caso de que el valor del mapa no sea menor al número de día ingresado, entonces la fecha es válida y se hace verdadera la bandera
                                    valid = true;
                                }
                            }
                        // El ciclo se repite hasta que la bandera de fecha válida sea verdadera
                        }while(!valid);
                        // Ya que se hicieron las comprobaciones, se puede asignar al empleado la fecha de contratación (se hace en tres partes para que sea más legible)
                        emp.setFechaDeContratacionDia(diaAux);
                        emp.setFechaDeContratacionMes(mesAux);
                        emp.setFechaDeContratacionAnio(anioAux);
                        // Se imprime el DNI para mostrarle al usuario el DNI del empleado que se acaba de dar de alta y lo pueda eliminar o buscar después
                        cout<<"Empleado dado de alta con DNI: "<<emp.getDni()<<'\n';
                        // Se agrega el empleado al archivo y a la lista mediante addData() ya que tiene todos sus campos completos
                        empleadosFile.addData(emp);
                        break;
                    case 2: // Eliminar
                        // Captura de DNI del registro a eliminar
                        cout << "Ingrese DNI de nueve dígitos" << '\n' << "->";
                        // Ciclo do while
                        do {
                            // Limpia el buffer
                            cin.ignore();
                            // Se captura el DNI en el string auxiliar
                            getline(cin,strAux,'\n');
                            // Hace una comprobación para verificar que el dato ingresado sea válido (de 9 dígitos, alfanumérico o que no se haya dejado la línea vacía)
                            if (strAux.length() != 9)
                                cout << "Longitud inválida, intente de nuevo" << '\n' << "->";
                            else if (!isAlphanumeric(strAux))
                                cout << "Debe contener solamente caracteres numéricos, intente de nuevo" << '\n'<< "->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el DNI en blanco, intente de nuevo"<<'\n'<<"->";
                        // Se repite hasta que se ingresa un dato válido
                        }while(strAux.length() != 9 || !isAlphanumeric(strAux) || strAux.empty());
                        // Checa si existe el registro en la lista de empleados
                        if(!empleadosFile.checkForExistance(strAux)){
                            cout<<"No existe un empleado con ese DNI"<<'\n';
                            // Si no existe el registro del empleado, se sale del case y vuelve al menú principal
                            break;
                        }else{
                            // Si el empleado existe manda a llamar a delData() para eliminarlo del archivo y de la lista
                            empleadosFile.delData(strAux);
                            // Se agrega el índice del empleado eliminado a la lista de disponibles
                            disponiblesFile.pushDisp(empleadosFile.getIndex());
                            // Se actualiza el archivo de disponibles con la lista actualizada
                            disponiblesFile.listToFile();
                        }
                        break;
                    case 3: // Buscar por DNI
                        // Captura de DNI
                        cout << "Ingrese DNI de nueve dígitos" << '\n' << "->";
                        do {
                            // Se captura el DNI en el string auxiliar
                            cin >> strAux;
                            // Hace una comprobación para verificar que el dato ingresado sea válido (de 9 dígitos, alfanumérico o que no se haya dejado la línea vacía)
                            if (strAux.length() != 9)
                                cout << "Longitud inválida, intente de nuevo" << '\n' << "->";
                            else if (!isAlphanumeric(strAux))
                                cout << "Debe contener solamente caracteres numéricos, intente de nuevo" << '\n'
                                     << "->";
                            else if (strAux.empty())
                                cout<<"No puede dejar el DNI en blanco, intente de nuevo"<<'\n'<<"->";
                        // Se repite hasta que se ingresa un dato válido
                        }while(strAux.length() != 9 || !isAlphanumeric(strAux));
                        // Checa si existe el registro en la lista de empleados
                        if(!empleadosFile.checkForExistance(strAux)) {
                            cout << "No existe un empleado con ese DNI" << '\n';
                            // Si no existe el registro del empleado, se sale del case y vuelve al menú principal
                            break;
                        }else{
                            // Si el empleado existe manda a llamar a findDataByDni() para imprimirlo (la impresión se efectúa dentro de la función)
                            empleadosFile.findDataByDni(strAux);
                        }
                        break;
                    case 4: // Generar lista de disponibles
                        // Se imprime la lista de disponibles con printList()
                        disponiblesFile.printList();
                        break;
                    case 5: // Salir
                        break;
                    // En caso de que se ingrese una opción inválida, se imprime un mensaje de error
                    default:
                        cout<<"Opción inválida, intente de nuevo\n->";
                }
            // El menú (ciclo) se repite hasta que se ingresa la opción 5 (salir)
            }while(opcion != 5);
        }
    /* Funciones para comprobar si una cadena es numérica, alfabética, alfanumérica, etc.
       Nótese que se usan las funciones estáticas en el principio de este código */
    /* Se usa all_of para checar si todos los caracteres de la cadena son numéricos
       y el tercer argumento de dicha función es un protocolo personalizado para hacer la comprobación (las funciones del principio) */
    bool isNumericOrPoint(const string &str){
        // Regresa verdadero si todos los caracteres de la cadena son numéricos o puntos
        return all_of(str.begin(),str.end(),isNumericOrPointChar);
    }
    bool isNumeric(const string &str){
        // Regresa verdadero si todos los caracteres de la cadena son numéricos
        return all_of(str.begin(),str.end(),::isdigit);
    }
    bool isAlphabeticOrSpace(const string &str) {
        // Regresa verdadero si todos los caracteres de la cadena son alfabéticos o espacios (no incluye Ñ)
        return all_of(str.begin(), str.end(), isAlphabethicCharacterOrSpace);
    }
    bool isAlphanumeric(const std::string& str) {
        // Regresa verdadero si todos los caracteres de la cadena son alfanuméricos (no incluye Ñ)
        return std::all_of(str.begin(), str.end(), ::isalnum);
    }
};


#endif //MENU_HPP


