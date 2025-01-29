#include "AlertaGastos.hpp"

void AlertaGastos::verificarAlerta() const {
    float limiteAtenção = salario * 0.5;  // Se gastar mais de 50% do salário
    float limiteCritico = salario * 0.8;  // Se gastar mais de 80% do salário

    if (saldoRestante <= 0) {
        std::cout << "[ALERTA] Você ultrapassou seu saldo! Evite novas compras.\n";
    } else if (saldoRestante <= limiteCritico) {
        std::cout << "[ALERTA] Seu saldo está quase esgotado! Planeje seus gastos.\n";
    } else if (diaAtual <= 10 && saldoRestante <= limiteAtenção) {
        std::cout << "[ALERTA] Você gastou mais da metade do seu salário logo no início do mês. Cuidado!\n";
    }
}

void AlertaGastos::atualizarSaldo(float novoSaldo) {
    saldoRestante = novoSaldo;
}
