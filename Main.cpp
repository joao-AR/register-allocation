#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <string.h>
#include <map>
#include <algorithm>
#include "Graph.hpp"
#include "Stack.hpp"
using namespace std;




int main() {
    // Vertices {V_inicio, V_fim}

    string line;
    string token;
    int g_num = -1; // Inicializa com um valor que indica nenhum grafo lido ainda
    int k;
    
    map<int, vector<int>> interference_map;
    stack<nodes_stack> stack;

    // Loop para ler linha a linha da entrada padrão
    while (getline(cin, line)) {
        istringstream iss(line);
        // Verifica se a linha começa com "Grafo"
        if (line.find("Grafo") == 0) {
            iss >> token; // Lê o primeiro token da linha
            iss >> g_num;
            
        } else if (line.find("K=") == 0) {
            iss >> token; // Lê o primeiro token da linha
            k = stoi(token.substr(2));

            cout << "Número registradores: " << k << endl;
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

    // Criar grafo incial
    Graph graph;

    for(const auto &imap : interference_map){
        int first_node = imap.first;

        const vector<int> &node_neightbors = imap.second;

        for(const auto &nn : node_neightbors ){
            graph.nodes[first_node].neighbors.insert(nn);

            // Registradores fisicos indisponiveis, pois, o nó interfere neles
            if(nn < k ){
                graph.nodes[first_node].unavailable_registers.insert(nn);
            }
        }
    }

    //Simplify Grafo e colocar na Stack
    //Nó grau < k, se tiver dois iguais remover menor registrador virtual


    //Rodar até o numero de registradores ser 2
    // for (int qtd_reg = k; qtd_reg >= 2; qtd_reg--){
        int ntr_neightbors_qtd = -1;
        bool spill;
        //Enquanto não tiver removido todos os nós do grafo e colocado na stack
        while (graph.nodes.size() != 0 ){
            // ntr: node to remove
            int ntr = select_node_to_remove(graph,k);
            // cout << "ntr: " << ntr << endl;
            // cout << "tamnho grafo: " << graph.nodes.size() << endl;
            //======Simplify Grafo e colocar na Stack======
            nodes_stack stack_node;

            stack_node.node = ntr;
            stack_node.unavailable_registers = graph.nodes[ntr].unavailable_registers;
            stack_node.neighbors = graph.nodes[ntr].neighbors;

            // Adicionar nó na pilha
            // cout << "push: " << stack_node.node << "|" << endl;
            stack.push(stack_node);

            //Remover Referencias ao nó nos outros nós antes de removelo
            for (auto &node_entry : graph.nodes) {
                GraphNode &node = node_entry.second;
                node.neighbors.erase(stack_node.node);
            }

            // Remove nó do grafo
            graph.nodes.erase(ntr);
            // cout << "erease: " << stack_node.node << "\n" << endl;
            // for (auto &un : stack_node.unavailable_registers){
            //     cout << " UV: " << un ;
            // }
            // cout << endl;
            
        }
        
            

        
        // //Todo Spill
        // graph.nodes.clear();

        //Todo logica
        //======Re-Build Grafo a partir da stack====== 

    // }
    //print_graph(graph);
    return 0;
}
