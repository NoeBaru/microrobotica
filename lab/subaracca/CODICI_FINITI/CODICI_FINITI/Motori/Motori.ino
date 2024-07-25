#include <AFMotor.h>

AF_DCMotor motor1(3);
AF_DCMotor motor2(4);
AF_DCMotor motor3(1);
AF_DCMotor motor4(2);

// Definisci la soglia per considerare una lettura nulla
const int nullThreshold = 100;
// Definisci il tempo in millisecondi per cui i valori devono essere al di sotto della soglia prima di fermare i motori
const int nullTimeThreshold = 500; // 0.5 secondi

unsigned long lastNonNullTime = 0;

void setup() {
  // Inizializza i motori
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  // Imposta i pin analogici a basso
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);

  Serial.begin(9600);
}

void loop() {
  // Leggi i valori analogici per ogni pin e determina l'azione
  int analogValueA0, analogValueA1, analogValueA2, analogValueA3;

  // Imposta i pin analogici a basso prima di leggere i valori
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);

  // Leggi i valori analogici
  analogValueA0 = analogRead(A0);
  analogValueA1 = analogRead(A1);
  analogValueA2 = analogRead(A2);
  analogValueA3 = analogRead(A3);

  // Verifica se tutti i valori sono al di sotto della soglia di nullità
  if (analogValueA0 < nullThreshold && analogValueA1 < nullThreshold && analogValueA2 < nullThreshold && analogValueA3 < nullThreshold) {
    // Se tutti i valori sono nulli, controlla da quanto tempo lo sono
    if (millis() - lastNonNullTime >= nullTimeThreshold) {
      // Se il tempo trascorso è maggiore o uguale al tempo soglia, ferma i motori
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
    }
  } else {
    // Se almeno un valore supera la soglia, aggiorna il tempo dell'ultimo valore non nullo
    lastNonNullTime = millis();

    // Determina l'azione in base al pin analogico con il valore più alto
    if (analogValueA0 > analogValueA1 && analogValueA0 > analogValueA2 && analogValueA0 > analogValueA3) {
      // Esegui l'azione per A0
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    } else if (analogValueA1 > analogValueA0 && analogValueA1 > analogValueA2 && analogValueA1 > analogValueA3) {
      // Esegui l'azione per A1
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
    } else if (analogValueA2 > analogValueA0 && analogValueA2 > analogValueA1 && analogValueA2 > analogValueA3) {
      // Esegui l'azione per A2
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    } else if (analogValueA3 > analogValueA0 && analogValueA3 > analogValueA1 && analogValueA3 > analogValueA2) {
      // Esegui l'azione per A3
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    } else {
      // Arresta completamente i motori se nessun valore supera la soglia
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
    }
  }

  delay(100); // Delay per la stabilità
}
