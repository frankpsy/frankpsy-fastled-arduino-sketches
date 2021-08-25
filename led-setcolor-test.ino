#include <FastLED.h>
#define NUMLEDS 256
#define DATAPIN 6

CRGB leds[NUMLEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATAPIN>(leds, NUMLEDS);

}

void loop() {
  int rIntensity = map(analogRead(0), 1023, 0, 0, 255);
  int gIntensity = map(analogRead(1), 1023, 0, 0, 255);
  int bIntensity = map(analogRead(2), 1023, 0, 0, 255);
  int i = 0;
  int j = 0;
  for (i = 0; i < NUMLEDS; ++i)
  {
    if (j == 0)
    {
      leds[i].r = rIntensity;
      leds[i].g = gIntensity;
      leds[i].b = bIntensity;
      j++;
    }
    else
    {
      leds[i].r = 255 - rIntensity;
      leds[i].g = 255 - gIntensity;
      leds[i].b = 255 - bIntensity;
      j--;
    }
  }
  FastLED.show();
  delay(1);
}
