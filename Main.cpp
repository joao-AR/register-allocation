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

    vector<pair<int, int>> allocations;
    string line;
    string token;
    int g_num = -1; // Inicializa com um valor que indica nenhum grafo lido ainda
    int k;

    map<int, vector<int>> interference_map;
    stack<nodes_stack> stack;
    Graph graph;
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

            // cout << "Número registradores: " << k << endl;
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

    cout << "Graph " << g_num << " -> Physical Registers: " << k << endl;
    cout << "----------------------------------------" << endl; 

    //Rodar até o numero de registradores ser 2
    for (int qtd_reg = k; qtd_reg >= 2; qtd_reg--){
        cout << "----------------------------------------" << endl; 
        cout << "K = " << qtd_reg <<  "\n" << endl; 

        //======Criar grafo incial======
        for(const auto &imap : interference_map){
            int first_node = imap.first;

            const vector<int> &node_neightbors = imap.second;

            for(const auto &nn : node_neightbors ){
                graph.nodes[first_node].neighbors.insert(nn);

                // Registradores fisicos indisponiveis, pois, o nó interfere neles
                if(nn < qtd_reg ){
                    
                    
                    graph.nodes[first_node].unavailable_registers.insert(nn);
                }

                cout << "reg: " << nn;
                cout << "NP -> ";
                for(auto &red : graph.nodes[first_node].unavailable_registers){
                        cout << red << " ";
                }
                cout << endl;
            }
        }

        int ntr_neightbors_qtd = -1;
        bool spill;
        //Enquanto não tiver removido todos os nós do grafo e colocado na stack
        while (graph.nodes.size() != 0 ){
            // ntr: node to remove
            int ntr = select_node_to_remove(graph,qtd_reg);

            //======Simplify Grafo e colocar na Stack======
            nodes_stack stack_node;

            stack_node.node = ntr;
            stack_node.unavailable_registers = graph.nodes[ntr].unavailable_registers;
            stack_node.neighbors = graph.nodes[ntr].neighbors;
            
            cout << "Push: " << stack_node.node;

            if(stack_node.neighbors.size() >= qtd_reg ){//Spill
                cout << " *";
            }        
            cout << endl;
            // Adicionar nó na pilha
            stack.push(stack_node);

            //Remover Referencias ao nó nos outros nós antes de removelo
            for (auto &node_entry : graph.nodes) {
                GraphNode &node = node_entry.second;
                node.neighbors.erase(stack_node.node);
            }

            // Remove nó do grafo
            graph.nodes.erase(ntr);
            
        }

        //======Re-construir Grafo dando pop na Stack======
        vector<pair<int, int>> registers;

        while(stack.size() != 0){
            int node = stack.top().node;
            // cout << "stack size: " << stack.size() << endl;
            // cout << "node: " << node << endl;
            //Pansando os dados da stack para o grafo
            graph.nodes[node].neighbors = stack.top().neighbors;
            graph.nodes[node].unavailable_registers = stack.top().unavailable_registers;
            
             // atualizando os registradores não disponiveis
            for(auto &reg : registers){
                if(graph.nodes[node].neighbors.count(reg.first) > 0){
                    graph.nodes[node].unavailable_registers.insert(reg.second);
                }
            }
            graph.nodes[node].reg = get_best_register(graph.nodes[node].unavailable_registers, qtd_reg);
            
            // cout << endl;
            cout << "Pop: "<< node << " -> ";
            if(graph.nodes[node].reg >= 0 ){
                cout << graph.nodes[node].reg << endl;
            
            }else if(graph.nodes[node].reg == -1){
                cout << "NO COLOR AVAILABLE" << endl;
                allocations.push_back(make_pair(qtd_reg,-1));
                break;
            }
            stack.pop(); 
            registers.push_back(make_pair(node,graph.nodes[node].reg ));
        }
            allocations.push_back(make_pair(qtd_reg,1));

        // graph.nodes.clear();
    }
    // cout << "----------------------------------------" << endl; 
    // cout << "----------------------------------------" << endl; 
    // for(auto &aloc : allocations){
    //     cout << "Graph " << g_num << " -> K = " <<  aloc.first;
    //     if(aloc.second == -1){
    //         cout << ": SPILL" << endl;
    //     }else{
    //         cout << ": Successful Allocation" << endl;
    //     }
    // }
    // print_graph(graph);
    return 0;
}
