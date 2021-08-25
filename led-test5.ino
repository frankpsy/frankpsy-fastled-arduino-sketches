#include <FastLED.h>

const int numLeds = 256;
const int dataPin = 6;
const int rPot = 0;
const int gPot = 1;
const int bPot = 2;
const int aButton = 3;
const int bButton = 4;
float addR = 0;
float addG = 0;
float addB = 0;
int oddSwitch = 0;
int k = 0;

CRGB leds[numLeds];

void setup() {
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLeds);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
}

void loop() {
  int i;
  int j;
  for (i = 0; i < numLeds; ++i)
  {
    leds[i].r = dim8_raw(map(analogRead(rPot), 1023, 0, 0, 255));
    leds[i].g = dim8_raw(map(analogRead(gPot), 1023, 0, 0, 255));
    leds[i].b = dim8_raw(map(analogRead(bPot), 1023, 0, 0, 255));
    if ((!digitalRead(bButton)) && (!digitalRead(aButton)))
    {
      k = 3;
    }
    else if (!digitalRead(bButton))
    {
      k = 1;
    }
    else if (!digitalRead(aButton))
    {
      k = 0;
    }
    i = i + k;
    FastLED.show();
    for (j = 0; j < numLeds; ++j)
    {
      if (leds[j].r > 1) 
        leds[j].r = leds[j].r - 1;
      else
        leds[j].r = 0;
      if (leds[j].g > 1)
        leds[j].g = leds[j].g - 1;
      else
        leds[j].g = 0;
      if (leds[j].b > 1)
        leds[j].b = leds[j].b - 1;
      else
        leds[j].b = 0;
    }
    delay(1);
  }

}
