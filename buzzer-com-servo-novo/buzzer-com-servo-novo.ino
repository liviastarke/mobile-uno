#include <Servo.h>

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
}

struct Musica {
  struct Nota * notas;
  int numerodenotas;
  int notai;
}

int duracao = 2000;
int blink_state = LOW;

int dorme[] = {
  MI, MI, SOL, MI, MI, SOL, MI, SOL, DO_2, SI, LA, LA, SOL, RE, MI, FA, RE, RE, MI, FA, RE, FA, SI, LA, SOL, SI, DO_2, DO, DO, DO_2, LA, FA, SOL, MI, DO, FA, SOL, LA, MI, SOL, DO, DO, DO_2, LA, FA, SOL, MI, DO, FA, MI, RE, DO 
};

int tempo[]= { 4, 4, 2, 4, 2, 2, 4, 4, 2, 2, 4, 2, 2, 4, 4, 2, 2, 4, 4, 1, 4, 4, 4, 4, 2, 2, 2, 4, 4, 2, 4, 4, 2, 4, 4, 2, 2, 2, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 2, 2, 2, 1 };

int numerodenotas;
int notai = 0;

Servo meuServo;


void setup() {
  // put your setup code here, to run once:
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
   numerodenotas = sizeof(tempo)/sizeof(tempo[0]);  
}

void loop() {
   digitalWrite(SEGMENT_B, LOW);
   digitalWrite(SEGMENT_A, HIGH);
   digitalWrite(SEGMENT_C, LOW);
   digitalWrite(SEGMENT_D, HIGH);
   digitalWrite(SEGMENT_E, HIGH);
   digitalWrite(SEGMENT_F, HIGH);
   digitalWrite(SEGMENT_G, HIGH);
  // put your main code here, to run repeatedly:
    meuServo.attach(SERVO_PIN);
    meuServo.write(10);
    if(digitalRead(BUTTON_PIN) == LOW) // não faz nada até que o botão seja pressionado
    {
      play();
    }
    else
    {
      noTone(BUZZER_PIN);
    }    
}

void play(){
  for(int i=0; i<=2;i++){
        for(int angulo=10; angulo<=170; angulo = angulo + 10)
        {
          meuServo.write(angulo);
          musica();
          if(digitalRead(BUTTON_PIN) == LOW){
            delay(100);
            return;
          }
        }

        for(int angulo=170; angulo>=10; angulo = angulo - 10)
        {
          meuServo.write(angulo);
          musica();
          if(digitalRead(BUTTON_PIN) == LOW){
            delay(100);
            return;
          }
        }
      }  
      meuServo.detach();
}

// toca a próxima nota da música
void musica(){
     if (notai > numerodenotas - 1)
        notai = 0;
    tone(BUZZER_PIN, dorme[notai], duracao/tempo[notai]);
    delay(duracao/tempo[notai]*1.1); // next: create non-blocking logic: https://forum.arduino.cc/t/simple-delays-non-blocking-timer-free/635670
    digitalWrite(LED1_PIN, blink_state);
    digitalWrite(LED2_PIN, !blink_state);
    noTone(BUZZER_PIN);
    notai++;
    blink_state = !blink_state;
    // if (blink_state == HIGH){
    //   blink_state = LOW;
    // }
    // else{
    //   blink_state = HIGH;
    // }
}
