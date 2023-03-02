/**
 * \file servomotorESP32.cpp
 * \brief Archivo de implementación para la biblioteca de servomotores ESP32
 * \author Joseph Santiago Portilla. Ing. Electrónico - @JoePortilla
 */

#include <Arduino.h>
#include "servomotorESP32.hpp"

ServoMotor::ServoMotor() {}

void ServoMotor::setup(uint8_t servoPin, uint8_t chPWM, uint32_t freqPWM, uint8_t resPWM,
                       float minPulseWidth, float maxPulseWidth,
                       uint16_t minPosition, uint16_t maxPosition)
{
    // Ajuste de variables
    _servoPin = servoPin;
    _chPWM = chPWM;
    _freqPWM = freqPWM;
    _resPWM = resPWM;
    _minPulseWidth = minPulseWidth;
    _maxPulseWidth = maxPulseWidth;
    _minPosition = minPosition;
    _maxPosition = maxPosition;

    ledcSetup(_chPWM, _freqPWM, _resPWM);
    ledcAttachPin(_servoPin, _chPWM);

    _dutyMin = widthToDuty(_minPulseWidth);
    _dutyMax = widthToDuty(_maxPulseWidth);
}

void ServoMotor::write(uint16_t deg)
{
    if (deg > _maxPosition)
        deg = _maxPosition;

    _duty = degToDuty(deg);

    ledcWrite(_chPWM, _duty);
}

uint16_t ServoMotor::widthToDuty(float pulseWidth)
{
    if (pulseWidth < 0.0)
        pulseWidth = 0.0;

    if (pulseWidth > 1000.0 / _freqPWM)
        pulseWidth = 1000.0 / _freqPWM;

    return round(pulseWidth / 1000.0 * _freqPWM * pow(2, _resPWM));
}

uint16_t ServoMotor::degToDuty(uint16_t deg)
{
    return map(deg, _minPosition, _maxPosition, _dutyMin, _dutyMax);
}