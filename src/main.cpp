#include <Arduino.h>
#include "servomotorESP32.hpp"

// Ajustes de Pines
const uint8_t servoPin = 25; // GPIO al que se conecta el servomotor.
// Ajustes de PWM
const uint8_t chPWM = 0;     // Canal del PWM a utilizar con el servomotor.
const uint32_t freqPWM = 50; // Frecuencia del PWM [Hz].
const uint8_t resPWM = 8;    // Resolución del PWM [bits].
// Ajustes de ancho de pulso
const float minPulseWidth = 0.5; // Ancho de pulso mínimo [ms].
const float maxPulseWidth = 2.5; // Ancho de pulso máximo [ms].
// Ajustes de posiciones límite.
const uint16_t minPosition = 0;   // Posición mínima [deg].
const uint16_t maxPosition = 180; // Posición máxima [deg].

// Creación de un objeto de la clase ServoMotor
ServoMotor servo;

void setup()
{
  // Inicializar la comunicación serial a 115200 baudios.
  Serial.begin(115200);
  // Ajustes iniciales del servomotor
  servo.setup(servoPin, chPWM, freqPWM, resPWM, minPulseWidth, maxPulseWidth, minPosition, maxPosition);
}

void loop()
{
  // Barrido de posiciones, de 0° a 180°.
  for (uint8_t degPosition = 0; degPosition <= 180; degPosition += 45)
  {
    Serial.println("Posición:" + String(degPosition) + "°");
    servo.write(degPosition);
    delay(1000);
  }

  // Barrido de posiciones, de 180° a 0°.
  for (uint8_t degPosition = 180; degPosition >= 0; degPosition -= 45)
  {
    Serial.println("Posición:" + String(degPosition) + "°");
    servo.write(degPosition);
    delay(1000);
  }
}