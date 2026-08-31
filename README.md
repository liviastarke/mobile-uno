# Projeto de Móbile

Há um problema provavelmente na contagem de notas, ele só está tocando a primeira nota de cada música repetidamente.

Agora ele está trocando de música, mas apertar o botão pela terceira vez não o faz parar de tocar, ele volta para a primeira música.

## Montagem

- 1 Placa UNO R3
- 1 buzzer 5V ativo (será que o passivo funciona da mesma maneira ou melhor?)
- 2 LEDs
- 3 resistores 220 Ohms
- 1 display de sete segmentos anodo comum
- 1 micro servo 9G
- 1 push-button

## Código

Compilar com a [IDE do Arduino](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE).

A música é armazenada em uma struct Musica, composta por um array de struct Notas. [PROGMEM](https://docs.arduino.cc/language-reference/pt/en/variables/utilities/PROGMEM/) é usado para economizar espaço de memória RAM.

