
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

// ST7920 128x64 display (connected via SPI software)
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ U8X8_PIN_NONE);

// Botones (definí los pines según tu conexión)
#define BTN_UP     32
#define BTN_DOWN   33
#define BTN_LEFT   34
#define BTN_RIGHT  35
#define BTN_OK     13
#define BTN_CANCEL 12
#define BTN_POWER  14

// Estado del sistema
enum Estado {MENU_PRINCIPAL, SELECCION_CURSO, TOMA_ASISTENCIA, SUBIDA_DATOS};
Estado estadoActual = MENU_PRINCIPAL;

void setup() {
  Serial.begin(115200);
  u8g2.begin();

  // Configurar pines de botones
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_OK, INPUT_PULLUP);
  pinMode(BTN_CANCEL, INPUT_PULLUP);
  pinMode(BTN_POWER, INPUT_PULLUP);

  mostrarMenuPrincipal();
}

void loop() {
  switch (estadoActual) {
    case MENU_PRINCIPAL:
      if (botonPresionado(BTN_OK)) {
        estadoActual = SELECCION_CURSO;
        mostrarSeleccionCurso();
      }
      break;
    case SELECCION_CURSO:
      if (botonPresionado(BTN_OK)) {
        estadoActual = TOMA_ASISTENCIA;
        mostrarTomaAsistencia();
      }
      break;
    case TOMA_ASISTENCIA:
      tomarAsistencia();
      break;
    case SUBIDA_DATOS:
      subirDatos();
      break;
  }

  delay(100);
}

bool botonPresionado(int pin) {
  return digitalRead(pin) == LOW;
}

void mostrarMenuPrincipal() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 15, "1. Tomar asistencia");
  u8g2.drawStr(10, 30, "2. Subir datos");
  u8g2.sendBuffer();
}

void mostrarSeleccionCurso() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawStr(0, 10, "Curso: 6BT");
  u8g2.drawStr(0, 20, "Turno: Tarde");
  u8g2.drawStr(0, 30, "Fecha: 14/04/2025");
  u8g2.drawStr(0, 50, "Presione OK para iniciar");
  u8g2.sendBuffer();
}

void mostrarTomaAsistencia() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawStr(0, 10, "Iniciando camara...");
  u8g2.drawStr(0, 30, "Espere un momento.");
  u8g2.sendBuffer();
}

void tomarAsistencia() {
  // Aquí iría la integración con Edge Impulse
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawStr(0, 10, "Reconociendo rostro...");
  u8g2.drawStr(0, 30, "Resultado: Juan Perez");
  u8g2.drawStr(0, 50, "[OK] Confirmar");
  u8g2.sendBuffer();

  // Simulamos confirmación
  if (botonPresionado(BTN_OK)) {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 10, "Marcado como presente");
    u8g2.sendBuffer();
    delay(2000);
    mostrarTomaAsistencia(); // siguiente alumno
  }
}

void subirDatos() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.drawStr(0, 10, "Subiendo datos...");
  u8g2.drawStr(0, 30, "Espere un momento.");
  u8g2.sendBuffer();

  delay(3000);
  mostrarMenuPrincipal();
  estadoActual = MENU_PRINCIPAL;
}
