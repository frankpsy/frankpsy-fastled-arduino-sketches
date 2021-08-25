// Dot location - red, green and blue dots positioned on a strip

#include <FastLED.h>

const int numLeds = 256;
const int dataPin = 6;
const int rPot = 0;
const int gPot = 1;
const int bPot = 2;
const int aButton = 3;
const int bButton = 4;
const int brightness = 1;

CRGB leds[numLeds];
int rLoc;
int gLoc;
int bLoc;
int rLocPrev;
int gLocPrev;
int bLocPrev;

void setup() {
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLeds);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {
  rLocPrev = rLoc;
  gLocPrev = gLoc;
  bLocPrev = bLoc;
  rLoc = map(analogRead(rPot), 0, 1023, 0, numLeds-1);
  gLoc = map(analogRead(gPot), 0, 1023, 0, numLeds-1);
  bLoc = map(analogRead(bPot), 0, 1023, 0, numLeds-1);

  leds[rLoc].r = brightness;
  if (rLocPrev != rLoc)
    leds[rLocPrev].r = 0;
  leds[gLoc].g = brightness;
  if (gLocPrev != gLoc)
    leds[gLocPrev].g = 0;
  leds[bLoc].b = brightness;
  if (bLocPrev != bLoc)
    leds[bLocPrev].b = 0;

  FastLED.show();
  delay(1);
}
