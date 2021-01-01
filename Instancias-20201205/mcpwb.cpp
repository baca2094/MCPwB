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
											std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches, std::vector<float> ganancias){
    
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
	int random;
	int size;
	int random2;
    std::vector<camion> reiniciar = camiones;
    std::vector<int> palprint;
	int contador = 1;
    int largo;
	int i = -1;

	int leches_A1 [tipos_leches[0].size()];
	int leches_B1 [tipos_leches[1].size()];
	int leches_C1 [tipos_leches[2].size()];
	int leches_A2 [tipos_leches[0].size()];
	int leches_B2 [tipos_leches[1].size()];
	int leches_C2 [tipos_leches[2].size()];
	
	int size_A = tipos_leches[0].size();
	int size_B = tipos_leches[1].size();
	int size_C = tipos_leches[2].size();

	std::copy(tipos_leches[0].begin(), tipos_leches[0].end(), leches_A1);
	std::copy(tipos_leches[1].begin(), tipos_leches[1].end(), leches_B1);
	std::copy(tipos_leches[2].begin(), tipos_leches[2].end(), leches_C1);

	std::copy(tipos_leches[0].begin(), tipos_leches[0].end(), leches_A2);
	std::copy(tipos_leches[1].begin(), tipos_leches[1].end(), leches_B2);
	std::copy(tipos_leches[2].begin(), tipos_leches[2].end(), leches_C2);
	
	srand(time(NULL));
	for(int i = 0; i < generacion_inicial.size(); i++) {
		
		if (i > 0){
			for (int k = 0; k < size_A; k++){
				tipos_leches[0].push_back(leches_A1[k]);
			}
			for (int k = 0; k < size_B; k++){
				tipos_leches[1].push_back(leches_B1[k]);
			}
			for (int k = 0; k < size_C; k++){
				tipos_leches[2].push_back(leches_C1[k]);
			}
		}
		for(int j = 0; j < generacion_inicial[i].size(); j++){
			if (generacion_inicial[i][j].getTipo_leche() == 'A'){
				while(generacion_inicial[i][j].getMin_leche() > generacion_inicial[i][j].getCapacidad_utilizada()){
					size = tipos_leches[0].size() - 1;
					if (size == 0){
						random = 0;
					}
					else {random = rand() % size;}
					if ((generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches[0][random]-1]) <= generacion_inicial[i][j].getCapacidad_total()){
						generacion_inicial[i][j].CargarCamion(cantidad_leche_nodo[tipos_leches[0][random]-1]);
						generacion_inicial[i][j].anadirNodo(tipos_leches[0][random]+1);
						generacion_inicial[i][j].setNodo_actual(tipos_leches[0][random]+1);
						tipos_leches[0].erase(tipos_leches[0].begin() + random);
					}
				}
			}

			else if (generacion_inicial[i][j].getTipo_leche() == 'B'){
				while(generacion_inicial[i][j].getMin_leche() > generacion_inicial[i][j].getCapacidad_utilizada()){
					random2 = rand() % 1;
					size = tipos_leches[random2].size() - 1;
					if (size == 0){
						random = 0;
					}
					else if (size < 0){ 
						random2 = (random2 == 0) ? 1: 0;
						random = rand() % size;
					}
					else {random = rand() % size;}
					if ((generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches[random2][random]-1]) <= generacion_inicial[i][j].getCapacidad_total()){
						generacion_inicial[i][j].CargarCamion(cantidad_leche_nodo[tipos_leches[random2][random]-1]);
						generacion_inicial[i][j].anadirNodo(tipos_leches[random2][random]+1);
						generacion_inicial[i][j].setNodo_actual(tipos_leches[random2][random]+1);
						tipos_leches[random2].erase(tipos_leches[random2].begin() + random);
					}
				}
			}

			else if (generacion_inicial[i][j].getTipo_leche() == 'C'){
				while(generacion_inicial[i][j].getMin_leche() > generacion_inicial[i][j].getCapacidad_utilizada()){
					random2 = rand() % 2;
					size = tipos_leches[random2].size() - 1;
					if (size == 0){random = 0;}
					else if (size < 0){
						random2 = 2;
						random = rand() % size;
						}
					else {random = rand() % size;}
					if ((generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches[random2][random]-1]) <= generacion_inicial[i][j].getCapacidad_total()){
						generacion_inicial[i][j].CargarCamion(cantidad_leche_nodo[tipos_leches[random2][random]-1]);
						generacion_inicial[i][j].anadirNodo(tipos_leches[random2][random]+1);
						generacion_inicial[i][j].setNodo_actual(tipos_leches[random2][random]+1);
						tipos_leches[random2].erase(tipos_leches[random2].begin() + random);
					}
				}
			}
		}

		int nodo;
		while(tipos_leches[0].size() > 0){
			nodo = tipos_leches[0][tipos_leches[0].size()-1];
			tipos_leches[0].pop_back();
			std::cout << nodo << std::endl;
			if ((generacion_inicial[i][0].getCapacidad_utilizada() + cantidad_leche_nodo[nodo-1]) <= generacion_inicial[i][0].getCapacidad_total()){
				generacion_inicial[i][0].CargarCamion(cantidad_leche_nodo[nodo-1]);
				generacion_inicial[i][0].anadirNodo(nodo);
				generacion_inicial[i][0].setNodo_actual(nodo);
			}
			else if ((generacion_inicial[i][1].getCapacidad_utilizada() + cantidad_leche_nodo[nodo-1]) <= generacion_inicial[i][1].getCapacidad_total()){
				generacion_inicial[i][1].CargarCamion(cantidad_leche_nodo[nodo-1]);
				generacion_inicial[i][1].anadirNodo(nodo);
				generacion_inicial[i][1].setNodo_actual(nodo);
			}
			else if ((generacion_inicial[i][2].getCapacidad_utilizada() + cantidad_leche_nodo[nodo-1]) <= generacion_inicial[i][2].getCapacidad_total()){
				generacion_inicial[i][2].CargarCamion(cantidad_leche_nodo[nodo-1]);
				generacion_inicial[i][2].anadirNodo(nodo);
				generacion_inicial[i][2].setNodo_actual(nodo);
			}
		}
		
		while(tipos_leches[1].size() > 0){
			nodo = tipos_leches[1][tipos_leches[1].size()-1];
			tipos_leches[1].pop_back();
			if ((generacion_inicial[i][1].getCapacidad_utilizada() + cantidad_leche_nodo[nodo-1]) <= generacion_inicial[i][1].getCapacidad_total()){
				generacion_inicial[i][1].CargarCamion(cantidad_leche_nodo[nodo-1]);
				generacion_inicial[i][1].anadirNodo(nodo);
				generacion_inicial[i][1].setNodo_actual(nodo);
			}
			else if ((generacion_inicial[i][2].getCapacidad_utilizada() + cantidad_leche_nodo[nodo-1]) <= generacion_inicial[i][2].getCapacidad_total()){
				generacion_inicial[i][2].CargarCamion(cantidad_leche_nodo[nodo-1]);
				generacion_inicial[i][2].anadirNodo(nodo);
				generacion_inicial[i][2].setNodo_actual(nodo);
			}
		}

		while(tipos_leches[2].size() > 0){
			nodo = tipos_leches[2][tipos_leches[2].size()-1];
			tipos_leches[2].pop_back();
			generacion_inicial[i][2].CargarCamion(cantidad_leche_nodo[nodo-1]);
			generacion_inicial[i][2].anadirNodo(nodo);
			generacion_inicial[i][2].setNodo_actual(nodo);
			
		}
		
		std::vector<int> aiuda;
		for (int k = 0; k < 3; k++){
			aiuda = generacion_inicial[i][k].getNodos_visitados();
			std::cout << i << " " << generacion_inicial[i][k].getTipo_leche() << generacion_inicial[i][k].getCapacidad_utilizada() << std::endl;
			for (int l = 0; l < aiuda.size(); l++){
				std::cout << aiuda[l] << " ";
			}
			std::cout << std::endl;
		}


	}

	/*
	for (int i = 0; i < auxiliar_camiones.size(); i++){

		palprint = auxiliar_generacion_inicial[i][j].getNodos_visitados();
		largo = palprint.size();
		if (i == 0){
			std::cout << "Los nodos para el camion de leche A son: " << std::endl;
			for (int j = 0; j < largo; j++){
				std::cout << palprint[j] << " ";
			}
		}

		else if (i == 1){
			std::cout << "Los nodos para el camion de leche B son: " << std::endl;
			for (int j = 0; j < largo; j++){
				std::cout << palprint[j] << " ";
			}
		}

		else if (i == 2){
			std::cout << "Los nodos para el camion de leche C son: " << std::endl;
			for (int j = 0; j < largo; j++){
				std::cout << palprint[j] << " ";
			}
		}

		std::cout << std::endl;
		std::cout << auxiliar_generacion_inicial[i][j].getCapacidad_utilizada() << std::endl;
	}
	*/

	return generacion_inicial;

}
