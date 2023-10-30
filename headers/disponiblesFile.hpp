// ! Los disponibles que se vayan agregando se deben pushear al frente para que se
// ! muestren después del -1

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
using namespace std;

class DisponiblesFile{
private:
    // Lista que contiene todos los índices libres para ocupar
    list<int> disponiblesList;
    // Path del archivo LIST_DISP.txt
    string dispDir;
public:
    DisponiblesFile(){
        dispDir = "backups/LIST_DISP.txt";
        // Al principio se pushea -1 para indicar el fin de la lista de disponibles
        disponiblesList.push_front(-1);
        disponiblesList.push_front(9);
        disponiblesList.push_front(2);
        disponiblesList.push_front(0);
    }
    // Método exclusivo para mostrar en consola la lista
    void printList(){
        for (auto const &iterator : disponiblesList){
            cout << iterator;
            // Condición para prevenir la impresión de una flecha después del -1 del final
            if(iterator != disponiblesList.back())
                cout<<"->";
        }
    }
    void listToFile(){
        ofstream ofs(dispDir, ios::out | ios::trunc);
        if(!ofs.is_open())
            throw ios::failure("Archivo LIST_DISP.txt no encontrado");
        for(auto const &iterator : disponiblesList){
            ofs << iterator;
            if(iterator != disponiblesList.back())
                ofs << " -> ";
        }
    }
    void fileToList(){
        disponiblesList.clear();
        ifstream ifs(dispDir, ios::in);
        if(!ifs.is_open())
            throw ios::failure("Archivo LIST_DISP.txt no encontrado");
        int numero;
        string aux;
        while(ifs >> numero){
            disponiblesList.push_back(numero);
            ifs.ignore(3);
        }
    }
};