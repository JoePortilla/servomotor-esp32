/**
 * \file servomotorESP32.hpp
 * \brief Archivo de cabecera para
 * \author Joseph Santiago Portilla. Ing. Electrónico - @JoePortilla
 */

#ifndef SERVOMOTORESP32_HPP
#define SERVOMOTORESP32_HPP

class ServoMotor
{
public:
    ServoMotor();

    void setup(uint8_t servoPin, uint8_t chPWM, uint32_t freqPWM = 50, uint8_t resPWM = 8, float minPulseWidth = 1, float maxPulseWidth = 2, uint16_t minPosition = 0, uint16_t maxPosition = 180);

    void write(uint32_t deg);

private:
    uint32_t _widthToDuty(float pulseWidth);
    uint16_t _degToDuty(uint16_t deg);

    uint8_t _servoPin;
    uint8_t _chPWM;
    uint32_t _freqPWM;
    uint8_t _resPWM;
    float _minPulseWidth;
    float _maxPulseWidth;
    uint16_t _minPosition;
    uint16_t _maxPosition;

    float _dutyMin = 0;
    float _dutyMax = 0;
    float _duty = 0;
};

#endif
