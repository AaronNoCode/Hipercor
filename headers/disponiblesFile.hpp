/*ESTRUCTURAS DE DATOS II
  SECCION D03
  GRACIELA LARA LOPEZ
  217782851 Ernesto Ariel Garcia Serna
  218169878 Omar Alejandro Quiroz Trujillo
  219550494 Cesar Aaron Perez Ramirez */

#ifndef DISPONIBLESFILE_HPP
#define DISPONIBLESFILE_HPP
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
    }
    //Método para pushear un elemento a la lista
    void pushDisp(int num){
        disponiblesList.push_front(num);
    }
    // Método exclusivo para mostrar en consola la lista
    void printList(){
        for (auto const &iterator : disponiblesList){
            cout << iterator;
            // Condición para prevenir la impresión de una flecha después del -1 del final
            if(iterator != disponiblesList.back())
                cout<<"->";
        }
        // Salto de línea para separar la lista de la siguiente impresión
        cout<<'\n';
    }
    // Método para pasar la lista al archivo
    void listToFile(){
        // Se abre el archivo en modo trunc para sobreescribir el contenido
        ofstream ofs(dispDir, ios::out | ios::trunc);
        // Se verifica que el archivo se haya abierto correctamente
        if(!ofs.is_open())
            throw ios::failure("Archivo LIST_DISP.txt no encontrado");
        // Se itera sobre la lista y se escribe en el archivo
        for(auto const &iterator : disponiblesList){
            ofs << iterator;
            // Condición para prevenir la impresión de una flecha después del -1 del final
            if(iterator != disponiblesList.back())
                ofs << " -> ";
        }
    }
    // Método para pasar el archivo a la lista (escalabilidad del programa)
    void fileToList(){
        // Se limpia la lista para evitar duplicados
        disponiblesList.clear();
        // Se abre el archivo en modo lectura
        ifstream ifs(dispDir, ios::in);
        // Se verifica que el archivo se haya abierto correctamente
        if(!ifs.is_open())
            throw ios::failure("Archivo LIST_DISP.txt no encontrado");
        int numero;
        string aux;
        // Se lee el archivo y se pushea cada número a la lista
        while(ifs >> numero){
            // Se pusha el número a la lista
            disponiblesList.push_back(numero);
            // Se ignora la flecha (->) para evitar errores
            ifs.ignore(3);
        }
    }
};
#endif //DISPONIBLESFILE_HPP