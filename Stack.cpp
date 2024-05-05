#include "Stack.hpp"
using namespace std;
#include <iostream>
int get_best_register (set<int>& unavailable_registers, int qtd_reg){
    int reg = 0;
    // cout << "Não POdi-> ";
    // for(auto &red : unavailable_registers){
    //     cout << red << " ";
    // }
    cout << endl; 

    while (reg < qtd_reg){
        if(unavailable_registers.count(reg) == 0 ){
            return reg;
        }else{
            reg++;
        }
    }
    reg = -1;
    return reg;
}