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

#define BTN_A 1
#define BTN_B 2
#define JOYX A6
#define JOYY A7
#define LED 10

RF24 radio(9,12);
const uint8_t addresses[][6] = {"1vrum","2vrum"};
CRGB leds[1];

void setup()
{
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);

    pinMode(BTN_A, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);
    FastLED.addLeds<NEOPIXEL, LED>(leds, 1);
}

void loop()
{
    uint8_t request = 0;

    if (digitalRead(BTN_A) == HIGH) {
        request |= ENG_FORWARD;
        leds[0] = CRGB::White; FastLED.show();
    } else {
        leds[0] = CRGB::RED; FastLED.show();
    }
    radio.write(&request, sizeof(uint8_t));
    delay(50);
}
