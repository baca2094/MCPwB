#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector> 
#include <math.h>
#include "camion.h"
#include "mcpwb.h"
#include "distancies.h"

using namespace std; 
  
// driver code 
int main(int argc, char** argv) 
{ 
    // filestream variable file 
    fstream file; 
    string word, t, q, filename; 
    int main_cont = 1; // contador para saber qué línea del archivo se está leyendo (que sección en realidad)
    int capacidades_flag = 0; //bandera (en realidad contador) para leer todas las capacidades de los camiones
    int requerimientos_flag = 0; // bandera (en realidad contador) para leer todos los requerimientos de leche de la fábrica
    int ganancias_flag = 0; // bandera (en realidad contador) para leer todas las ganancias por tipo de leche de la fábrica
    int nodos_flag = 0; // bandera que permite saber qué sección del nodo se está leyendo (n°, posición x, posición y, tipo de leche del nodo o cantidad producida)
    int n_camiones; //variable que guarda la cantidad de camiones del problema
    int n_leches; //variable que guarda cuántos tipos de leche hay en el problema
    int n_nodos; //variable que guarda cuántos nodos tiene el problema
    int nodo_actual; //nodo actual que se está guardando
    std::vector<float> capacidades_camiones; // vector que guarda las capacidades de los camiones
    std::vector<float> requerimientos_leches; // vector que guarda los requerimientos por tipo de leche de la fábrica
    std::vector<float> ganancias_leches; // vector que guarda las ganancias que ofrece cada tipo de leche
    std::vector<std::vector<float>> posiciones_nodos; // matriz (vector de vectores) con las posiciones (x,y) de cada nodo
    std::vector<float> auxiliar_posiciones; // vector auxiliar para guardar las posiciones de los nodos en la matriz anterior
    std::vector<string> tipo_leche_nodo; // vector que guarda el tipo de leche que produce cada nodo
    std::vector<float> cantidad_leche_nodo; // vector que guarda la cantidad de leche que produce cada nodo
    std::vector<std::vector<float>> distancias; //matriz para guardar las distancias entre los nodos
    std::vector<int> nodos_leche_A; // nodos que producen leche tipo A
    std::vector<int> nodos_leche_B; // nodos que producen leche tipo B
    std::vector<int> nodos_leche_C; // nodos que producen leche tipo C
    string leches = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // string que contiene todos los posibles tipos de leches en orden de calidad
    std::vector<camion> camiones; // vector que contiene todos los camiones que participan del problema
    std::vector<std::vector<int>> vector_vector_leche; // vector ordenado de los tipos de leche (el primer elemento tiene los nodos con leche tipo A, 
                                                       // el segundo con nodos de leche tipo B, y así)
    std::vector<camion> solucion;
  
    // filename of the file 
    filename = argv[1]; 
  
    // opening file 
    file.open(filename.c_str()); 
  
    // extracting words from the file 
    while (file >> word) 
    { 
        if (main_cont == 1){
            //se está leyendo la cantidad de camiones
            n_camiones = stoi(word);
            main_cont++;
        }

        else if (main_cont == 2){
            //se guardan la capacidad de los camiones
            capacidades_camiones.push_back(stof(word));
            capacidades_flag++;
            if (capacidades_flag == n_camiones){

                main_cont++;
            }
        }

        else if (main_cont == 3){
            //se ve cuántos tipos de leche hay
            n_leches = stoi(word);
            main_cont++;
        }

        else if (main_cont == 4){
            //se guardan los requerimientos de cada leche de la fábrica
            requerimientos_leches.push_back(stof(word));
            requerimientos_flag++;
            if(requerimientos_flag == n_leches){

                main_cont++;
            }
        }
        
        else if (main_cont == 5){
            //se guardan las ganancias por tipo de leche
            ganancias_leches.push_back(stof(word));
            ganancias_flag++;
            if (ganancias_flag == n_leches){

                main_cont++;
            }
        }

        else if (main_cont == 6){
            //se ve cuántos nodos hay
            n_nodos = stoi(word);
            main_cont++;
        }

        else if (main_cont == 7){

            if (nodos_flag == 0){

                nodo_actual = stoi(word) - 1;
                nodos_flag++;
            }

            else if (nodos_flag == 1){
                //se guarda la posición "x" en el vector auxiliar
                auxiliar_posiciones.push_back(stof(word));
                nodos_flag++;
            }

            else if (nodos_flag == 2){
                //se guarda la posición "y" en el nodo auxiliar y luego se guarda este vector en la matriz de posiciones 
                auxiliar_posiciones.push_back(stof(word));
                posiciones_nodos.push_back(auxiliar_posiciones);
                auxiliar_posiciones.clear();
                nodos_flag++;
            }

            else if (nodos_flag == 3){
                //se guarda el tipo de leche que produce el nodo
                tipo_leche_nodo.push_back(word);
                nodos_flag++;

                if (word == "A"){

                    nodos_leche_A.push_back(nodo_actual);
                }

                else if (word == "B") {

                    nodos_leche_B.push_back(nodo_actual);
                }

                else if (word == "C"){

                    nodos_leche_C.push_back(nodo_actual);
                }
            }

            else if (nodos_flag == 4){
                //se guarda la cantidad de leche que produce el nodo
                cantidad_leche_nodo.push_back(stof(word));
                nodos_flag = 0;
            }
        }
    }
    float max_q, max_leche;
    int index_max_q, index_max_leche;
    while (!capacidades_camiones.empty()){
        
        max_q = -1;
        max_leche = -1;
        for (int i = 0; i < capacidades_camiones.size(); i++){
            if (capacidades_camiones[i] > max_q){
                max_q = capacidades_camiones[i];
                index_max_q = i;
            }
        }
        for (int i = 0; i < requerimientos_leches.size(); i++){
            if (requerimientos_leches[i] > max_leche){
                max_leche = requerimientos_leches[i];
                index_max_leche = i;
            }
        }

        camion kamion(max_q, leches[index_max_leche], max_leche);
        camiones.push_back(kamion);

        capacidades_camiones.erase(capacidades_camiones.begin() + index_max_q);
        requerimientos_leches.erase(requerimientos_leches.begin()+ index_max_leche);
    }

    vector_vector_leche.push_back(nodos_leche_A);
    vector_vector_leche.push_back(nodos_leche_B);
    vector_vector_leche.push_back(nodos_leche_C);
//std::vector<camion> mcpwb(int population_size, int iteraciones, std::vector<camion> camiones, string leches, std::vector<float> cantidad_leche_nodo, 
//                          std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches, std::vector<float> ganancias)
    
    solucion = mcpwb(20, 10, camiones, leches, cantidad_leche_nodo, distancias, vector_vector_leche, ganancias_leches);

/*
    distancias = distancies(posiciones_nodos);

    for (int i = 0; i < distancias.size(); i++) { 
        for (int j = 0; j < distancias[i].size(); j++) 
            cout << distancias[i][j] << " "; 
        cout << endl; 
    }
    cout << n_camiones << endl;
    for(int i=0; i < capacidades_camiones.size(); ++i)
        cout << capacidades_camiones[i] << endl;
    for(int i=0; i < requerimientos_leches.size(); ++i)
        cout << requerimientos_leches[i] << endl;
    for(int i=0; i < ganancias_leches.size(); ++i)
        cout << ganancias_leches[i] << endl;
    for (int i = 0; i < posiciones_nodos.size(); i++) { 
        for (int j = 0; j < posiciones_nodos[i].size(); j++) 
            cout << posiciones_nodos[i][j] << " "; 
        cout << endl; 
    }  
    for(int i=0; i < cantidad_leche_nodo.size(); ++i)
        cout << cantidad_leche_nodo[i] << endl;
    for(int i=0; i < tipo_leche_nodo.size(); ++i)
        cout << tipo_leche_nodo[i] << endl;
    

    for (int i = 0; i < camiones.size(); i++){
        cout << camiones[i].getCapacidad_total() << endl;
        cout << camiones[i].getTipo_leche() << endl;
        cout << camiones[i].getMin_leche() << endl;
        cout << camiones[i].getCapacidad_utilizada() << endl;

    }
    */
    return 0; 
} 
