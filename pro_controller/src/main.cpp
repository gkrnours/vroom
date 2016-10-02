#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"

#define MASK_DIR 0xC0
#define MASK_ENG 0x30
#define DIR_FORWARD 0x00
#define DIR_RIGHT 0x40
#define DIR_LEFT 0x80
#define ENG_STOP 0x00
#define ENG_BACK 0x10
#define ENG_FORWARD 0x20
#define ENG_FAST 0x30
#define LIGHT_FRONT 0x08
#define LIGHT_BACK 0x04
#define FX_VIBRATE 0x02
#define FX_SOUND 0x01

#define BUTTON 5
#define JOYX A5
#define JOYY A8
#define RED 0
#define GREEN 1
#define BLUE 2

RF24 radio(9,12);
const uint8_t addresses[][6] = {"1vrum","2vrum"};

void setup()
{
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);

    pinMode(BUTTON, INPUT);
    pinMode(RED,   OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE,  OUTPUT);
    digitalWrite(BLUE, HIGH);
    delay(500);
    digitalWrite(BLUE, LOW);
}

void loop()
{
    uint8_t request = 0;

    if (digitalRead(BUTTON) == HIGH) {
        digitalWrite(GREEN, HIGH);
        digitalWrite(RED,   LOW);
        request |= ENG_FORWARD;
    } else {
        digitalWrite(RED,   HIGH);
        digitalWrite(GREEN, LOW);
    }
    radio.write(&request, sizeof(uint8_t));
    delay(50);
}
