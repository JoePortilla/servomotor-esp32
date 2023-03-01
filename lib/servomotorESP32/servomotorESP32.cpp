/**
 * \file servomotorESP32.cpp
 * \brief Archivo de implementación para
 * \author Joseph Santiago Portilla. Ing. Electrónico - @JoePortilla
 */

#include <Arduino.h>
#include "servomotorESP32.hpp"

ServoMotor::ServoMotor()
{
}

void ServoMotor::setup(uint8_t servoPin, uint8_t chPWM, uint32_t freqPWM, uint8_t resPWM, float minPulseWidth, float maxPulseWidth, uint16_t minPosition, uint16_t maxPosition)
{
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

    _dutyMin = _widthToDuty(_minPulseWidth);
    _dutyMax = _widthToDuty(_maxPulseWidth);
}

void ServoMotor::write(uint32_t deg)
{
    _duty = _degToDuty(deg);
    ledcWrite(_chPWM, _duty);
}

uint32_t ServoMotor::_widthToDuty(float pulseWidth)
{
    if (pulseWidth < 0)
        pulseWidth = 0;

    return round(pulseWidth / 1000 * _freqPWM * pow(2, _resPWM));
}

uint16_t ServoMotor::_degToDuty(uint16_t deg)
{
    if (deg < 0)
        deg = 0;

    if (deg > 360)
        deg = 360;

    return map(deg, _minPosition, _maxPosition, _dutyMin, _dutyMax);
}