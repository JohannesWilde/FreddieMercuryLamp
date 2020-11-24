#ifndef AUXILIARIES_RANGE_HPP
#define AUXILIARIES_RANGE_HPP

namespace Auxiliaries
{

template <typename T, T minVal, T maxVal>
class Range
{
public:

    static T constexpr min = minVal;
    static T constexpr max = maxVal;

    static T shiftIntoRange(T const & val)
    {
        if (val < minVal)
        {
            return minVal;
        }
        else if (val > maxVal)
        {
             return maxVal;
        }
        else
        {
            return val;
        }
    }

};


enum ValueChangerDirection
{
    ChangeValueUp,
    ChangeValueDown
};

template <typename T, typename Range_>
class ValueChangerDirected
{
public:
    typedef Range_ Range;

    ValueChangerDirected(ValueChangerDirection const direction = ChangeValueUp)
        : direction_(direction)
    {
    }

    void setDirection(ValueChangerDirection const direction)
    {
        direction_ = direction;
    }

    ValueChangerDirection getDirection() const
    {
        return direction_;
    }

    void reverseDirection()
    {
        switch (direction_)
        {
        case ChangeValueUp:
        {
            direction_ = ChangeValueDown;
            break;
        }
        case ChangeValueDown:
        {
            direction_ = ChangeValueUp;
            break;
        }
        }
    }

    // T change(T const & val);

protected:

    ValueChangerDirection direction_;
};

template <typename T, typename Range_>
class ValueChangerLooping : public ValueChangerDirected<T, Range_>
{
public:
    typedef Range_ Range;

    ValueChangerLooping(ValueChangerDirection const direction = ChangeValueUp)
        : ValueChangerDirected<T, Range_>(direction)
    {
    }

    T change(T const & val)
    {
        T returnVal = val;
        if ((Range::max <= val) && (ChangeValueUp == this->direction_))
        {
            this->direction_ = ChangeValueDown;
        }
        else if ((Range::min >= val) && (ChangeValueDown == this->direction_))
        {
            this->direction_ = ChangeValueUp;
        }

        switch (this->direction_)
        {
        case ChangeValueUp:
        {
            returnVal = (val + 1);
            break;
        }
        case ChangeValueDown:
        {
            returnVal = (val - 1);
            break;
        }
        }

        return returnVal;
    }
};

template <typename T, typename Range_>
class ValueChangerStopping : public ValueChangerDirected<T, Range_>
{
public:
    typedef Range_ Range;

    ValueChangerStopping(ValueChangerDirection const direction = ChangeValueUp)
        : ValueChangerDirected<T, Range_>(direction)
    {
    }

    T change(T const & val)
    {
        T returnVal = val; // default to unchanged value

        switch (this->direction_)
        {
        case ChangeValueUp:
        {
            if (Range::max > val)
            {
                returnVal = (val + 1);
            }
            break;
        }
        case ChangeValueDown:
        {
            if (Range::min < val)
            {
                returnVal = (val - 1);
            }
            break;
        }
        }

        return returnVal;
    }

};

}

#endif // AUXILIARIES_RANGE_HPP
