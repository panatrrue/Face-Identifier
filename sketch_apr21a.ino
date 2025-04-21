#include <WiFi.h>
#include <esp_camera.h>
#include <FS.h>
#include <SPIFFS.h>
#include <U8g2lib.h>

// Pines para botones (pueden adaptarse)
const int botonConfirmar = 12;
const int botonCancelar = 13;
const int flechaArriba = 14;
const int flechaAbajo = 15;
const int flechaIzquierda = 2;
const int flechaDerecha = 4;
const int botonEncendido = 16;

// Pantalla ST7920
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/18, /* data=*/23, /* CS=*/5, /* reset=*/U8X8_PIN_NONE);

// Wi-Fi
const char* ssid = "TuSSID";
const char* password = "TuPassword";

// Modo
enum Estado { MENU_PRINCIPAL, SELECCION_CURSO, TOMA_LISTA, ENVIO_DATOS, ESPERANDO_FOTO };
Estado estadoActual = MENU_PRINCIPAL;

void mostrarMenuPrincipal() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(10, 20, "1. Toma de Lista");
  u8g2.drawStr(10, 35, "2. Enviar Registros");
  u8g2.sendBuffer();
}

void seleccionarCurso() {
  u8g2.clearBuffer();
  u8g2.drawStr(10, 20, "Seleccionar Curso:");
  u8g2.drawStr(10, 35, "6BT");
  u8g2.sendBuffer();
}

void setup() {
  Serial.begin(115200);

  // Inicializar pantalla
  u8g2.begin();

  // Inicializar botones
  pinMode(botonConfirmar, INPUT_PULLUP);
  pinMode(botonCancelar, INPUT_PULLUP);
  pinMode(flechaArriba, INPUT_PULLUP);
  pinMode(flechaAbajo, INPUT_PULLUP);
  pinMode(flechaIzquierda, INPUT_PULLUP);
  pinMode(flechaDerecha, INPUT_PULLUP);
  pinMode(botonEncendido, INPUT_PULLUP);

  // Inicializar WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a Wi-Fi");

  mostrarMenuPrincipal();
}

void loop() {
  switch (estadoActual) {
    case MENU_PRINCIPAL:
      if (digitalRead(flechaAbajo) == LOW) {
        estadoActual = SELECCION_CURSO;
        seleccionarCurso();
        delay(500);
      }
      break;

    case SELECCION_CURSO:
      if (digitalRead(botonConfirmar) == LOW) {
        estadoActual = TOMA_LISTA;
        tomarLista();
      }
      break;

    case TOMA_LISTA:
      // Simulación del reconocimiento facial
      u8g2.clearBuffer();
      u8g2.drawStr(0, 20, "Escaneando rostro...");
      u8g2.sendBuffer();
      delay(3000); // simula tiempo de análisis
      registrarAsistencia("Perez, Juan", true);
      estadoActual = MENU_PRINCIPAL;
      mostrarMenuPrincipal();
      break;

    case ENVIO_DATOS:
      enviarDatos();
      estadoActual = MENU_PRINCIPAL;
      mostrarMenuPrincipal();
      break;
  }
}

void tomarLista() {
  // Aquí iría la lógica real de captura y reconocimiento facial
  estadoActual = TOMA_LISTA;
}

void registrarAsistencia(String nombre, bool presente) {
  u8g2.clearBuffer();
  u8g2.drawStr(0, 20, "Registrado:");
  u8g2.drawStr(0, 35, nombre.c_str());
  u8g2.sendBuffer();
  delay(2000);
  // Guardar a SD o SPIFFS (por implementar)
}

void enviarDatos() {
  u8g2.clearBuffer();
  u8g2.drawStr(0, 20, "Enviando registros...");
  u8g2.sendBuffer();

  // Aquí podés agregar una petición HTTP POST para subir los datos al backend
  delay(2000);
}
