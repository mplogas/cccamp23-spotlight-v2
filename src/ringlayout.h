#ifndef RINGLAYOUT_H
#define RINGLAYOUT_H

#include <Arduino.h>


// Ring - Pixel Start -> Pixel End (Pixel number)
// 0 - 0 -> 0 (1)
// 1 - 1 -> 17 (16)
// 2 - 18 -> 49 (32)
// 3 - 49 -> 93 (44)

class RingLayout
{
    private:
        const uint8_t pixelCount = 93; 
        //void setPixelCount(uint8_t pixelCount);
        //void setRingLayout(uint16_t rings[4]);
    public:
        // RingLayout();
        // RingLayout(uint8_t pixelCount); 
        // RingLayout(uint8_t pixelCount, uint16_t rings[4]); 
    protected:
        const uint16_t Rings[5] = {0,1,17,49,pixelCount};
        uint8_t _ringCount() const
        {
            return sizeof(Rings) / sizeof(Rings[0]);
        }
};

#endif