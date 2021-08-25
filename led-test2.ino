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

void setup() {
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLeds);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  
}

void loop() {
  int i;
  for (i = 0; i <= 48; ++i)
  {
    leds[i].r = dim8_raw(map(analogRead(rPot), 0, 1023, 0, brightness));
    leds[i].g = dim8_raw(map(analogRead(gPot), 0, 1023, 0, brightness));
    leds[i].b = dim8_raw(map(analogRead(bPot), 0, 1023, 0, brightness));
  }
  if (dim)
  {
    brightness = brightness - 5;
  }
  else
  {
    brightness = brightness + 5;
  }
  if (brightness >= 255)
  {
    dim = true;
  }
  if (brightness <= 0)
  {
    dim = false;
  }
  FastLED.show();
  delay(1);
}
