//-----BIBLIOTECAS-----
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

//-----DIRETIVAS CONSTANTES-----
#define PINO_LED_VERMELHO 13
#define PINO_LED_VERDE 11
#define PINO_LED_AZUL 12
#define PINO_PWM 22
#define FREQUENCIA_CLOCK 125000000

//-----VARIÁVEIS GLOBAIS-----
uint16_t periodo_wrap;
float divisor_de_clock;
uint16_t duty_cycle; // Ciclo de trabalho do PWM
uint numero_slice;

//-----PROTÓTIPOS-----
void alteracao_parametros(uint estagio);
void configuracao_pwm(void);
void inicializacao_dos_pinos(void);

//-----FUNÇÃO PRINCIPAL-----
int main(void){
    uint contador_estagio = 1;

    while(true){
        alteracao_parametros(contador_estagio);
        configuracao_pwm();
        contador_estagio++;
        if(contador_estagio == 5)
            contador_estagio = 1;
        sleep_ms(1000);
    }

    return 0;
}

//-----FUNÇÕES COMPLEMENTARES-----
void alteracao_parametros(uint estagio){
    switch(estagio){
        case 1: // Estágio 1
            divisor_de_clock = 200.15;
            uint divisor_inteiro = (int)divisor_de_clock;
            uint divisor_frac = (int)(divisor_de_clock - divisor_inteiro) * 100;
            uint frequencia_pwm = 50;
            periodo_wrap = FREQUENCIA_CLOCK / ((divisor_inteiro + divisor_frac / 16) * frequencia_pwm) - 1;
            duty_cycle = periodo_wrap * 50 / 100;
            break;
        case 2: // Estágio 2
            duty_cycle = periodo_wrap * 3 / 2500; // 0,12%
            break;
        case 3: // Estágio 3
            duty_cycle = periodo_wrap * 735 / 1000000; // 0,0735%
            break;
        case 4: // Estágio 4
            duty_cycle = periodo_wrap / 4000; // 0,025%
            break;
    }
}

void configuracao_pwm(void){
    numero_slice = pwm_gpio_to_slice_num(PINO_PWM); // Obtém o canal (slice) PWM da GPIO
    pwm_set_clkdiv(numero_slice, divisor_de_clock); // Define o divisor de clock do PWM
    pwm_set_wrap(numero_slice, periodo_wrap); // Define o valor de wrap, que é o valor máximo do contador PWM
    pwm_set_gpio_level(PINO_PWM, duty_cycle); // Define o ciclo de trabalho (duty cycle) do PWM
    pwm_set_enabled(numero_slice, true); // Habilita o PWM no slice correspondente
}

void inicializacao_dos_pinos(void){
    gpio_init(PINO_LED_VERMELHO);
    gpio_set_dir(PINO_LED_VERMELHO, GPIO_OUT);

    gpio_init(PINO_LED_VERDE);
    gpio_set_dir(PINO_LED_VERDE, GPIO_OUT);

    gpio_init(PINO_LED_AZUL);
    gpio_set_dir(PINO_LED_AZUL, GPIO_OUT);

    gpio_set_function(PINO_PWM, GPIO_FUNC_PWM); // Habilita o pino GPIO como PWM
}
