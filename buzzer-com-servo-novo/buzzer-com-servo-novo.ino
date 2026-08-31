#include <Servo.h>
#include <avr/pgmspace.h> // O que exatamente tem aqui? Por que funciona sem essa linha?

#define NUM_NOTAS(song) sizeof(song)/sizeof(song[0])

#define DO 262
#define RE 294
#define MI 330
#define FA 349
#define SOL 392
#define LA 440
#define SI 494
#define DO_2 523

#define BUZZER_PIN 6
#define SERVO_PIN  9  // servo no pino 9 (só pode ser no 9 ou no 10)
#define BUTTON_PIN 7

#define LED1_PIN   1
#define LED2_PIN   2

#define SEGMENT_A  5
#define SEGMENT_B  4
#define SEGMENT_C 11
#define SEGMENT_D 12
#define SEGMENT_E 13
#define SEGMENT_F  8
#define SEGMENT_G 10

struct Nota {
  int frequencia;
  int duracao;
};

struct Musica {
  struct Nota * notas;
  int numerodenotas;
  int notai;
};

const struct Nota wiegenlied[] PROGMEM = {
    {MI,    4},
    {MI,    4},
    {SOL,   2},
    {MI,    4},
    {MI,    2},
    {SOL,   2},
    {MI,    4},
    {SOL,   4},
    {DO_2,  2},
    {SI,    2},
    {LA,    4},
    {LA,    2},
    {SOL,   2},
    {RE,    4},
    {MI,    4},
    {FA,    2},
    {RE,    2},
    {RE,    4},
    {MI,    4},
    {FA,    1},
    {RE,    4},
    {FA,    4},
    {SI,    4},
    {LA,    4},
    {SOL,   2},
    {SI,    2},
    {DO_2,  2},
    {DO,    4},
    {DO,    4},
    {DO_2,  2},
    {LA,    4},
    {FA,    4},
    {SOL,   2},
    {MI,    4},
    {DO,    4},
    {FA,    2},
    {SOL,   2},
    {LA,    2},
    {MI,    4},
    {SOL,   2},
    {DO,    4},
    {DO,    4},
    {DO_2,  2},
    {LA,    4},
    {FA,    4},
    {SOL,   2},
    {MI,    4},
    {DO,    4},
    {FA,    2},
    {MI,    2},
    {RE,    2},
    {DO,    1},
  };

const struct Nota twinkle_twinkle[] PROGMEM = {
    // Twin - kle, twin - kle, lit - tle star,
    {DO,    4},
    {DO,    4},
    {SOL,   4},
    {SOL,   4},
    {LA,    4},
    {LA,    4},
    {SOL,   2},
    // How I won - der what you are!
    {FA,    4},
    {FA,    4},
    {MI,    4},
    {MI,    4},
    {RE,    4},
    {RE,    4},
    {DO,    2},
    // Up a - bove the world so high,
    {SOL,   4},
    {SOL,   4},
    {FA,    4},
    {FA,    4},
    {MI,    4},
    {MI,    4},
    {RE,    2},
    // Like a dia - mond in the sky.
    {SOL,   4},
    {SOL,   4},
    {FA,    4},
    {FA,    4},
    {MI,    4},
    {MI,    4},
    {RE,    2},
    // Twin - kle, twin - kle, lit - tle star,
    {DO,    4},
    {DO,    4},
    {SOL,   4},
    {SOL,   4},
    {LA,    4},
    {LA,    4},
    {SOL,   2},
    // How I won - der what you are!
    {FA,    4},
    {FA,    4},
    {MI,    4},
    {MI,    4},
    {RE,    4},
    {RE,    4},
    {DO,    2},
};

struct Musica dorme = {
  wiegenlied,
  NUM_NOTAS(wiegenlied),//sizeof(wiegenlied)/sizeof(wiegenlied[0]),
  0
};

const int duracao = 2000;
int blink_state = LOW;

Servo meuServo;


void setup() {
   pinMode(BUTTON_PIN,INPUT_PULLUP);
   pinMode(LED1_PIN, OUTPUT);
   pinMode(LED2_PIN, OUTPUT);
   pinMode(SEGMENT_A, OUTPUT);
   pinMode(SEGMENT_B, OUTPUT);
   pinMode(SEGMENT_C, OUTPUT);
   pinMode(SEGMENT_D, OUTPUT);
   pinMode(SEGMENT_E, OUTPUT);
   pinMode(SEGMENT_F, OUTPUT);
   pinMode(SEGMENT_G, OUTPUT); 
}

void loop() {
   digitalWrite(SEGMENT_B, LOW);
   digitalWrite(SEGMENT_A, HIGH);
   digitalWrite(SEGMENT_C, LOW);
   digitalWrite(SEGMENT_D, HIGH);
   digitalWrite(SEGMENT_E, HIGH);
   digitalWrite(SEGMENT_F, HIGH);
   digitalWrite(SEGMENT_G, HIGH);

    meuServo.attach(SERVO_PIN);
    meuServo.write(10);
    
    // não faz nada até que o botão seja pressionado
    if(digitalRead(BUTTON_PIN) == LOW){
      play();
    }
    else{
      noTone(BUZZER_PIN);
    }    
}

void play(){
  for(int i=0; i<=2;i++){
        for(int angulo=10; angulo<=170; angulo = angulo + 10){
          meuServo.write(angulo);
          musica();
          if(processamento() == 0){
            delay(100);
            return;
          }
        }

        for(int angulo=170; angulo>=10; angulo = angulo - 10){
          meuServo.write(angulo);
          musica();
          if(processamento() == 0){
            delay(100);
            return;
          }
        }
      }  
      meuServo.detach();
}

int processamento(){
  if(digitalRead(BUTTON_PIN) == LOW){
    if(dorme.notas == wiegenlied){
      set_musica(twinkle_twinkle);
    }
    else{
      set_musica(wiegenlied);
      return 0;
    }
  }
  return 1;
}

void set_musica(struct Nota song[]){
    dorme.notas = song;
    dorme.numerodenotas = sizeof(song)/sizeof(song[0]);
    dorme.notai = 0;
}

// toca a próxima nota da música
void musica(){
    if (dorme.notai > dorme.numerodenotas - 1)
        dorme.notai = 0;
    
    int freq = pgm_read_word(&(dorme.notas[dorme.notai].frequencia));
    int dur  = pgm_read_word(&(dorme.notas[dorme.notai].duracao));

    tone(BUZZER_PIN, freq, duracao/dur);
    delay(duracao/dur*1.1); // TODO: create non-blocking logic: https://forum.arduino.cc/t/simple-delays-non-blocking-timer-free/635670
    
    // tone(BUZZER_PIN, dorme.notas[dorme.notai].frequencia, duracao/dorme.notas[dorme.notai].duracao);
    // delay(duracao/dorme.notas[dorme.notai].duracao*1.1);

    digitalWrite(LED1_PIN, blink_state);
    digitalWrite(LED2_PIN, !blink_state);
    
    noTone(BUZZER_PIN);
    
    dorme.notai++;
    blink_state = !blink_state;
}
