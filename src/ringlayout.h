#ifndef RINGLAYOUT_H
#define RINGLAYOUT_H

#include <Arduino.h>

class RingLayout
{
    private:
        uint8_t pixelCount; 
    public:
        RingLayout(uint8_t pixelCount); 
    protected:
        const uint16_t Rings[4];
        uint8_t _ringCount();
};

#endif