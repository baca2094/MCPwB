#include "mcpwb.h"
#include <iostream>
#include <array>

// función para calcular la utilidad de cada camión
float utilidad(float capacidad_utilizada, float ganancia_leche, float distancia_recorrida){

	return ((capacidad_utilizada*ganancia_leche) - distancia_recorrida);
}
// función para calcular la utilidad de una posible solución (3 camiones en este caso)
float utilidad_grupo(std::vector<camion> camiones){
	
	float utilidad = 0;
	for (int i = 0; i < camiones.size(); i++){
		utilidad += camiones[i].getUtilidad();
	}

	return utilidad;
}

// función para encontrar la mejor solución de la población
int mejor_utilidad(float utilidades_grupos[], int size){

	float mejor = -1;
	int mejor_pos = -1;
	for (int i = 0; i < size; i++){
		if (utilidades_grupos[i] > mejor){
			mejor = utilidades_grupos[i];
			mejor_pos = i;
		}
	}
	return mejor_pos;
}

// función para resolver el problema
void mcpwb(int population_size, int iteraciones, std::vector<camion> camiones, std::string leches, std::vector<float> cantidad_leche_nodo, 
							std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches, std::vector<float> ganancias){
	
	float utilidad_cromosoma [population_size];
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
	std::vector<camion> solucion;

 	pop_actual = sol_inicial(population_size, camiones_ordenados, cantidad_leche_nodo, distancias, tipos_leches, ganancias);
	
	for (int i = 0; i < pop_actual.size(); i++){
		for (int j = 0; j < pop_actual[i].size(); j++){
			pop_actual[i][j].distanciaRecorrida(distancias);
			pop_actual[i][j].setUtilidad(utilidad(pop_actual[i][j].getCapacidad_utilizada(), ganancias[j], pop_actual[i][j].getDistancia_recorrida()));
		}
	}
	float aux_utilidad = 0;
	for (int i = 0; i < pop_actual.size(); i++){
		utilidad_cromosoma[i] = utilidad_grupo(pop_actual[i]);
	}
	float mejor_utilidad_grupo;
	int mejor_utilidad_pos;
	mejor_utilidad_pos = mejor_utilidad(utilidad_cromosoma, population_size);
	mejor_utilidad_grupo = utilidad_cromosoma[mejor_utilidad_pos];
	for (int i = 0; i < pop_actual[mejor_utilidad_pos].size(); i++){
		camion camion1 = pop_actual[mejor_utilidad_pos][i];
		solucion.push_back(camion1);
		//no entiendo por qué pop_actual[mejor_utilidad_pos][i].getUtilidad() tira bien el resultado
		//pero solucion[i].getUtilidad() no.
	}
	std::vector<int> palprint;
	std::cout << solucion[0].getUtilidad() << " " << solucion[1].getUtilidad() << 
	" " << solucion[2].getUtilidad() << " = " << mejor_utilidad_grupo << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < solucion.size(); i++){
		palprint = solucion[i].getNodos_visitados();
		std::cout << "1-";
		for (int j = 0; j < palprint.size(); j++){
			std::cout << palprint[j] << "-";
		}
		std::cout << "1 ";
		std::cout << solucion[i].getDistancia_recorrida() << " " << solucion[i].getCapacidad_utilizada() <<
		" " << solucion[i].getTipo_leche() << std::endl;
	}
	
	srand(time(NULL));
	int iteracion_actual = 1;
	float pc = 80;
	float pm = 5;
	int random1 = 0;
	int random2 = 0;
	int value1;
	int value2;
	int random_pc;
	int random_pm;
	int size;
	int gen1 = 0;
	int gen2 = 0;
	int random_cut;
	float utilidad_camion;
	std::vector<std::vector<camion>> auxiliar;
	std::vector<int> auxiliar_nodos1;
	std::vector<int> auxiliar_nodos2;
	std::vector<int> auxiliar_nodos3;
	std::vector<int> auxiliar_nodos4;
	while(iteracion_actual <= iteraciones){
		/*
		while(!pop_actual.empty()){
			size = pop_actual.size();
			gen1 = gen2;
			while (gen1 == gen2){
				if (size == 2){
					gen1 = 0;
					gen2 = 1;
				}
				else{
					gen1 = rand() % size;
					gen2 = rand() % size;
				}
			}
			random_pc = rand() % 100 + 1;
			if (random_pc <= pc){
				for (int i = 0; i < 3; i++){
					auxiliar_nodos1 = pop_actual[gen1][i].getNodos_visitados();
					auxiliar_nodos2 = pop_actual[gen2][i].getNodos_visitados();
					int size1 = auxiliar_nodos1.size();
					int size2 = auxiliar_nodos2.size();
					int min = std::min(size1, size2);
					random_cut = 0;
					while (random_cut == 0){
						random_cut = rand() % min;
					}
					for (int i = 0; i < random_cut; i++){
						auxiliar_nodos3.push_back(auxiliar_nodos1[i]);
					}
					for (int i = random_cut; i < size2; i++){
						auxiliar_nodos3.push_back(auxiliar_nodos2[i]);
					}
					for (int i = 0; i < random_cut; i++){
						auxiliar_nodos3.push_back(auxiliar_nodos2[i]);
					}
					for (int i = random_cut; i < size1; i++){
						auxiliar_nodos3.push_back(auxiliar_nodos1[i]);
					}

				}
			}
			
			

		}
		*/
		for (int i = 0; i < pop_actual.size(); i++){
			random1 = random2;
			for (int j = 0; j < pop_actual[i].size(); j++){
				random_pm = rand() % 100 + 1;
				if (random_pm <= pm){
					utilidad_camion = 0;
					auxiliar_nodos1 = pop_actual[i][j].getNodos_visitados();
					size = auxiliar_nodos1.size();
					while (random1 == random2){
						random1 = rand() % size;
						random2 = rand() % size;
					}
					value1 = auxiliar_nodos1[random1];
					value2 = auxiliar_nodos1[random2];
					auxiliar_nodos1[random1] = value2;
					auxiliar_nodos1[random2] = value1;
					pop_actual[i][j].setNodos_visitados(auxiliar_nodos1);
					pop_actual[i][j].setDistancia_recorrida(0);
					pop_actual[i][j].setCapacidad_utilizada(0);
					pop_actual[i][j].distanciaRecorrida(distancias);
					pop_actual[i][j].setUtilidad(utilidad_camion);
					for (int k = 0; k < auxiliar_nodos1.size(); k++){
						pop_actual[i][j].CargarCamion(cantidad_leche_nodo[auxiliar_nodos1[k]-1]);
					}
					pop_actual[i][j].setUtilidad((utilidad(pop_actual[i][j].getCapacidad_utilizada(), ganancias[j], pop_actual[i][j].getDistancia_recorrida())));
				}
			}
		}

		for (int i = 0; i < pop_actual.size(); i++){
			utilidad_cromosoma[i] = utilidad_grupo(pop_actual[i]);
			//std::cout << utilidad_cromosoma[i] << std::endl;
			//std::cout << mejor_utilidad_grupo << std::endl;
			if (utilidad_cromosoma[i] >= mejor_utilidad_grupo){
				mejor_utilidad_grupo = utilidad_cromosoma[i];
				mejor_utilidad_pos = i;
				camion camion1 = pop_actual[i][0];
				camion camion2 = pop_actual[i][1];
				camion camion3 = pop_actual[i][2];
				solucion[0] = camion1;
				solucion[1] = camion2;
				solucion[2] = camion3;
			}
		}
		iteracion_actual++;
	}

	std::cout << solucion[0].getUtilidad() << " " << solucion[1].getUtilidad() << 
	" " << solucion[2].getUtilidad() << " = " << mejor_utilidad_grupo << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < solucion.size(); i++){
		palprint = solucion[i].getNodos_visitados();
		std::cout << "1-";
		for (int j = 0; j < palprint.size(); j++){
			std::cout << palprint[j] << "-";
		}
		std::cout << "1 ";
		std::cout << solucion[i].getDistancia_recorrida() << " " << solucion[i].getCapacidad_utilizada() <<
		" " << solucion[i].getTipo_leche() << std::endl;
	}
}

