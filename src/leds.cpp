#include <Arduino.h>
#include <NeoPixelBus.h>
#include "ringlayout.h"

enum Effect {Inwards, Outwards};


static const RgbColor WHITE = RgbColor(255);   
static const RgbColor GREY(128); 
static const RgbColor BLACK(0);    
static const RgbColor RED(128, 0, 0);
static const RgbColor GREEN(0, 128, 0);
static const RgbColor BLUE(0, 0, 128);

class Led {
    private:
        NeoRingTopology<RingLayout> topo; 
        NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod>* pStrip = NULL; 
        unsigned long lastrunMs;


        void setStrip(uint16_t pixelCount, uint8_t pin) {
            if (pStrip) delete pStrip;
            pStrip = new NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod>(pixelCount,pin);
        }

    public:


        Led(uint16_t pixelCount, uint8_t pin) {
            setStrip(pixelCount,pin);
        }

        ~Led()
        {
        }

        void init() {
            pStrip->Begin();
            pStrip->Show();
        }

        void printTopo() {
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
        }

        void runEffect(Effect e, unsigned long durationMs) {
            RgbColor color = BLUE;
            unsigned long currentRunMs = millis();
            if (currentRunMs - lastrunMs >= durationMs) {
                switch (e)
                {
                    case Outwards:
                        /* code */
                        break;
                    Inwards:
                    default:
                        effectInwards();
                        break;
                }

                lastrunMs = millis();
            }

        }
    protected:   
        void effectInwards()  {
            // use the topo to map the 2d polar cordinate to the pixel
            // and use that to SetPixelColor
            RgbColor color = BLUE;
            for (uint16_t r = topo.getCountOfRings(); r > 0; r--)
            {
                //set previous ring black
                if(r - 1 < topo.getCountOfRings() - 1) {
                    for(uint16_t p = 0; p < topo.getPixelCountAtRing(r); p++)
                    {
                        pStrip->SetPixelColor(topo.Map(r, p), BLACK);

                    }
                }
                pStrip->Show();

                //set actual ring color
                for(uint16_t p = 0; p < topo.getPixelCountAtRing(r - 1); p++)
                {
                    pStrip->SetPixelColor(topo.Map(r - 1, p), color);

                }
                pStrip->Show();
                }
        }
        
};
