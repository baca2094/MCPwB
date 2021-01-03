#include "mcpwb.h"
#include <iostream>
#include <array>
std::vector<camion> mcpwb(int population_size, int iteraciones, std::vector<camion> camiones, std::string leches, std::vector<float> cantidad_leche_nodo, 
							std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches, std::vector<float> ganancias){
	
	float pc = 0.8;
	float pm = 0.05;
	int iteracion_actual = 1;
	std::vector<camion> camiones_ordenados;
	for (int i = 0; i < leches.length(); i++){
		if (!camiones.empty()){
			for (int j = 0; j < camiones.size(); j++){

				if (camiones[j].getTipo_leche() == leches[i]){
					camiones_ordenados.push_back(camiones[j]);
					camiones.erase(camiones.begin() + j);
					break;
				}

			}
		}
		else {break;}
	}

	std::vector<std::vector<camion>> pop_actual;
	std::vector<camion> pop_actual1;
 	pop_actual = sol_inicial(population_size, camiones_ordenados, cantidad_leche_nodo, distancias, tipos_leches, ganancias);
	
	pop_actual1.push_back(pop_actual[0][0]);
	pop_actual1.push_back(pop_actual[0][1]);
	pop_actual1.push_back(pop_actual[0][2]);
	/*while(iteracion_actual <= iteraciones){

		std::vector<camion> aux_camiones;

	}
	*/

	return pop_actual1;
}

