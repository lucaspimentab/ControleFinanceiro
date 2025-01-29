#ifndef OPERACOES_HPP
#define OPERACOES_HPP

#include <vector>
#include <string>
#include "Compra.hpp"
#include "Categoria.hpp"

class Operacoes {
private:
    std::vector<Compra> compras; 
    std::string nomeUsuario; // Nome do usuário associado
    Categoria categoria; 
    float saldoDisponivel;  // Saldo disponível do usuário
    float salarioUsuario;   // Salário do usuário
    int diaAtual;           // Dia atual do sistema

public:
    Operacoes(float salario, float saldo, int dia);
    Operacoes(const std::string& nomeUsuario);
    double calcularGastosMensais();

    void addCompra(const Compra& compra);
    void listarCompras();
    const std::vector<Compra>& getCompras() const;

    void carregarCompras();
    void salvarCompras();
    void menuCompras();
    void adicionarCompra();

    void mudarCategorias();
    void adicionarCategoria();
    void removerCategoria();
    void listarCategorias();

    std::string getUsuario() const;  
};

#endif