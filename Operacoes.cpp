#include "Operacoes.hpp"
#include "Compra.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>  // Para std::fixed e std::setprecision
#include <algorithm> // Para std::sort

Operacoes::Operacoes(const std::string& nomeUsuario) : nomeUsuario(nomeUsuario) {}

void Operacoes::addCompra(const Compra& compra) {
    compras.push_back(compra);
    salvarCompras(); // Salva as compras no arquivo após adicionar
}

bool compararPorData(const Compra& a, const Compra& b) {
    return a.getData() < b.getData();  // Supondo que a função getData() retorne uma string no formato dd/mm/aaaa
}

void Operacoes::listarCompras() const {
    if (compras.empty()) {
        std::cout << "Nenhuma compra registrada." << std::endl;
        return;
    }

    // Ordenar as compras por data antes de exibir
    std::vector<Compra> comprasOrdenadas = compras;
    std::sort(comprasOrdenadas.begin(), comprasOrdenadas.end(), compararPorData);

    std::cout << "--- Lista de Compras ---" << std::endl;
    for (const auto& compra : comprasOrdenadas) {
        std::cout << "Valor: RS " << std::fixed << std::setprecision(2) << compra.getValor()
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
