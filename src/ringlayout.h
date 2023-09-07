#ifndef RINGLAYOUT_H
#define RINGLAYOUT_H

#include <Arduino.h>

class RingLayout
{
    private:
        const uint8_t pixelCount = 92; 
        //void setPixelCount(uint8_t pixelCount);
        //void setRingLayout(uint16_t rings[4]);
    public:
        // RingLayout();
        // RingLayout(uint8_t pixelCount); 
        // RingLayout(uint8_t pixelCount, uint16_t rings[4]); 
    protected:
        const uint16_t Rings[4] = {0, 1, 16, 16 + 32};
        uint8_t _ringCount() const
        {
            return sizeof(Rings) / sizeof(Rings[0]);
        }
};

#endif