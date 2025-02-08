//-----BIBLIOTECAS-----
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

//-----DIRETIVAS CONSTANTES-----
#define PINO_LED_VERMELHO 13
#define PINO_LED_VERDE 11
#define PINO_LED_AZUL 12
#define PINO_PWM 22

//-----VARIÁVEIS GLOBAIS-----
const uint16_t periodo = 2000;
const float divisor_de_pwm = 16.0;
const uint16_t taxa_incr_decr = 100;
uint numero_slice;

//-----PROTÓTIPOS-----
void configuracao_pwm(void);
void inicializacao_dos_pinos(void);

//-----FUNÇÃO PRINCIPAL-----
int main(void){
    while(true){

    }

    return 0;
}

//-----FUNÇÕES COMPLEMENTARES-----
void configuracao_pwm(void){
    gpio_set_function(PINO_PWM, GPIO_FUNC_PWM);
    numero_slice = pwm_gpio_to_slice_num(PINO_PWM);
    pwm_set_clkdiv(numero_slice, divisor_de_pwm);
    pwm_set_wrap(numero_slice, periodo);
    pwm_set_gpio_level(PINO_PWM, taxa_incr_decr);
    pwm_set_enabled(numero_slice, true);
}

void inicializacao_dos_pinos(void){
    gpio_init(PINO_LED_VERMELHO);
    gpio_set_dir(PINO_LED_VERMELHO, GPIO_OUT);

    gpio_init(PINO_LED_VERDE);
    gpio_set_dir(PINO_LED_VERDE, GPIO_OUT);

    gpio_init(PINO_LED_AZUL);
    gpio_set_dir(PINO_LED_AZUL, GPIO_OUT);
}
