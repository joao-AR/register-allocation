// Graph.cpp
using namespace std;
#include "Graph.hpp"

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