// función para generar la población inicial
std::vector<std::vector<camion>> sol_inicial(int population_size, std::vector<camion> camiones, std::vector<float> cantidad_leche_nodo, 
											std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches_nodos, std::vector<float> ganancias){
    
	std::vector<std::vector<camion>> generacion_inicial;
	generacion_inicial.push_back(camiones);
	std::vector<camion> auxiliar_camiones;
	// se crean el resto de camiones para la solución inicial
	for (int i = 0; i < population_size -1 ; i++){
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
					random2 = rand() % 1;
					if (random2 == 0 && tipos_leches_nodos[0].empty()){
						random2 = 1;
					}
					size = tipos_leches_nodos[random2].size();
					random = rand() % size;
					if (generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches_nodos[random2][random]-1] <= generacion_inicial[i][j].getCapacidad_total()){
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
				while ((!tipos_leches_nodos[0].empty() || !tipos_leches_nodos[1].empty() || !tipos_leches_nodos[2].empty()) && max_iteraciones <= 3
				&& generacion_inicial[i][j].getCapacidad_utilizada() <= generacion_inicial[i][j].getCapacidad_total()){
					random2 = rand() % 2;
					if (random2 == 0 && tipos_leches_nodos[0].empty() ){
						if (tipos_leches_nodos[1].empty() && !tipos_leches_nodos[2].empty()){
							random2 = 2;
						}
						else {random2 = rand() % 1 + 1;}
					}
					else if (random2 == 1 && tipos_leches_nodos[1].empty() ){
						random2 = 2;
					}
					size = tipos_leches_nodos[random2].size();
					random = rand() % size;
					if (generacion_inicial[i][j].getCapacidad_utilizada() + cantidad_leche_nodo[tipos_leches_nodos[random2][random]-1] <= generacion_inicial[i][j].getCapacidad_total()){
						generacion_inicial[i][j].anadirNodo(tipos_leches_nodos[random2][random]);
						generacion_inicial[i][j].setNodo_actual(tipos_leches_nodos[random2][random]);
						generacion_inicial[i][j].CargarCamion(cantidad_leche_nodo[tipos_leches_nodos[random2][random]-1]);
						tipos_leches_nodos[random2].erase(tipos_leches_nodos[random2].begin() + random);
					}
					else {max_iteraciones++;}
				}
			}
		}
	}

	/*
	std::vector<int> palprint;
	palprint = generacion_inicial[0][0].getNodos_visitados();
	for (int i = 0; i < palprint.size(); i++){
		std::cout << palprint[i] << " ";
	}
	std::cout << std::endl;
	std::cout << generacion_inicial[0][0].getDistancia_recorrida() << std::endl;
	*/
	
	return generacion_inicial;
}

