#ifndef EMPLEADOSFILE_HPP
#define EMPLEADOSFILE_HPP
//Tú te encargas de ponerle el salto de línea al final de los registros
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include "../headers/empleado.hpp"
using namespace std;
class EmpleadosFile{
private:
    string fileDir;
    string auxDir;
    list<Empleado> empleadosList;
public:
    EmpleadosFile() {
        fileDir = "backups/EMPLEADOS.txt";
        auxDir = "backups/AUX.txt";
    }
    void addData(Empleado &empl){
        ofstream ofs(fileDir, ios::out | ios::app);
        if(!ofs.is_open())
            throw ios::failure("Archivo no encontrado");
        empleadosList.push_back(empl);
        listToFile();
    }
    void delData(string dni) {
        fstream fs(fileDir, ios::in | ios::out);
        string line;
        int index = 0;
        bool empleadosListUpdated = false;
        if (!fs.is_open())
            throw ios::failure("Archivo no encontrado");
        ofstream ofs(auxDir, ios::out | ios::trunc);
        while (getline(fs, line, '\n')) {
            stringstream iss(line);
            Empleado empleadoAux;
            iss >> empleadoAux;

            if (dni == empleadoAux.getDni()) {
                if(empleadoAux.getDni()[0] == '*'){
                    cout<<"Eliminado lógicamente"<<'\n';
                    break;
                }
                line[0] = '*';
                iss.str(line);
            }
            ofs << line <<'\n';
        }
        fs.close();
        ofs.close();
    }
    void findDataByDni(){

    }
    void listToFile(){
        ofstream ofs(fileDir, ios::out | ios::trunc);
        if(!ofs.is_open())
            throw ios::failure("Archivo no encontrado");
        for (auto &iterator : empleadosList){
            ofs << iterator << '\n';
        }
        ofs.close();
    }
    void fileToList(){
        ifstream ifs(fileDir, ios::in);
        Empleado empleadoAux;
        string line;
        if(!ifs.is_open())
            throw ios::failure("Archivo no encontrado");
        while(getline(ifs, line,'\n')){
            stringstream iss(line);
            iss >> empleadoAux;
            empleadosList.push_back(empleadoAux);
        }
        ifs.close();
    }
};
#endif