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
int main(int argc, char** argv){ 
    
    // filestream variable file 
    fstream file; 
    string filename, word;
    int main_cont = 1;
  	int n_camiones;
	std::vector<float> capacidades_camiones;
	capacidades_camiones.reserve(3);
	int auxiliar_pos = 0;
	int n_leches;
	std::vector<float> ganancias_leche;
	ganancias_leche.reserve(3);
	int n_nodos;
	std::vector<int> nodos;
	int nodos_flag = 0;
	int nodo_actual;
	std::vector<std::vector<float>> posiciones_nodos;
	std::vector<float> requerimientos_leches;
	requerimientos_leches.reserve(3);
	std::vector<std::vector<int>> tipos_leches_nodos(3);
	std::vector<float> cantidad_leche;
	std::vector<std::vector<float>> distancias;
	std::vector<camion> camiones;
	string tipos_leches = "ABC";
	std::vector<float> auxiliar_posiciones;
	auxiliar_posiciones.reserve(2);
    // filename of the file 
    filename = argv[1]; 
  
    // opening file 
    file.open(filename.c_str()); 
	
    while (file >> word){
		if (main_cont == 1){
            //se está leyendo la cantidad de camiones
            n_camiones = stoi(word);
            main_cont++;
        }

        else if (main_cont == 2){
            //se guardan la capacidad de los camiones
            capacidades_camiones.push_back(stof(word));
			auxiliar_pos++;
            if (auxiliar_pos == n_camiones){
                main_cont++;
				auxiliar_pos = 0;
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
            auxiliar_pos++;
            if(auxiliar_pos == n_leches){
				auxiliar_pos = 0;
                main_cont++;
            }
        }
        
        else if (main_cont == 5){
            //se guardan las ganancias por tipo de leche
            ganancias_leche.push_back(stof(word));
            auxiliar_pos++;
            if (auxiliar_pos == n_leches){
				auxiliar_pos = 0;
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
                nodo_actual = stoi(word);
                nodos_flag++;
            }

            else if (nodos_flag == 1){
                //se guarda la posición "x" del nodo
				auxiliar_posiciones.push_back(stof(word));
                nodos_flag++;
            }

            else if (nodos_flag == 2){
                //se guarda la posición "y" del nodo
				auxiliar_posiciones.push_back(stof(word));
                posiciones_nodos.push_back(auxiliar_posiciones);
                auxiliar_posiciones.clear();
                nodos_flag++;
            }

            else if (nodos_flag == 3){
                //se guarda el nodo en su grupo de leche
                if (word == "A"){
					tipos_leches_nodos[0].push_back(nodo_actual);
                }
				else if (word == "B"){
					tipos_leches_nodos[1].push_back(nodo_actual);
				}
				else if (word == "C"){
					tipos_leches_nodos[2].push_back(nodo_actual);
				}
				nodos_flag++;
                
            }

            else if (nodos_flag == 4){
                //se guarda la cantidad de leche que produce el nodo
                cantidad_leche.push_back(stof(word));
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
		//camion(float capacidad, char leche, float min, float ganancia);
        camion kamion(max_q, tipos_leches[index_max_leche], max_leche);
        camiones.push_back(kamion);

        capacidades_camiones.erase(capacidades_camiones.begin() + index_max_q);
        requerimientos_leches[index_max_leche] = 0;
    }

	distancias = distancies(posiciones_nodos);
	mcpwb(10, 1, camiones, tipos_leches, cantidad_leche, distancias, tipos_leches_nodos, ganancias_leche);
    
    
	return 0; 
} 
