#ifndef OPERACOES_HPP
#define OPERACOES_HPP

#include <string>
#include <vector>

using namespace std;

class Operacoes {
private:
    string usuario;
    vector<string> compras;

public:
    Operacoes(const string& usuario);
    void addCompra(float valor, const string& categoria);
    void listarCompras() const;
};

#endif
