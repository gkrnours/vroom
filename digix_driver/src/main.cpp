#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"
#include "TBMotor.h"

#define TIMEOUT 450
#define MASK_DIR 0xC0
#define MASK_ENG 0x30
#define DIR_FORWARD 0x00
#define DIR_RIGHT 0x40
#define DIR_LEFT 0x80
#define ENG_STOP 0x00
#define ENG_BACK 0x10
#define ENG_FORWARD 0x20
#define ENG_FAST 0x30

RF24 radio(9,12);
TBMotor engine(5, 1);
TBMotor wheel(2, 0);
const uint8_t addresses[][6] = {"1vrum","2vrum"};

void setup()
{
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
    radio.startListening();
}

void loop()
{
    uint8_t request;
    unsigned long time = millis();
    while (!radio.available() && millis() - time < TIMEOUT);
    if (TIMEOUT <= millis() - time) {
        engine.stop();
    } else {
        while (radio.available()) {
            // Skip untreated request,
            radio.read(&request, sizeof(uint8_t));
        }

        switch (request & MASK_DIR) {
        case DIR_FORWARD:
            break;
        case DIR_RIGHT:
            break;
        case DIR_LEFT:
            break;
        }

        switch (request & MASK_ENG) {
        case ENG_STOP:
            engine.run(BACKWARD);
            engine.setSpeed(0x00);
            break;
        case ENG_BACK:
            engine.run(BACKWARD);
            engine.setSpeed(0x80);
            break;
        case ENG_FORWARD:
            engine.run(FORWARD);
            engine.setSpeed(0x80);
            break;
        case ENG_FAST:
            engine.run(FORWARD);
            engine.setSpeed(0xff);
            break;
        }
    }
}
