#ifndef STACK_H
#define STACK_H
    #include <set>
    struct nodes_stack {
        int node;
        std::set<int> neighbors;
        std::set<int> unavailable_registers;
        bool possible_spill;
    };

    int get_best_register (std::set<int>& unavailable_registers, int qtd_reg);

#endif  
