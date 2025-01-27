#ifndef ESTATISTICA_HPP
#define ESTATISTICA_HPP

#include <vector>
#include <string>
#include <map>
#include "Compra.hpp"

class Estatistica {
public:
    Estatistica(const std::vector<Compra>& compras);

    // Funções principais
    void calcularGastosPorCategoria();         // Calcula os gastos por categoria
    void exibirEstatisticas();                 // Exibe as estatísticas gerais
    void analisarComBaseSalario(float salario) const; // Analisa os gastos com base no salário
    void exibirComparacaoComSalario(float salario) const; // Exibe comparação com o salário

private:
    std::vector<Compra> compras;               // Lista de compras
    std::map<std::string, float> gastosPorCategoria; // Mapa de categoria -> valor gasto
    float totalGasto;                          // Total gasto pelo usuário

    // Funções auxiliares
    void calcularTotalGasto();                 // Calcula o total gasto
};

#endif