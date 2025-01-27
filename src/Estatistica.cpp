#include "Estatistica.hpp"
#include <iostream>
#include <iomanip>
#include "Sistema.hpp"        // Inclua o cabeçalho da classe Sistema
#include "Operacoes.hpp"

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

void Estatistica::exibirEstatisticas() {
    calcularGastosPorCategoria(); // Calcula os gastos por categoria

    std::cout << "--- Estatísticas de Gastos ---\n";
    float totalGasto = this->totalGasto;
    std::cout << "Total gasto: R$ " << totalGasto << "\n";
    
    // Exibindo as categorias e seus respectivos gastos
    for (const auto& categoria : gastosPorCategoria) {
        float porcentagem = (categoria.second / totalGasto) * 100;
        std::cout << "Categoria: " << categoria.first
                  << " - R$ " << categoria.second
                  << " (" << std::fixed << std::setprecision(2) << porcentagem << "%)\n";
    }

    char opcao;
    std::cout << "Deseja comparar os gastos com seu salário? (S/N): ";
    std::cin >> opcao;

    if (opcao == 'S' || opcao == 's') {
        float salario;
        std::cout << "Digite o seu salário: R$ ";
        std::cin >> salario;

        // Evitar divisão por zero
        if (salario <= 0) {
            std::cout << "Salário inválido! Não é possível calcular a comparação.\n";
        } else {
            exibirComparacaoComSalario(salario);
        }
    }
}

// Remova esta segunda definição de exibirComparacaoComSalario
// void Estatistica::exibirComparacaoComSalario(float salario) const { ...

// Apenas mantenha esta função aqui:
void Estatistica::exibirComparacaoComSalario(float salario) const {
    std::cout << "--- Comparação com Salário ---" << std::endl;
    for (const auto& [categoria, valor] : gastosPorCategoria) {
        // Evitar divisão por zero
        if (salario > 0) {
            float porcentagemSalario = (valor / salario) * 100;
            std::cout << "Categoria: " << categoria 
                      << " - " << std::fixed << std::setprecision(2) << porcentagemSalario
                      << "% do salário" << std::endl;
        } else {
            std::cout << "Salário inválido para comparação.\n";
        }
    }
}
