# Projeto de Móbile

buzzer-com-servo-novo foi a versão inicial do projeto, ao atualizar para Projeto-Mobile-Color foi adicionado um efeito de fade-in/fade-out nos LEDs usando PWM.

## Funcionalidade

O móbile começa a tocar música quando o botão é pressionado. É possível trocar de música apertando o botão novamente, e apertar o botão pela terceira vez o faz parar de tocar. 
O móbile também para de tocar após 50 segundos. Se ele parar por tempo, ao ser ligado novamente ele continua a música exatamente de onde parou. Se ele for desligado por botão, 
ele volta ao começo da primeira música ao ser reiniciado.

Enquanto a música toca, dois LEDs piscam e um Servo motor se move em passos de 10 graus no ritmo da música.

## Montagem

- 1 Placa UNO R3
- 1 buzzer 5V ativo (será que o passivo funciona da mesma maneira ou melhor?)
- 2 LEDs
- 3 resistores 220 Ohms
- 1 display de sete segmentos anodo comum
- 1 Micro Servo 9G
- 1 push-button

## Código

Compilar com a [IDE do Arduino](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE).

A música é armazenada em uma struct Musica, composta por um array de struct Notas. [PROGMEM](https://docs.arduino.cc/language-reference/pt/en/variables/utilities/PROGMEM/) é usado para economizar espaço de memória RAM.

