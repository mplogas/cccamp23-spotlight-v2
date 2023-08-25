#include <NeoPixelBus.h>

const uint8_t PixelCount = 92;
const uint8_t PixelPin = 25;  // make sure to set this to the correct pin, ignored for Esp8266

class RingLayout
{
protected:
    //ring0 and ring_all are required!
    const uint16_t Rings[5] = {0, 16, 32, 44, PixelCount}; 
    
    uint8_t _ringCount() const
    {
        return sizeof(Rings) / sizeof(Rings[0]);
    }
};

NeoRingTopology<RingLayout> topo;
NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod> strip(PixelCount, PixelPin);

RgbColor white(128,128,128);
RgbColor red(128, 0, 0);
RgbColor green(0, 128, 0);
RgbColor blue(0, 0, 128);
RgbColor black(0);

void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");

    Serial.println();
    Serial.printf("rings available: ");
    Serial.print(topo.getCountOfRings());
    Serial.println();
    Serial.printf("total pixels available: ");
    Serial.print(topo.getPixelCount());

    strip.Begin();
    strip.Show();

    Serial.println();
    Serial.println("Running...");
}

void loop()
{
    // // strip testcode
    // Serial.println();
    // Serial.println("blink 5th and 10th pixel ...");

    // testStrip.SetPixelColor(5,red);
    // testStrip.SetPixelColor(10,red);
    // testStrip.Show();
    // delay(2500);
    // testStrip.SetPixelColor(5,green);
    // testStrip.SetPixelColor(10,green);
    // testStrip.Show();
    // delay(2500);
    // testStrip.SetPixelColor(5,blue);
    // testStrip.SetPixelColor(10,blue);
    // testStrip.Show();
    // delay(2500);
    
    Serial.println();
    Serial.println("entering loop");
    delay(2500);    

    // use the topo to map the 2d polar cordinate to the pixel
    // and use that to SetPixelColor
    for (uint16_t r = 0; r < topo.getCountOfRings(); r++)
    {
        Serial.println();
        Serial.printf("setting ring ");
        Serial.print(r);
        Serial.println();
        for(uint16_t p = 0; p < topo.getPixelCountAtRing(r); p++)
        {
            Serial.printf("setting pixel ");
            Serial.print(p);
            Serial.printf(" overall pixel ");
            Serial.print(topo.Map(r, p));
            Serial.println();
            strip.SetPixelColor(topo.Map(r, p), red);
        }
    }
    strip.Show();
    delay(5000);    

    Serial.println();
    Serial.println("Clearing to black");
    strip.ClearTo(black);
    strip.Show();
    delay(1000);
}