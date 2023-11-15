#include <Arduino.h>
#include <Servo.h>

// Variáveis Globais

// Sensor ultrassonico 1

const int triggerPin = 10;
const int echoPin = 11;

// Sensor ultrassonico 2

const int triggerPin2 = 12;
const int echoPin2 = 13;

// Servo motor
Servo myservo;
const int servoPin = 3;


// Declaração de funções
int ultrasomDistance();
int moveServo();

void setup() {

  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  myservo.attach(servoPin);

}

void loop() {

  int distance = ultrasomDistance();
  Serial.print("Distância em cm: ");
  Serial.print(distance);

  if(distance < 10){
    int move = moveServo();
  }

}

// Função para obter as distâncias dos sensores ultrassonicos
int ultrasomDistance(){

    long duration;
    float distance_cm;

    // Gere um pulso no pino do trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Meça o tempo que o sinal leva para retornar
    duration = pulseIn(echoPin, HIGH);

    // Calcule a distância em centímetros e polegadas
    distance_cm = duration / 29.1 / 2.0;

    return distance_cm;
}

int moveServo(){
    // Gire o servo para a posição inicial (0 graus)
    myservo.write(0);
    delay(1000);  // Aguarde por 1 segundo

    // Gire o servo para uma posição intermediária (90 graus)
    myservo.write(90);
    delay(1000);  // Aguarde por 1 segundo

    // Gire o servo para a posição final (180 graus)
    myservo.write(180);
    delay(1000);  // Aguarde por 1 segundo

    return 1;
}
