#include "leds.h"

LEDs::LEDs(uint16_t pixelCount, uint8_t pin) {
    setStrip(pixelCount,pin);
    setColor(BLUE);
    setEffect(Effect::Outwards);
}

void LEDs::setStrip(uint16_t pixelCount, uint8_t pin) {
    if (pStrip) delete pStrip;
    pStrip = new NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod>(pixelCount,pin);
}

void LEDs::init() {
    pStrip->Begin();
    pStrip->Show();
}

void LEDs::printTopo() {
    Serial.println();
    Serial.printf("rings available: ");
    Serial.print(topo.getCountOfRings());
    Serial.println();
    for (uint16_t r = 0; r < topo.getCountOfRings(); r++) {
            Serial.printf("ring: ");
            Serial.print(r);
            Serial.printf(" start: ");
            Serial.print(topo.Map(r, 0));
            Serial.printf(" end: ");
            Serial.print(topo.Map(r, topo.getPixelCountAtRing(r) - 1));
            Serial.println();
    }
}

void LEDs::setColor(RgbColor c) {
    color = c;
}

void LEDs::setEffect(Effect e) {
    effect = e;
}

void LEDs::runEffect(unsigned long durationMs) {
    unsigned long currentRunMs = millis();
    // Serial.println();
    // Serial.println("lastrun:");
    // Serial.println(lastrunMs);
    // Serial.println("currentrun:");
    // Serial.println(currentRunMs);
    // Serial.println("duration:");
    // Serial.println(durationMs);

    if (currentRunMs - lastrunMs >= durationMs) {
        Serial.println();
        Serial.println("running effect:");
        switch (effect)
        {
            case Outwards:
                Serial.println("outwards");
                effectOutwards();
                break;
            Inwards:
            default:
                Serial.println("inwards");
                effectInwards();
                break;
        }

        lastrunMs = millis();
    }
}

void LEDs::effectInwards()  {
    // use the topo to map the 2d polar cordinate to the pixel
    // and use that to SetPixelColor
    uint8_t currentRing;

    Serial.println();
    if(lastRing > topo.getCountOfRings()) {
        Serial.println("first run...");
        currentRing = topo.getCountOfRings() - 1;
        // Serial.printf("current ring: ");
        // Serial.print(currentRing);
        // Serial.println();
    }
    else {
        Serial.println();
        for(uint16_t p = 0; p < topo.getPixelCountAtRing(lastRing); p++)
        {
            // Serial.printf("blacking pixel ");
            // Serial.print(p);
            // Serial.printf(" overall pixel ");
            // Serial.print(topo.Map(lastRing, p));
            // Serial.println();
            pStrip->SetPixelColor(topo.Map(lastRing, p), BLACK);
        }
        pStrip->Show();

        if(lastRing == 0) currentRing = topo.getCountOfRings() - 1;
        else currentRing = lastRing - 1;
        // Serial.printf("last ring: ");
        // Serial.print(lastRing);
        // Serial.println();
        // Serial.printf("current ring: ");
        // Serial.print(currentRing);
        // Serial.println();
    }

    //set actual ring color
    color.Darken(255*currentRing/8); //NOTE: dividing currentRing by the total number of rings will set the outer ring black
    for(uint16_t p = 0; p < topo.getPixelCountAtRing(currentRing); p++)
    {
        // Serial.printf("setting pixel ");
        // Serial.print(p);
        // Serial.printf(" overall pixel ");
        // Serial.print(topo.Map(currentRing, p));
        // Serial.println();
        pStrip->SetPixelColor(topo.Map(currentRing, p), color);

    }
    pStrip->Show();

    lastRing = currentRing;
}

void LEDs::effectOutwards()  {
    uint8_t currentRing;

    Serial.println();
    if(lastRing > topo.getCountOfRings()) {
        Serial.println("first run...");
        currentRing = 0;
    }
    else {
        for(uint16_t p = 0; p < topo.getPixelCountAtRing(lastRing); p++)
        {
            pStrip->SetPixelColor(topo.Map(lastRing, p), BLACK);
        }
        pStrip->Show();

        if(lastRing == topo.getCountOfRings() - 1) currentRing = 0;
        else currentRing = lastRing + 1;
    }

    //set actual ring color
    color.Darken(255*currentRing/16);
    for(uint16_t p = 0; p < topo.getPixelCountAtRing(currentRing); p++)
    {
        pStrip->SetPixelColor(topo.Map(currentRing, p), color);

    }
    pStrip->Show();

    lastRing = currentRing;
}
