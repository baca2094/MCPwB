#ifndef CAMION_H
#define CAMION_H
#include <vector>

class camion {
	private:
		float capacidad_total;
		
		float capacidad_utilizada;
		
		char tipo_leche;
		
		std::vector<int> nodos_visitados;
		
		float min_leche;
		
		int nodo_actual;

		float distancia_recorrida;

		float utilidad;
	
	public:
		//constructor
		camion(float capacidad, char leche, float min);
		
		//copy constructor
		camion(const camion &p);

		//funciones Set
		void setCapacidad_total(float capacidad);

		void setCapacidad_utilizada(float capacidad);

		void setTipo_leche(char leche);

		void setNodos_visitados(std::vector<int> nodo);

		void setMin_leche(float min);

		void setNodo_actual(int nodo);

		void setDistancia_recorrida(float distancia);

		void setGanancia_leche (float ganancia);

		void setGanancia_total (float ganancia);

		void setUtilidad (float Utilidad);
		
		//funciones Get
		float getCapacidad_total() {return capacidad_total;}
		
		float getCapacidad_utilizada() {return capacidad_utilizada;}
		
		char getTipo_leche() {return tipo_leche;}
		
		std::vector<int> getNodos_visitados() {return nodos_visitados;}
		
		float getMin_leche() {return min_leche;}
		
		int getNodo_actual() {return nodo_actual;}

		float getDistancia_recorrida() {return distancia_recorrida;}

		float getUtilidad() {return utilidad;}
		//función de carga
		void CargarCamion(float carga);
		//añadir nodo a los visitados
		void anadirNodo(int nodo);
		//determinar distancia recorrida
		void distanciaRecorrida(std::vector<std::vector<float>>);
};

#endif
