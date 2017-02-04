#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 6

char inputs[4] = { 0, 0, 0, 0 };

uint32_t defaultColor;
uint32_t autonomousColor;
uint32_t pilotAttentionColor;
uint32_t ballGettingColor;
uint32_t gearGettingColor;
uint32_t raveColors;
uint32_t timeColor30;
uint32_t timeColor60;
uint32_t timeColor90;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  Wire.begin(0);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(55);
  strip.show();
  setColors(1);
}

byte count = 0;

void receiveEvent(byte howMany)
{
  while (howMany)
  {
    inputs[4-howMany] = Wire.read();
    howMany--;
  }
}

void loop()
{
  if (inputs[0] == 2)
  {
    // Set the colors. //
    if (inputs[1] == 1) setColors(1);
    else if (inputs[1] == 2) setColors(2);
    else if (inputs[1] == 3) setColors(3);
    // Now, for modes. //
    if (inputs[2] == 1)// autonomousRainbow();
    {}
    else if (inputs[2] == 2) defaultMode();
    else if (inputs[2] == 3) pilotAttentionMode();
    else if (inputs[2] == 4) ballReceivingMode();
    else if (inputs[2] == 5) gearReceivingMode();
    else if (inputs[2] == 6) bothReceivingMode();
    else if (inputs[2] == 7) gearDeliveryMode();
    else if (inputs[2] == 8) timeWarning90();
    else if (inputs[2] == 9) timeWarning60();
    else if (inputs[2] == 10) timeWarning30();
    else if (inputs[2] == 11) targetingMode();
  }
}

void setColors(int i)
{
  if (i = 1)
  {
    defaultColor = strip.Color(255, 0, 90);
    autonomousColor = 15;
    pilotAttentionColor = strip.Color(255, 79, 0);
    ballGettingColor = strip.Color(0, 200, 0);
    gearGettingColor = strip.Color(225, 225, 0);
    raveColors = 25;
    timeColor90 = strip.Color(0, 255, 0);
    timeColor60 = strip.Color(255, 255, 0);
    timeColor30 = strip.Color(255, 0, 0);
  }
}

//void autonomousRainbow()
//{
  // Deprecated. //
//}

void defaultMode()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, defaultColor);
  }
  strip.show();
  return;
}

void pilotAttentionMode()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i % 2 == 0)
      strip.setPixelColor(i, pilotAttentionColor);
    else
      strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  return;
}

void ballReceivingMode()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, ballGettingColor);
  }
  strip.show();
  return;
}

void gearReceivingMode()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, gearGettingColor);
  }
  strip.show();
  return;
}

int state  = 0;
int gsplit = 0;
int wsplit = 0;

void gearDeliveryMode()
{ 
  if (state == 0)
  {
    gearDeliveryGreenState();
    delay(25);
  }
  else if (state == 1)
  {
    gearDeliveryWhiteState();
    delay(25);
  }
  else
  {
    state = 0;
    gsplit = 0;
    wsplit = 0;
  }
}

void gearDeliveryGreenState()
{
  if (gsplit == strip.numPixels() / 2)
  {
    state++;
    return;
  }
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i >= 0 + gsplit && i < strip.numPixels() / 2 + gsplit)
    {
      strip.setPixelColor(i, gearGettingColor);
    }
    else
    {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
  }
  strip.show();
  gsplit++;
}

void gearDeliveryWhiteState()
{
  if (wsplit == strip.numPixels() / 2)
  {
    state++;
    return;
  }
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i >= 0 + wsplit && i < strip.numPixels() / 2 + wsplit)
    {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    else
    {
      strip.setPixelColor(i, gearGettingColor);
    }
  }
  strip.show();
  wsplit++;
}

void bothReceivingMode()
{
  for (int i = 0, count = 1; i < strip.numPixels(); i++, count++)
  {
    if (i < 4) strip.setPixelColor(i, ballGettingColor);
    else if (i < 8) strip.setPixelColor(i, gearGettingColor);
    else if (i < 12) strip.setPixelColor(i, ballGettingColor);
    else strip.setPixelColor(i, gearGettingColor);
  }
  strip.show();
  return;
}
void timeWarning90()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor90);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor90);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor90);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
}
void timeWarning60()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor60);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor60);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor60);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
}
void timeWarning30()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor30);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor30);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, timeColor30);
  }
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(250);
}

char num = 0;

void targetingMode()
{
  if (num == strip.numPixels())
    num = 0;
  for (int i = 0; i < strip.numPixels(); i++)
  {
    if (i >= 0 + num && i < 1 + num)
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    else
      strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  strip.show();
  num++;
  delay(50);
}

