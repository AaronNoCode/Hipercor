/*ESTRUCTURAS DE DATOS II
  SECCION D03
  GRACIELA LARA LOPEZ
  217782851 Ernesto Ariel Garcia Serna
  218169878 Omar Alejandro Quiroz Trujillo
  219550494 Cesar Aaron Perez Ramirez */

#ifndef EMPLEADOSFILE_HPP
#define EMPLEADOSFILE_HPP

#include <list>
#include <string>
#include <sstream>
#include <fstream>
// Include de la clase empleado para poder usarla en el método addData, delData, etc.
#include "empleado.hpp"
// Ya que no se usa otro namespace, se usa std para no tener que escribir std::list, std::string, etc.
using namespace std;
// Clase que se encarga de manejar el archivo de empleados
class EmpleadosFile{
    // Atributos privados de la clase
private:
    // Path a los archivos de empleados y auxiliar
    string empleadosFileDir;
    string auxDir;
    // Lista que contiene todos los empleados
    list<Empleado> empleadosList;
    // Index usado para la lista de disponibles
    int index;
    // Métodos públicos de la clase
public:
    // Constructor para declarar el path a los archivos
    EmpleadosFile() {
        // Path a los archivos dentro de la carpeta backups
        empleadosFileDir = "backups/EMPLEADOS.txt";
        auxDir = "backups/AUX.txt";
    }
    // Método para agregar un empleado al archivo (apendizar)
    void addData(Empleado &empl){
        // Abre el archivo de empleados en modo append
        ofstream ofs(empleadosFileDir, ios::out | ios::app);
        // Si no se pudo abrir el archivo, lanza una excepción
        if(!ofs.is_open())
            throw ios::failure("Archivo no encontrado");
        // Hace push el empleado a la lista de empleados
        empleadosList.push_back(empl);
        // Escribe el empleado en el archivo usando el método toString()
        ofs << empl.toString()<<'\n';
    }
    // Método para eliminar un empleado del archivo (borrado lógico)
    void delData(string dni) {
        // Este index sirve para la lista de disponibles
        index = 0;
        // Busca el empleado con el dni dado
        for (auto const &iterator : empleadosList){
            // Si lo encuentra, sale del ciclo for
            if (iterator.getDni() == dni)
                break;
            else {
                // Si no lo encuentra, aumenta el index
                index++;
            }
        }
        // Abre el archivo de empleados en modo lectura
        ifstream fsEmpleadosFile(empleadosFileDir, ios::in);
        // Se crea un string para guardar cada línea del archivo
        string line;
        // Si no se pudo abrir el archivo, lanza una excepción
        if (!fsEmpleadosFile.is_open())
            throw ios::failure("Archivo no encontrado");
        // Abre un archivo auxiliar en modo escritura y truncamiento
        ofstream ofsAux(auxDir, ios::out | ios::trunc);
        // Mientras no llegue al final del archivo, lee línea por línea
        while (getline(fsEmpleadosFile, line, '\n')) {
            // Se crea un stringstream para poder leer el archivo línea por línea
            stringstream iss(line);
            // Se crea un objeto empleado para guardar la línea
            Empleado empleadoAux;
            // Se lee la línea y se guarda en empleadoAux
            iss >> empleadoAux;
            // Si el dni del empleadoAux (leído del archivo) es igual al dni del empleado que se quiere eliminar entra al condicional
            if (dni == empleadoAux.getDni()) {
                // Si el DNI del empleadoAux ya tenía un * al principio, indica que ya estaba borrado anteriormente
                if(empleadoAux.getDni()[0] == '*'){
                    cout<<"Ya está eliminado lógicamente"<<'\n';
                    // Rompe el ciclo while
                    break;
                }else{
                    // Si no, se le pone un * al principio para indicar que está borrado lógicamente
                    line[0] = '*';
                    // Imprime un mensaje en consola para indicar que se borró lógicamente y de manera correcta
                    cout<<empleadoAux.getDni()<<" Eliminado lógicamente"<<'\n';
                }
            }
            // Se escribe la línea con el asterisco escrito en el archivo auxiliar (esto es posible ya que se hizo la comprobación de que el DNI sí existiera en la lista de empleados)
            ofsAux << line << '\n';
        }
        // Se cierran los archivos
        fsEmpleadosFile.close();
        ofsAux.close();
        // AUX.txt se convierte en el archivo principal y se borra el anterior
        remove(empleadosFileDir.c_str());
        rename("backups/AUX.txt", empleadosFileDir.c_str());
    }
    /* Este método se usa para ahorrar tiempo de ejecución, ya que sólo se usa para revisar si el empleado existe en la lista (lo checa por DNI)
      No se usa en la función de arriba, se usa en el menú principal*/
    bool checkForExistance(string &dni){
        // Busca el empleado con el dni dado con un ciclo for
        for (auto const &iterator : empleadosList){
            // Si lo encuentra, regresa true
            if (iterator.getDni() == dni)
                return true;
        }
        // Si se recorre toda la lista y no se encuentra, regresa false
        return false;
    }
    // Este método es para mostrar en pantalla si el registro fue borrado lógicamente o no, si no, lo imprime
    void findDataByDni(string dni){
        // Se usa un index para indicar cuántas líneas deben leerse antes de llegar al registro deseado
        int index = 0;
        // Se busca el empleado con el dni dado con un ciclo for en la lista de empleados
        for (auto const &iterator : empleadosList){
            // Si lo encuentra, sale del ciclo for y entra en el condicional
            if(iterator.getDni() == dni){
                // Se crea un string auxiliar para guardar la línea del archivo
                string line;
                // Se abre el archivo en modo lectura
                ifstream fs(empleadosFileDir, ios::in);
                do{
                    // Se leen lineas hasta que índice sea 0 (llega a la línea donde se encuentra el registro)
                    // Esto es necesario para ir moviendo el puntero del archivo hasta el registro deseado
                    getline(fs,line,'\n');
                    // Se disminuye el index
                    index--;
                    // Si el index es menor a 0, sale del ciclo
                }while(index >= 0);
                // Si el primer caracter de la línea es un asterisco, indica que el registro está borrado lógicamente
                if (line[0] == '*')
                    // Impresión en consola para indicar que el registro está borrado lógicamente
                    cout<<"Registro borrado lógico"<<'\n';
                // Si no está borrado, imprime el registro en pantalla
                else
                    // Se imprime la línea (el empleado)
                    cout<<line<<'\n';
            // En caso de que no se encuentre el registro en la iteración, se aumenta el index
            }else {
                index++;
            }
        }
    }
    // Exclusivo para ingresarlo a la lista de disponibles
    int getIndex() const{
        // Regresa el índice
        return index;
    }
    // Toma la lista de empleados y la escribe en el archivo
    void listToFile(){
        // Se abre el archivo en modo escritura y truncamiento
        ofstream ofs(empleadosFileDir, ios::out | ios::trunc);
        // Si no se pudo abrir el archivo, lanza una excepción
        if(!ofs.is_open())
            throw ios::failure("Archivo no encontrado");
        // Se escribe la lista en el archivo
        for (auto &iterator : empleadosList){
            // En cada vuelta se escribe un empleado al archivo
            ofs << iterator << '\n';
        }
        // Se cierra el archivo
        ofs.close();
    }
    // Toma el archivo y lo escribe en la lista (sin usar, elaborado pensando en escalabilidad del programa)
    void fileToList(){
        // Se abre el archivo en modo lectura
        ifstream ifs(empleadosFileDir, ios::in);
        // Se crea un objeto empleado auxiliar para guardar cada línea del archivo en un objeto empleado
        Empleado empleadoAux;
        // Se crea un string para guardar cada línea leída del archivo
        string line;
        // Si no se pudo abrir el archivo, lanza una excepción
        if(!ifs.is_open())
            throw ios::failure("Archivo no encontrado");
        // Se lee el archivo línea por línea y se guarda en empleadoAux, para luego pushearlo a la lista
        while(getline(ifs, line,'\n')){
            // Se crea un stringstream para poder meter la línea en empleadoAux
            stringstream iss(line);
            // Se guarda el stringstream en empleadoAux usando el operador sobrecargado
            iss >> empleadoAux;
            // Se pushea el empleado a la lista de empleados
            empleadosList.push_back(empleadoAux);
        }
        // Se cierra el archivo
        ifs.close();
    }
};
#endif //EMPLEADOSFILE_HPP