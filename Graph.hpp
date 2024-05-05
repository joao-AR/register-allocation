// Graph.h

#ifndef GRAPH_H
#define GRAPH_H
    
    // Includes necessários
    #include <iostream>
    #include <map>
    #include <set>
    using namespace std;

    struct GraphNode {
        set<int> neighbors;
        set<int> unavailable_registers;
        int reg = -1;
    };

    struct Graph {
        map<int, GraphNode> nodes;
        int k;
    };

    void print_graph(const Graph &g);
    int select_node_to_remove(const Graph &g, int qtd_reg);
#endif
