
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#include "ButtonTimed.hpp"
#include "Colors.hpp"
#include "Freddie.hpp"

using namespace Colors;
using namespace Freddie;

enum PowerState
{
    PowerOn,
    PowerOff
};

enum LedDisplayMode
{
    ModeRedWhite,
    ModeRed,
    ModeGreen,
    ModeBlue,
    ModeWhite,
    ModeFull,
    _ModesCount // number of modes - not a mode itself
};

typedef unsigned long Time_t;

static Time_t currentTime = millis();
ButtonTimed<0> buttonMode(currentTime);
ButtonTimed<4> buttonPower(currentTime);
int constexpr pinLedsStrip = 3;
unsigned constexpr ledsCount = 10;
unsigned constexpr ledsBrightness = 20; // [0, 255]

unsigned constexpr eepromAddressMode = 0;
//unsigned constexpr eepromAddressBrightness = eepromAddressMode + sizeof(LedDisplayMode);

static PowerState powerState = PowerOn; // default to On
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
    currentTime = millis();

    // update buttons
    ButtonTimedState const buttonPowerState = buttonPower.getState(currentTime);
    ButtonTimedState const buttonModeState = buttonMode.getState(currentTime);

    // check power button
    if (buttonPowerState.released)
    {
        switch (powerState)
        {
        case PowerOff:
        {
            powerState = PowerOn;
            ledsNeedUpdate = true;
            break;
        }
        case PowerOn:
        {
            powerState = PowerOff;
            lightUpFreddie(ledsStrip, Colors::Black);
            break;
        }
        }
    }

    if (PowerOn == powerState)
    {
        if (buttonModeState.longDuration && buttonModeState.isDown)
        {
            lightUpFreddie(ledsStrip, Colors::Yellow);

        }
        else if (buttonModeState.released && !buttonModeState.longDurationReleased)
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
                lightUpFreddie(ledsStrip, /*rays*/ Colors::Red, /*Freddies*/ Colors::White, /*words*/ Colors::White);
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
                // change to default
                mode = ModeRedWhite;
    //            ledsStripShowNumber(ledsStrip, Colors::Red + Colors::Green, mode);
    //            ledsNeedUpdate = false;
                break;
            }
            }
        }
    }
}


void ledsStripFillColor(Adafruit_NeoPixel & strip, Color_t const & color)
{
    for(uint16_t i = 0; i < strip.numPixels(); ++i)
    {
        strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    }
    strip.show(); //  Update strip
}


void ledsStripShowNumber(Adafruit_NeoPixel & strip, Color_t const & color, uint16_t number)
{
    for(uint16_t i = 0; i < strip.numPixels(); ++i)
    {
        strip.setPixelColor(i, ((number & 1) != 0) ? color : 0);         //  Set pixel's color (in RAM)
        number >>= 1;
    }
    strip.show(); //  Update strip
}

