#include <Arduino.h>
#include <Servo.h>

const int triggerPin = 12; // Pino do trigger do sensor
const int echoPin = 13;    // Pino do echo do sensor

Servo myservo;  // Crie um objeto Servo

const int servoPin = 14;  // Pino ao qual o servo está conectado


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);

    Serial.begin(115200);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

     myservo.attach(servoPin);  // Vincule o objeto Servo ao pino do servo
}

void loop() {
  // put your main code here, to run repeatedly:
    long duration;
    float distance_cm, distance_inch;

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

    // Exiba a distância no monitor serial
    Serial.print("Distância em cm: ");
    Serial.print(distance_cm);

    delay(1000); // Ajuste o atraso conforme necessário


    // Gire o servo para a posição inicial (0 graus)
    myservo.write(0);
    delay(1000);  // Aguarde por 1 segundo

    // Gire o servo para uma posição intermediária (90 graus)
    myservo.write(90);
    delay(1000);  // Aguarde por 1 segundo

    // Gire o servo para a posição final (180 graus)
    myservo.write(180);
    delay(1000);  // Aguarde por 1 segundo
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}