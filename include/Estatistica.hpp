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
    void calcularGastosPorCategoria();
    void exibirEstatisticas() const;
    void analisarComBaseSalario(float salario) const;

private:
    std::vector<Compra> compras;
    std::map<std::string, float> gastosPorCategoria;
    float totalGasto;

    // Funções auxiliares
    void calcularTotalGasto();
    void exibirComparacaoComSalario(float salario) const;
};

#endif