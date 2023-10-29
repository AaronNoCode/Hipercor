// ! Menú principal
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "../headers/empleado.hpp"
#include "../headers/empleadosFile.hpp"

using namespace std;
void menuPrincipal(){
    short opcion;
    do{
        system("cls");
        cout << "\t.:Menu principal:.\n1.-Agregar\n2.-Eliminar\n3.-Buscar por DNI\n4.-Generar lista de disponibles\n5.-Salir\n->";
        cin >> opcion;
        switch(opcion){
            case 1: // Agregar
                break;
            case 2: // Eliminar
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

int main(){
    Empleado e;
    EmpleadosFile empleadoFile;
    string dni = "63920323";
    Empleado e1, e2, e3;
    e1.setDni("43920323");
    e2.setDni("53920323");
    e3.setDni("63920323");
    e1.setNombre("Jorge");
    e2.setNombre("Jorge");
    e3.setNombre("Jorge");
    e1.setCargo("Jefe");
    e2.setCargo("Jefe");
    e3.setCargo("Jefe");
    e1.setEdad(20);
    e2.setEdad(20);
    e3.setEdad(20);
    e1.setSueldo(2000);
    e2.setSueldo(2000);
    e3.setSueldo(2000);
    e1.setFechaDeContratacion(Fecha(1,1,2020));
    e2.setFechaDeContratacion(Fecha(1,1,2020));
    e3.setFechaDeContratacion(Fecha(1,1,2020));
    empleadoFile.addData(e1);
    empleadoFile.addData(e2);
    empleadoFile.addData(e3);

    empleadoFile.delData("63920323");
    /*menuPrincipal();*/
    return 0;
}