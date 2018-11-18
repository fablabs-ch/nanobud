#ifndef _GAME_H
#define _GAME_H

#include <inputlistener.h>

class Game: public InputListener {
public:
    virtual void init();
    virtual void loop(unsigned long nowMs, unsigned long dtMs);
};

#endif
