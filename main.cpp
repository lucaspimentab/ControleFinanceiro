#include <iostream>
#include "Usuario.hpp"
#include "Operacoes.hpp"

using namespace std;

void menuPrincipal() {
    cout << "--- Bem-vindo ao Sistema de Controle Financeiro ---" << endl;

    while (true) {
        cout << "\nMenu:\n1. Criar usuário\n2. Fazer login\n3. Sair\nEscolha uma opção: ";
        int opcao;
        cin >> opcao;
        cin.ignore(); // Limpar o buffer de entrada

        if (opcao == 1) {
            string nome, senha;
            cout << "Digite o nome do usuário: ";
            getline(cin, nome);
            cout << "Digite a senha do usuário: ";
            getline(cin, senha);

            Usuario novoUsuario(nome, senha);
            // Passar o caminho correto do arquivo para salvar o usuário
            Usuario::salvarUsuario(novoUsuario.criarUsuario(), "data/usuarios.txt");
        } else if (opcao == 2) {
            string nome, senha;
            cout << "Digite o nome do usuário: ";
            getline(cin, nome);
            cout << "Digite a senha do usuário: ";
            getline(cin, senha);

            // Passar o caminho correto do arquivo para carregar os usuários
            vector<string> usuarios = Usuario::carregarUsuarios("data/usuarios.txt");
            if (usuarios.empty()) {
                cout << "Nenhum usuário cadastrado ainda." << endl;
                continue;
            }

            if (Usuario::validarUsuario(nome, senha, usuarios)) {
                cout << "Bem-vindo, " << nome << "!" << endl;
                Operacoes operacoes(nome);

                while (true) {
                    cout << "\n--- Menu de Compras ---\n1. Adicionar compra\n2. Listar compras\n3. Logout\nEscolha uma opção: ";
                    int escolha;
                    cin >> escolha;
                    cin.ignore();

                    if (escolha == 1) {
                        float valor;
                        string categoria;
                        cout << "Digite o valor da compra: ";
                        cin >> valor;
                        cin.ignore();
                        cout << "Digite a categoria da compra: ";
                        getline(cin, categoria);
                        operacoes.addCompra(valor, categoria);
                    } else if (escolha == 2) {
                        operacoes.listarCompras();
                    } else if (escolha == 3) {
                        break;
                    } else {
                        cout << "Opção inválida!" << endl;
                    }
                }
            } else {
                cout << "Usuário ou senha incorretos!" << endl;
            }
        } else if (opcao == 3) {
            cout << "Saindo... Até mais!" << endl;
            break;
        } else {
            cout << "Opção inválida!" << endl;
        }
    }
}

int main() {
    menuPrincipal();
    return 0;  
}
