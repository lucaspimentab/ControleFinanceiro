#include "Estatistica.hpp"
#include <iostream>
#include <iomanip>

Estatistica::Estatistica(const std::vector<Compra>& compras) 
    : compras(compras), totalGasto(0.0f) {}

void Estatistica::calcularTotalGasto() {
    totalGasto = 0.0f;
    for (const auto& compra : compras) {
        totalGasto += compra.getValor();
    }
}

void Estatistica::calcularGastosPorCategoria() {
    gastosPorCategoria.clear();
    for (const auto& compra : compras) {
        gastosPorCategoria[compra.getCategoria()] += compra.getValor();
    }
    calcularTotalGasto();
}

void Estatistica::exibirEstatisticas() const {
    if (gastosPorCategoria.empty()) {
        std::cout << "Nenhum gasto registrado para exibir estatísticas." << std::endl;
        return;
    }

    std::cout << "--- Estatísticas de Gastos ---" << std::endl;
    for (const auto& [categoria, valor] : gastosPorCategoria) {
        float porcentagem = (valor / totalGasto) * 100;
        std::cout << "Categoria: " << categoria 
                  << " - R$ " << std::fixed << std::setprecision(2) << valor
                  << " (" << porcentagem << "%)" << std::endl;
    }
    std::cout << "Total gasto: R$ " << std::fixed << std::setprecision(2) << totalGasto << std::endl;
}

void Estatistica::analisarComBaseSalario(float salario) const {
    if (gastosPorCategoria.empty() || salario <= 0) {
        std::cout << "Nenhum dado para análise ou salário inválido." << std::endl;
        return;
    }

    std::cout << "--- Comparação com Salário ---" << std::endl;
    for (const auto& [categoria, valor] : gastosPorCategoria) {
        float porcentagemSalario = (valor / salario) * 100;
        std::cout << "Categoria: " << categoria 
                  << " - " << std::fixed << std::setprecision(2) << porcentagemSalario
                  << "% do salário" << std::endl;
    }
}

void Estatistica::exibirComparacaoComSalario(float salario) const {
    std::cout << "Deseja comparar os gastos com seu salário? (S/N): ";
    char opcao;
    std::cin >> opcao;
    if (opcao == 'S' || opcao == 's') {
        std::cout << "Digite seu salário: R$ ";
        std::cin >> salario;
        analisarComBaseSalario(salario);
    }
}