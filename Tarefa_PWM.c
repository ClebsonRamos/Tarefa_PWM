//-----BIBLIOTECAS-----
#include "pico/stdlib.h"
#include "hardware/pwm.h"

//-----DIRETIVAS CONSTANTES-----
#define PINO_PWM 22 // OBS.: Usar o pino 22 caso execute na simulação ou 12 caso execute na BitDogLab.
#define DELAY_5S 5000 // Pausa de 5 segundos para os estágios 1, 2 e 3.
#define DELAY_10MS 10 // Pausa de 10 milissegundos para a oscilação suave do braço do servomotor.

//-----VARIÁVEIS GLOBAIS-----
uint16_t periodo_wrap = 20000; // WRAP
float divisor_de_clock = 125.0; // Divisor de clock
uint16_t duty_cycle = 0; // Ciclo de trabalho do PWM
uint numero_slice; // Slice associado ao pino.
static volatile bool controle_incremento = true; // Registra se o servomotor está subindo ou descendo no estágio 5.

//-----PROTÓTIPOS-----
void alteracao_ciclo_ativo(uint estagio);
void configuracao_pwm(void);

//-----FUNÇÃO PRINCIPAL-----
int main(void){
    bool estagios_iniciais = true; // Variável para alternância entre os estágios iniciais e o estágio de oscilação suave.

    configuracao_pwm();

    gpio_set_function(PINO_PWM, GPIO_FUNC_PWM); // Habilita o pino GPIO como PWM

    while(true){
        if(estagios_iniciais){ // Desvio condicional para os 4 primeiros estágios.
            for(uint i = 1; i < 4; i++)
                alteracao_ciclo_ativo(i);
            estagios_iniciais = !estagios_iniciais;
        }else{ // Desvio condicional para o estágio de oscilação.
            alteracao_ciclo_ativo(4);
        }
    }
    return 0;
}

//-----FUNÇÕES COMPLEMENTARES-----
void alteracao_ciclo_ativo(uint estagio){ // Função para alteração do ciclo ativo em função do estágio de ação.
    switch(estagio){
        case 1: // Estágio 1 - Posicionamento do braço em 180°
            duty_cycle = periodo_wrap * 3 / 25; // 12,00% do WRAP (2400)
            break;
        case 2: // Estágio 2 - Posicionamento do braço em 90°
            duty_cycle = periodo_wrap * 147 / 2000; // 7,35% do WRAP (1470)
            break;
        case 3: // Estágio 3 - Posicionamento do braço em 0°
            duty_cycle = periodo_wrap / 40; // 2,50% do WRAP (500)
            break;
        case 4: // Estágio 4 - Oscilação suave
            if(controle_incremento){ // Braço do servomotor subindo.
                duty_cycle += 5; // 0,025% do WRAP
                if(duty_cycle == periodo_wrap * 3 / 25) // WRAP = 2400
                    controle_incremento = false;
            }else{ // Braço do servomotor descendo.
                duty_cycle -= 5; // 0,025% do WRAP
                if(duty_cycle == periodo_wrap / 40) // WRAP = 500
                    controle_incremento = true;
            }
            break;
    }
    pwm_set_gpio_level(PINO_PWM, duty_cycle); // Alteração do ciclo ativo.
    if(estagio < 4)
        sleep_ms(DELAY_5S);
    else
        sleep_ms(DELAY_10MS);
}

void configuracao_pwm(void){ // Função para a configuração do PWM.
    numero_slice = pwm_gpio_to_slice_num(PINO_PWM); // Obtém o canal (slice) PWM da GPIO
    pwm_set_clkdiv(numero_slice, divisor_de_clock); // Define o divisor de clock do PWM
    pwm_set_wrap(numero_slice, periodo_wrap); // Define o valor de wrap, que é o valor máximo do contador PWM
    pwm_set_gpio_level(PINO_PWM, duty_cycle); // Define o ciclo de trabalho (duty cycle) do PWM
    pwm_set_enabled(numero_slice, true); // Habilita o PWM no slice correspondente
}
