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

    // Ajuste del canal de PWM
    ledcSetup(_chPWM, _freqPWM, _resPWM);
    // Enlace del canal de PWM al GPIO donde se conecta el servomotor.
    ledcAttachPin(_servoPin, _chPWM);

    // Calculo del ancho de pulso mínimo [bits].
    _dutyMin = widthToDuty(_minPulseWidth);
    // Calculo del ancho de pulso máximo [bits].
    _dutyMax = widthToDuty(_maxPulseWidth);
}

void ServoMotor::write(uint16_t deg)
{
    // Validación de la posición [deg] dada, si es mayor a la máxima posición se iguala
    // al valor de la máxima posición.
    if (deg > _maxPosition)
        deg = _maxPosition;

    // Conversión de la posición [deg] a ciclo de trabajo [bits].
    _duty = degToDuty(deg);

    // Escritura del ciclo de trabajo en el canal PWM.
    ledcWrite(_chPWM, _duty);
}

uint16_t ServoMotor::widthToDuty(float pulseWidth)
{
    // Validación del ancho de pulso dado [ms].
    // Si el valor es negativo se iguala a cero.
    if (pulseWidth < 0.0)
        pulseWidth = 0.0;
    // Si el valor es mayor al periodo de la señal, se iguala al periodo de la señal.
    if (pulseWidth > 1000.0 / _freqPWM)
        pulseWidth = 1000.0 / _freqPWM;

    // Calculo del ciclo de trabajo [bits] de acuerdo a la frec. y res. del canal PWM.
    return round(pulseWidth / 1000.0 * _freqPWM * pow(2, _resPWM));
}

uint16_t ServoMotor::degToDuty(uint16_t deg)
{
    // Mapeo del ciclo de trabajo mínimo y máximo de acuerdo a las posiciones límite definidas.
    return map(deg, _minPosition, _maxPosition, _dutyMin, _dutyMax);
}