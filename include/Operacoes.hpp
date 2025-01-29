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

public:
    Operacoes(const std::string& nomeUsuario);

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

    // Adicione o getter aqui
    std::string getUsuario() const;  
};

#endif