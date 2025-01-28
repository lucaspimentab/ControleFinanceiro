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
        std::cout << "\n--- Menu de Compras ---\n"
                  << "1. Adicionar compra\n"
                  << "2. Listar compras\n"
                  << "3. Gerar relatório\n"
                  << "4. Ver estatísticas\n"
                  << "5. Mudar categorias\n"
                  << "6. Logout\n"
                  << "Escolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();  // Limpa o buffer de entrada

        if (escolha == 1) {
            operacoes.adicionarCompra();
        } else if (escolha == 2) {
            operacoes.listarCompras();
        } else if (escolha == 3) {
            gerarRelatorio(operacoes);  // Passa 'operacoes' como argumento
        } else if (escolha == 4) {
            exibirEstatisticas(operacoes);  // Passa 'operacoes' como argumento
        } else if (escolha == 5) {
            operacoes.mudarCategorias();
        } else if (escolha == 6) {
            break;  // Logout
        } else {
            std::cout << "Opção inválida!" << std::endl;
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
    std::cout << "--- Estatísticas de Gastos ---\n";

    // Pergunta se o usuário quer estatísticas mensais ou anuais
    std::cout << "Escolha o período para as estatísticas:\n";
    std::cout << "1. Mensal\n2. Anual\nEscolha uma opção: ";
    int periodo;
    std::cin >> periodo;
    std::cin.ignore();

    int mes = 0, ano = 0;

    if (periodo == 1) {
        std::cout << "Digite o mês (1-12): ";
        std::cin >> mes;
        std::cout << "Digite o ano: ";
        std::cin >> ano;
    } else if (periodo == 2) {
        std::cout << "Digite o ano: ";
        std::cin >> ano;
    } else {
        std::cout << "Opção inválida!\n";
        return;
    }

    // Filtra as compras com base no período escolhido (mensal ou anual)
    std::vector<Compra> comprasFiltradas;
    for (const auto& compra : operacoes.getCompras()) {
        int compraMes, compraAno;
        std::sscanf(compra.getData().c_str(), "%d/%d/%d", &compraMes, &compraAno, &compraAno);

        if ((periodo == 1 && compraMes == mes && compraAno == ano) || 
            (periodo == 2 && compraAno == ano)) {
            comprasFiltradas.push_back(compra);
        }
    }

    Estatistica estatistica(comprasFiltradas); // Passa as compras filtradas para a classe Estatistica
    estatistica.exibirEstatisticas(); // Chama a função exibirEstatisticas de Estatistica
}