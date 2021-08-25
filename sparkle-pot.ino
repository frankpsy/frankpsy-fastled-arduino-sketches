// Sparkle - shows sparkle on strip of the current color

#include <FastLED.h>

const int numLeds = 48;
const int dataPin = 6;
const int rPot = 0;
const int gPot = 1;
const int bPot = 2;
const int aButton = 3;
const int bButton = 4;

CRGB leds[numLeds];
const int sparkleTotal = 16;
int sparkleLocations[sparkleTotal];
int sparkleValues[sparkleTotal];

void setup() {
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLeds);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  randomSeed(analogRead(0));

  // New sparkle locations and set values for them
  int i;
  for (i = 0; i < sparkleTotal; ++i)
  {
    sparkleLocations[i] = random(numLeds);
    sparkleValues[i] = random(255);
  }
}

void loop() {
  CRGB currentColor;
  
  // Grab current analog pot color value
  currentColor.r = map(analogRead(rPot), 0, 1023, 0, 255);
  currentColor.g = map(analogRead(gPot), 0, 1023, 0, 255);
  currentColor.b = map(analogRead(bPot), 0, 1023, 0, 255);

  // Set colors for the correct pixels using sparkleLocations / sparkleValues
  int i;
  for (i = 0; i < sparkleTotal; ++i)
  {
    leds[sparkleLocations[i]].r = dim8_raw(map(sparkleValues[i], 0, 255, 0, currentColor.r));
    leds[sparkleLocations[i]].g = dim8_raw(map(sparkleValues[i], 0, 255, 0, currentColor.g));
    leds[sparkleLocations[i]].b = dim8_raw(map(sparkleValues[i], 0, 255, 0, currentColor.b));
  }

  // Show now
  FastLED.show();
  delay(1);

  // Reduce values of each sparkle, then clean up and replace each sparkle that has
  // completely dimmed
  for (i = 0; i < sparkleTotal; ++i)
  {
    sparkleValues[i] = sparkleValues[i] - 1;
    if (sparkleValues[i] <= 0)
    {
      leds[sparkleLocations[i]] = CRGB::Black;
      sparkleLocations[i] = random(numLeds);
      sparkleValues[i] = random(255);
    }
  }
}
