#include <Arduino.h>
#include "leds.h"

const uint8_t PixelCount = 92;
const uint8_t PixelPin = 25;  // make sure to set this to the correct pin, ignored for Esp8266

Effect lightEffect = Effect::Inwards;
leds light(PixelCount, PixelPin);

void setup()
{
    light.init();
    light.printTopo();
 }

void loop()
{
    light.runEffect(lightEffect, 2000);
 }