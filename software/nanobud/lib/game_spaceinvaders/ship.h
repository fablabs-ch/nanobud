#ifndef _GAME_SPACEINVADERS_SHIP_H
#define _GAME_SPACEINVADERS_SHIP_H

#include <U8glib.h>

class PlayerShip {
public:

    enum { SHIP_RAD = 6, SHIP_W = SHIP_RAD * 2 + 1, SHIP_H = 6 };

    PlayerShip() {

    }

     void init(int displayWidth, int displayHeight){
         this->displayWidth = displayWidth;
         this->displayHeight = displayHeight;
         this->x = displayWidth/2;
         this->y = displayHeight-SHIP_H-1;
     }

    void draw(U8GLIB* display) {
        display->drawHLine(this->x - 1, this->y, 3);
        display->drawHLine(this->x - 1, this->y + 1, 3);
        display->drawHLine(this->x - (SHIP_RAD - 1), this->y + 2, SHIP_W - 2);
        display->drawHLine(this->x - SHIP_RAD, this->y + 3, SHIP_W);
        display->drawHLine(this->x - SHIP_RAD, this->y + 4, SHIP_W);
        display->drawHLine(this->x - SHIP_RAD, this->y + 5, SHIP_W);
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
    int getY(){
        return this->y;
    }
private:
    int displayWidth, displayHeight;
     int x, y;
};

#endif
