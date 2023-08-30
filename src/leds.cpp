#include <Arduino.h>
#include <NeoPixelBus.h>
#include "ringlayout.h"


class Led {
    private:
        uint8_t pixelCount; 
        uint8_t pixelPin; 
        NeoRingTopology<RingLayout> topo;
        //NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod> strip;
    public:
        Led(uint8_t pixelCount, uint8_t pin) {
            this->pixelCount = pixelCount;
            this->pixelPin = pin;
            //this->strip = NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod>(pixelCount, pixelPin);
        }
    protected:
        
}
