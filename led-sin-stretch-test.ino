

#include <FastLED.h>

const int numLeds = 48;
const int dataPin = 6;
const int rPot = 0;
const int gPot = 1;
const int bPot = 2;
const int aButton = 3;
const int bButton = 4;

CRGB leds[numLeds];

void setup() {
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLeds);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {
  int i;
  CRGB currentColor;

  //currentColor.r = map(analogRead(rPot), 1023, 0, 0, 255);
  //currentColor.g = map(analogRead(gPot), 1023, 0, 0, 255);
  //currentColor.b = map(analogRead(bPot), 1023, 0, 0, 255);
  
  for (i = 0; i < numLeds; ++i)
  {
    leds[i].r = dim8_raw(quadwave8(i*map(analogRead(rPot), 1023, 0, 0, 50))+map(analogRead(bPot), 1023, 0, 0, 1023));
    //leds[i].g = dim8_raw(triwave8(i*17)+map(analogRead(gPot), 1023, 0, 0, 1023));
    /*if (leds[i].g >= 128)
      leds[i].g = leds[i].g - 128;
    else
      leds[i].g = 0;*/
    leds[i].fadeLightBy(250);
  }
  FastLED.show();
}
