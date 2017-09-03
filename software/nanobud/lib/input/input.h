#ifndef _INPUT_H
#define _INPUT_H

#include <Arduino.h>
#include <inputListener.h>

#define ANTI_REBOUND_MS 50
#define BUTTON_LONG_PRESS_MS 1000

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
    Input(int pinButton, int pinRotaryA, int pinRotaryB, InputListener* listener=0);

    void init();

    void loop(unsigned long nowMs, unsigned long dtMs);

    void changeDetected();

private:
    int pinButton;
    int pinRotaryA;
    int pinRotaryB;
    InputListener* listener;

    volatile int lastEncoded;
    volatile long encoderValue;
    long lastEncoderValue;
    bool buttonPressed;
    bool lastButtonPressed;
    unsigned long timeButtonDown;
    bool ignoreNextRelease;

    unsigned long antiReboundMs;

    void updateEncoder();
    void checkButtonLongPress(unsigned long nowMs, unsigned long dtMs);
    void checkButtonNormalPress(unsigned long nowMs);
    void checkRotation(unsigned long nowMs);

};
#endif
