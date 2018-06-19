#ifndef _INPUT_LISTENER_H
#define _INPUT_LISTENER_H

#define ANTI_REBOUND_MS 50
#define DELAY_BEFORE_REPEAT_MS 150

typedef enum button{
    CENTER,
    RIGHT,
    LEFT,
    TOP,
    BOTTOM
} Button;

class InputListener {
public:
    // button pressed once
    virtual void pressEvent(Button button, unsigned long nowMs) = 0;
    // repeat this event while the button is pressed (happen every X ms)
    virtual void repeatPressEvent(Button button, unsigned long nowMs);
};

#endif
