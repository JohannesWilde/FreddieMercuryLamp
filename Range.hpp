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
class ValueChanger
{
public:
    typedef Range_ Range;

    ValueChanger(ValueChangerDirection const direction = ChangeValueUp)
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

    T change(T const & val)
    {
        T returnVal = val;
        if ((Range::max <= val) && (ChangeValueUp == direction_))
        {
            direction_ = ChangeValueDown;
        }
        else if ((Range::min >= val) && (ChangeValueDown == direction_))
        {
            direction_ = ChangeValueUp;
        }

        switch (direction_)
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

private:
    ValueChangerDirection direction_;
};

}

#endif // AUXILIARIES_RANGE_HPP
