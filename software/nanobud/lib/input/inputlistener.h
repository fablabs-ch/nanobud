#ifndef _INPUT_LISTENER_H
#define _INPUT_LISTENER_H


class InputListener {
public:
    virtual void rotaryEvent(int delta) = 0;
    virtual void pressEvent() = 0;
    virtual void longPressEvent() = 0;
};

#endif
