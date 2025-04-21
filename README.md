# 📸 Sistema de Toma de Asistencia con Reconocimiento Facial - Secundaria

Este proyecto permite tomar lista automáticamente a alumnos de un curso usando un dispositivo con **ESP32-CAM** y una interfaz web para administrar los registros de asistencia.

---

## 📦 Componentes del sistema

### 1. 📷 Dispositivo de asistencia (ESP32-CAM + Display LCD)
- **ESP32-CAM AI-Thinker**
- **Pantalla gráfica LCD 128x64 (ST7920)**
- **Teclado físico con botones (1-9, confirmar, cancelar, flechas, encendido, apagado, etc.)**
- **Reconocimiento facial con modelo de Edge Impulse**
- **Sistema de menús para toma de lista**
- **Almacenamiento de asistencia en memoria o SD**
- **Envío de datos por Wi-Fi al servidor web**

### 2. 🌐 Backend (API REST)
- **Node.js + Express + TypeScript**
- **Base de datos SQLite (fácil de mover y ligera)**
- Endpoints:
  - `/login` - Autenticación de docentes
  - `/students` - Gestión de alumnos
  - `/attendance` - Registro y consulta de asistencias
  - `/upload` - Recepción de datos del ESP32-CAM
  - `/export` - Exportación a CSV

### 3. 💻 Interfaz Web
- **React + Tailwind CSS**
- Funcionalidades:
  - Login de docentes
  - Visualización de asistencias
  - Edición y gestión de alumnos
  - Exportación de datos
  - Sincronización con el ESP32-CAM

---

## 🧰 Requisitos

### Hardware:
- ESP32-CAM AI-Thinker
- Pantalla ST7920 128x64
- Teclado con botones físicos
- Fuente de alimentación/batería
- Acceso a red Wi-Fi compartida

### Software:
- [Arduino IDE](https://www.arduino.cc/en/software) con librerías:
  - `U8g2` para pantalla
  - `WiFi.h`, `HTTPClient.h`, etc.
- Node.js 18+
- npm/yarn
- Edge Impulse para entrenamiento del modelo facial

---

## 🚀 Instalación

### Backend

```bash
git clone https://github.com/tuusuario/asistencia-backend.git
cd asistencia-backend
npm install
npm run dev
