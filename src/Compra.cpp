#include "Compra.hpp"

Compra::Compra(float valor, const std::string& categoria, const std::string& data)
    : valor(valor), categoria(categoria), data(data) {}

float Compra::getValor() const {
    return valor;
}

std::string Compra::getCategoria() const {
    return categoria;
}

std::string Compra::getData() const {
    return data;
}

bool Compra::categoriaValida(int opcao) {
    static const std::vector<std::string> categorias = {
        "Alimentação", "Transporte", "Saúde", "Lazer", "Educação", "Outros"
    };
    return opcao > 0 && opcao <= static_cast<int>(categorias.size());
}

std::vector<std::string> Compra::obterCategorias() {
    return {"Alimentação", "Transporte", "Saúde", "Lazer", "Educação", "Outros"};
}
