#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>  // Para std::fixed e std::setprecision
#include <algorithm> // Para std::sort
#include "Usuario.hpp"
#include "Operacoes.hpp"
#include "Compra.hpp"
#include "Relatorio.hpp"

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

            // Carregar os usuários existentes para verificação
            vector<string> usuarios = Usuario::carregarUsuarios("data/usuarios.txt");

            // Verifica se o nome do usuário já existe
            bool usuarioExistente = false;
            for (const auto& u : usuarios) {
                stringstream ss(u);
                string nomeArquivo;
                getline(ss, nomeArquivo, ';');
                
                if (nomeArquivo == nome) {
                    usuarioExistente = true;
                    break;
                }
            }

            if (usuarioExistente) {
                cout << "Usuário já existente. Tente outro nome." << endl;
            } else {
                // Criar e salvar o novo usuário
                Usuario novoUsuario(nome, senha);
                Usuario::salvarUsuario(novoUsuario.criarUsuario(), "data/usuarios.txt");
            }
        } else if (opcao == 2) {
            string nome, senha;
            cout << "Digite o nome do usuário: ";
            getline(cin, nome);
            cout << "Digite a senha do usuário: ";
            getline(cin, senha);

            // Carregar os usuários e verificar se o login é válido
            vector<string> usuarios = Usuario::carregarUsuarios("data/usuarios.txt");
            if (usuarios.empty()) {
                cout << "Nenhum usuário cadastrado ainda." << endl;
                continue;
            }

            if (Usuario::validarUsuario(nome, senha, usuarios)) {
                cout << "Bem-vindo, " << nome << "!" << endl;
                Operacoes operacoes(nome);

                // Carregar as compras do arquivo quando o usuário logar
                operacoes.carregarCompras();

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

                        // Exibir as categorias para o usuário escolher
                        vector<string> categorias = Compra::obterCategorias();
                        cout << "\nEscolha a categoria da compra:\n";
                        for (size_t i = 0; i < categorias.size(); ++i) {  // Alteração aqui: use size_t
                            cout << i + 1 << ". " << categorias[i] << endl;
                        }

                        int opcaoCategoria;
                        cout << "Digite o número da categoria: ";
                        cin >> opcaoCategoria;
                        cin.ignore();

                        // Verificar se a opção escolhida é válida
                        if (!Compra::categoriaValida(opcaoCategoria)) {
                            cout << "Opção inválida!" << endl;
                            continue;
                        }

                        categoria = categorias[opcaoCategoria - 1];

                        string data;
                        cout << "Digite a data da compra (formato: dd/mm/aaaa): ";
                        getline(cin, data);

                        // Criar a compra e adicionar à lista
                        Compra compra(valor, categoria, data);
                        operacoes.addCompra(compra); // Agora passando a instância de Compra
                    } else if (escolha == 2) {
                        // Listar as compras
                        operacoes.listarCompras();

                        // Perguntar se o usuário deseja gerar um relatório
                        cout << "\nVocê deseja gerar um relatório mensal ou anual? (1 para mensal, 2 para anual, 0 para não gerar): ";
                        int relatorioEscolha;
                        cin >> relatorioEscolha;
                        cin.ignore();

                        if (relatorioEscolha == 1) {
                            // Relatório mensal
                            int mes, ano;
                            cout << "Digite o mês (1-12): ";
                            cin >> mes;
                            cout << "Digite o ano: ";
                            cin >> ano;
                            cin.ignore();

                            Relatorio::gerarRelatorioMensal(operacoes.getCompras(), mes, ano);
                        } else if (relatorioEscolha == 2) {
                            // Relatório anual
                            int ano;
                            cout << "Digite o ano: ";
                            cin >> ano;
                            cin.ignore();

                            Relatorio::gerarRelatorioAnual(operacoes.getCompras(), ano);
                        } else {
                            cout << "Não foi gerado nenhum relatório." << endl;
                        }
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
