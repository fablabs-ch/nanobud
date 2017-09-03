#ifndef _INPUT_LISTENER_H
#define _INPUT_LISTENER_H


class InputListener {
public:
    virtual void rotaryEvent(int delta, unsigned long nowMs) = 0;
    virtual void pressEvent(unsigned long nowMs) = 0;
    virtual void longPressEvent(unsigned long nowMs) = 0;
};

#endif
