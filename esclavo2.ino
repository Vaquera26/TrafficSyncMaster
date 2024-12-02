//esclavo 2:
#include <Wire.h>

void setup() {
  Wire.begin(0x02); // Dirección del esclavo 2
  Wire.onReceive(receiveEvent);

  // Configuración inicial
  pinMode(2, OUTPUT); // Rojo avanzar
  pinMode(4, OUTPUT); // Verde avanzar
  pinMode(6, OUTPUT); // Rojo girar
  pinMode(7, OUTPUT); // Verde girar

  // Inicia ambos LEDs en rojo
  digitalWrite(2, HIGH); // Rojo avanzar
  digitalWrite(4, LOW);  // Verde avanzar apagado

  digitalWrite(6, HIGH); // Rojo girar
  digitalWrite(7, LOW);  // Verde girar apagado
}

void loop() {
  // Vacío, todo ocurre en receiveEvent
}

void receiveEvent(int howMany) {
  String command = "";
  while (Wire.available()) {
    command += (char)Wire.read();
  }
  Serial.print("Comando recibido: ");
  Serial.println(command);
  processCommand(command);
}

void processCommand(String cmd) {
  // Semáforo de avanzar
  if (cmd == "2:GREEN") {
    apagarAvanzar();      // Apaga cualquier estado previo
    digitalWrite(4, HIGH); // Enciende verde avanzar
    Serial.println("Semáforo 2: Avanzar en verde");
  } else if (cmd == "2:YELLOW") {
    apagarAvanzar();      // Apaga cualquier estado previo
    digitalWrite(4, HIGH); // Verde
    digitalWrite(2, HIGH); // Rojo (combinación para amarillo)
    Serial.println("Semáforo 2: Avanzar en amarillo");
  } else if (cmd == "2:RED") {
    apagarAvanzar();      // Apaga cualquier estado previo
    digitalWrite(2, HIGH); // Enciende rojo avanzar
    Serial.println("Semáforo 2: Avanzar en rojo");
  }

  // Semáforo de girar
  else if (cmd == "2:TURN_GREEN") {
    apagarGirar();        // Apaga cualquier estado previo
    digitalWrite(7, HIGH); // Enciende verde girar
    Serial.println("Semáforo 2: Girar en verde");
  } 
  else if (cmd == "2:TURN_YELLOW") {
   apagarGirar();     // Apaga cualquier estado previo
    digitalWrite(7, HIGH); // Verde
    digitalWrite(6, HIGH); // Rojo (combinación para amarillo)
    Serial.println("Semáforo 2: Avanzar en amarillo");
  } else if (cmd == "2:TURN_RED") {
    apagarGirar();        // Apaga cualquier estado previo
    digitalWrite(6, HIGH); // Rojo girar
    Serial.println("Semáforo 2: Girar en rojo");
  }
}

void apagarAvanzar() {
  digitalWrite(2, LOW); // Apaga rojo avanzar
  digitalWrite(4, LOW); // Apaga verde avanzar
  digitalWrite(5, LOW); // Apaga amarillo avanzar
}

void apagarGirar() {
  digitalWrite(6, LOW); // Apaga rojo girar
  digitalWrite(7, LOW); // Apaga verde girar
}