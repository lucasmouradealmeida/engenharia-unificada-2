#include <Arduino.h>
#include <Servo.h>

// Variáveis Globais

// Sensor ultrassonico 1
const int triggerPin = 10;
const int echoPin = 11;

// Servo motor
Servo myservo;
const int servoPin = 3;

// Valor de calibração
float calibracao = 60.0;
int numLeiturasCalibracao = 100;

// Declaração de funções
float ultrasomDistance();
void moveServo(int angle);
void calibrarSensor();

void setup() {
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.attach(servoPin);
  myservo.write(0);

  calibrarSensor();
}

void loop() {
  float distance = ultrasomDistance();

  // Condição de giro para o servo
  if (distance > 9.99) {
    moveServo(0);
    Serial.println("Tanque vazio -> Distância: " + String(distance) + "cm");
  } else if (distance < 9.99 && distance > 4.99) {
    Serial.println("Tanque em níveis seguros -> Distância: " + String(distance) + "cm");
  } else if (distance < 4.99) {
    moveServo(90);
    Serial.println("Estabilizando para níveis seguros -> Distância: " + String(distance) + "cm");
  }
}

// Função para obter as distâncias dos sensores ultrassonicos
#define NUM_READINGS 15

float ultrasomDistance() {
  long duration;
  float distance_cm = 0.0;

  for (int i = 0; i < NUM_READINGS; ++i) {
    // Gere um pulso no pino do trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(10);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Meça o tempo que o sinal leva para retornar
    duration = pulseIn(echoPin, HIGH);

    // Certifique-se de que calibracao não seja zero
    if (calibracao != 0) {
      // Calcule a distância em centímetros e some aos resultados anteriores
      distance_cm += duration / calibracao;
    }

    // Aguarde um curto intervalo antes da próxima leitura
    delay(100);
  }

  // Calcule a média das distâncias medidas
  distance_cm /= NUM_READINGS;

  return distance_cm;
}

void moveServo(int angle) {
  // Gire o servo para uma posição intermediária (90 graus)
  myservo.write(angle);
  delay(1000);

  if (angle == 90) {
    Serial.println("Alerta de tanque em níveis críticos: Abrindo as comportas");
    Serial.println();
  }
}

void calibrarSensor() {
  Serial.println("Aguarde... Calibrando o sensor.");

  // Espera inicial
  delay(3000);

  float distanciaMedia = 0.0;

  for (int i = 0; i < numLeiturasCalibracao; ++i) {
    calibracao = calibracao + 0.15;  // Evitar divisão por zero

    float distance = ultrasomDistance();

    Serial.println("Distância: " + String(distance) + "cm");

    if (distance > 9.99 && distance < 10.10) {
      Serial.println("Calibração concluída");
      Serial.println();
      return;
    }

    delay(10);
  }

  // Calcule a média das leituras válidas
  distanciaMedia /= numLeiturasCalibracao;

  calibracao = distanciaMedia / 14.0;

  Serial.println("Calibração concluída. Valor de calibração: " + String(calibracao));
  Serial.println();
}
