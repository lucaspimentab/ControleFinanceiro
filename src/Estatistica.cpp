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
    calcularGastosPorCategoria();

    std::cout << "--- Estatísticas de Gastos ---\n";
    std::cout << "Total gasto: R$ " << totalGasto << "\n";

    for (const auto& [categoria, valor] : gastosPorCategoria) {
        float porcentagem = (valor / totalGasto) * 100;
        std::cout << "Categoria: " << categoria
                  << " - R$ " << valor
                  << " (" << std::fixed << std::setprecision(2) << porcentagem << "%)\n";
    }

    char opcao;
    std::cout << "Deseja comparar os gastos com seu salário? (S/N): ";
    std::cin >> opcao;

    if (opcao == 'S' || opcao == 's') {
        float salario;
        std::cout << "Digite o seu salário: R$ ";
        std::cin >> salario;

        if (salario > 0) {
            exibirComparacaoComSalario(salario);
        } else {
            std::cout << "Salário inválido! Não é possível calcular a comparação.\n";
        }
    }
}

void Estatistica::exibirComparacaoComSalario(float salario) const {
    std::cout << "--- Comparação com Salário ---" << std::endl;
    for (const auto& [categoria, valor] : gastosPorCategoria) {
        float porcentagemSalario = (valor / salario) * 100;
        std::cout << "Categoria: " << categoria 
                  << " - " << std::fixed << std::setprecision(2) << porcentagemSalario
                  << "% do salário" << std::endl;
    }
}

void Estatistica::calcularGastosPorCategoria() {
    gastosPorCategoria.clear(); // Limpa o mapa para evitar duplicação de valores
    totalGasto = 0.0f;          // Reinicia o total

    for (const auto& compra : compras) {
        float valor = compra.getValor();
        std::string categoria = compra.getCategoria();

        // Soma ao total e atualiza a categoria
        totalGasto += valor;
        gastosPorCategoria[categoria] += valor;
    }
}
