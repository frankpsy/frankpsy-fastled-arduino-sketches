// Bounce

#include <FastLED.h>

const int numLeds = 48;
const int dataPin = 6;
const int rPot = 0;
const int gPot = 1;
const int bPot = 2;
const int aButton = 3;
const int bButton = 4;

CRGB leds[numLeds];
int currentLocationA = 0;
int prevLocationA = 0;
float sineValueA = 0;
int currentLocationB = 0;
int prevLocationB = 0;
float sineValueB = 0;
int currentLocationC = 0;
int prevLocationC = 0;
float sineValueC = 0;
bool triggerA = false;
bool triggerB = false;

CRGB colorA;
CRGB colorB;
CRGB colorC;

void setup() {
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLeds);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop()
{
  if (!digitalRead(aButton))
    triggerA = true;
  if (!digitalRead(bButton))
    triggerB = true;
  if (digitalRead(aButton) && triggerA)
  {
    colorA.r = map(analogRead(rPot), 1023, 0, 0, 255);
    colorA.g = map(analogRead(gPot), 1023, 0, 0, 255);
    colorA.b = map(analogRead(bPot), 1023, 0, 0, 255);
    triggerA = false;
  }
  if (digitalRead(bButton) && triggerB)
  {
    colorB.r = map(analogRead(rPot), 1023, 0, 0, 255);
    colorB.g = map(analogRead(gPot), 1023, 0, 0, 255);
    colorB.b = map(analogRead(bPot), 1023, 0, 0, 255);
    triggerB = false;
  }
  colorC.r = map(analogRead(rPot), 1023, 0, 0, 255);
  colorC.g = map(analogRead(gPot), 1023, 0, 0, 255);
  colorC.b = map(analogRead(bPot), 1023, 0, 0, 255);
  
  currentLocationA = map(sin8(sineValueA*2), 0, 255, 0, numLeds-1);
  sineValueA++;
  leds[currentLocationA] = colorA;
  if (prevLocationA != currentLocationA)
    leds[prevLocationA] = CRGB::Black;
  prevLocationA = currentLocationA;
  
  currentLocationB = map(sin8(sineValueB*3), 0, 255, 0, numLeds-1);
  sineValueB++;
  leds[currentLocationB] = colorB;
  if (prevLocationB != currentLocationB)
    leds[prevLocationB] = CRGB::Black;
  prevLocationB = currentLocationB;

  currentLocationC = map(sin8(sineValueC), 0, 255, 0, numLeds-1);
  sineValueC++;
  leds[currentLocationC] = colorC;
  if (prevLocationC != currentLocationC)
    leds[prevLocationC] = CRGB::Black;
  prevLocationC = currentLocationC;
  FastLED.show();
  delay(25);
}
