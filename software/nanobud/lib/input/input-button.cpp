#include "input-button.h"

InputButton::InputButton(){

}

void InputButton::construct(int pin, Button button, InputListener* listener){
    this->pin = pin;
    this->button = button;
    this->listener = listener;
}

void InputButton::init(){
    pinMode(this->pin, INPUT_PULLUP);
}

void InputButton::loop(unsigned long nowMs, unsigned long dtMs){
    bool pressed = digitalRead(this->pin) == LOW;
    if(pressed){
        this->nextRepeat -= min(dtMs, this->nextRepeat);
        if(!this->wasPressed && (nowMs - this->lastPress) >= ANTI_REBOUND_MS){
            this->nextRepeat = DELAY_BEFORE_REPEAT_MS;
            this->lastPress = nowMs;
            this->listener->pressEvent(this->button, nowMs);
            this->listener->repeatPressEvent(this->button, nowMs);
        }
        if(this->nextRepeat==0){
            this->nextRepeat = DELAY_BEFORE_REPEAT_MS;
            this->listener->repeatPressEvent(this->button, nowMs);
        }
    }
    this->wasPressed = pressed;
}
