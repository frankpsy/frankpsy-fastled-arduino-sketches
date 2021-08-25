#include <FastLED.h>

const int numLeds = 48;
const int dataPin = 6;
const int rPot = 0;
const int gPot = 1;
const int bPot = 2;
const int aButton = 3;
const int bButton = 4;
float addR = 0;
float addG = 0;
float addB = 0;
float brightness = 0;
bool dim = false;

CRGB leds[numLeds];
CRGB dots[3];
int whichDot = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLeds);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  dots[0] = CRGB::Black;
  dots[1] = CRGB::Black;
  dots[2] = CRGB::Black;
}

void loop() {
  int i;
  dots[whichDot].r = dim8_raw(map(analogRead(rPot), 0, 1023, 0, 255));
  dots[whichDot].g = dim8_raw(map(analogRead(gPot), 0, 1023, 0, 255));
  dots[whichDot].b = dim8_raw(map(analogRead(bPot), 0, 1023, 0, 255));
  if (!digitalRead(aButton))
  {
    whichDot++;
    if (whichDot > 2)
      whichDot = 0;
      delay(500);
  }
  fill_solid(leds, numLeds, CRGB::Black);
  leds[0] = dots[0];
  leds[1] = dots[1];
  leds[2] = dots[2];
  FastLED.show();
  delay(1);
}
