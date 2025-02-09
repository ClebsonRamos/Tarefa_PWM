TAREFA PWM


DESCRIÇÃO

Esse projeto tem como funcionalidade controlar um servomotor para realizar movimentos sincronizados. Foi construída uma simulação através da plataforma Wokwi e importada para o projeto. Quando ativada, a simulação posiciona o braço do servomotor à 180 graus (posição sul). Após 5 segundos, o braço é movido 90 graus no sentido anti-horário (posição leste). Depois de mais 5 segundos, novamente o braço do servomotor é movido 90 graus no sentido anti-horário (posição norte) e aguarda mais 5 segundos.
Findada a pausa de 5 segundos, o servomotor oscila suavemente sua posição da posição norte à posição sul, e da posição sul à posição norte, permanecendo nesse movimento indefinidamente. Para realizar essa movimentação suave, o programa manipula o período de movimentação atravéz de alterações no PWM, com um incremento/decremento de 5 microssegundos. Entre cada incremento/decremento, há uma pausa de 10 milissegundos.
No código desenvolvido, há um comentário ao lado da constante que representa o pino selecionado onde orienta-se assumir o valor 22 (GPIO 22) para executar o código na simulação, ou 12 (GPIO 12) caso queira executar o código no ambiente de aprendizagem BitDogLab.
Na BitDogLab, o pino GPIO 12 está conectado ao LED azul. Ao ser escolhido, ele será habilitado como PWM e será possível observar um comportamento semelhante na oscilação da sua luminosidade.


COMPONENTES NECESSÁRIOS

  * 1 placa Raspberry Pi Pico W, com um microcontrolador RP2040;
  * 1 servomotor;
  * 1 LED azul.


LINK DO VÍDEO DE APRESENTAÇÃO DO PROJETO

https://drive.google.com/file/d/1AleiYe0omlf9S96H5K3Y9sbvmfSuK7Cw/view?usp=sharing
