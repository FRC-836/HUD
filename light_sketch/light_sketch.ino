#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(100);
  strip.show();
}

int state      = 0;
int rsplit     = 0;
int bsplit     = 0;

void loop() 
{
  if (state == 0)
  {
    redState();
  }
  else if (state == 1)
  {
    blueState();
  }
  else
  {
    state  = 0;
    bsplit = 0;
    rsplit = 0;
  }
}

void redState()
{
  if (rsplit == strip.numPixels() / 2)
  {
    state++;
    return;
  }
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i >= 0 + rsplit && i < strip.numPixels() / 2 + rsplit)
    {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
  }
  strip.show();
  rsplit++;
}

void blueState()
{
  if (bsplit == strip.numPixels() / 2)
  {
    state++;
    return;
  }
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i >= 0 + bsplit && i < strip.numPixels() / 2 + bsplit)
    {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
  }
  strip.show();
  bsplit++;
}

