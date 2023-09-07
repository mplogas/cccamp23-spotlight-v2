#include <Arduino.h>
#include "leds.h"

const uint8_t PixelCount = 93;
const uint8_t PixelPin = 25;  // make sure to set this to the correct pin, ignored for Esp8266

Effect lightEffect = Effect::Outwards;
LEDs light(PixelCount, PixelPin);

void setup()
{          
    Serial.begin(115200);
    while (!Serial); // wait for serial attach  

    Serial.printf("setting up");
    light.init();
    light.printTopo();
 }

void loop()
{
    light.runEffect(lightEffect, 750);
 }