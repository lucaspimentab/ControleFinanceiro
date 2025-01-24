#ifndef OPERACOES_HPP
#define OPERACOES_HPP

#include <vector>
#include "Compra.hpp" 

class Operacoes {
private:
    std::vector<Compra> compras; 
    std::string nomeUsuario;

public:
    Operacoes(const std::string& nomeUsuario);

    void addCompra(const Compra& compra);
    void listarCompras() const;
    const std::vector<Compra>& getCompras() const;

    void carregarCompras();
    void salvarCompras();

    void menuCompras();  
    void adicionarCompra();  
};

#endif
