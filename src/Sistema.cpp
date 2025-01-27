#include <iostream>
#include "Sistema.hpp"
#include "Usuario.hpp"
#include "Operacoes.hpp"
#include "Relatorio.hpp"
#include "Estatistica.hpp"

void Sistema::iniciar() {
    while (true) {
        exibirMenuPrincipal();
    }
}

void Sistema::exibirMenuPrincipal() {
    std::cout << "--- Bem-vindo ao Sistema de Controle Financeiro ---\n";
    std::cout << "1. Criar usuário\n2. Fazer login\n3. Sair\nEscolha uma opção: ";
    
    int opcao;
    std::cin >> opcao;
    std::cin.ignore(); // Limpar o buffer de entrada

    if (opcao == 1) {
        criarUsuario();
    } else if (opcao == 2) {
        fazerLogin();
    } else if (opcao == 3) {
        std::cout << "Saindo... Até mais!\n";
        exit(0); // Saída do programa
    } else {
        std::cout << "Opção inválida!\n";
    }
}

void Sistema::criarUsuario() {
    std::string nome, senha;
    std::cout << "Digite o nome do novo usuário: ";
    std::getline(std::cin, nome);
    std::cout << "Digite a senha: ";
    std::getline(std::cin, senha);

    // Carregar os usuários existentes
    std::vector<std::string> usuarios = Usuario::carregarUsuarios("data/usuarios.txt");

    // Verificar se o usuário já existe
    if (Usuario::usuarioExistente(nome, usuarios)) {
        std::cout << "Usuário já existe!\n";
    } else {
        Usuario novoUsuario(nome, senha);
        std::string dados = novoUsuario.criarUsuario();
        Usuario::salvarUsuario(dados, "data/usuarios.txt");
        std::cout << "Usuário criado com sucesso!\n";
    }
}

void Sistema::fazerLogin() {
    std::string nome, senha;
    std::cout << "Digite o nome de usuário: ";
    std::getline(std::cin, nome);
    std::cout << "Digite a senha: ";
    std::getline(std::cin, senha);

    std::vector<std::string> usuarios = Usuario::carregarUsuarios("data/usuarios.txt");
    if (Usuario::validarUsuario(nome, senha, usuarios)) {
        std::cout << "Bem-vindo, " << nome << "!\n";
        Operacoes operacoes(nome);
        operacoes.carregarCompras();  // Carregar as compras do usuário

        // Chama o menu de compras
        menuCompras(operacoes);
    } else {
        std::cout << "Usuário ou senha incorretos!\n";
    }
}

void Sistema::menuCompras(Operacoes& operacoes) {
    while (true) {
        std::cout << "\n--- Menu de Compras ---\n";
        std::cout << "1. Adicionar compra\n";
        std::cout << "2. Listar compras\n";
        std::cout << "3. Gerar relatório\n";  
        std::cout << "4. Ver estatísticas\n"; // Nova opção
        std::cout << "5. Logout\n";  
        std::cout << "Escolha uma opção: ";
        
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();

        if (escolha == 1) {
            operacoes.adicionarCompra();
        } else if (escolha == 2) {
            operacoes.listarCompras();
        } else if (escolha == 3) {
            gerarRelatorio(operacoes);  
        } else if (escolha == 4) {
            exibirEstatisticas(operacoes);
        } else if (escolha == 5) {
            break;  // Logout
        } else {
            std::cout << "Opção inválida!\n";
        }
    }
}

void Sistema::gerarRelatorio(Operacoes& operacoes) {
    std::cout << "Deseja gerar um relatório mensal ou anual? (1 para mensal, 2 para anual, 0 para não gerar): ";
    int relatorioEscolha;
    std::cin >> relatorioEscolha;
    std::cin.ignore();

    if (relatorioEscolha == 1) {
        int mes, ano;
        std::cout << "Digite o mês (1-12): ";
        std::cin >> mes;
        std::cout << "Digite o ano: ";
        std::cin >> ano;
        std::cin.ignore();
        Relatorio::gerarRelatorioMensal(operacoes.getCompras(), mes, ano);
    } else if (relatorioEscolha == 2) {
        int ano;
        std::cout << "Digite o ano: ";
        std::cin >> ano;
        std::cin.ignore();
        Relatorio::gerarRelatorioAnual(operacoes.getCompras(), ano);
    } else {
        std::cout << "Não foi gerado nenhum relatório.\n";
    }
}

void Sistema::exibirEstatisticas(Operacoes& operacoes) {
    Estatistica estatisticas(operacoes.getCompras());
    estatisticas.calcularGastosPorCategoria();
    estatisticas.exibirEstatisticas();  // Exibe os gastos por categoria

    float salario;
    std::cout << "\nDeseja comparar os gastos com seu salário? (S/N): ";
    char opcao;
    std::cin >> opcao;
    if (opcao == 'S' || opcao == 's') {
        std::cout << "Digite o seu salário: R$ ";
        std::cin >> salario;
        estatisticas.analisarComBaseSalario(salario);  // Compara com o salário do usuário
    }
}