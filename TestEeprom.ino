
#include <Adafruit_NeoPixel.h>
#include "Button.hpp"
#include <EEPROM.h>

enum LedDisplayMode
{
  ModeFull,
  ModeRed,
  ModeGreen,
  ModeBlue,
  ModeWhite,
  _ModesCount // number of modes - not a mode itself
};

Button<4> button;
int constexpr pinLedsStrip = 3;
unsigned constexpr ledsCount = 10;
unsigned constexpr ledsBrightness = 20; // [0, 255]

unsigned constexpr eepromAddress = 0;

static LedDisplayMode mode = ModeFull;
static Adafruit_NeoPixel ledsStrip(ledsCount, pinLedsStrip, NEO_GRBW + NEO_KHZ800);

// the setup function runs once when you press reset or power the board
void setup()
{
  // read back leds stripe mode
  EEPROM.get(eepromAddress, mode);
  mode = mode % _ModesCount;
  
  // initialize leds
  ledsStrip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  ledsStrip.show();            // Turn OFF all pixels ASAP
  ledsStrip.setBrightness(ledsBrightness);
}

// the loop function runs over and over again forever
void loop()
{
  bool const buttonReleased = button.released();
  
  if (buttonReleased)
  {
    mode = (mode + 1) % _ModesCount;
    EEPROM.put(eepromAddress, mode);
  }
  
  switch (mode)
  {
    case ModeFull:
    {
      ledsStripFillColor(ledsStrip, Adafruit_NeoPixel::Color(255, 255, 255, 255));
      break;
    }
    case ModeRed:
    {
      ledsStripFillColor(ledsStrip, Adafruit_NeoPixel::Color(255, 0, 0, 0));
      break;
    }
    case ModeGreen:
    {
      ledsStripFillColor(ledsStrip, Adafruit_NeoPixel::Color(0, 255, 0, 0));
      break;
    }
    case ModeBlue:
    {
      ledsStripFillColor(ledsStrip, Adafruit_NeoPixel::Color(0, 0, 255, 0));
      break;
    }
    case ModeWhite:
    {
      ledsStripFillColor(ledsStrip, Adafruit_NeoPixel::Color(0, 0, 0, 255));
      break;
    }
  }
}

void ledsStripFillColor(Adafruit_NeoPixel & strip, uint32_t color)
{
  for(uint16_t i = 0; i < strip.numPixels(); ++i)
  {
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  strip.show(); //  Update strip
}
