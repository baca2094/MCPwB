#include "camion.h"
#include <iostream>

//constructor
camion::camion(float capacidad, char leche, float min){

	setCapacidad_total(capacidad);
	setTipo_leche(leche);
	setMin_leche(min);
	setCapacidad_utilizada(0);
	setNodo_actual(1);
	setDistancia_recorrida(0);
}

//copy constructor
camion::camion(const camion &p){

	capacidad_total = p.capacidad_total;
		
	capacidad_utilizada = p.capacidad_utilizada;
		
	tipo_leche = p.tipo_leche;
		
	nodos_visitados = p.nodos_visitados;
		
	min_leche = p.min_leche;
		
	nodo_actual = p.nodo_actual;

	utilidad = p.utilidad;

	distancia_recorrida = p.distancia_recorrida;
}

void camion::setCapacidad_total(float capacidad){

	capacidad_total = capacidad;
}

void camion::setCapacidad_utilizada(float capacidad){

	capacidad_utilizada = capacidad;
}

void camion::setTipo_leche(char leche){

	tipo_leche = leche;
}

void camion::setNodos_visitados(std::vector<int> nodos){

	nodos_visitados = nodos;
}

void camion::setMin_leche(float min){

	min_leche = min;
}

void camion::setNodo_actual(int nodo){

	nodo_actual = nodo;
}

void camion::setDistancia_recorrida(float distancia){

	distancia_recorrida = distancia;
}

void camion::setUtilidad(float Utilidad){

	utilidad = Utilidad;
}

void camion::CargarCamion(float carga){

	capacidad_utilizada += carga;
}

void camion::anadirNodo(int nodo){

	nodos_visitados.push_back(nodo);
}

void camion::distanciaRecorrida(std::vector<std::vector<float>> distancias){

	for (int i = 0; i <= nodos_visitados.size(); i++){
		if (i == 0){
			distancia_recorrida += distancias[0][nodos_visitados[0]-1];
		}
		else if (i == (nodos_visitados.size())){
			distancia_recorrida += distancias[nodos_visitados[i-1]-1][0];
		}
		else {
			distancia_recorrida += distancias[nodos_visitados[i-1]-1][nodos_visitados[i]-1];
		}
	}

}