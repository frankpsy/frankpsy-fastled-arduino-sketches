// Sparkle 2 - shows sparkle on strip with different colors

#include <FastLED.h>

const int numLeds = 256;
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
CRGB sparkleColors[sparkleTotal];
int currentSparkleColor = 0;
bool buttonBounce = false;

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

  // set colors to white by default
  for (i = 0; i < sparkleTotal; ++i)
  {
    sparkleColors[i] = CRGB::Black;
  }
}

void loop() {
  CRGB currentColor;
  
  // Grab current analog pot color value
  currentColor.r = map(analogRead(rPot), 1023, 0, 0, 255);
  currentColor.g = map(analogRead(gPot), 1023, 0, 0, 255);
  currentColor.b = map(analogRead(bPot), 1023, 0, 0, 255);

  // Set sparkleColor with analog pot color value
  sparkleColors[currentSparkleColor] = currentColor;

  // Set colors for the correct pixels using sparkleLocations / sparkleValues
  int i;
  for (i = 0; i < sparkleTotal; ++i)
  {
    leds[sparkleLocations[i]].r = dim8_raw(map(sparkleValues[i], 0, 255, 0, sparkleColors[i].r));
    leds[sparkleLocations[i]].g = dim8_raw(map(sparkleValues[i], 0, 255, 0, sparkleColors[i].g));
    leds[sparkleLocations[i]].b = dim8_raw(map(sparkleValues[i], 0, 255, 0, sparkleColors[i].b));
  }

  // Use button press to change current sparkle color
  if (!digitalRead(aButton) && !buttonBounce)
  {
    buttonBounce = true;
    if (currentSparkleColor < sparkleTotal)
      currentSparkleColor++;
    else
      currentSparkleColor = 0;
  }
  if (digitalRead(aButton) && buttonBounce)
    buttonBounce = false;

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
