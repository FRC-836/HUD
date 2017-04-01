#include <Adafruit_NeoPixel.h>
#include <Wire.h>

//constants
const   uint8_t  PIN = 7;
const uint16_t NUM_PIXELS = 48;
const uint8_t  BRIGHTNESS = 50;

const uint8_t RING1_PIN = 2;  
const uint8_t RING2_PIN = 1;

//test for debugCommand.
uint8_t red = 127; 
uint8_t green = 255;
uint8_t blue = 63;
uint32_t col = ((uint32_t)red << 16) | ((uint32_t)green <<  8) | blue;
// 0, 11, col, 4, 56 

//packet
uint8_t inputs[5] = { 0, 4, 0, 0, 0 };

//our current operation mode
uint8_t OPERATION_MODE = 1;

//whether the pixels are on or not (ANTI-HEADACHE BOOLEAN)
boolean POWERED = true;
boolean RING1POWERED = true;
boolean RING2POWERED = true;

//colors that change with color mode
uint32_t defaultColor;
uint32_t pilotAttentionColor;
uint32_t ballGettingColor;
uint32_t gearGettingColor;
uint32_t raveColors;

//neopixel STRIP
Adafruit_NeoPixel STRIP = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel RING1 = Adafruit_NeoPixel(16, RING1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel RING2 = Adafruit_NeoPixel(16, RING2_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip3  = Adafruit_NeoPixel(16 , 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4  = Adafruit_NeoPixel(16, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5  = Adafruit_NeoPixel(16 , 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6  = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8  = Adafruit_NeoPixel(16, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9  = Adafruit_NeoPixel(16 , 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel RING10 = Adafruit_NeoPixel(16, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel RING11 = Adafruit_NeoPixel(16 , 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel RING12 = Adafruit_NeoPixel(16, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel RING13 = Adafruit_NeoPixel(16 , 13, NEO_GRB + NEO_KHZ800);

//colors that never change
const uint32_t timeColor60 = STRIP.Color(0, 255, 0);
const uint32_t timeColor30 = STRIP.Color(255, 100, 0);
const uint32_t timeColor10 = STRIP.Color(255, 0, 0);

//enums
enum class COMMANDS : uint8_t
{
  SET_OPERATING_MODE = 0,
  SET_COLOR_MODE,   // 1
  DEFAULT_COLORS,   // 2
  PILOT_ATTENTION,  // 3
  GET_BALL,         // 4
  GET_GEAR,         // 5
  GET_BOTH,         // 6
  GEAR_DELIVERY,    // 7
  TIME_WARNING,     // 8
  TARGETING_MODE,   // 9
  RAVE_MODE,        // 10
  DEBUG_COMMAND,    // 11
  SET_POWER,    // 12
};
enum class OP_MODE : uint8_t
{
  COMPETITION,
  DEBUG,
};

void setup() 
{
  //setup I2C
  Wire.begin(4);
  Wire.onReceive(receiveEvent);

  //set up serial (may be unnecessary)
  Serial.begin(9600);

  //setup the neopixel STRIP
  STRIP.begin();
  RING1.begin();
  RING2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  strip6.begin();
  strip8.begin();
  strip9.begin();
  RING10.begin();
  RING11.begin();
  RING12.begin();
  RING13.begin();
  STRIP.setBrightness(BRIGHTNESS);
  RING1.setBrightness(80);
  RING2.setBrightness(80);
  strip3.setBrightness(80);
  strip4.setBrightness(80); //adjust brightness here
  strip5.setBrightness(80);
  strip6.setBrightness(80);
  strip8.setBrightness(80);
  strip9.setBrightness(80);
  RING10.setBrightness(80); //adjust brightness here
  RING11.setBrightness(80);
  RING12.setBrightness(80);
  RING13.setBrightness(80);
  RING1.show();
  RING2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip8.show();
  strip9.show();
  RING10.show();
  RING11.show();
  RING12.show();
  RING13.show();
  STRIP.show();
  //set initial color mode
  setColorMode(1);
}

void receiveEvent(uint8_t howMany)
{
  uint8_t i = 0;
  Serial.println("hello1");
  while (Wire.available())
  {
    if (i > 4)
      return;
    inputs[i] = Wire.read();
    i++;
  }
}

void loop()
{
//  ring1Lights();
//  ring2Lights();
    for(int i=0; i < RING1.numPixels(); i++)
    {
      RING1.setPixelColor(i, RING1.Color(255, 0, 255));
      RING2.setPixelColor(i, RING1.Color(255, 0, 255));
      strip3.setPixelColor(i, RING1.Color(255, 0, 255));
      strip4.setPixelColor(i, RING1.Color(255, 0, 255));
      strip5.setPixelColor(i, RING1.Color(255, 0, 255));
      strip6.setPixelColor(i, RING1.Color(255, 0, 255));
      strip8.setPixelColor(i, RING1.Color(255, 0, 255));
      strip9.setPixelColor(i, RING1.Color(255, 0, 255));
      RING10.setPixelColor(i, RING1.Color(255, 0, 255));
      RING11.setPixelColor(i, RING1.Color(255, 0, 255));
      RING12.setPixelColor(i, RING1.Color(255, 0, 255));
      RING13.setPixelColor(i, RING1.Color(255, 0, 255));
    }
    RING1.show();
    RING2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip8.show();
    strip9.show();
    RING10.show();
    RING11.show();
    RING12.show();
    RING13.show();
  //switch on command
  switch (inputs[1])
  {
    case (uint8_t)COMMANDS::DEBUG_COMMAND:
      if (OPERATION_MODE != 2)
        break;
      break;
    case (uint8_t)COMMANDS::DEFAULT_COLORS:
      if (OPERATION_MODE != 1)
        break;
      defaultMode();
      break;
    case (uint8_t)COMMANDS::RAVE_MODE:
      if (OPERATION_MODE != 1)
        break;
      raveMode();
      break;
    case (uint8_t)COMMANDS::PILOT_ATTENTION:
      if (OPERATION_MODE != 1)
        break;
      pilotAttentionMode();
      break;
    case (uint8_t)COMMANDS::GET_BALL:
      if (OPERATION_MODE != 1)
        break;
      ballReceivingMode();
      break;
    case (uint8_t)COMMANDS::GET_GEAR:
      if (OPERATION_MODE != 1)
        break;
      gearReceivingMode();
      break;
    case (uint8_t)COMMANDS::GET_BOTH:
      if (OPERATION_MODE != 1)
        break;
      bothReceivingMode();
      break;
    case (uint8_t)COMMANDS::GEAR_DELIVERY:
      if (OPERATION_MODE != 1)
        break;
      gearDeliveryMode();
      break;
    case (uint8_t)COMMANDS::TIME_WARNING:
      if (OPERATION_MODE != 1)
        break;
      timeWarning(inputs[2]);
      break;
    case (uint8_t)COMMANDS::TARGETING_MODE:
      if (OPERATION_MODE != 1)
        break;
      targetingMode(inputs[2], inputs[3]);
      break;
    case (uint8_t)COMMANDS::SET_COLOR_MODE:
      if (OPERATION_MODE != 1)
        break;
      setColorMode(inputs[2]);
      break;
    case (uint8_t)COMMANDS::SET_OPERATING_MODE:
      setOpMode(inputs[2] /*, potentially more. */);
      break;
    case (uint8_t)COMMANDS::SET_POWER:
      pixelsPowered(inputs[2], inputs[3]);
      break;
    default:
      //invalid command
      break;
  }
}
void ring1Lights()
{
  if (!RING1POWERED) return;
  for (uint8_t i = 0; i < 16; i++)
  {
    RING1.setPixelColor(i, RING1.Color(255, 0, 255));
  }
  RING1.show();
}
void ring2Lights()
{
  if (!RING2POWERED) return;
  for (uint8_t i = 0; i < 16; i++)
  {
    RING2.setPixelColor(i, RING2.Color(255, 0, 255));
  }
  RING2.show();
}
void setOpMode(uint8_t opMode)
{
  switch(opMode)
  {
    case (uint8_t)OP_MODE::COMPETITION:
      OPERATION_MODE = 1;
      break;
    case (uint8_t)OP_MODE::DEBUG:
      OPERATION_MODE = 2;
      break;
    default:
      //invalid op mode
      break;
  }
}
void setColorMode (uint8_t i)
{
  if (i == 1)
  {
    defaultColor = STRIP.Color(255, 0, 255);
    pilotAttentionColor = STRIP.Color(0, 0, 0, 255); // TODO: make it
    ballGettingColor = STRIP.Color(0, 255, 0);
    gearGettingColor = STRIP.Color(255, 115, 0);
  }
  else if (i == 2)
  {
    defaultColor = STRIP.Color(0, 255, 0);
    pilotAttentionColor = STRIP.Color(255, 39, 0); // TODO: make it
    ballGettingColor = STRIP.Color(255, 0, 255);
    gearGettingColor = STRIP.Color(0, 0, 255);
  }
  else if (i == 3)
  {
    defaultColor = STRIP.Color(0, 0, 255);
    pilotAttentionColor = STRIP.Color(79, 0, 255); // TODO: make it
    ballGettingColor = STRIP.Color(175, 0, 65);
    gearGettingColor = STRIP.Color(0, 255, 255);
  }
  else if (i == 4)
  {
    defaultColor = STRIP.Color(31, 237, 126);
    pilotAttentionColor = STRIP.Color(176, 0, 65); // TODO: make it
    ballGettingColor = STRIP.Color(0, 0, 255);
    gearGettingColor = STRIP.Color(255, 39, 0);
  }
  else if (i == 5)
  {
    defaultColor = STRIP.Color(100, 0, 200/*, 7*/);
    pilotAttentionColor = STRIP.Color(0, 0, 255); // TODO: make it
    ballGettingColor = STRIP.Color(255, 79, 0);
    gearGettingColor = STRIP.Color(100, 200, 0);
  }
}

void pixelsPowered(boolean powerState, uint8_t number)
{
  if (number == 1)
  {
    POWERED = powerState;
  }
  else if (number == 2)
  {
    RING1POWERED = powerState;
  }
  else if (number == 3)
  {
    RING2POWERED = powerState;
  }
  else if (number == 4)
  {
    POWERED = powerState;
    RING1POWERED = powerState;
    RING2POWERED = powerState;
  }
}

void defaultMode()
{
  if (!POWERED) return;
  for (uint16_t i = 0; i < NUM_PIXELS; i++)
  {
    STRIP.setPixelColor(i, defaultColor);
  }
  STRIP.show();
  return;
}

int pilotAttentionCount = 0;

void pilotAttentionMode()
{
  if (!POWERED) return;
//  if (pilotAttentionCount % 2 == 0)
//  {
//    for (int i = 0; i < NUM_PIXELS; i++)
//    {
//      if (i % 2 == 0)
//      {
//        STRIP.setPixelColor(i, pilotAttentionColor);
//      }
//      else
//      {
//        STRIP.setPixelColor(i, STRIP.Color(255, 255, 255));
//      }
//    }
//    STRIP.show();
//    delay(200);
//    pilotAttentionCount++;
//  }
//  else
//  {
//    for (int i = 0; i < NUM_PIXELS; i++)
//    {
//      if (i % 2 == 0)
//      {
//        STRIP.setPixelColor(i, STRIP.Color(255, 255, 255));
//      }
//      else
//      {
//        STRIP.setPixelColor(i, pilotAttentionColor);
//      }
//    }
//    STRIP.show();
//    delay(200);
//    pilotAttentionCount++;
//  }
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    STRIP.setPixelColor(i, pilotAttentionColor);
  }

  delay(100);
  STRIP.show();
  for(int i = 0; i < NUM_PIXELS; i++)
  {
    STRIP.setPixelColor(i, STRIP.Color(0, 0, 0));
  }
  delay(100);
  STRIP.show();
  return;
}

void ballReceivingMode()
{
  if (!POWERED) return;
  for (uint16_t i = 0; i < NUM_PIXELS; i++)
  {
    STRIP.setPixelColor(i, ballGettingColor);
  }
  STRIP.show();
  return;
}

void gearReceivingMode()
{
  if (!POWERED) return;
  for (uint16_t i = 0; i < NUM_PIXELS; i++)
  {
    STRIP.setPixelColor(i, gearGettingColor);
  }
  STRIP.show();
  return;
}

uint8_t state  = 0;
uint8_t gsplit = 0;
uint8_t wsplit = 0;

void gearDeliveryMode()
{ 
  if (!POWERED) return;
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
  for (uint16_t i = 0; i < NUM_PIXELS; i++)
  {
    if (i >= 0 + gsplit && i < NUM_PIXELS / 2 + gsplit)
    {
      STRIP.setPixelColor(i, gearGettingColor);
    }
    else
    {
      STRIP.setPixelColor(i,  STRIP.Color(255, 255, 255));
    }
  }
  STRIP.show();
  gsplit++;
}

void gearDeliveryWhiteState()
{
  if (wsplit == NUM_PIXELS / 2)
  {
    state++;
    return;
  }
  for (uint16_t i = 0; i < NUM_PIXELS; i++)
  {
    if (i >= 0 + wsplit && i < NUM_PIXELS / 2 + wsplit)
    {
      STRIP.setPixelColor(i,  STRIP.Color(127, 127, 127));
    }
    else
    {
      STRIP.setPixelColor(i, gearGettingColor);
    }
  }
  STRIP.show();
  wsplit++;
}

void bothReceivingMode()
{
  if (!POWERED) return;
  for (uint16_t i = 0, count = 1; i < NUM_PIXELS; i++, count++)
  {
    if (i < 25) 
    {
      if (i < 13)
        STRIP.setPixelColor(i, ballGettingColor);
      else
        STRIP.setPixelColor(i, gearGettingColor);
    }
    else if (i < 33)
    {
      if (i > 28)
        STRIP.setPixelColor(i, gearGettingColor);
      else
        STRIP.setPixelColor(i, ballGettingColor);
    }
    else if (i < 58)
    {
      if (i < 46)
        STRIP.setPixelColor(i, ballGettingColor);
      else
        STRIP.setPixelColor(i, gearGettingColor);
    }
    else
    {
      if (i < 62)
        STRIP.setPixelColor(i, ballGettingColor);
      else
        STRIP.setPixelColor(i, gearGettingColor);
    }
  }
  STRIP.show();
  return;
}
void timeWarning(uint8_t currentTime)
{
  if (!POWERED) return;
  //color selection based on time remaining
  uint32_t color;
  if (currentTime == 60) 
    color = timeColor60;
  else if (currentTime == 30) 
    color = timeColor30;
  else if (currentTime == 10) 
    color = timeColor10;
  else 
    return;

  for (uint8_t i = 0; i < NUM_PIXELS; i++) 
    STRIP.setPixelColor(i, color);
  STRIP.show();
  delay(750);
  for (uint8_t i = 0; i < NUM_PIXELS; i++) 
    STRIP.setPixelColor(i,  STRIP.Color(127, 127, 127));
  STRIP.show();
  delay(250);

  for (uint8_t i = 0; i < NUM_PIXELS; i++) 
    STRIP.setPixelColor(i, color);
  STRIP.show();
  delay(750);
  for (uint8_t i = 0; i < NUM_PIXELS; i++) 
    STRIP.setPixelColor(i,  STRIP.Color(127, 127, 127));
  STRIP.show();
  delay(250);
  for (uint8_t i = 0; i < NUM_PIXELS; i++) 
    STRIP.setPixelColor(i, color);
  STRIP.show();
  delay(750);
  for (uint8_t i = 0; i < NUM_PIXELS; i++) 
    STRIP.setPixelColor(i,  STRIP.Color(127, 127, 127));
  STRIP.show();
  delay(250);
}

uint8_t num = 0;

void targetingMode(uint8_t startIndex, uint8_t endIndex)
{
  if (!POWERED) return;
  if (num == NUM_PIXELS)
    num = 0;
  for (uint8_t i = 0; i < NUM_PIXELS; i++)
  {
    if (i >= 0 + num && i < 2 + num)
      STRIP.setPixelColor(i, STRIP.Color(255, 0, 0));
    else
    {
      if (i == startIndex || i == endIndex)
      {
        STRIP.setPixelColor(i, STRIP.Color(0, 0, 255));
      }
      else
        STRIP.setPixelColor(i, STRIP.Color(0, 255, 0));
    }
  }
  STRIP.show();
  num++;
  delay(50);
}

void raveMode()
{
  if (!POWERED) return;
//  for (uint8_t i = 0; i < NUM_PIXELS; i++)
//  {
//    STRIP.setPixelColor(i, STRIP.Color(random(155), random(75), random(45)));
//  }
//  STRIP.show();
//  delay(75);
  rainbowCycle(0);
}

void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256*5; j++)
  { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_PIXELS; i++)
    {
      STRIP.setPixelColor(i, Wheel(((i * 256 / NUM_PIXELS) + j) & 255));
    }
    STRIP.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return STRIP.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return STRIP.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return STRIP.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void commandTemplateA(uint8_t startIndex, uint8_t endIndex)
{
  if (!POWERED) return;
  for (uint8_t i = startIndex; i < endIndex; i++)
  {
    STRIP.setPixelColor(i, /*designated color*/ STRIP.Color(0, 0, 0));
  }
}

//instead of having a multitude of commands, instead use a color-code system?

void commandTemplateB(uint32_t color, uint8_t startIndex, uint8_t endIndex)
{
  if (!POWERED) return;
  for (uint8_t i = startIndex; i < endIndex; i++)
  {
    STRIP.setPixelColor(i, color);
  }
  STRIP.show();
}

