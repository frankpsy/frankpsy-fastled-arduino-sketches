#include <FastLED.h>
#define NUMLEDS 51
#define DATAPIN 6

CRGB leds[NUMLEDS];
int ledposition = 0;
int buttonState;
int lastButtonState = LOW;
int mscount = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATAPIN>(leds, NUMLEDS);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

}

void loop() {
  leds[ledposition].r = map(analogRead(0), 0, 1023, 0, 255);
  leds[ledposition].g = 0;
  leds[ledposition].b = 0;
  leds[ledposition+1].g = map(analogRead(1), 0, 1023, 0, 255);
  leds[ledposition+1].r = 0;
  leds[ledposition+1].b = 0;
  leds[ledposition+2].b = map(analogRead(2), 0, 1023, 0, 255);
  leds[ledposition+2].r = 0;
  leds[ledposition+2].g = 0;
  if ((digitalRead(4) == false) && (mscount > 25))
  {
    leds[ledposition] = CRGB::Black;
    ledposition++;
    if (ledposition > NUMLEDS)
    {
      ledposition = 0;
    }
    mscount = 0;
  }
  if ((digitalRead(3) == false) && (mscount > 25))
  {
    leds[ledposition+2] = CRGB::Black;
    ledposition--;
    if (ledposition < 0)
    {
      ledposition = 48;
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
    }
    mscount = 0;
  }
  FastLED.show();
  delay(1);
  mscount++;
}
