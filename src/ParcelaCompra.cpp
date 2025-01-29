// #include "ParcelaCompra.hpp"
// #include <cmath>       // Para arredondamento
// #include <stdexcept>   // Para exceções como std::out_of_range

// ParcelaCompra::ParcelaCompra(float valor, const std::string& categoria, const std::string& data, int numParcelas)
//     : Compra(valor, categoria, data), numParcelas(numParcelas) {
//     if (valor <= 0.0f) {
//         throw std::invalid_argument("O valor total deve ser maior que zero.");
//     }
//     if (numParcelas <= 0) {
//         throw std::invalid_argument("O número de parcelas deve ser maior que zero.");
//     }

//     float valorParcela = std::round((valor / numParcelas) * 100) / 100.0f; // Arredondar para 2 casas decimais
//     for (int i = 0; i < numParcelas; ++i) {
//         valoresParcelas.push_back(valorParcela);
//     }

//     // Ajusta o valor da última parcela caso haja diferença devido ao arredondamento
//     float totalParcelado = valorParcela * numParcelas;
//     if (totalParcelado != valor) {
//         valoresParcelas.back() += valor - totalParcelado;
//     }
// }

// int ParcelaCompra::getNumParcelas() const {
//     return numParcelas;
// }

// std::vector<float> ParcelaCompra::getValoresParcelas() const {
//     return valoresParcelas;
// }

// float ParcelaCompra::getValorParcela(int index) const {
//     if (index >= 0 && index < numParcelas) {
//         return valoresParcelas[index];
//     }
//     throw std::out_of_range("Índice de parcela inválido");
// }

#include "ParcelaCompra.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Operacoes.hpp"

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

std::string addOneMonth(const std::string& date) {
    int day, month, year;
    std::stringstream ss(date);
    char slash;
    ss >> day >> slash >> month >> slash >> year;

    if (month == 12) {
        month = 1;
        year++;
    } else {
        month++;
    }

    int maxDaysInMonth = daysInMonth(month, year);
    if (day > maxDaysInMonth) {
        day = maxDaysInMonth;
    }

    std::stringstream result;
    result << std::setfill('0') << std::setw(2) << day << "/"
           << std::setfill('0') << std::setw(2) << month << "/"
           << year;

    return result.str();
}


void ParcelaCompra::ParcelarCompra(float valor, const std::string& categoriaEscolhida, const std::string &data, int numParcelas, Operacoes &operacoes)
{
    float parcelasValue = valor / numParcelas;
    std::string parcelaData = data;

    for (int i = 0; i < numParcelas; i++)
    {
        Compra compra(parcelasValue, categoriaEscolhida, parcelaData);
        operacoes.addCompra(compra);
        parcelaData = addOneMonth(parcelaData);
        std::cout << "Parcela " << i + 1 << ": R$ " << std::fixed << std::setprecision(2) << parcelasValue << "\n";
    }
}
