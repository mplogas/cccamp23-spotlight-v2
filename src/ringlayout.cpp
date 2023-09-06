#include "ringlayout.h"

class RingLayout
{
    private:
        uint8_t pixelCount; 
    public:
        RingLayout(uint8_t pixelCount) {
            this->pixelCount = pixelCount;
        }
    protected:
        //ring0 and ring_all are required!
        const uint16_t Rings[5] = {0, 1, 16, 16 + 32, this->pixelCount};

        uint8_t _ringCount() const
        {
            return sizeof(Rings) / sizeof(Rings[0]);
        }
};