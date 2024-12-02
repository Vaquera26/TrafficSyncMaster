#include <Wire.h>

// Declaración de constantes para los pines del Semáforo 3
const int SEMAFORO_3_ROJO = 2;
const int SEMAFORO_3_VERDE = 5;
const int SEMAFORO_3_AMARILLO = 4;

// Declaración de constantes para los pines del Semáforo 4
const int SEMAFORO_4_ROJO = 6;
const int SEMAFORO_4_VERDE = 8;
const int SEMAFORO_4_AMARILLO = 7 ;

void setup() {
  Wire.begin(0x03); // Dirección del esclavo 3
  Wire.onReceive(receiveEvent);

  // Configuración inicial de los pines
  pinMode(SEMAFORO_3_ROJO, OUTPUT);
  pinMode(SEMAFORO_3_VERDE, OUTPUT);
  pinMode(SEMAFORO_3_AMARILLO, OUTPUT);
  pinMode(SEMAFORO_4_ROJO, OUTPUT);
  pinMode(SEMAFORO_4_VERDE, OUTPUT);
  pinMode(SEMAFORO_4_AMARILLO, OUTPUT);

  // Estado inicial: ambos semáforos en rojo
  digitalWrite(SEMAFORO_3_ROJO, HIGH);
  digitalWrite(SEMAFORO_3_VERDE, LOW);
  digitalWrite(SEMAFORO_3_AMARILLO, LOW);
  digitalWrite(SEMAFORO_4_ROJO, HIGH);
  digitalWrite(SEMAFORO_4_VERDE, LOW);
  digitalWrite(SEMAFORO_4_AMARILLO, LOW);

  Serial.begin(9600); // Para depuración
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
  // Semáforo 3
  if (cmd == "3:GREEN") {
    apagarSemaforo3();
    digitalWrite(SEMAFORO_3_VERDE, HIGH); // Enciende verde
    Serial.println("Semáforo 3: Verde encendido");
  } else if (cmd == "3:YELLOW") {
    apagarSemaforo3();
    digitalWrite(SEMAFORO_3_AMARILLO, HIGH); // Enciende amarillo
    Serial.println("Semáforo 3: Amarillo encendido");
  } else if (cmd == "3:RED") {
    apagarSemaforo3();
    digitalWrite(SEMAFORO_3_ROJO, HIGH); // Enciende rojo
    Serial.println("Semáforo 3: Rojo encendido");
  }

  // Semáforo 4
  else if (cmd == "4:GREEN") {
    apagarSemaforo4();
    digitalWrite(SEMAFORO_4_VERDE, HIGH); // Enciende verde
    Serial.println("Semáforo 4: Verde encendido");
  } else if (cmd == "4:YELLOW") {
    apagarSemaforo4();
    digitalWrite(SEMAFORO_4_AMARILLO, HIGH); // Enciende amarillo
    Serial.println("Semáforo 4: Amarillo encendido");
  } else if (cmd == "4:RED") {
    apagarSemaforo4();
    digitalWrite(SEMAFORO_4_ROJO, HIGH); // Enciende rojo
    Serial.println("Semáforo 4: Rojo encendido");
  }
}

void apagarSemaforo3() {
  digitalWrite(SEMAFORO_3_ROJO, LOW);     // Apaga rojo
  digitalWrite(SEMAFORO_3_VERDE, LOW);    // Apaga verde
  digitalWrite(SEMAFORO_3_AMARILLO, LOW); // Apaga amarillo
}

void apagarSemaforo4() {
  digitalWrite(SEMAFORO_4_ROJO, LOW);     // Apaga rojo
  digitalWrite(SEMAFORO_4_VERDE, LOW);    // Apaga verde
  digitalWrite(SEMAFORO_4_AMARILLO, LOW); // Apaga amarillo
}
