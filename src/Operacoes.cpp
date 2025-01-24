#include "Operacoes.hpp"
#include "Compra.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

Operacoes::Operacoes(const std::string& nomeUsuario) : nomeUsuario(nomeUsuario) {}

void Operacoes::addCompra(const Compra& compra) {
    compras.push_back(compra);
    salvarCompras(); // Salva as compras no arquivo após adicionar
}

// Função para comparar as compras por data (ano, mês, dia)
bool compararPorData(const Compra& a, const Compra& b) {
    // Extraímos o ano, mês e dia das datas para comparação
    std::string dataA = a.getData();
    std::string dataB = b.getData();
    
    // Ano (primeiros 4 caracteres)
    int anoA = std::stoi(dataA.substr(6, 4));
    int anoB = std::stoi(dataB.substr(6, 4));
    if (anoA != anoB) return anoA < anoB;
    
    // Mês (caracteres 4-5)
    int mesA = std::stoi(dataA.substr(3, 2));
    int mesB = std::stoi(dataB.substr(3, 2));
    if (mesA != mesB) return mesA < mesB;
    
    // Dia (caracteres 0-1)
    int diaA = std::stoi(dataA.substr(0, 2));
    int diaB = std::stoi(dataB.substr(0, 2));
    return diaA < diaB;
}

void Operacoes::listarCompras() const {
    if (compras.empty()) {
        std::cout << "Nenhuma compra registrada." << std::endl;
        return;
    }

    // Ordenar as compras por data (ano, mês, dia)
    std::vector<Compra> comprasOrdenadas = compras;
    std::sort(comprasOrdenadas.begin(), comprasOrdenadas.end(), compararPorData);

    std::cout << "--- Lista de Compras ---" << std::endl;
    for (const auto& compra : comprasOrdenadas) {
        std::cout << "Valor: R$ " << std::fixed << std::setprecision(2) << compra.getValor()
                  << ", Categoria: " << compra.getCategoria()
                  << ", Data: " << compra.getData() << std::endl;
    }
}

const std::vector<Compra>& Operacoes::getCompras() const {
    return compras;
}

void Operacoes::carregarCompras() {
    std::ifstream arquivo("data/compras-" + nomeUsuario + ".txt");
    if (!arquivo.is_open()) return;

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string valorStr, categoria, data;

        std::getline(ss, valorStr, ';');
        std::getline(ss, categoria, ';');
        std::getline(ss, data, ';');

        float valor = std::stof(valorStr);
        Compra compra(valor, categoria, data);
        compras.push_back(compra);
    }
}

void Operacoes::salvarCompras() {
    std::ofstream arquivo("data/compras-" + nomeUsuario + ".txt");
    for (const auto& compra : compras) {
        arquivo << compra.getValor() << ";" << compra.getCategoria() << ";" << compra.getData() << std::endl;
    }
}

void Operacoes::menuCompras() {
    while (true) {
        std::cout << "\n--- Menu de Compras ---\n1. Adicionar compra\n2. Listar compras\n3. Logout\nEscolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();  // Limpar o buffer de entrada

        if (escolha == 1) {
            adicionarCompra();
        } else if (escolha == 2) {
            listarCompras();
        } else if (escolha == 3) {
            break;
        } else {
            std::cout << "Opção inválida!" << std::endl;
        }
    }
}

void Operacoes::adicionarCompra() {
    float valor;
    std::string categoria;
    std::cout << "Digite o valor da compra: ";
    std::cin >> valor;
    std::cin.ignore();

    // Exibir categorias para o usuário
    std::vector<std::string> categorias = Compra::obterCategorias();
    std::cout << "\nEscolha a categoria da compra:\n";
    for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << i + 1 << ". " << categorias[i] << std::endl;
    }

    int opcaoCategoria;
    std::cout << "Digite o número da categoria: ";
    std::cin >> opcaoCategoria;
    std::cin.ignore();

    if (!Compra::categoriaValida(opcaoCategoria)) {
        std::cout << "Opção inválida!" << std::endl;
        return;
    }

    categoria = categorias[opcaoCategoria - 1];

    std::string data;
    std::cout << "Digite a data da compra (formato: dd/mm/aaaa): ";
    std::getline(std::cin, data);

    Compra compra(valor, categoria, data);
    addCompra(compra);
}