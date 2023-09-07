#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <NeoPixelBus.h>
#include "ringlayout.h"

enum Effect {Inwards, Outwards};

static const RgbColor WHITE(255);   
static const RgbColor GREY(128); 
static const RgbColor BLACK(0);    
static const RgbColor RED(128, 0, 0);
static const RgbColor GREEN(0, 128, 0);
static const RgbColor BLUE(0, 0, 128);

class leds
{
    private:
        NeoRingTopology<RingLayout> topo; 
        NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod>* pStrip; 
        unsigned long lastrunMs;
        void setStrip(uint16_t pixelCount, uint8_t pin);
    public:
        leds(uint16_t pixelCount, uint8_t pin);

        void init();
        void printTopo();
        void runEffect(Effect e, unsigned long durationMs);
    protected:
        void effectInwards();
};

#endif