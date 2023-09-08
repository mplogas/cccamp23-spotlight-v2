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
static const RgbColor ROSE(255, 20, 147);

class LEDs
{
    private:
        NeoRingTopology<RingLayout> topo; 
        NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod>* pStrip; 
        unsigned long lastrunMs = 0;
        void setStrip(uint16_t pixelCount, uint8_t pin);
        uint8_t lastRing = 255;
        Effect effect;
        RgbColor color;
    public:
        LEDs(uint16_t pixelCount, uint8_t pin);

        void init();
        void printTopo();
        void setEffect(Effect e);
        void setColor(RgbColor c);
        void runEffect(unsigned long durationMs);
    protected:
        void effectInwards();
        void effectOutwards();
};

#endif