#ifndef OPERACOES_HPP
#define OPERACOES_HPP

#include <vector>
#include "Compra.hpp" // Certifique-se de incluir o cabeçalho correto

class Operacoes {
private:
    std::vector<Compra> compras; // Agora a classe Compra será reconhecida
    std::string nomeUsuario;

public:
    Operacoes(const std::string& nomeUsuario);

    void addCompra(const Compra& compra);
    void listarCompras() const;
    const std::vector<Compra>& getCompras() const;

    void carregarCompras();
    void salvarCompras();
};

#endif
