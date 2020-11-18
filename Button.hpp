#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Arduino.h>

template <int pinNumber>
class Button
{
public:
  Button()
  {
    pinMode(pinNumber, INPUT_PULLUP);
    wasDownPreviously_ = isDown();
  }

  ~Button()
  {
    pinMode(pinNumber, INPUT);
  }

  /**
   * isDown - button is currently being pressed down.
   */
  bool isDown()
  {
	bool const isDownNow = isDown_();
	wasDownPreviously_ = isDownNow;
    return isDownNow;
  }

  /**
   * pressed - button was pressed.
   */
  bool pressed()
  {
	bool const isDownNow = isDown_();
	bool const wasPressed = !wasDownPreviously_ && isDownNow;
	wasDownPreviously_ = isDownNow;
    return wasPressed;
  }

  /**
   * released - button was released.
   */
  bool released()
  {
	bool const isDownNow = isDown_();
	bool const wasReleased = wasDownPreviously_ && !isDownNow;
	wasDownPreviously_ = isDownNow;
    return wasReleased;
  }

private:
  bool wasDownPreviously_;
  
  bool isDown_()
  {
    return (LOW == digitalRead(pinNumber));
  }  
};

#endif // BUTTON_HPP
