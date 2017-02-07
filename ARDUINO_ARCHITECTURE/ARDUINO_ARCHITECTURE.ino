#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 6

char inputs[4] = { 0, 0, 0, 0 };

uint32_t defaultColor;
uint32_t pilotAttentionColor;
uint32_t ballGettingColor;
uint32_t gearGettingColor;
uint32_t raveColors;

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
  if      (inputs[0] == 1)  setOperationMode(inputs[1]);
  else if (inputs[0] == 2)  setColorMode(inputs[1]);
  else if (inputs[0] == 3)  defaultMode();
  else if (inputs[0] == 4)  pilotAttentionMode();
  else if (inputs[0] == 5)  ballReceivingMode();
  else if (inputs[0] == 6)  gearReceivingMode();
  else if (inputs[0] == 7)  bothReceivingMode();
  else if (inputs[0] == 8)  gearDeliveryMode();
  else if (inputs[0] == 9)  timeWarning(inputs[1]);
  else if (inputs[0] == 10) pilotAttentionMode();
}

void setOperationMode (char i)
{
  
}

void setColorMode (char i)
{
  if (i == 1)
  {
    defaultColor = strip.Color(255, 0, 255);
    pilotAttentionColor = strip.Color(255, 79, 0);
    ballGettingColor = strip.Color(0, 255, 0);
    gearGettingColor = strip.Color(255, 255, 0);
  }
  else if (i == 2)
  {
    defaultColor = strip.Color(0, 255, 0);
    pilotAttentionColor = strip.Color(0, 0, 0); // TODO: make it
    ballGettingColor = strip.Color(255, 0, 255);
    gearGettingColor = strip.Color(0, 0, 255);
  }
  else if (i == 3)
  {
    defaultColor = strip.Color(0, 0, 255);
    pilotAttentionColor = strip.Color(0, 0, 0); // TODO: make it
    ballGettingColor = strip.Color(200, 0, 100);
    gearGettingColor = strip.Color(0, 255, 255);
  }
  else if (i == 4)
  {
    defaultColor = strip.Color(255, 255, 255);
    pilotAttentionColor = strip.Color(0, 0, 0); // TODO: make it
    ballGettingColor = strip.Color(0, 0, 255);
    gearGettingColor = strip.Color(255, 79, 0);
  }
  else if (i == 5)
  {
    defaultColor = strip.Color(100, 0, 255);
    pilotAttentionColor = strip.Color(0, 0, 0); // TODO: make it
    ballGettingColor = strip.Color(255, 79, 0);
    gearGettingColor = strip.Color(100, 200, 0);
  }
}

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
    gearDeliveryAState();
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

void gearDeliveryAState()
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
void timeWarning(char currentTime)
{
  uint32_t color;
  if      (currentTime == 60) color = strip.Color(0, 255, 0);
  else if (currentTime == 30) color = strip.Color(255, 255, 0);
  else if (currentTime == 10) color = strip.Color(0, 0, 255);
  else return;
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, color);
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(255, 255, 255));
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, color);
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(255, 255, 255));
  strip.show();
  delay(250);
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, color);
  strip.show();
  delay(750);
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(255, 255, 255));
  strip.show();
  delay(250);
}

char num = 0;

void targetingMode()
{
  if (num == strip.numPixels()) num = 0;
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

