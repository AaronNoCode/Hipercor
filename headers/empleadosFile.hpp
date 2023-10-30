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
    string empleadosFileDir;
    string auxDir;
    list<Empleado> empleadosList;
    int index;
public:
    EmpleadosFile() {
        empleadosFileDir = "backups/EMPLEADOS.txt";
        auxDir = "backups/AUX.txt";
    }
    void addData(Empleado empl){
        ofstream ofs(empleadosFileDir, ios::out | ios::app);
        if(!ofs.is_open())
            throw ios::failure("Archivo no encontrado");
        empleadosList.push_back(empl);
        listToFile();
    }
    void delData(string dni) {
        index = 0;
        for (auto const &iterator : empleadosList){
            if (iterator.getDni() == dni)
                break;
            else {
                index++;
            }
        }
        fstream fsEmpleadosFile(empleadosFileDir, ios::in | ios::out);
        string line;
        if (!fsEmpleadosFile.is_open())
            throw ios::failure("Archivo no encontrado");
        ofstream ofsAux(auxDir, ios::out | ios::trunc);
        while (getline(fsEmpleadosFile, line, '\n')) {
            stringstream iss(line);
            Empleado empleadoAux;
            iss >> empleadoAux;
            empleadoAux.popBackDni();
            if (dni == empleadoAux.getDni()) {
                if(empleadoAux.getDni()[0] == '*'){
                    cout<<"Ya está eliminado lógicamente"<<'\n';
                    break;
                }else{
                    line[0] = '*';
                    cout<<empleadoAux.getDni()<<" Eliminado lógicamente"<<'\n';
                }
                iss.str(line);
            }

            ofsAux << line << '\n';
        }
        fsEmpleadosFile.close();
        ofsAux.close();
        // AUX.txt se convierte en el archivo principal
        remove(empleadosFileDir.c_str());
        rename("backups/AUX.txt", empleadosFileDir.c_str());
    }
    bool checkForExistance(string &dni){
        for (auto const &iterator : empleadosList){
            if (iterator.getDni() == dni)
                return true;
        }
        return false;
    }
    void findDataByDni(string dni){
        int index = 0; //0
        for (auto const &iterator : empleadosList){
            if(iterator.getDni() == dni){
                string line;
                ifstream fs(empleadosFileDir, ios::in);
                do{
                    getline(fs,line,'\n');
                    index--;
                }while(index >= 0);
                if (line[0] == '*')
                    cout<<"Registro borrado lógico"<<'\n';
                else
                    cout<<line<<'\n';
            }else {
                index++;
            }
        }
    }
    int getIndex() const{
        return index;
    }
    void listToFile(){
        ofstream ofs(empleadosFileDir, ios::out | ios::trunc);
        if(!ofs.is_open())
            throw ios::failure("Archivo no encontrado");
        for (auto &iterator : empleadosList){
            ofs << iterator << '\n';
        }
        ofs.close();
    }
    void fileToList(){
        ifstream ifs(empleadosFileDir, ios::in);
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