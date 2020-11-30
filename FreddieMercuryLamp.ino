
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#include "ButtonTimed.hpp"
#include "Colors.hpp"
#include "Freddie.hpp"
#include "PowerbankKeepAlive.hpp"
#include "Range.hpp"

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
    ModeRainbowRays,
    ModeRed,
    ModeGreen,
    ModeBlue,
    ModeWhite,
    ModeFull,
    _ModesCount // number of modes - not a mode itself
};

typedef unsigned long Time_t;

static Time_t currentTime = millis();
ButtonTimed<0, LOW> buttonMode(currentTime);
ButtonTimed<2, LOW> buttonPower(currentTime);
int constexpr pinPowerbankKeepAlive = 4;
int constexpr pinLedsStrip = 3;
uint16_t constexpr ledsCount = 15;
typedef Auxiliaries::Range<uint8_t , /*ledsBrightnessMin*/ 63, /*ledsBrightnessMax*/ 255> RangeBrightness;
uint8_t ledsBrightness = RangeBrightness::min; // [0, 255]

unsigned constexpr eepromAddressMode = 0;
unsigned constexpr eepromAddressBrightness = eepromAddressMode + sizeof(LedDisplayMode);

static PowerState powerState = PowerOn; // default to On
static LedDisplayMode mode = ModeFull;
static bool ledsNeedUpdate = true;
static Adafruit_NeoPixel ledsStrip(ledsCount, pinLedsStrip, NEO_GRBW + NEO_KHZ800);
static Auxiliaries::ValueChangerStopping<uint8_t, RangeBrightness> brightnessValueChanger(/*direction*/ Auxiliaries::ValueChangerDirection::ChangeValueDown);


// the setup function runs once when you press reset or power the board
void setup()
{
    // read back leds stripe mode
    EEPROM.get<LedDisplayMode>(eepromAddressMode, mode);
    mode = static_cast<LedDisplayMode>(mode % _ModesCount);

    EEPROM.get<uint8_t>(eepromAddressBrightness, ledsBrightness);
    ledsBrightness = RangeBrightness::shiftIntoRange(ledsBrightness);

    // initialize leds
    ledsStrip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    ledsStrip.show();            // Turn OFF all pixels ASAP
    ledsStrip.setBrightness(Adafruit_NeoPixel::gamma8(ledsBrightness));

    PowerbankKeepAlive<pinPowerbankKeepAlive, HIGH, 5000, 10> powerbankKeepAlive(currentTime);

    while (true)
    {
        currentTime = millis();

        // update powerbankKeepAlive
        powerbankKeepAlive.update(currentTime);

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
                static Time_t constexpr brightnessUpdateDurationMs = 20;
                static Time_t lastTimeBrightnessChangedMs = currentTime - brightnessUpdateDurationMs;
                if ((currentTime - lastTimeBrightnessChangedMs) >= brightnessUpdateDurationMs)
                {
                    lastTimeBrightnessChangedMs = currentTime;
                    ledsBrightness = brightnessValueChanger.change(ledsBrightness);
                    EEPROM.put<uint8_t>(eepromAddressBrightness, ledsBrightness);
                    ledsStrip.setBrightness(Adafruit_NeoPixel::gamma8(ledsBrightness));
                    ledsNeedUpdate = true;
                }
            }
            else if (buttonModeState.released)
            {
                if (buttonModeState.longDurationReleased)
                {
                    brightnessValueChanger.reverseDirection();
                }
                else // short duration released
                {
                    mode = static_cast<LedDisplayMode>((mode + 1) % _ModesCount);
                    EEPROM.put<LedDisplayMode>(eepromAddressMode, mode);
                    ledsNeedUpdate = true;
                }
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
                case ModeRainbowRays:
                {
                    static Time_t constexpr modeRainbowRaysUpdateDurationMs = 40;
                    static Time_t lastTimeModeRainbowRaysChangedMs = currentTime - modeRainbowRaysUpdateDurationMs;
                    if ((currentTime - lastTimeModeRainbowRaysChangedMs) >= modeRainbowRaysUpdateDurationMs)
                    {
                        lastTimeModeRainbowRaysChangedMs = currentTime;
                        lightUpFreddieHimself(ledsStrip, /*Freddies*/ Colors::White);
                        lightUpFreddiesWords(ledsStrip, /*words*/ Colors::White);

        //                lightUpFreddiesRays(ledStrip, /*ray0*/ , /*ray1*/ , /*ray2*/ );

                        static uint32_t pixelHue = 0;
                        uint32_t constexpr hueOffset0 = 10000;
                        uint32_t constexpr hueOffset1 = 20000;
                        lightUpFreddiesRays(ledsStrip,
                                            /*ray0*/ Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(pixelHue, 255, 255)),
                                            /*ray1*/ Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(pixelHue + hueOffset0, 255, 255)),
                                            /*ray2*/ Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(pixelHue + hueOffset1, 255, 255)));

                        pixelHue += 128;
                        if (pixelHue >= 65536)
                        {
                            pixelHue -= 65536;
                        }
                    }
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
