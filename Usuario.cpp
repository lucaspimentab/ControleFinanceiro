#include "Usuario.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Usuario::Usuario(const string& nome, const string& senha) : nome(nome), senha(senha) {}

string Usuario::criarUsuario() const {
    return nome + ";" + senha;
}

void Usuario::salvarUsuario(const string& usuario, const string& arquivo) {
    try {
        // Tenta abrir o arquivo no modo append
        ofstream file(arquivo, ios::app);
        if (!file.is_open()) {
            throw runtime_error("Não foi possível abrir o arquivo para escrita.");
        }

        // Escreve o novo usuário no arquivo
        file << usuario << endl;
        file.close();

        cout << "Usuário salvo com sucesso!" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao salvar o usuário: " << e.what() << endl;
    }
}

vector<string> Usuario::carregarUsuarios(const string& arquivo) {
    vector<string> usuarios;
    ifstream file(arquivo);

    if (!file.is_open()) {
        return usuarios;
    }

    string linha;
    while (getline(file, linha)) {
        usuarios.push_back(linha);
    }

    file.close();
    return usuarios;
}

bool Usuario::validarUsuario(const string& nome, const string& senha, const vector<string>& usuarios) {
    for (const auto& u : usuarios) {
        stringstream ss(u);
        string nomeArquivo, senhaArquivo;
        getline(ss, nomeArquivo, ';');
        getline(ss, senhaArquivo, ';');

        if (nomeArquivo == nome && senhaArquivo == senha) {
            return true;
        }
    }
    return false;
}