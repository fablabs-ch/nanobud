#ifndef _INPUT_BUTTON_H
#define _INPUT_BUTTON_H

#include <Arduino.h>
#include <inputListener.h>

class InputButton {
public:
    InputButton();

    void construct(int pin, Button button, InputListener* listener=0);
    void init();

    void loop(unsigned long nowMs, unsigned long dtMs);
private:
    int pin;
    Button button;

    InputListener* listener;

    unsigned long lastPress = 0;
    unsigned long nextRepeat = -1;
    bool wasPressed = false;

};
#endif
