#include <Arduino.h>
#include <WiFi.h>
#include "leds.h"

const uint8_t PixelCount = 93;
const uint8_t PixelPin = 25;  // make sure to set this to the correct pin, ignored for Esp8266
const char* SSID = "SPOTLIGHTv2";
const char* PASSWORD = "#cccamp.2023";
WiFiServer server(80);

Effect lightEffect = Effect::Outwards;
RgbColor color = ROSE;
LEDs light(PixelCount, PixelPin);



void setup()
{          
    Serial.begin(115200);
    while (!Serial); // wait for serial attach  

    Serial.printf("setting up");
    light.init(color,lightEffect);
    light.printTopo();

    WiFi.mode(WIFI_AP);
    WiFi.softAP(SSID, PASSWORD);
    server.begin();
 }

void loop()
{
    light.runEffect(250);
 }