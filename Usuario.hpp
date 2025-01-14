#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>

using namespace std;

class Usuario {
private:
    string nome;
    string senha;

public:
    Usuario(const string& nome, const string& senha);
    string criarUsuario() const;
    static void salvarUsuario(const string& usuario, const string& arquivo = "data/usuarios.txt");
    static vector<string> carregarUsuarios(const string& arquivo = "data/usuarios.txt");
    static bool validarUsuario(const string& nome, const string& senha, const vector<string>& usuarios);
};

#endif