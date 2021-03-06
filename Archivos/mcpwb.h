#ifndef MCPWB_H
#define MCPWB_H
#include <vector> 
#include <string>
#include "camion.h"

void mcpwb(int population_size, int iteraciones, std::vector<camion> camiones, std::string leches, std::vector<float> cantidad_leche_nodo, 
							std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches, std::vector<float> ganancias);

std::vector<std::vector<camion>> sol_inicial(int population_size, std::vector<camion> camiones, std::vector<float> cantidad_leche_nodo, 
											std::vector<std::vector<float>> distancias, std::vector<std::vector<int>> tipos_leches, std::vector<float> ganancias);

float utilidad(float capacidad_utilizada, float ganancia_leche, float distancia_recorrida);

float utilidad_grupo(std::vector<camion> camiones);

int mejor_utilidad(float utilidades_grupos[], int size);

std::vector<int> encontrar_duplicados(int poblacion, std::vector<int> nodos);

bool leche(std::vector<std::vector<int>> tipos_leches, char tipo, int nodo);

std::vector<int> diferencia(int poblacion, std::vector<int> nodos1, std::vector<int> nodos2, char tipo, std::vector<std::vector<int>> tipos_leches);

#endif