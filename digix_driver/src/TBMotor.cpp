#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #if defined(__AVR__)
        #include <avr/io.h>
    #endif
    #include "WProgram.h"
#endif


#include "TBMotor.h"


TBMotor::TBMotor(uint8_t dir_pin, uint8_t speed_pin)
{
    this->dir_pin = dir_pin;
    this->pwm_pin = speed_pin;
    pinMode(dir_pin, OUTPUT);
    pinMode(speed_pin, OUTPUT);
    analogWrite(speed_pin, 0);
}

void TBMotor::run(uint8_t dir)
{
    switch (dir) {
    case RELEASE:
        this->setSpeed(0);
        break;
    case FORWARD:
        digitalWrite(this->dir_pin, HIGH);
        break;
    case BACKWARD:
        digitalWrite(this->dir_pin, LOW);
        break;
    }
}

void TBMotor::setSpeed(uint8_t speed)
{
    analogWrite(this->pwm_pin, speed);
}

void TBMotor::stop()
{
    this->setSpeed(0);
}
