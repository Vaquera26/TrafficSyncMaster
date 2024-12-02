#include <Wire.h>

// Declaración de constantes para los pines
const int PIN_ROJO_AVANZAR = 2;
const int PIN_VERDE_AVANZAR = 4;
const int PIN_AZUL_AVANZAR = 5;
const int PIN_ROJO_GIRAR = 6;
const int PIN_VERDE_GIRAR = 7;

void setup() {
  Wire.begin(0x01); // Dirección del esclavo 1
  Wire.onReceive(receiveEvent);

  // Configuración inicial de pines
  pinMode(PIN_ROJO_AVANZAR, OUTPUT);  // Rojo avanzar
  pinMode(PIN_VERDE_AVANZAR, OUTPUT); // Verde avanzar
  pinMode(PIN_AZUL_AVANZAR, OUTPUT);  // Azul avanzar
  pinMode(PIN_ROJO_GIRAR, OUTPUT);    // Rojo girar
  pinMode(PIN_VERDE_GIRAR, OUTPUT);   // Verde girar

  // Configuración inicial de estados
  digitalWrite(PIN_ROJO_AVANZAR, HIGH); // Rojo avanzar encendido
  digitalWrite(PIN_VERDE_AVANZAR, LOW); // Verde avanzar apagado
  digitalWrite(PIN_AZUL_AVANZAR, LOW);  // Azul avanzar apagado
  digitalWrite(PIN_ROJO_GIRAR, HIGH);   // Rojo girar encendido
  digitalWrite(PIN_VERDE_GIRAR, LOW);   // Verde girar apagado
}

void loop() {
  // Vacío, todo ocurre en receiveEvent
}

void receiveEvent(int howMany) {
  String command = "";
  while (Wire.available()) {
    command += (char)Wire.read();
  }
  processCommand(command);
}

void processCommand(String cmd) {
  // Semáforo de avanzar
  if (cmd == "1:GREEN") {
    apagarAvanzar();                          // Apaga cualquier estado previo
    digitalWrite(PIN_VERDE_AVANZAR, HIGH);    // Enciende verde avanzar
  } else if (cmd == "1:YELLOW") {
    apagarAvanzar();                          // Apaga cualquier estado previo
    digitalWrite(PIN_ROJO_AVANZAR, HIGH);     // Enciende rojo avanzar
    digitalWrite(PIN_VERDE_AVANZAR, HIGH);    // Enciende verde avanzar
    Serial.println("Semáforo de avanzar en amarillo");
  } else if (cmd == "1:RED") {
    apagarAvanzar();                          // Apaga cualquier estado previo
    digitalWrite(PIN_ROJO_AVANZAR, HIGH);     // Enciende rojo avanzar
  }

  // Semáforo de girar
  else if (cmd == "1:TURN_GREEN") {
    apagarGirar();                            // Apaga cualquier estado previo
    digitalWrite(PIN_VERDE_GIRAR, HIGH);      // Enciende verde girar
  } else if (cmd == "1:TURN_YELLOW") {
    apagarGirar();                            // Apaga cualquier estado previo
    digitalWrite(PIN_ROJO_GIRAR, HIGH);       // Enciende rojo girar
    digitalWrite(PIN_VERDE_GIRAR, HIGH);      // Enciende verde girar
    Serial.println("Semáforo de girar en amarillo");
  } else if (cmd == "1:TURN_RED") {
    apagarGirar();                            // Apaga cualquier estado previo
    digitalWrite(PIN_ROJO_GIRAR, HIGH);       // Enciende rojo girar
  }
}

void apagarAvanzar() {
  digitalWrite(PIN_ROJO_AVANZAR, LOW);   // Apaga rojo avanzar
  digitalWrite(PIN_VERDE_AVANZAR, LOW);  // Apaga verde avanzar
  digitalWrite(PIN_AZUL_AVANZAR, LOW);   // Apaga azul avanzar
}

void apagarGirar() {
  digitalWrite(PIN_ROJO_GIRAR, LOW);     // Apaga rojo girar
  digitalWrite(PIN_VERDE_GIRAR, LOW);    // Apaga verde girar
}
