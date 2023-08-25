#include <NeoPixelBus.h>

const uint8_t PixelCount = 92;
const uint8_t PixelPin = 25;  // make sure to set this to the correct pin, ignored for Esp8266

class RingLayout
{
protected:
    //ring0 and ring_all are required!
    const uint16_t Rings[4] = {0, 16, 16 + 32, PixelCount};

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
    for (uint16_t r = 0; r < topo.getCountOfRings(); r++) {
            Serial.println();
            Serial.printf("ring: ");
            Serial.print(r);
            Serial.printf(" start: ");
            Serial.print(topo.Map(r, 0));
            Serial.printf(" end: ");
            Serial.print(topo.Map(r, topo.getPixelCountAtRing(r) - 1));
            Serial.println();
    }

    Serial.printf("total pixels available: ");
    Serial.print(topo.getPixelCount());

    strip.Begin();
    strip.Show();

    Serial.println();
    Serial.println("Running...");
}

void loop()
{
    Serial.println();
    Serial.println("entering loop");

    // use the topo to map the 2d polar cordinate to the pixel
    // and use that to SetPixelColor
    for (uint16_t r = topo.getCountOfRings(); r > 0; r--)
    {
        Serial.println();
        Serial.printf("setting ring ");
        Serial.print(r - 1);
        Serial.println();

        // BUG :(
        //set previous ring black
        if(r - 1 < topo.getCountOfRings() - 1) {
            for(uint16_t p = 0; p < topo.getPixelCountAtRing(r); p++)
            {
                Serial.printf("blacking pixel ");
                Serial.print(p);
                Serial.printf(" overall pixel ");
                Serial.print(topo.Map(r, p));
                Serial.println();
                strip.SetPixelColor(topo.Map(r, p), black);

            }
        }
        strip.Show();

        //set actual ring color
        for(uint16_t p = 0; p < topo.getPixelCountAtRing(r - 1); p++)
        {
            Serial.printf("setting pixel ");
            Serial.print(p);
            Serial.printf(" overall pixel ");
            Serial.print(topo.Map(r - 1, p));
            Serial.println();
            strip.SetPixelColor(topo.Map(r - 1, p), red);

        }
        strip.Show();
        delay(500);
    }


    Serial.println();
    Serial.println("Clearing to black");
    strip.ClearTo(black);
    strip.Show();
    delay(1000);
}

void testStrip() {
    // strip testcode
    Serial.println();
    Serial.println("blink 5th and 10th pixel ...");

    strip.SetPixelColor(5,red);
    strip.SetPixelColor(10,red);
    strip.Show();
    delay(2500);
    strip.SetPixelColor(5,green);
    strip.SetPixelColor(10,green);
    strip.Show();
    delay(2500);
    strip.SetPixelColor(5,blue);
    strip.SetPixelColor(10,blue);
    strip.Show();
    delay(2500);
}