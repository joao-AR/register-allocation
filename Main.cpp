#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line;
    std::string token;
    int g_num = -1; // Inicializa com um valor que indica nenhum grafo lido ainda
    int num_reg;

    // Loop para ler linha a linha da entrada padrão
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        // Verifica se a linha começa com "Grafo"
        if (line.find("Grafo") == 0) {
            iss >> token; // Lê o primeiro token da linha
            iss >> g_num;
            
        } else if (line.find("K=") == 0) {
            iss >> token; // Lê o primeiro token da linha
            num_reg = std::stoi(token.substr(2));

            std::cout << "Número do grafo: " << num_reg << std::endl;
        } else {
            // Se não é uma linha começando com "Grafo" ou "K=", apenas imprime a linha
            std::cout << line << std::endl;
        }
    }

    return 0;
}
