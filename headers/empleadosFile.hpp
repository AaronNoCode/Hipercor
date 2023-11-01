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
#include "empleado.hpp"
using namespace std;
class EmpleadosFile{
private:
    string empleadosFileDir;
    string auxDir;
    // Lista que contiene todos los empleados
    list<Empleado> empleadosList;
    int index;
public:
    EmpleadosFile() {
        // Path a los archivos
        empleadosFileDir = "backups/EMPLEADOS.txt";
        auxDir = "backups/AUX.txt";
    }
    void addData(Empleado &empl){
        // Abre el archivo de empleados en modo append
        ofstream ofs(empleadosFileDir, ios::out | ios::app);
        // Si no se pudo abrir el archivo, lanza una excepción
        if(!ofs.is_open())
            throw ios::failure("Archivo no encontrado");
        // Hace push el empleado a la lista
        empleadosList.push_back(empl);
        // Escribe la lista en el archivo
        ofs << empl.toString()<<'\n';
    }
    void delData(string dni) {
        // Este index sirve para la lista de disponibles
        index = 0;
        // Busca el empleado con el dni dado
        for (auto const &iterator : empleadosList){
            if (iterator.getDni() == dni)
                break;
            else {
                // Si no lo encuentra, aumenta el index
                index++;
            }
        }
        // Abre el archivo de empleados en modo lectura
        ifstream fsEmpleadosFile(empleadosFileDir, ios::in);
        string line;
        // Si no se pudo abrir el archivo, lanza una excepción
        if (!fsEmpleadosFile.is_open())
            throw ios::failure("Archivo no encontrado");
        // Abre un archivo auxiliar en modo escritura y truncamiento
        ofstream ofsAux(auxDir, ios::out | ios::trunc);
        while (getline(fsEmpleadosFile, line, '\n')) {
            // Se crea un stringstream para poder leer el archivo línea por línea
            stringstream iss(line);
            Empleado empleadoAux;
            // Se lee la línea y se guarda en empleadoAux
            iss >> empleadoAux;
            // Si el dni del empleadoAux es igual al dni del empleado que se quiere eliminar
            if (dni == empleadoAux.getDni()) {
                // Si el DNI del empleadoAux ya tenía un * al principio, indica que ya estaba borrado anteriormente
                if(empleadoAux.getDni()[0] == '*'){
                    cout<<"Ya está eliminado lógicamente"<<'\n';
                    break;
                }else{
                    // Si no, se le pone un * al principio para indicar que está borrado lógicamente
                    line[0] = '*';
                    cout<<empleadoAux.getDni()<<" Eliminado lógicamente"<<'\n';
                }
            }
            // Se escribe la línea en el archivo auxiliar
            ofsAux << line << '\n';
        }
        // Se cierran los archivos
        fsEmpleadosFile.close();
        ofsAux.close();
        // AUX.txt se convierte en el archivo principal y se borra el anterior
        remove(empleadosFileDir.c_str());
        rename("backups/AUX.txt", empleadosFileDir.c_str());
    }
    // Este método se usa para ahorrar tiempo de ejecución, ya que sólo se usa para revisar si el empleado existe en la lista (lo checa por DNI)
    bool checkForExistance(string &dni){
        for (auto const &iterator : empleadosList){
            if (iterator.getDni() == dni)
                return true;
        }
        // Si no lo encuentra, regresa false
        return false;
    }
    // Este método es para mostrar en pantalla si el registro fue borrado lógicamente o no, si no, lo imprime
    void findDataByDni(string dni){
        // Se usa un index para indicar cuántas líneas deben leerse antes de llegar al registro deseado
        int index = 0;
        for (auto const &iterator : empleadosList){
            if(iterator.getDni() == dni){
                string line;
                // Se abre el archivo en modo lectura
                ifstream fs(empleadosFileDir, ios::in);
                do{
                    // Se leen lineas hasta que índice sea 0
                    getline(fs,line,'\n');
                    index--;
                }while(index >= 0);
                if (line[0] == '*')
                    cout<<"Registro borrado lógico"<<'\n';
                else
                    // Se imprime la línea (el empleado)
                    cout<<line<<'\n';
            // En caso de que no se encuentre el registro, se aumenta el index
            }else {
                index++;
            }
        }
    }
    // Exclusivo para ingresarlo a la lista de disponibles
    int getIndex() const{
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
            ofs << iterator << '\n';
        }
        // Se cierra el archivo
        ofs.close();
    }
    // Toma el archivo y lo escribe en la lista (sin usar, elaborado pensando en escalabilidad del programa)
    void fileToList(){
        // Se abre el archivo en modo lectura
        ifstream ifs(empleadosFileDir, ios::in);
        Empleado empleadoAux;
        string line;
        // Si no se pudo abrir el archivo, lanza una excepción
        if(!ifs.is_open())
            throw ios::failure("Archivo no encontrado");
        // Se lee el archivo línea por línea y se guarda en empleadoAux, para luego pushearlo a la lista
        while(getline(ifs, line,'\n')){
            stringstream iss(line);
            iss >> empleadoAux;
            empleadosList.push_back(empleadoAux);
        }
        // Se cierra el archivo
        ifs.close();
    }
};
#endif