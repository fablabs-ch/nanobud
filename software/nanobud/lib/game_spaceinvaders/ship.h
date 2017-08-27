#ifndef _GAME_SPACEINVADERS_SHIP_H
#define _GAME_SPACEINVADERS_SHIP_H

#include <U8glib.h>

class PlayerShip {
public:
    enum { SHIP_RAD = 6, SHIP_W = SHIP_RAD * 2 + 1, SHIP_H = 6, SHIP_Y = screenH - 1 - SHIP_H };

    PlayerShip(int displayWidth, int displayHeight, int x, int y)
     : displayWidth(displayWidth), x(x), y(y) {}

    void draw(U8GLIB* display) {
        display.drawHLine(this->x - 1, SHIP_Y, 3);
        display.drawHLine(this->x - 1, SHIP_Y + 1, 3);
        display.drawHLine(this->x - (SHIP_RAD - 1), SHIP_Y + 2, SHIP_W - 2);
        display.drawHLine(this->x - SHIP_RAD, SHIP_Y + 3, SHIP_W);
        display.drawHLine(this->x - SHIP_RAD, SHIP_Y + 4, SHIP_W);
        display.drawHLine(this->x - SHIP_RAD, SHIP_Y + 5, SHIP_W);
    }

    void move(int delta){
        this->x += delta;
        if (this->x - SHIP_RAD < 0){
            this->x = SHIP_RAD;
        }
        if (this->x + SHIP_RAD >= this->displayWidth){
            this->x = this->displayWidth - SHIP_RAD - 1;
        }
    }

    void step() {
        //Nothing to do
    }

    int getX(){
        return this->x;
    }
private:
     int x;
     int displayWidth;
};

#endif
