#include "AlertaGastos.hpp"

void AlertaGastos::verificarAlerta() const {
    // Limites de alerta baseados no salário
    float limiteAtenção = salario * 0.5;  // Se gastar mais de 50% do salário
    float limiteCritico = salario * 0.8;  // Se gastar mais de 80% do salário

    // Verifica o saldo e gera alertas
    if (saldoRestante < 0) {  // Saldo negativo
        std::cout << "[ALERTA] Você ultrapassou seu saldo! Evite novas compras.\n";
    } else if (saldoRestante <= limiteCritico) {  // Saldo próximo ao crítico
        std::cout << "[ALERTA] Seu saldo está quase esgotado! Planeje seus gastos.\n";
    } else if (diaAtual <= 10 && saldoRestante <= limiteAtenção) {  // Alerta para metade do salário no início do mês
        std::cout << "[ALERTA] Você gastou mais da metade do seu salário logo no início do mês. Cuidado!\n";
    }
}

void AlertaGastos::atualizarSaldo(float novoSaldo) {
    saldoRestante = novoSaldo;  // Atualiza o saldo no alerta
}