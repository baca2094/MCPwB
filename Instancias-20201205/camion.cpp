#include "camion.h"

//constructor
camion::camion(float capacidad, char leche, float min){

	setCapacidad_total(capacidad);
	setTipo_leche(leche);
	setMin_leche(min);
	setCapacidad_utilizada();
	setNodo_actual(1);
}

//copy constructor
camion::camion(const camion &p){

	capacidad_total = p.capacidad_total;
		
	capacidad_utilizada = p.capacidad_utilizada;
		
	tipo_leche = p.tipo_leche;
		
	nodos_visitados = p.nodos_visitados;
		
	min_leche = p.min_leche;
		
	nodo_actual = p.nodo_actual;
}

void camion::setCapacidad_total(float capacidad){

	capacidad_total = capacidad;
}

void camion::setCapacidad_utilizada(){

	capacidad_utilizada = 0;
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

void camion::CargarCamion(float carga){

	capacidad_utilizada += carga;
}

void camion::anadirNodo(int nodo){

	nodos_visitados.push_back(nodo);
}