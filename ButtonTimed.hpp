#ifndef BUTTON_TIMED_HPP
#define BUTTON_TIMED_HPP

#include <Arduino.h>
#include "Button.hpp"


struct ButtonTimedState : public ButtonState
{
    ButtonTimedState(bool const isDown,
                     bool const pressed,
                     bool const released,
                     bool const longDuration)
        : ButtonState(isDown, pressed, released)
        , longDuration(longDuration)
    {
    }

    ButtonTimedState(ButtonState const & buttonState,
                     bool const longDuration)
        : ButtonState(buttonState)
        , longDuration(longDuration)
    {
    }

    ButtonTimedState(ButtonTimedState const & other)
        : ButtonState(other.isDown, other.pressed, other.released)
        , longDuration(other.longDuration)
    {
    }

    bool longDuration : 1;
} __attribute__((packed));


template <int pinNumber>
class ButtonTimed : public Button<pinNumber>
{
public:
    typedef unsigned long TimeMs_t;

    ButtonTimed(TimeMs_t const & currentTimeMs)
        : lastTimeToggledMs_(currentTimeMs)
    {
    }

    ~ButtonTimed()
    {
    }

    /**
   * isDown - button is currently being pressed down.
   */
    bool isDown(TimeMs_t const & currentTimeMs)
    {
        bool const wasDownPreviouslyBackup = Button<pinNumber>::getWasDownPreviously_();
        bool const isDownNow = Button<pinNumber>::isDown();
        // Button<pinNumber>::wasDownPreviously_ now holds the isDownNow value
        potentiallyUpdateLastTimeToggled_(wasDownPreviouslyBackup, Button<pinNumber>::getWasDownPreviously_(), currentTimeMs);
        return isDownNow;
    }

    /**
   * pressed - button was pressed.
   */
    bool pressed(TimeMs_t const & currentTimeMs)
    {
        bool const wasDownPreviouslyBackup = Button<pinNumber>::getWasDownPreviously_();
        bool const isPressed = Button<pinNumber>::pressed();
        // Button<pinNumber>::wasDownPreviously_ now holds the isDownNow value
        potentiallyUpdateLastTimeToggled_(wasDownPreviouslyBackup, Button<pinNumber>::getWasDownPreviously_(), currentTimeMs);
        return isPressed;
    }

    /**
   * released - button was released.
   */
    bool released(TimeMs_t const & currentTimeMs)
    {
        bool const wasDownPreviouslyBackup = Button<pinNumber>::getWasDownPreviously_();
        bool const wasReleased = Button<pinNumber>::released();
        // Button<pinNumber>::wasDownPreviously_ now holds the isDownNow value
        potentiallyUpdateLastTimeToggled_(wasDownPreviouslyBackup, Button<pinNumber>::getWasDownPreviously_(), currentTimeMs);
        return wasReleased;
    }

    /**
     * @brief getState Return the current state of the button.
     * @return ButtonTimedState instance.
     */
    ButtonTimedState getState(TimeMs_t const & currentTimeMs)
    {
        bool const wasDownPreviouslyBackup = Button<pinNumber>::getWasDownPreviously_();
        ButtonState const buttonState = Button<pinNumber>::getState();
        // Button<pinNumber>::wasDownPreviously_ now holds the isDownNow value
        potentiallyUpdateLastTimeToggled_(wasDownPreviouslyBackup, Button<pinNumber>::getWasDownPreviously_(), currentTimeMs);
        ButtonTimedState const buttonTimedState(buttonState,
                                                isLongDuration(currentTimeMs, lastTimeToggledMs_));
        return buttonTimedState;
    }

private:

    void potentiallyUpdateLastTimeToggled_(bool const wasPreviouslyDown,
                                           bool const isDownNow,
                                           TimeMs_t const & currentTimeMs)
    {
        if (isDownNow != wasPreviouslyDown)
        {
            lastTimeToggledMs_ = currentTimeMs;
        }
    }

    static bool isLongDuration(TimeMs_t const & currentTimeMs, TimeMs_t const & lastTimeMs)
    {
        return ((currentTimeMs - lastTimeMs) >= durationLongMs_);
    }

    static TimeMs_t constexpr durationLongMs_ = 1000;
    TimeMs_t lastTimeToggledMs_;

};

#endif // BUTTON_TIMED_HPP
