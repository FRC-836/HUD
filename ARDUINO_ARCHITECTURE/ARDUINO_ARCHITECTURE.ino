#include <Adafruit_NeoPixel.h>
#include <Wire.h>

//constants
const int PIN = 6;
const int NUM_PIXELS = 16;

//packet
char inputs[4] = { 0, 0, 0, 0 };

//colors that change with color mode
uint32_t defaultColor;
uint32_t pilotAttentionColor;
uint32_t ballGettingColor;
uint32_t gearGettingColor;
uint32_t raveColors;

//colors that never change
const uint32_t timeColor90 = strip.Color(0, 255, 0);
const uint32_t timeColor60 = strip.Color(255, 255, 0);
const uint32_t timeColor30 = strip.Color(255, 0, 0);

//neopixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, 
                                            NEO_GRB + NEO_KHZ800);

//enums
enum class COMMANDS : uint8_t
{
  SET_OPERATING_MODE = 0,
  SET_COLOR_MODE,
  DEFAULT_COLORS,
  PILOT_ATTENTION,
  GET_BALL,
  GET_GEAR,
  GET_BOTH,
  GEAR_DELIVERY,
  TIME_WARNING,
  TARGETING_MODE,
};
enum class OP_MODE : uint8_t
{
  COMPETITION,
  DEBUG,
};

void setup() 
{
  //setup I2C
  Wire.begin(0);
  Wire.onReceive(receiveEvent);

  //set up serial (may be unnecessary)
  Serial.begin(9600);

  //setup the neopixel strip
  strip.begin();
  strip.setBrightness(55);
  strip.show();

  //set initial color mode
  setColors(1);
}

byte count = 0;

void receiveEvent(byte howMany)
{
  //not a good idea, could theoretically get negative array index
  //FIX
  while (howMany)
  {
    inputs[4-howMany] = Wire.read();
    howMany--;
  }
}

void loop()
{
  //switch on command
  switch (inputs[0])
  {
    case DEFAULT:
      defaultMode();
      break;
    case PILOT_ATTENTION:
      pilotAttentionMode();
      break;
    case GET_BALL:
      ballReceivingMode();
      break;
    case GET_GEAR:
      gearReceivingMode();
      break;
    case GET_BOTH:
      bothReceivingMode();
      break;
    case GEAR_DELIVERY:
      gearDeliveryMode()
      break;
    case TIME_WARNING:
      timeWarning(/*num seconds left goes here*/);
      break;
    case TARGETING_MODE:
      targetingMode();
      break;
    case SET_COLOR_MODE:
      setColorMode(/*color mode goes here*/);
      break;
    case SET_OPERATING_MODE:
      setOpMode(/*color mode goes here*/);
      break;
    default:
      //invalid command
      break;
  }
}
void setOpMode(uint8_t opMode)
{
  switch(opMode)
  {
    case COMPETITION:
      break;
    case DEBUG:
      break;
    default:
      //invalid op mode
      break;
  }
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
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, defaultColor);
  }
  strip.show();
  return;
}

void pilotAttentionMode()
{
  for (int i = 0; i < NUM_PIXELS; i++)
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
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, ballGettingColor);
  }
  strip.show();
  return;
}

void gearReceivingMode()
{
  for (int i = 0; i < NUM_PIXELS; i++)
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
  if (gsplit == NUM_PIXELS / 2)
  {
    state++;
    return;
  }
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    if (i >= 0 + gsplit && i < NUM_PIXELS / 2 + gsplit)
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
  if (wsplit == NUM_PIXELS / 2)
  {
    state++;
    return;
  }
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    if (i >= 0 + wsplit && i < NUM_PIXELS / 2 + wsplit)
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
  for (int i = 0, count = 1; i < NUM_PIXELS; i++, count++)
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
  //color selection based on time remaining
  uint32_t color;
  if (currentTime == 60) 
    color = strip.Color(0, 255, 0);
  else if (currentTime == 30) 
    color = strip.Color(255, 255, 0);
  else if (currentTime == 10) 
    color = strip.Color(0, 0, 255);
  else 
    return;

  for (int i = 0; i < strip.numPixels(); i++) 
    strip.setPixelColor(i, color);
  strip.show();
  delay(750);

  for (int i = 0; i < strip.numPixels(); i++) 
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  strip.show();
  delay(250);

  for (int i = 0; i < strip.numPixels(); i++) 
    strip.setPixelColor(i, color);
  strip.show();
  delay(750);

  for (int i = 0; i < strip.numPixels(); i++) 
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  strip.show();
  delay(250);

  for (int i = 0; i < strip.numPixels(); i++) 
    strip.setPixelColor(i, color);
  strip.show();
  delay(750);

  for (int i = 0; i < strip.numPixels(); i++) 
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  strip.show();
  delay(250);
}

char num = 0;

void targetingMode()
{
  if (num == NUM_PIXELS)
    num = 0;
  for (int i = 0; i < NUM_PIXELS; i++)
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

