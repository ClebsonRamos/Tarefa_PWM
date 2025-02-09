//-----BIBLIOTECAS-----
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

//-----DIRETIVAS CONSTANTES-----
#define PINO_LED_AZUL 12
#define PINO_PWM 22

//-----VARIÁVEIS GLOBAIS-----
uint16_t periodo_wrap = 20000;
float divisor_de_clock = 125.0;
uint16_t duty_cycle = 0; // Ciclo de trabalho do PWM
uint numero_slice;

//-----PROTÓTIPOS-----
void alteracao_parametros(uint estagio);
void configuracao_pwm(void);
void inicializacao_dos_pinos(void);

//-----FUNÇÃO PRINCIPAL-----
int main(void){
    uint32_t intervalo_ms = 5000;
    bool estagios_iniciais = true;

    stdio_init_all();
    inicializacao_dos_pinos();
    configuracao_pwm();

    while(true){
        if(estagios_iniciais){
            for(uint i = 1; i < 4; i++){
                alteracao_parametros(i);
                sleep_ms(intervalo_ms);
            }
            estagios_iniciais = !estagios_iniciais;
        }
    }

    return 0;
}

//-----FUNÇÕES COMPLEMENTARES-----
void alteracao_parametros(uint estagio){
    switch(estagio){
        case 1: // Estágio 1
            duty_cycle = 0;
            break;
        case 2: // Estágio 2
            duty_cycle = periodo_wrap * 3 / 25; // 12,00%
            break;
        case 3: // Estágio 3
            duty_cycle = periodo_wrap * 147 / 2000; // 7,35%
            break;
        case 4: // Estágio 4
            duty_cycle = periodo_wrap / 40; // 2,50%
            break;
    }
    printf("duty cycle: %d\n", duty_cycle);
    pwm_set_gpio_level(PINO_PWM, duty_cycle);
}

void configuracao_pwm(void){
    numero_slice = pwm_gpio_to_slice_num(PINO_PWM); // Obtém o canal (slice) PWM da GPIO
    pwm_set_clkdiv(numero_slice, divisor_de_clock); // Define o divisor de clock do PWM
    pwm_set_wrap(numero_slice, periodo_wrap); // Define o valor de wrap, que é o valor máximo do contador PWM
    pwm_set_gpio_level(PINO_PWM, duty_cycle); // Define o ciclo de trabalho (duty cycle) do PWM
    pwm_set_enabled(numero_slice, true); // Habilita o PWM no slice correspondente
}

void inicializacao_dos_pinos(void){
    gpio_init(PINO_LED_AZUL);
    gpio_set_dir(PINO_LED_AZUL, GPIO_OUT);
    gpio_put(PINO_LED_AZUL, false);

    gpio_set_function(PINO_PWM, GPIO_FUNC_PWM); // Habilita o pino GPIO como PWM
}
