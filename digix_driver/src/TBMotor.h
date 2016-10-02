#ifndef _TBMOTOR_
#define _TBMOTOR_

#include <inttypes.h>
#define FORWARD 1
#define BACKWARD 2
#define RELEASE 0

class TBMotor
{
public:
    TBMotor(uint8_t dir_pin, uint8_t speed_pin);
    void run(uint8_t dir);
    void setSpeed(uint8_t speed);
    void stop(void);

private:
    uint8_t dir_pin;
    uint8_t pwm_pin;
};

#endif
