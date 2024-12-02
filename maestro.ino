#include <Wire.h>

// Direcciones I2C
#define SLAVE_1 0x01
#define SLAVE_2 0x02
#define SLAVE_3 0x03

// Pin del botón
const int BUTTON_PIN = 10;

// Pines del display de 7 segmentos
const int DISPLAY_PINS[] = {2, 3, 4, 5, 6, 7, 8}; // a, b, c, d, e, f, g
const int NUM_DISPLAY_PINS = sizeof(DISPLAY_PINS) / sizeof(DISPLAY_PINS[0]);

// Variables de estado
bool pedestrianRequest = false;
bool lastButtonHandled = false;

// Arreglo para registrar los semáforos en verde
String activeGreenLights[10]; 
int greenLightCount = 0;

const byte SEGMENT_MAP[10] = {
  0b01111110, // 0
  0b00001100, // 1
  0b10110110, // 2
  0b10011110, // 3
  0b11001100, // 4
  0b11011010, // 5
  0b11111010, // 6
  0b00001110, // 7
  0b11111110, // 8
  0b11011110  // 9
};


void setup() {
  Wire.begin();
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Configuración inicial de los pines del display
  for (int i = 0; i < NUM_DISPLAY_PINS; i++) {
    pinMode(DISPLAY_PINS[i], OUTPUT);
    digitalWrite(DISPLAY_PINS[i], HIGH); // Encender todos los segmentos al inicio
  }
     digitalWrite(2, HIGH); // Segmento a
      digitalWrite(3, HIGH); // Segmento b
      digitalWrite(4, HIGH); // Segmento c
      digitalWrite(5, HIGH); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, HIGH); // Segmento f
      digitalWrite(8, LOW);  // Segmento g

  resetAllLights();
}

void loop() {
  Serial.println("Semáforos 3 y 4 en verde");
  activateGreen(SLAVE_3, "3:GREEN");

  sendCommand(SLAVE_1, "1:RED");
  sendCommand(SLAVE_1, "1:TURN_RED");
  sendCommand(SLAVE_2, "2:RED");
  sendCommand(SLAVE_2, "2:TURN_RED");
  checkPedestrianButton();

  delayWithButtonCheck(5000);

  if (!lastButtonHandled) {
    sendCommand(SLAVE_3, "3:YELLOW");
    delayWithButtonCheck(2000);
  } else {
    lastButtonHandled = false;
  }

  deactivateGreen(SLAVE_3, "3:GREEN");
  sendCommand(SLAVE_3, "3:RED");

  activateGreen(SLAVE_3, "4:GREEN");
  checkPedestrianButton();

  delayWithButtonCheck(5000);

  if (!lastButtonHandled) {
    sendCommand(SLAVE_3, "4:YELLOW");
    delayWithButtonCheck(2000);
  } else {
    lastButtonHandled = false;
  }

  deactivateGreen(SLAVE_3, "4:GREEN");
  sendCommand(SLAVE_3, "4:RED");

  activateGreen(SLAVE_1, "1:TURN_GREEN");
  activateGreen(SLAVE_2, "2:TURN_GREEN");
  checkPedestrianButton();

  delayWithButtonCheck(5000);

  if (!lastButtonHandled) {
    sendCommand(SLAVE_1, "1:TURN_YELLOW");
    sendCommand(SLAVE_2, "2:TURN_YELLOW");
    delayWithButtonCheck(2000);
  } else {
    lastButtonHandled = false;
  }

  deactivateGreen(SLAVE_1, "1:TURN_GREEN");
  deactivateGreen(SLAVE_2, "2:TURN_GREEN");

  sendCommand(SLAVE_1, "1:TURN_RED");
  sendCommand(SLAVE_2, "2:TURN_RED");
  checkPedestrianButton();

  activateGreen(SLAVE_1, "1:GREEN");
  activateGreen(SLAVE_2, "2:GREEN");


  delayWithButtonCheck(5000);

  if (!lastButtonHandled) {
    sendCommand(SLAVE_1, "1:YELLOW");
    sendCommand(SLAVE_2, "2:YELLOW");
    delayWithButtonCheck(2000);
  } else {
    lastButtonHandled = false;
  }

    deactivateGreen(SLAVE_1, "1:GREEN");
  deactivateGreen(SLAVE_2, "2:GREEN");

  delayWithButtonCheck(2000);
}

void checkPedestrianButton() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    pedestrianRequest = true;
    Serial.println("Botón peatonal presionado");
    handlePedestrianRequest();
  }
}

void handlePedestrianRequest() {
  Serial.println("Solicitud peatonal recibida.");

  delay(2000);
for (int i = 0; i < greenLightCount; i++) {
    String yellowCommand = activeGreenLights[i];

    // Reemplazar variantes de GREEN por YELLOW
    if (yellowCommand.indexOf("TURN_GREEN") != -1) {
        yellowCommand.replace("TURN_GREEN", "TURN_YELLOW");
    } else if (yellowCommand.indexOf(":GREEN") != -1) {
        yellowCommand.replace(":GREEN", ":YELLOW");
    }

    sendCommand(getSlaveAddress(activeGreenLights[i]), yellowCommand);
}


  delay(2000);

  resetAllLights();

  // Iniciar el temporizador peatonal en el display de 7 segmentos
  iniciarTemporizadorPeatonal();

  greenLightCount = 0;
  Serial.println("Ciclo normal reanudado.");
  pedestrianRequest = false;
  lastButtonHandled = true;
}

