/**
 * \file servomotorESP32.hpp
 * \brief Archivo de cabecera para la biblioteca de servomotores ESP32
 * \author Joseph Santiago Portilla. Ing. Electrónico - @JoePortilla
 */

#ifndef SERVOMOTORESP32_HPP
#define SERVOMOTORESP32_HPP

/**
 * \brief Clase para instanciar un servomotor. Incluye funciones
 * que permiten configurar sus pines, ajustes de PWM, pulsos y posición.
 */
class ServoMotor
{
public:
    /**
     * \brief Constructor inicial.
     */
    ServoMotor();

    /**
     * \brief Función para configurar el servomotor y el canal del PWM que controla sus
     * movimientos. Se deben configuar los valores máx. y mín. del pulso en milisegundos, y
     * las posiciones máx. y mín. del servomotor en grados.
     * \param servoPin: GPIO al que se conecta el servomotor (Pines con PWM: 2,4,12-19,21-23,25-27,32-33).
     * \param chPWM: Canal del PWM a utilizar con el servomotor (ESP32: 16 Canales independientes disponibles).
     * \param freqPWM: Frecuencia del PWM [Hz] (ESP32: De 10 Hz a 40 MHz).
     * \param resPWM: Resolución del PWM [bits] (ESP32: De 1 bit a 16 bits).
     * \param minPulseWidth: Ancho de pulso mínimo [ms] aceptado por el servomotor.
     * \param maxPulseWidth: Ancho de pulso máximo [ms] aceptado por el servomotor.
     * \param minPosition: Posición mínima [deg] a la que puede moverse el servomotor.
     * \param maxPosition: Posición máxima [deg] a la que puede moverse el servomotor.
     * \returns Sin retorno.
     */
    void setup(uint8_t servoPin, uint8_t chPWM, uint32_t freqPWM = 50, uint8_t resPWM = 8,
               float minPulseWidth = 1, float maxPulseWidth = 2,
               uint16_t minPosition = 0, uint16_t maxPosition = 180);

    /**
     * \brief Función para
     * \param deg:
     * \returns Sin retorno.
     */
    void write(uint16_t deg);

    /**
     * \brief Función para
     * \param pulseWidth: a
     * \returns Ciclo de trabajo.
     */
    uint16_t widthToDuty(float pulseWidth);

    /**
     * \brief Función para
     * \param deg: a
     * \returns Ciclo de trabajo.
     */
    uint16_t degToDuty(uint16_t deg);

private:
    uint8_t _servoPin;     // GPIO al que se conecta el servomotor (Pines con PWM: 2,4,12-19,21-23,25-27,32-33).
    uint8_t _chPWM;        // Canal del PWM a utilizar con el servomotor (ESP32: 16 Canales independientes disponibles).
    uint32_t _freqPWM;     // Frecuencia del PWM [Hz] (ESP32: De 10 Hz a 40 MHz).
    uint8_t _resPWM;       // Resolución del PWM [bits] (ESP32: De 1 bit a 16 bits).
    float _minPulseWidth;  // Ancho de pulso mínimo [ms] aceptado por el servomotor.
    float _maxPulseWidth;  // Ancho de pulso máximo [ms] aceptado por el servomotor.
    uint16_t _minPosition; // Posición mínima [deg] a la que puede moverse el servomotor.
    uint16_t _maxPosition; // Posición máxima [deg] a la que puede moverse el servomotor.

    float _dutyMin; //
    float _dutyMax; //
    float _duty;    //
};

#endif
