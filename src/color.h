#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>
#include <NeoPixelBus.h>

class Color {
  public:
    static RgbColor hexToRgb(String value);
    static String rgbToHex(const RgbColor& hex);
};

#endif
