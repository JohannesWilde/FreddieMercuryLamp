
#include <Adafruit_NeoPixel.h>
#include "Button.hpp"
#include <EEPROM.h>

namespace Colors
{

constexpr uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t constexpr Red = Color(255, 0, 0, 0);
uint32_t constexpr Green = Color(0, 255, 0, 0);
uint32_t constexpr Blue = Color(0, 0, 255, 0);
uint32_t constexpr White = Color(0, 0, 0, 255);
}

enum LedDisplayMode
{
    ModeRed,
    ModeGreen,
    ModeBlue,
    ModeWhite,
    ModeFull,
    _ModesCount // number of modes - not a mode itself
};

Button<4> button;
int constexpr pinLedsStrip = 3;
unsigned constexpr ledsCount = 10;
unsigned constexpr ledsBrightness = 20; // [0, 255]

unsigned constexpr eepromAddressMode = 0;
//unsigned constexpr eepromAddressBrightness = eepromAddressMode + sizeof(LedDisplayMode);

static LedDisplayMode mode = ModeFull;
static bool ledsNeedUpdate = true;
static Adafruit_NeoPixel ledsStrip(ledsCount, pinLedsStrip, NEO_GRBW + NEO_KHZ800);

// the setup function runs once when you press reset or power the board
void setup()
{
    // read back leds stripe mode
    EEPROM.get<LedDisplayMode>(eepromAddressMode, mode);
    mode = static_cast<LedDisplayMode>(mode % _ModesCount);

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
        mode = static_cast<LedDisplayMode>((mode + 1) % _ModesCount);
        EEPROM.put<LedDisplayMode>(eepromAddressMode, mode);
        ledsNeedUpdate = true;
    }

    if (ledsNeedUpdate)
    {
        switch (mode)
        {
        case ModeRedWhite:
        {
            ledsStripFillColor(ledsStrip, Adafruit_NeoPixel::Color(255, 255, 255, 255));
            ledsNeedUpdate = false;
            break;
        }
        case ModeFull:
        {
            ledsStripFillColor(ledsStrip, Colors::Red + Colors::Green + Colors::Blue + Colors::White);
            ledsNeedUpdate = false;
            break;
        }
        case ModeRed:
        {
            ledsStripFillColor(ledsStrip, Colors::Red);
            ledsNeedUpdate = false;
            break;
        }
        case ModeGreen:
        {
            ledsStripFillColor(ledsStrip, Colors::Green);
            ledsNeedUpdate = false;
            break;
        }
        case ModeBlue:
        {
            ledsStripFillColor(ledsStrip, Colors::Blue);
            ledsNeedUpdate = false;
            break;
        }
        case ModeWhite:
        {
            ledsStripFillColor(ledsStrip, Colors::White);
            ledsNeedUpdate = false;
            break;
        }
        default:
        {
            ledsStripShowNumber(ledsStrip, Colors::Red + Colors::Green, mode);
            ledsNeedUpdate = false;
            break;
        }
        }
    }
}

void ledsStripFillColor(Adafruit_NeoPixel & strip, uint32_t const & color)
{
    for(uint16_t i = 0; i < strip.numPixels(); ++i)
    {
        strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    }
    strip.show(); //  Update strip
}

void ledsStripShowNumber(Adafruit_NeoPixel & strip, uint32_t const & color, uint16_t number)
{
    for(uint16_t i = 0; i < strip.numPixels(); ++i)
    {
        strip.setPixelColor(i, ((number & 1) != 0) ? color : 0);         //  Set pixel's color (in RAM)
        number >>= 1;
    }
    strip.show(); //  Update strip
}

