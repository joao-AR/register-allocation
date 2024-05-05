// Graph.cpp
using namespace std;
#include "Graph.hpp"
#include "Stack.hpp"

// Função para imprimir o grafo de interferência
void print_graph(const Graph &g) {
    cout << "Grafo de Interferência:" <<  endl;
    for (const auto &node : g.nodes) {
        cout << "Nó " << node.first << ": ";
        for (const int &neighbor : node.second.neighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

//Seleciona o nó mais adequado para remover e retorna
int select_node_to_remove(const Graph &g, int qtd_reg){
    int ntr = -1;
    int ntr_neightbors_qtd = -1; 

    for (const auto &node : g.nodes){
            nodes_stack stack_node; 
            int node_value = node.first; 
            int node_neightbors_qtd = node.second.neighbors.size();

            // GRAU < K
            if(node_neightbors_qtd < qtd_reg ){
                //Se o Grau do Nó de remoção for igual ao Grau do Nó atual
                if(ntr_neightbors_qtd == node_neightbors_qtd ){
                    //Pegar o de numero menor
                    if(node_value < ntr){
                        ntr = node_value;
                        ntr_neightbors_qtd = node_neightbors_qtd;
                    }
                }else{
                    ntr_neightbors_qtd = node_neightbors_qtd;
                    ntr = node_value;
                }
            
            }else{
                if(ntr_neightbors_qtd >= qtd_reg || ntr_neightbors_qtd == -1 ){
                    // Pegar o nó com a maior quantidade de vizinhos
                    if(ntr_neightbors_qtd < node_neightbors_qtd){
                        ntr = node_value;
                        ntr_neightbors_qtd = node_neightbors_qtd;
                    
                    //Pegar o Nó de menor valor
                    }else if(ntr_neightbors_qtd == node_neightbors_qtd){
                        if(node_value < ntr){
                            ntr = node_value;
                            ntr_neightbors_qtd = node_neightbors_qtd;
                        }
                    }
                }
            }
    }

    return ntr; 
}