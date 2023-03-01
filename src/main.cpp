#include <Arduino.h>
#include "servomotorESP32.hpp"

const uint8_t ch = 0;
const uint32_t freq = 50;
const uint8_t res = 8;
const uint8_t servoPin = 25;
const float pulseMin = 0.45; // ms
const float pulseMax = 2.45; // ms

ServoMotor servo;

void setup()
{
  Serial.begin(115200);
  servo.setup(servoPin, ch, freq, res, pulseMin, pulseMax);
}

void loop()
{
  servo.write(0);
  delay(500);

  servo.write(90);
  delay(500);

  servo.write(45);
  delay(500);

  servo.write(180);
  delay(800);
}