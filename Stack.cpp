#include "Stack.hpp"
using namespace std;

int get_best_register (set<int>& unavailable_registers, int qtd_reg){
    int reg = 0;

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