void activateGreen(int slave, String command) {
  sendCommand(slave, command);
  if (greenLightCount < 10) {
    activeGreenLights[greenLightCount++] = command;
  }
}

void deactivateGreen(int slave, String command) {
  String greenCommand = command;
  greenCommand.replace(":YELLOW", ":GREEN");
  for (int i = 0; i < greenLightCount; i++) {
    if (activeGreenLights[i] == greenCommand) {
      for (int j = i; j < greenLightCount - 1; j++) {
        activeGreenLights[j] = activeGreenLights[j + 1];
      }
      greenLightCount--;
      break;
    }
  }
}

void resetAllLights() {
  sendCommand(SLAVE_1, "1:RED");
  sendCommand(SLAVE_1, "1:TURN_RED");
  sendCommand(SLAVE_2, "2:RED");
  sendCommand(SLAVE_2, "2:TURN_RED");
  sendCommand(SLAVE_3, "3:RED");
  sendCommand(SLAVE_3, "4:RED");
}

void iniciarTemporizadorPeatonal() {
  Serial.println("Iniciando temporizador peatonal...");
  for (int i = 9; i >= 0; i--) {
    mostrarNumeroManual(i); // Mostrar el número en el display
    delay(1000);
  }
  Serial.println("Temporizador peatonal completado.");
     digitalWrite(2, HIGH); // Segmento a
      digitalWrite(3, HIGH); // Segmento b
      digitalWrite(4, HIGH); // Segmento c
      digitalWrite(5, HIGH); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, HIGH); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
}


void mostrarNumeroEnDisplay(int numero) {
  if (numero < 0 || numero > 9) return; // Asegurarse de que sea un número válido.

  byte segmentos = SEGMENT_MAP[numero];
  for (int i = 0; i < NUM_DISPLAY_PINS; i++) {
    // Aplica cada bit a los pines correspondientes
    digitalWrite(DISPLAY_PINS[i], (segmentos >> i) & 0x01);
  }
}


void delayWithButtonCheck(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    checkPedestrianButton();
  }
}

int getSlaveAddress(String command) {
  if (command.startsWith("1:") || command.startsWith("1:TURN_")) return SLAVE_1;
  if (command.startsWith("2:") || command.startsWith("2:TURN")) return SLAVE_2;
  if (command.startsWith("3:") || command.startsWith("4:")) return SLAVE_3;
  return -1;
}

void sendCommand(int address, String command) {
  Wire.beginTransmission(address);
  Wire.write(command.c_str());
  Wire.endTransmission();
  Serial.print("Enviado a ");
  Serial.print(address, HEX);
  Serial.print(": ");
  Serial.println(command);
}

void mostrarNumeroManual(int numero) {
  switch (numero) {
    case 0: // Mostrar 0
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, LOW); // Segmento d
      digitalWrite(6, LOW); // Segmento e
      digitalWrite(7, LOW); // Segmento f
      digitalWrite(8, HIGH);  // Segmento g
      break;
    case 1: // Mostrar 1
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, HIGH); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, HIGH); // Segmento f
      digitalWrite(8, HIGH);  // Segmento g
      break;
    case 2: // Mostrar 2
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, HIGH); // Segmento c
      digitalWrite(5, LOW); // Segmento d
      digitalWrite(6, LOW); // Segmento e
      digitalWrite(7, HIGH); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    case 3: // Mostrar 3
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, LOW); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, HIGH); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    case 4: // Mostrar 4
      digitalWrite(2, HIGH); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, HIGH); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, LOW); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    case 5: // Mostrar 5
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, HIGH); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, LOW); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, LOW); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    case 6: // Mostrar 6
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, HIGH); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, LOW); // Segmento d
      digitalWrite(6, LOW); // Segmento e
      digitalWrite(7, LOW); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    case 7: // Mostrar 7
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, HIGH); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, HIGH); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    case 8: // Mostrar 8
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, LOW); // Segmento d
      digitalWrite(6, LOW); // Segmento e
      digitalWrite(7, LOW); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    case 9: // Mostrar 9
      digitalWrite(2, LOW); // Segmento a
      digitalWrite(3, LOW); // Segmento b
      digitalWrite(4, LOW); // Segmento c
      digitalWrite(5, LOW); // Segmento d
      digitalWrite(6, HIGH); // Segmento e
      digitalWrite(7, LOW); // Segmento f
      digitalWrite(8, LOW);  // Segmento g
      break;
    default: // Apagar el display si no es un número válido
      for (int i = 0; i < NUM_DISPLAY_PINS; i++) {
        digitalWrite(DISPLAY_PINS[i], LOW);
      }
  }
}

