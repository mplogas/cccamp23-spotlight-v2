#include "color.h"

RgbColor Color::hexToRgb(String value) {
  value.replace("#", "");
  int number = (int) strtol( value.c_str(), NULL, 16);
  
  // Split them up into r, g, b values
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  
  RgbColor color(r,g,b);
  return color;
}
    

String Color::rgbToHex(const RgbColor& color) {
  long hexColor = ((long)color.R << 16L) | ((long)color.G << 8L) | (long)color.B;
  String out = String(hexColor, HEX);

  while(out.length() < 6) {
    out = "0" + out;
  }

  return out;
}