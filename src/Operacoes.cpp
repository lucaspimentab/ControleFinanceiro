#include "Operacoes.hpp"
#include "Compra.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>

Operacoes::Operacoes(const std::string& nomeUsuario) : nomeUsuario(nomeUsuario), categoria(nomeUsuario) {

} 

void Operacoes::addCompra(const Compra& compra) {
    compras.push_back(compra);
    salvarCompras(); // Salva as compras no arquivo após adicionar
}

bool compararPorData(const Compra& a, const Compra& b) {
    std::string dataA = a.getData();
    std::string dataB = b.getData();

    int anoA = std::stoi(dataA.substr(6, 4));
    int anoB = std::stoi(dataB.substr(6, 4));
    if (anoA != anoB) return anoA < anoB;

    int mesA = std::stoi(dataA.substr(3, 2));
    int mesB = std::stoi(dataB.substr(3, 2));
    if (mesA != mesB) return mesA < mesB;

    int diaA = std::stoi(dataA.substr(0, 2));
    int diaB = std::stoi(dataB.substr(0, 2));
    return diaA < diaB;
}

void Operacoes::listarCompras() {
    if (compras.empty()) {
        std::cout << "Nenhuma compra registrada." << std::endl;
        return;
    }

    std::vector<Compra> comprasOrdenadas = compras;
    std::sort(comprasOrdenadas.begin(), comprasOrdenadas.end(), compararPorData);

    std::cout << "--- Lista de Compras ---" << std::endl;
    for (size_t i = 0; i < comprasOrdenadas.size(); ++i) {
        std::cout << i + 1 << ". Valor: R$ " << std::fixed << std::setprecision(2) << comprasOrdenadas[i].getValor()
                  << ", Categoria: " << comprasOrdenadas[i].getCategoria()
                  << ", Data: " << comprasOrdenadas[i].getData() << std::endl;
    }

    size_t opcaoExcluir;
    std::cout << "\nDigite o número da compra que deseja remover (0 para voltar): ";
    std::cin >> opcaoExcluir;
    std::cin.ignore();

    if (opcaoExcluir > 0 && opcaoExcluir <= comprasOrdenadas.size()) {
        compras.erase(compras.begin() + opcaoExcluir - 1);
        salvarCompras();
        std::cout << "Compra removida com sucesso!\n";
    } else if (opcaoExcluir != 0) {
        std::cout << "Opção inválida!\n";
    }
}

const std::vector<Compra>& Operacoes::getCompras() const {
    return compras;
}

void Operacoes::carregarCompras() {
    std::ifstream arquivo("data/compras-" + nomeUsuario + ".txt");
    if (!arquivo.is_open()) return;

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string valorStr, categoria, data;

        std::getline(ss, valorStr, ';');
        std::getline(ss, categoria, ';');
        std::getline(ss, data, ';');

        float valor = std::stof(valorStr);
        Compra compra(valor, categoria, data);
        compras.push_back(compra);
    }
}

void Operacoes::salvarCompras() {
    std::ofstream arquivo("data/compras-" + nomeUsuario + ".txt");
    for (const auto& compra : compras) {
        arquivo << compra.getValor() << ";" << compra.getCategoria() << ";" << compra.getData() << std::endl;
    }
}

void Operacoes::menuCompras() {
    while (true) {
        std::cout << "\n--- Menu de Compras ---\n1. Adicionar compra\n2. Listar compras\n3. Logout\nEscolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();

        if (escolha == 1) {
            adicionarCompra();
        } else if (escolha == 2) {
            listarCompras();
        } else if (escolha == 3) {
            break;
        } else {
            std::cout << "Opção inválida!" << std::endl;
        }
    }
}

void Operacoes::adicionarCompra() {
    float valor;
    std::string categoriaEscolhida;

    std::cout << "Digite o valor da compra: ";
    std::cin >> valor;
    std::cin.ignore();

    // Agora, você usa a instância da classe Categoria para acessar as categorias
    const auto& categorias = categoria.obterCategorias();  // Aqui você usa a instância de Categoria
    if (categorias.empty()) {
        std::cout << "Nenhuma categoria disponível. Adicione uma antes de continuar." << std::endl;
        return;
    }

    std::cout << "\nEscolha a categoria da compra:\n";
    for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << i + 1 << ". " << categorias[i] << std::endl;
    }

    int opcaoCategoria;
    std::cout << "Digite o número da categoria: ";
    std::cin >> opcaoCategoria;
    std::cin.ignore();

    if (opcaoCategoria < 1 || static_cast<std::size_t>(opcaoCategoria) > categorias.size()) {
        std::cout << "Opção inválida!" << std::endl;
        return;
    }

    categoriaEscolhida = categorias[opcaoCategoria - 1];  // Aqui você usa a categoria selecionada

    std::string data;
    std::cout << "Digite a data da compra (formato: dd/mm/aaaa): ";
    std::getline(std::cin, data);

    if (data.size() != 10 || data[2] != '/' || data[5] != '/') {
        std::cout << "Formato de data inválido! Por favor, use o formato dd/mm/aaaa." << std::endl;
        return;
    }

    Compra compra(valor, categoriaEscolhida, data);
    addCompra(compra);
    std::cout << "Compra adicionada com sucesso!" << std::endl;
}


void Operacoes::mudarCategorias() {
    while (true) {
        std::cout << "\n--- Mudar Categorias ---\n1. Adicionar categoria\n2. Remover categoria\n3. Listar categorias\n4. Voltar\nEscolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();

        if (escolha == 1) {
            adicionarCategoria();
        } else if (escolha == 2) {
            removerCategoria();
        } else if (escolha == 3) {
            listarCategorias();
        } else if (escolha == 4) {
            break;
        } else {
            std::cout << "Opção inválida!" << std::endl;
        }
    }
}

void Operacoes::adicionarCategoria() {
    std::string novaCategoria;
    std::cout << "Digite o nome da nova categoria: ";
    std::getline(std::cin, novaCategoria);

    categoria.adicionarCategoria(novaCategoria, nomeUsuario); // Passando nomeUsuario
    std::cout << "Categoria adicionada com sucesso!" << std::endl;
}

void Operacoes::removerCategoria() {
    listarCategorias();

    int opcao;
    std::cout << "Digite o número da categoria que deseja remover: ";
    std::cin >> opcao;
    std::cin.ignore();

    if (opcao < 1 || static_cast<std::size_t>(opcao) > categoria.obterCategorias().size()) {
        std::cout << "Opção inválida!" << std::endl;
        return;
    }

    std::string categoriaRemover = categoria.obterCategorias()[opcao - 1];
    categoria.excluirCategoria(categoriaRemover, nomeUsuario); // Passando nomeUsuario
    std::cout << "Categoria removida com sucesso!" << std::endl;
}

void Operacoes::listarCategorias() {
    const auto& categorias = categoria.obterCategorias();
    if (categorias.empty()) {
        std::cout << "Nenhuma categoria cadastrada." << std::endl;
        return;
    }

    std::cout << "--- Categorias ---\n";
    for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << i + 1 << ". " << categorias[i] << std::endl;
    }
}