std::vector<std::vector<camion>> sol_inicial(int population_size, std::vector<camion> camiones, std::vector<float> cantidad_leche_nodo, 
											std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches_nodos, std::vector<float> ganancias){
    
	std::vector<std::vector<camion>> generacion_inicial;
	generacion_inicial.push_back(camiones);
	std::vector<camion> auxiliar_camiones;
	for (int i = 0; i < population_size ; i++){
		camion camion1 = camiones[0];
		camion camion2 = camiones[1];
		camion camion3 = camiones[2];
		auxiliar_camiones.push_back(camion1);
		auxiliar_camiones.push_back(camion2);
		auxiliar_camiones.push_back(camion3);
		generacion_inicial.push_back(auxiliar_camiones);
		auxiliar_camiones.clear();
	}
	int size;
	int random;
	int random2;
	int leches_A1 [tipos_leches_nodos[0].size()];
	int leches_B1 [tipos_leches_nodos[1].size()];
	int leches_C1 [tipos_leches_nodos[2].size()];
	
	int size_A = tipos_leches_nodos[0].size();
	int size_B = tipos_leches_nodos[1].size();
	int size_C = tipos_leches_nodos[2].size();

	std::copy(tipos_leches_nodos[0].begin(), tipos_leches_nodos[0].end(), leches_A1);
	std::copy(tipos_leches_nodos[1].begin(), tipos_leches_nodos[1].end(), leches_B1);
	std::copy(tipos_leches_nodos[2].begin(), tipos_leches_nodos[2].end(), leches_C1);
	srand(time(NULL));
	int max_iteraciones = 0;
	for (int i = 0; i < generacion_inicial.size(); i++){
		if (i > 0){
			for (int k = 0; k < size_A; k++){
				tipos_leches_nodos[0].push_back(leches_A1[k]);
			}
			for (int k = 0; k < size_B; k++){
				tipos_leches_nodos[1].push_back(leches_B1[k]);
			}
			for (int k = 0; k < size_C; k++){
				tipos_leches_nodos[2].push_back(leches_C1[k]);
			}
		}
		for (int j = 0; j < generacion_inicial[i].size(); j++){
			if (j == 0){
				max_iteraciones = 0;
				while((generacion_inicial[i][j].getCapacidad_utilizada() < generacion_inicial[i][j].getCapacidad_total()) 
				&& !tipos_leches_nodos[0].empty() && max_iteraciones < 3){
					size = tipos_leches_nodos[0].size();
					if (size == 0){
						random = 0;
					}
					else {random = rand() % size;}
					
					if (generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches_nodos[0][random]-1] <= generacion_inicial[i][j].getCapacidad_total()){
						generacion_inicial[i][j].anadirNodo(tipos_leches_nodos[0][random]);
						generacion_inicial[i][j].setNodo_actual(tipos_leches_nodos[0][random]);
						generacion_inicial[i][j].CargarCamion(cantidad_leche_nodo[tipos_leches_nodos[0][random]-1]);
						tipos_leches_nodos[0].erase(tipos_leches_nodos[0].begin() + random);
					}
					else {max_iteraciones++;}
				}
			}

			else if (j == 1){
				max_iteraciones = 0;
				while ((!tipos_leches_nodos[0].empty() || !tipos_leches_nodos[1].empty()) && max_iteraciones <= 3
				&& generacion_inicial[i][j].getCapacidad_utilizada() <= generacion_inicial[i][j].getCapacidad_total()){
					std::cout << "entré a b" << std::endl;
					random2 = rand() % 1;
					size = tipos_leches_nodos[random2].size();
					if (size == 0){
						random = 0;
					}
					else {random = rand() % size;}
					if (generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches_nodos[random2][random]-1] <= generacion_inicial[i][j].getCapacidad_total()){
						std::cout << "entra aqui conchjetumare" << std::endl;
						generacion_inicial[i][j].anadirNodo(tipos_leches_nodos[random2][random]);
						generacion_inicial[i][j].setNodo_actual(tipos_leches_nodos[random2][random]);
						generacion_inicial[i][j].CargarCamion(cantidad_leche_nodo[tipos_leches_nodos[random2][random]-1]);
						tipos_leches_nodos[random2].erase(tipos_leches_nodos[random2].begin() + random);
					}
					else {max_iteraciones++;}
				}
			}
			else if (j == 2){
				max_iteraciones = 0;
				while ((!tipos_leches_nodos[0].empty() || !tipos_leches_nodos[1].empty() || !tipos_leches_nodos[2].empty()) && max_iteraciones == 3
				&& generacion_inicial[i][j].getCapacidad_utilizada() <= generacion_inicial[i][j].getCapacidad_total()){
					std::cout << "entra aqui conchjetumare1" << std::endl;
					random2 = rand() % 2;
					size = tipos_leches_nodos[random2].size();
					if (size == 0){random = 0;}
					else if (size < 0){
						for(int k = 0; k < tipos_leches_nodos.size(); k++){
							if (!tipos_leches_nodos[k].empty()){
								random2 = k;
								if (tipos_leches_nodos[random2].size() -1 == 0){
									random = 0;
								}
								else {
									size = tipos_leches_nodos[random2].size() - 1;
									random = rand() % size;									
								}
							}
						}
					}
					else {random = rand() % size;}
					if (generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches_nodos[random2][random]-1] <= generacion_inicial[i][j].getCapacidad_total()){
						generacion_inicial[i][j].anadirNodo(tipos_leches_nodos[random2][random]);
						generacion_inicial[i][j].setNodo_actual(tipos_leches_nodos[random2][random]);
						generacion_inicial[i][j].CargarCamion(cantidad_leche_nodo[tipos_leches_nodos[random2][random]-1]);
						tipos_leches_nodos[random2].erase(tipos_leches_nodos[random2].begin() + random);
						std::cout << "entra aqui conchjetumare" << std::endl;
					}
					else {max_iteraciones++;}
				}
			}
		}
	}
	std::cout << "llegué al final" << std::endl;
	std::vector<int> palprint;
	for (int i = 0; i < generacion_inicial.size(); i++){
		for (int j = 0; j < generacion_inicial[i].size(); j++){
			std::cout << generacion_inicial[i][j].getCapacidad_utilizada() << std::endl;
			std::cout << generacion_inicial[i][j].getCapacidad_total() << std::endl;
			palprint = generacion_inicial[i][j].getNodos_visitados();
			for (int k = 0; k < palprint.size(); k++){
				std::cout << palprint[k] << " ";
			}
		std::cout << std::endl;
		}
	}
	
	return generacion_inicial;

}
