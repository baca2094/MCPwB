float calcular_distancia(float x1, float x2, float y1, float y2){

	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

std::vector<std::vector<float>> distancies(std::vector<std::vector<float>> v){

	std::vector<std::vector<float>> distancias;
	std::vector<float> auxiliar;
	float x, y;

	for (int i = 0; i < v.size(); i++) {

		x = v[i][0];
		y = v[i][1];

        for (int j = 0; j < v.size(); j++) {

        	auxiliar.push_back(calcular_distancia(x,v[j][0],y,v[j][1]));
        }

        distancias.push_back(auxiliar);
        auxiliar.clear();
	}

	return distancias;
}
