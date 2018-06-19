#ifndef _INPUT_H
#define _INPUT_H

#include <Arduino.h>
#include <inputListener.h>
#include <input-button.h>

// #define DEBUG_INPUT

#ifdef DEBUG_INPUT
    #define DEBUG_INPUT_PRINT(x)  Serial.print (x)
    #define DEBUG_INPUT_PRINTLN(x)  Serial.println (x)
#else
    #define DEBUG_INPUT_PRINT(x)
    #define DEBUG_INPUT_PRINTLN(x)
#endif

class Input {
public:
    Input(int pinCenter, int pintLeft, int pinRight, int pinTop, int pinBottom, InputListener* listener=0);

    void init();

    void loop(unsigned long nowMs, unsigned long dtMs);

    void changeDetected();

private:
    InputButton buttons[5];

    int pinCenter;
    int pintLeft;
    int pinRight;
    int pinTop;
    int pinBottom;
    InputListener* listener;
    //
    // bool buttonPressed;
    // bool lastButtonPressed;
    // unsigned long timeButtonDown;
    // bool ignoreNextRelease;
    //
    // unsigned long antiReboundMs;
    //
    // void checkButtonLongPress(unsigned long nowMs, unsigned long dtMs);
    // void checkButtonNormalPress(unsigned long nowMs);

};
#endif
