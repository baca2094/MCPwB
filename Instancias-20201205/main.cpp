#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector> 
using namespace std; 
  
// driver code 
int main(int argc, char** argv){ 
    
    // filestream variable file 
    fstream file; 
    string filename, word;
    int n_camiones, n_nodos, contador = 0, n_leches, contador_camiones = 0, contador_leches = 0, contador_nodos = 0, contador_nodos2 = 0, 
    general_flag = 1, flag_camiones = 0, flag_leches = 0, flag_ganancias = 0, flag_nodos;
  	
    // filename of the file 
    filename = argv[1]; 
  
    // opening file 
    file.open(filename.c_str()); 
  
    // extracting words from the file 
/*
    int contador_camiones = 0;
    int contador_leches = 0;
    int contador_nodos = 0;
    int contador_nodos2 = 0;
    int general_flag = 1;
    int flag_camiones = 0;
    int flag_leches = 0;
    int flag_ganancias = 0;
    int flag_nodos;
*/
    vector<float> capacidades;
    vector<float> req_leches;
    vector<vector<int>> nodos_por_leche;
    vector<float> ganancias_leches;
    vector<float> produccion_nodos;
    string leches = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (file > word){
        // displaying content 
        //cout << word << endl;
        
        if (general_flag == 1 || (flag_camiones == 1 && contador < 2) || (flag_leches == 1 && contador < 4)){

        	contador += 1;

        }
        
        if (contador == 1 && flag_camiones == 0){

         	n_camiones = stoi(word);
         	flag_camiones = 1;
         	general_flag = 0;
         	//float capacidades [n_camiones];
        }

        if (contador == 2 && flag_camiones == 1){

        	capacidades.push_back(stof(word));
        	contador_camiones += 1;

        	if (contador_camiones >= n_camiones){

        		flag_camiones = 0;
        		general_flag = 1;
        	}
        } 

        if (contador == 3){

        	n_leches = stoi(word);
        	flag_leches = 1;
        	general_flag = 0;
        	//float req_leches [n_leches];
        	//vector <int> nodos_por_leche[n_leches];
        }

        if (contador == 4 && flag_leches == 1){

        	req_leches.push_back(stof(word));
        	contador_leches += 1;

        	if (contador_leches >= n_leches){

        		general_flag = 1;
        		contador_leches = 0;
        		//float ganancias_leches [n_leches];

        	}
        }

        if (contador == 5 && flag_leches == 1){

        	general_flag = 0;
        	ganancias_leches.push_back(stof(word));
        	contador_leches += 1;

        	if(contador_leches >= n_leches){

        		flag_leches = 0;
        		general_flag = 1;
        		flag_nodos = 1;
        	}
        }

        if (contador == 6 && flag_nodos == 1){

        	int n_nodos = stoi(word);
        	int distancias_nodos [n_nodos][n_nodos];
        	int coordenadas_nodos [n_nodos][2];
        	//float produccion_nodos [n_nodos];

        }

        if (contador == 7 && flag_nodos == 1){

        	general_flag = 0;

        	if (contador_nodos2 == 0){

        		contador_nodos2 += 1;
        	}

        	else if (contador_nodos2 == 1){

        		coordenadas_nodos [contador_nodos][0] = stof(word);
        		contador_nodos2 += 1;
        	}

        	else if (contador_nodos2 == 2){

        		coordenadas_nodos [contador_nodos][1] = stof(word);
        		contador_nodos2 += 1;
        	}

        	else if (contador_nodos2 == 3){

        		contador_nodos2 += 1;
        		if (contador_nodos != 0){
        			for(int i = 0; i < leches.length(); i++) {

        				if (leches.at(i) == word){

        					nodos_por_leche[i].push_back(contador_nodos);
        					contador_nodos2 += 1;
        					break;

        				}

					}
        		}
        	}

        	else if (contador_nodos2 == 4){

        		contador_nodos2 = 0;
        		if (contador_nodos != 0){
        			produccion_nodos[contador_nodos-1] = stof(word);
        		}
        		contador_nodos += 1;
        	}

        }
    } 
    
    file.close();


    return 0; 
} 
