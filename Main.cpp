#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
#include <map>
#include <algorithm>
#include "Graph.hpp"
using namespace std;



int main() {
    // Vertices {V_inicio, V_fim}

    string line;
    string token;
    int g_num = -1; // Inicializa com um valor que indica nenhum grafo lido ainda
    int num_reg;
    
    map<int, vector<int>> interference_map;

    // Loop para ler linha a linha da entrada padrão
    while (getline(cin, line)) {
        istringstream iss(line);
        // Verifica se a linha começa com "Grafo"
        if (line.find("Grafo") == 0) {
            iss >> token; // Lê o primeiro token da linha
            iss >> g_num;
            
        } else if (line.find("K=") == 0) {
            iss >> token; // Lê o primeiro token da linha
            num_reg = stoi(token.substr(2));

            cout << "Número registradores: " << num_reg << endl;
        } else {
            //Linha Grafo de Interferencia

            // Usando um stringstream para dividir a string com base nos espaços
            istringstream iss(line);
            string token;
            bool first_node = false;
            int node;

            int tokenInt;
            // Lendo cada palavra separada por espaço e armazenando nos respectivos vetores
            while (iss >> token) {
                if (token.compare("-->") != 0){
                    tokenInt = stoi(token); //Converte token de string para inteiro
                    if(first_node == false){
                        node = tokenInt;
                        first_node = true;
                    }else{
                        interference_map[node].push_back(tokenInt);
                    }
                } 
            }

            
        }

    }
    // Criar grafo 
    Graph graph;

    for(const auto &imap : interference_map){
        int first_node = imap.first;

        const vector<int> &node_neightbors = imap.second;

        for(const auto &nn : node_neightbors ){
            graph.nodes[first_node].neighbors.insert(nn);
        }
    }
    print_graph(graph);
    return 0;
}
