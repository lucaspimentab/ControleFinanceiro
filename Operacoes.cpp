#include "Operacoes.hpp"
#include <iostream>
#include <iomanip>

Operacoes::Operacoes(const string& usuario) : usuario(usuario) {}

void Operacoes::addCompra(float valor, const string& categoria) {
    compras.push_back("Valor: " + to_string(valor) + ", Categoria: " + categoria);
    cout << "Compra adicionada: " << valor << " - " << categoria << endl;
}

void Operacoes::listarCompras() const {
    if (compras.empty()) {
        cout << "Nenhuma compra registrada." << endl;
        return;
    }

    cout << "Compras registradas:" << endl;
    for (const auto& compra : compras) {
        cout << compra << endl;
    }
}