#ifndef COMPRA_HPP
#define COMPRA_HPP

#include <string>
#include <vector>

class Compra {
private:
    float valor;
    std::string categoria;
    std::string data;

public:
    Compra(float valor, const std::string& categoria, const std::string& data);

    float getValor() const;
    std::string getCategoria() const;
    std::string getData() const;

    static bool categoriaValida(int opcao);
    static std::vector<std::string> obterCategorias(); // Adicionado
};

#endif
