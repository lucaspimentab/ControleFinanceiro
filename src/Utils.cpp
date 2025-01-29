// utils.cpp
#include "utils.hpp"
#include <regex>

bool validarNome(const std::string& nome) {
    return std::regex_match(nome, std::regex("^[A-Za-zÀ-ÿ ]+$"));
}

bool validarSalario(const std::string& salario) {
    return std::regex_match(salario, std::regex("^[0-9]+(\\.[0-9]+)?$"));
}