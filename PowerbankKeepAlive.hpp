#ifndef POWERBANK_KEEP_ALIVE_HPP
#define POWERBANK_KEEP_ALIVE_HPP

#include <Arduino.h>

namespace PowerbankKeepAliveProperties
{

typedef unsigned long TimeMs_t;

enum State
{
    Active,
    Inactive
};

template<int activeValue>
int inline stateToPinValue_(State const state);

} // namespace PowerbankKeepAlive

// For activeValue assume one of the following:
//  #define HIGH 0x1
//  #define LOW  0x0

template <int pinNumber,
          int activeValue,
          PowerbankKeepAliveProperties::TimeMs_t updateIntervalMs,
          PowerbankKeepAliveProperties::TimeMs_t updateDurationMs>
class PowerbankKeepAlive
{
public:

    PowerbankKeepAlive(PowerbankKeepAliveProperties::TimeMs_t const currentTimeMs)
        : lastUpdateTimeMs_(currentTimeMs)
        , currentState_(PowerbankKeepAliveProperties::State::Inactive)
    {
        setState_(currentState_);
        pinMode(pinNumber, OUTPUT);
    }

    ~PowerbankKeepAlive()
    {
        setState_(PowerbankKeepAliveProperties::State::Inactive);
    }

    bool isActive()
    {
        int const currentVal = digitalRead(pinNumber);
        return (activeValue == currentVal);
    }

    void update(PowerbankKeepAliveProperties::TimeMs_t const & currentTimeMs)
    {
        switch (currentState_)
        {
        case PowerbankKeepAliveProperties::State::Active:
        {
            if ((currentTimeMs - lastUpdateTimeMs_) > updateDurationMs)
            {
                lastUpdateTimeMs_ = currentTimeMs;
                currentState_ = PowerbankKeepAliveProperties::State::Inactive;
                setState_(currentState_);
            }
            break;
        }
        case PowerbankKeepAliveProperties::State::Inactive:
        {
            if ((currentTimeMs - lastUpdateTimeMs_) > inactiveDuration_)
            {
                lastUpdateTimeMs_ = currentTimeMs;
                currentState_ = PowerbankKeepAliveProperties::State::Active;
                setState_(currentState_);
            }
            break;
        }
        }
    }

private:
    PowerbankKeepAliveProperties::TimeMs_t lastUpdateTimeMs_;
    PowerbankKeepAliveProperties::State currentState_;

    static PowerbankKeepAliveProperties::TimeMs_t constexpr inactiveDuration_ = updateIntervalMs - updateDurationMs;

    static void setState_(PowerbankKeepAliveProperties::State const state)
    {
        digitalWrite(pinNumber, PowerbankKeepAliveProperties::stateToPinValue_<activeValue>(state));
    }

};




template<>
int PowerbankKeepAliveProperties::stateToPinValue_<HIGH>(PowerbankKeepAliveProperties::State const state)
{
    switch (state)
    {
    case PowerbankKeepAliveProperties::State::Active:
    {
        return HIGH;
    }
    case PowerbankKeepAliveProperties::State::Inactive:
    {
        return LOW;
    }
    }
    return LOW;
}

template<>
int PowerbankKeepAliveProperties::stateToPinValue_<LOW>(PowerbankKeepAliveProperties::State const state)
{
    switch (state)
    {
    case PowerbankKeepAliveProperties::State::Active:
    {
        return LOW;
    }
    case PowerbankKeepAliveProperties::State::Inactive:
    {
        return HIGH;
    }
    }
    return HIGH;
}

#endif // POWERBANK_KEEP_ALIVE_HPP
