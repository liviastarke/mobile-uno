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

#define FALSE 0
#define TRUE  1

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
int angulo = 10;
int positive_rotation = TRUE;
unsigned long tempo_inicio;
unsigned long tempo_proxima_nota;
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

    digitalWrite(SEGMENT_B, LOW);
    digitalWrite(SEGMENT_A, HIGH);
    digitalWrite(SEGMENT_C, LOW);
    digitalWrite(SEGMENT_D, HIGH);
    digitalWrite(SEGMENT_E, HIGH);
    digitalWrite(SEGMENT_F, HIGH);
    digitalWrite(SEGMENT_G, HIGH);
}

void loop() {
  // estado desligado
    meuServo.attach(SERVO_PIN);
    meuServo.write(angulo);
    
    // não faz nada até que o botão seja pressionado
    if(digitalRead(BUTTON_PIN) == LOW){
      delay(1000);
      tempo_inicio = millis();
      tempo_proxima_nota = tempo_inicio;
      processamento();
    }
    else{
      noTone(BUZZER_PIN);
    }
    meuServo.detach();
}

void rotate(){
  if(positive_rotation){
    angulo = angulo + 10;
  }
  else{
    angulo = angulo - 10;
  }
  meuServo.write(angulo);
}

void processamento(){
  while(millis() < tempo_inicio + 50000){
    if(digitalRead(BUTTON_PIN) == LOW){
      noTone(BUZZER_PIN);
      delay(1000);
      if(dorme.notas == wiegenlied){

        dorme.notas = twinkle_twinkle;
        dorme.numerodenotas = NUM_NOTAS(twinkle_twinkle);//sizeof(twinkle_twinkle)/sizeof(twinkle_twinkle[0]);
        dorme.notai = 0;

        digitalWrite(SEGMENT_B, LOW);
        digitalWrite(SEGMENT_A, LOW);
        digitalWrite(SEGMENT_C, HIGH);
        digitalWrite(SEGMENT_D, LOW);
        digitalWrite(SEGMENT_E, LOW);
        digitalWrite(SEGMENT_F, HIGH);
        digitalWrite(SEGMENT_G, LOW);

        tempo_inicio = millis();
      }
      else{
        dorme.notas = wiegenlied;
        dorme.numerodenotas = NUM_NOTAS(wiegenlied);//sizeof(wiegenlied)/sizeof(wiegenlied[0]);
        dorme.notai = 0;

        digitalWrite(SEGMENT_B, LOW);
        digitalWrite(SEGMENT_A, HIGH);
        digitalWrite(SEGMENT_C, LOW);
        digitalWrite(SEGMENT_D, HIGH);
        digitalWrite(SEGMENT_E, HIGH);
        digitalWrite(SEGMENT_F, HIGH);
        digitalWrite(SEGMENT_G, HIGH);
        return;
      }
    }

    if (millis() >= tempo_proxima_nota){
      // para de tocar a última nota.
      noTone(BUZZER_PIN);

      // pisca LED
      digitalWrite(LED1_PIN, blink_state);
      digitalWrite(LED2_PIN, !blink_state);
      blink_state = !blink_state;

      // rotaciona o servo
      if(angulo <= 10 || angulo >= 170){
        positive_rotation = !positive_rotation;
      }
      rotate();

      // toca nota
      play_note();
    }
  }
}

// toca a próxima nota da música
void play_note(){
    if (dorme.notai > dorme.numerodenotas - 1)
        dorme.notai = 0;
    
    int freq = pgm_read_word(&(dorme.notas[dorme.notai].frequencia));
    int dur  = pgm_read_word(&(dorme.notas[dorme.notai].duracao));

    tone(BUZZER_PIN, freq, duracao/dur);
    tempo_proxima_nota = millis() + duracao/dur*1.1;
    dorme.notai = dorme.notai + 1;
}
